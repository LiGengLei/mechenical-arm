
/*
 *
 *  Copyright (c) 2014-2015 Warren J. Jasper <wjasper@tx.ncsu.edu>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef PMD_H
#define PMD_H

#ifdef __cplusplus
extern "C" { 
#endif 
#include "libusb.h"
#include "hidapi.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

/* These definitions are used to build the request type in usb_control_msg */
#define MCC_VID         (0x09db)  // Vendor ID for Measurement Computing
#define CTRL_IN         (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT        (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#define INTR_LENGTH     64

#define  INPUT_REPORT   (1 << 8)
#define  OUTPUT_REPORT  (2 << 8)

/* Description of the requestType byte */
// Data transfer direction D7
#define HOST_TO_DEVICE (0x0 << 7)
#define DEVICE_TO_HOST (0x1 << 7)
// Type D5-D6
#define STANDARD_TYPE (0x0 << 5)
#define CLASS_TYPE    (0x1 << 5)
#define VENDOR_TYPE   (0x2 << 5)
#define RESERVED_TYPE (0x3 << 5)
// Recipient D0 - D4
#define DEVICE_RECIPIENT    (0x0)
#define INTERFACE_RECIPIENT (0x1)
#define ENDPOINT_RECIPIENT  (0x2)
#define OTHER_RECIPIENT     (0x3)
#define RESERVED_RECIPIENT  (0x4) 


/* MDB Control Transfers */
#define MAX_MESSAGE_LENGTH 64      // max length of MBD Packet in bytes
#define STRING_MESSAGE     (0x80)  // Send string messages to the device
#define RAW_DATA           (0x81)  // Return RAW data from the device

#define EP_INTR (1 | LIBUSB_ENDPOINT_IN)
#define EP_DATA (2 | LIBUSB_ENDPOINT_IN)

libusb_device_handle* usb_device_find_USB_MCC(int productId, char *serialID);
int usb_get_max_packet_size(libusb_device_handle* udev, int endpointNum);

typedef struct calibrationTimeStamp_t {
  uint8_t year;   // Calibration date year
  uint8_t month;  // Calibration date month
  uint8_t day;    // Calibration date day
  uint8_t hour;   // Calibration date hour
  uint8_t minute; // Calibration date minute
  uint8_t second; // Calibration date second
} calibrationTimeStamp;

int PMD_SendOutputReport(hid_device* hid, uint8_t* values, size_t length);
int PMD_GetInputReport(hid_device* hid, uint8_t *values, size_t length, int delay);
int PMD_GetFeatureReport(hid_device* hid, uint8_t *data, int length);
int getUsbSerialNumber(libusb_device_handle *udev, unsigned char serial[]);

int sendStringRequest(libusb_device_handle *udev, char *message);
int getStringReturn(libusb_device_handle *udev, char *message);
void getRawData(libusb_device_handle *udev, void* data);

/* Structures for Temperature */
//*******************************************************************
// NIST Thermocouple coefficients
//
// The following types are supported:
//
//	J, K, R, S, T, N, E, B

/* Define the types of Thermocouples supported */
#define TYPE_J	0
#define TYPE_K	1
#define TYPE_T	2
#define TYPE_E	3
#define TYPE_R	4
#define TYPE_S	5
#define TYPE_B	6
#define TYPE_N	7

typedef struct NIST_Table_t {
  unsigned char nCoefficients;
  double VThreshold;
  const double* Coefficients;
} NIST_Table;

typedef struct NIST_Reverse_t {
  unsigned char nCoefficients;
  const double* Coefficients;
} NIST_Reverse;
	
typedef struct Thermocouple_Data_t {
  unsigned char nTables;
  const NIST_Reverse* ReverseTable;
  const NIST_Table* Tables;
} Thermocouple_Data;

double NISTCalcVoltage(unsigned char tc_type, double temp);
double NISTCalcTemp(unsigned char tc_type, double voltage);

int usb_get_max_packet_size(libusb_device_handle* udev, int endpointNum) 
{
  struct libusb_device *device;
  struct libusb_device_descriptor desc;
  struct libusb_config_descriptor *config;
  const struct libusb_interface *interface;
  const struct libusb_interface_descriptor *altsetting;
  const struct libusb_endpoint_descriptor *endpoint;
  int packet_size;
  int ret;

  device = libusb_get_device(udev);
  ret = libusb_get_active_config_descriptor(device, &config);
  if (ret < 0) {
    perror("usb_get_max_packet_size: error in libusb_get_active_config_descriptor");
    return ret;
  }
  interface = &config->interface[0];
  altsetting = &interface->altsetting[0];
  endpoint = &altsetting->endpoint[endpointNum];
  if (endpoint == NULL) {
   ret = libusb_get_device_descriptor(device, &desc);
   if (ret < 0) {
     perror("usb_get_max_packet_size: error in libusb_get_device_descriptor");
     return ret;
   }
   packet_size = desc.bMaxPacketSize0;
  } else {
    packet_size = endpoint->wMaxPacketSize;
  }
  libusb_free_config_descriptor(config);
  if (ret < 0) {
    perror("usb_get_max_packet_size: error in libusb_free_condfig_descriptor");
    return ret;
  }
  
  return packet_size;
}

