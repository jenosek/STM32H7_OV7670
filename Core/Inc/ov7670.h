#ifndef OV7670_H
#define OV7670_H

#include "dcmi.h"

/* ADRESSES OF REGISTERS
*****************************************/
// Communication modes
#define CAM_WRITE	0x42
#define CAM_READ	0x43

// Settings
#define CAM_COM2	0x09
#define CAM_COM3	0x0C
#define CAM_CLKRC	0x11
#define CAM_COM7	0x12
#define CAM_COM8 	0x13
#define CAM_COM10	0x15
#define CAM_MVFP	0x1E
#define CAM_TSLB 	0x3A
#define CAM_COM13	0x3D
#define CAM_COM14	0x3E
#define CAM_COM15 	0x40
#define CAM_MANU	0x67
#define CAM_MANV	0x68
#define CAM_DBLV	0x6B
#define CAM_RSVD	0xB0

// Testing patterns
#define CAM_XSC		0x70
#define CAM_YSC		0x71



/* PINOUT
*****************************************/
// Camera ports
#define CAM_PWR_PORT 	GPIOA
#define CAM_PWDN_PORT	GPIOD
#define CAM_RESET_PORT 	GPIOD

// Camera pins
#define CAM_PWR_PIN 	GPIO_PIN_5
#define CAM_PWDN_PIN	GPIO_PIN_14
#define CAM_RESET_PIN 	GPIO_PIN_15


// CAMERA MODES ALIASES
typedef enum
{
  CAM_VGA = 0x00,
  CAM_CIF = 0x10,
  CAM_QVGA = 0x20,
  CAM_QCIF = 0x30
} CAM_resolution;

typedef enum
{
  CAM_YUV = 0x00,
  CAM_RGB = 0x01

} CAM_format;


/* INTERNAL STATIC VARIABLES
*****************************************/
static DCMI_HandleTypeDef* p_dcmi;
static I2C_HandleTypeDef* p_I2C;

/* FUNCTIONS
*****************************************/
// Communication with camera's registers
HAL_StatusTypeDef camera_write(uint8_t adress, uint8_t data);
HAL_StatusTypeDef camera_read(uint8_t adress, uint8_t* data);

// Camera control
HAL_StatusTypeDef camera_init(DCMI_HandleTypeDef* dcmi_handle, I2C_HandleTypeDef* i2c_handle, CAM_resolution resolution, CAM_format format);
HAL_StatusTypeDef camera_capture_photo(uint8_t* destination_adress, uint32_t size);
HAL_StatusTypeDef camera_shut_down();

#endif
