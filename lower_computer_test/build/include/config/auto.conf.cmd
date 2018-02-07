deps_config := \
	/home/lgl/master/esp/esp-idf/components/app_trace/Kconfig \
	/home/lgl/master/esp/esp-idf/components/aws_iot/Kconfig \
	/home/lgl/master/esp/esp-idf/components/bt/Kconfig \
	/home/lgl/master/esp/esp-idf/components/esp32/Kconfig \
	/home/lgl/master/esp/esp-idf/components/ethernet/Kconfig \
	/home/lgl/master/esp/esp-idf/components/fatfs/Kconfig \
	/home/lgl/master/esp/esp-idf/components/freertos/Kconfig \
	/home/lgl/master/esp/esp-idf/components/heap/Kconfig \
	/home/lgl/master/esp/esp-idf/components/libsodium/Kconfig \
	/home/lgl/master/esp/esp-idf/components/log/Kconfig \
	/home/lgl/master/esp/esp-idf/components/lwip/Kconfig \
	/home/lgl/master/esp/esp-idf/components/mbedtls/Kconfig \
	/home/lgl/master/esp/esp-idf/components/openssl/Kconfig \
	/home/lgl/master/esp/esp-idf/components/pthread/Kconfig \
	/home/lgl/master/esp/esp-idf/components/spi_flash/Kconfig \
	/home/lgl/master/esp/esp-idf/components/spiffs/Kconfig \
	/home/lgl/master/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/lgl/master/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/lgl/master/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/lgl/master/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/lgl/master/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/lgl/master/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
