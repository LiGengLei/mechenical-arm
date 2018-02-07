#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "soc/gpio_sig_map.h"
#include "string.h"
extern "C"{
#include "positive_kinematic_right_to_RPY.h"
/**
 * TEST CODE BRIEF
 *
 * Use PCNT module to count rising edges generated by LEDC module.
 *
 * Functionality of GPIOs used in this example:
 *   - GPIO18 - output pin of a sample 1 Hz pulse generator,
 *   - GPIO4 - pulse input pin,
 *   - GPIO5 - control input pin.
 *
 * Load example, open a serial port to view the message printed on your screen.
 *
 * To do this test, you should connect GPIO18 with GPIO4.
 * GPIO5 is the control signal, you can leave it floating with internal pull up,
 * or connect it to ground. If left floating, the count value will be increasing.
 * If you connect GPIO5 to GND, the count value will be decreasing.
 *
 * An interrupt will be triggered when the counter value:
 *   - reaches 'thresh1' or 'thresh0' value,
 *   - reaches 'l_lim' value or 'h_lim' value,
 *   - will be reset to zero.
 */
#define PCNT_H_LIM_VAL      6000
#define PCNT_L_LIM_VAL     -6000
#define code_number         1000
#define pi                  3.1415926
#define EX_UART_NUM UART_NUM_0
#define BUF_SIZE (1024)

/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
int A[6] = {35, 33, 26, 27, 13, 22};   // 编码器A线接口
int B[6] = {34, 32, 25, 14, 12,  23};  // 编码器B线接口
struct HandMsg
{
    double six_angle[6];//输出主手六个关节角度值
    double eulerian_angle[3];//主手末端相对于基坐标系的姿态
    double pose[3];//主手末端相对于基坐标系的位置
}handmsg;

int16_t pcnt_cnt[6];
double six_Angle[6];
double Eulerian_Angle[3];//RPY
double Pose[3];//XYZ
/* Initialize PCNT functions:
 *  - configure and initialize PCNT
 *  - set up the input filter
 *  - set up the counter events to watch
 */
static void pcnt_example_init(void)
{
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config ;
    pcnt_config.channel = PCNT_CHANNEL_0;
    pcnt_config.unit = PCNT_UNIT_0;
    // What to do on the positive / negative edge of pulse input?
    pcnt_config.pos_mode = PCNT_COUNT_INC;   // Count up on the positive edge
    pcnt_config.neg_mode = PCNT_COUNT_DEC;   // Keep the counter value on the negative edge
    // What to do when control input is low or high?
    pcnt_config.lctrl_mode = PCNT_MODE_REVERSE; // Reverse counting direction if low
    pcnt_config.hctrl_mode = PCNT_MODE_KEEP;   // Keep the primary counter mode if high
    // Set the maximum and minimum limit values to watch
    pcnt_config.counter_h_lim = PCNT_H_LIM_VAL;
    pcnt_config.counter_l_lim = PCNT_L_LIM_VAL;
    pcnt_config_t pcA[6];
    pcnt_config_t pcB[6];
    pcnt_unit_t unit;
    for(int i = PCNT_UNIT_0; i < 6; i++ )
    {
        unit = (pcnt_unit_t)i;
        pcA[unit] = pcnt_config;
        pcB[unit] = pcnt_config;

        pcA[unit].unit = unit;
        pcA[unit].channel = PCNT_CHANNEL_0;
        pcA[unit].pulse_gpio_num = A[unit];
        pcA[unit].ctrl_gpio_num = B[unit];

        pcB[unit].unit = unit;
        pcB[unit].channel = PCNT_CHANNEL_1;
        pcB[unit].pulse_gpio_num = B[unit];
        pcB[unit].ctrl_gpio_num = A[unit];
        pcB[unit].hctrl_mode = PCNT_MODE_REVERSE;
        pcB[unit].lctrl_mode = PCNT_MODE_KEEP;


        /* Initialize PCNT unit */
        pcnt_unit_config(pcA + unit);
        pcnt_unit_config(pcB + unit);
        /* Initialize PCNT's counter */
        pcnt_counter_pause(unit);
        pcnt_counter_clear(unit);

        /* Register ISR handler and enable interrupts for PCNT unit
        pcnt_isr_register(pcnt_example_intr_handler, NULL, 0, NULL);*/
        pcnt_intr_enable(unit);

        /* Everything is set up, now go to counting */
        pcnt_counter_resume(unit);
        }
}

void uart_setup(){
 /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config ;
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_param_config(EX_UART_NUM, &uart_config);

    // Set UART pins using UART0 default pins i.e. no changes
    uart_set_pin(EX_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 0, NULL, 0);
}

static void tx_task(void *pvParameters)
{
    while (1)
    {
        for(int i=PCNT_UNIT_0;i<6;i++)
        {
            pcnt_get_counter_value((pcnt_unit_t)i, &pcnt_cnt[i]);
            six_Angle[i]=pcnt_cnt[i]*2*pi/code_number/4;
        }
        Master_positive_solution(Eulerian_Angle,Pose,six_Angle);
        for(int i=0;i<6;i++)
        {
            handmsg.six_angle[i]=six_Angle[i];
        }
        for(int i=0;i<3;i++)
        {
            handmsg.eulerian_angle[i]=Eulerian_Angle[i];
        }
        for(int i=0;i<3;i++)
        {
            handmsg.pose[i]=Pose[i];
        }
        uart_write_bytes(EX_UART_NUM, (const char*)(&handmsg), sizeof(handmsg));
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    /* Initialize PCNT functions */
    pcnt_example_init();
    uart_setup();
    xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);
}
}