libusb_device_handle* usb_device_find_USB_MCC( int productId, char *serialID )
{
  int vendorId = MCC_VID;

  struct libusb_device_handle *udev = NULL;
  struct libusb_device_descriptor desc;
  struct libusb_device **list;
  struct libusb_device *found = NULL;
  struct libusb_device *device;
  char serial[9];

  ssize_t cnt = 0;
  ssize_t i = 0;
  int err = 0;
  int cfg;
  int config;

  // discover devices
  cnt = libusb_get_device_list(NULL, &list);
  if (cnt < 0) {
    perror("usb_device_find_USB_MCC: No USB devices found on bus.");
    return  (libusb_device_handle*) cnt;
  }

  for (i = 0; i < cnt; i++) {
    device = list[i];
    err = libusb_get_device_descriptor(device, &desc);
    if (err < 0) {
      perror("usb_device_find_USB_MCC: Can not get USB device descriptor");
      goto out;
    }
    if (desc.idVendor == vendorId && desc.idProduct == productId) {
      found = device;
      err = libusb_open(found, &udev);
      if (err < 0) {
	perror("usb_device_find_USB_MCC: libusb_open failed.");
	udev = NULL;
	continue;
      }
      err = libusb_kernel_driver_active(udev, 0);
      if (err == 1) {
	/* 
	   device active by another driver. (like HID).  This can be dangerous,
           as we don't know if the kenel has claimed the interface or another
           process.  No easy way to tell at this moment, but HID devices won't
           work otherwise.
	 */
#if defined(LIBUSB_API_VERSION) && (LIBUSB_API_VERSION >= 0x01000103)
	libusb_set_auto_detach_kernel_driver(udev, 1);
#else
	libusb_detach_kernel_driver(udev, 0);
#endif
      }
      err = libusb_claim_interface(udev, 0);
      if (err < 0) {
        // perror("error claiming interface 0");
	libusb_close(udev);
	udev = NULL;
	continue;
      }
      /* Check to see if serial ID match */
      if (serialID != NULL) {
	err = libusb_get_string_descriptor_ascii(udev, desc.iSerialNumber, (unsigned char *) serial, sizeof(serial));
	if (err < 0) {
	  perror("usb_device_find_USB_MCC: Error reading serial number for device.");
	  libusb_release_interface(udev, 0);
	  libusb_close(udev);
	  udev = NULL;
	  continue;
	}
        if (strcmp(serialID, serial) == 0) {
	  break;
	} else {
	  libusb_release_interface(udev, 0);
	  libusb_close(udev);
	  udev = NULL;
	  continue;
	}
      } else {
        
        /* If we got to here, we found a match and were able to claim the interface.  At
  	  this point we should stop looking and break out;
        */
	break;
      }
    }
  }
  libusb_free_device_list(list,1);

  if (udev) {
    cfg = libusb_get_configuration(udev, &config);
    if (cfg != 0) {
      err = libusb_set_configuration(udev, 1);
      if (err < 0) {
	perror("usb_device_find_USB_MCC: error in setting configuration.");
      }
    }
  }
  return udev;

out:
  libusb_free_device_list(list,1);
  libusb_close(udev);
  libusb_exit(NULL);
  return (libusb_device_handle*) -1;
}

int getUsbSerialNumber(libusb_device_handle *udev, unsigned char serial[])
{
  struct libusb_device_descriptor desc;
  struct libusb_device *device;
  int ret;

  device = libusb_get_device(udev);
  ret = libusb_get_device_descriptor(device, &desc);
  if (ret < 0) return ret;
  ret = libusb_get_string_descriptor_ascii(udev, desc.iSerialNumber, serial, 8);
  if (ret < 0) return ret;
  serial[8] = '\0';
  return 0;
}

#define HS_DELAY1 20

int sendStringRequest(libusb_device_handle *udev, char *message)
{
  uint8_t requesttype = (HOST_TO_DEVICE | VENDOR_TYPE | DEVICE_RECIPIENT);
  unsigned char string[MAX_MESSAGE_LENGTH];
  int ret;
  
  strncpy((char *)string, message, MAX_MESSAGE_LENGTH);
  string[MAX_MESSAGE_LENGTH - 1] = '\0';
  //  printf("SendStringRequest: string = %s\n", string);

  ret = libusb_control_transfer(udev, requesttype, STRING_MESSAGE, 0, 0, (unsigned char *) string, MAX_MESSAGE_LENGTH, HS_DELAY1);
  return ret;
}

int  getStringReturn(libusb_device_handle *udev, char *message)
{
  /* Return 64 byte message */
  uint8_t requesttype = (DEVICE_TO_HOST | VENDOR_TYPE | DEVICE_RECIPIENT);
  int ret;

  ret = libusb_control_transfer(udev, requesttype, STRING_MESSAGE, 0, 0, (unsigned char *)message, MAX_MESSAGE_LENGTH, HS_DELAY1);
  //  printf("getStringReturn: string = %s\n", message);
  return ret;
}

/********************** HID wrapper functions ******************/
int PMD_SendOutputReport(hid_device* hid, uint8_t* values, size_t length)
{
  int ret;
  
  ret = hid_write(hid, values, length);
  if (ret < 0) {
    printf("PMD_SendOutputReport.  Unable to write data %ls \n", hid_error(hid));
  }
  return ret;
}

int PMD_GetInputReport(hid_device* hid, uint8_t *values, size_t length, int delay)
{
  int res;
  
  //  err = hid_read_timeout(hid, values, length, delay);
  res = hid_read_timeout(hid, values, length, delay);
  if (res < 0) {
    printf("PMD_GetInputReport.  Unable to read data %ls \n", hid_error(hid));
    return res;
  }
  return res;
}

int PMD_GetFeatureReport(hid_device* hid, uint8_t *data, int length)
{
  hid_get_feature_report(hid, data, length);
  return length;
}
#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif 

#endif  //PMD_H
