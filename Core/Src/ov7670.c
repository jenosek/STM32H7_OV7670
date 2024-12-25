#include "ov7670.h"

HAL_StatusTypeDef camera_write(uint8_t adress, uint8_t data) {
	HAL_StatusTypeDef status; //BUSY

	status = HAL_I2C_Mem_Write(p_I2C, CAM_WRITE, adress, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
	HAL_Delay(70);

	return status;
}

HAL_StatusTypeDef camera_read(uint8_t adress, uint8_t* data) {
	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit(p_I2C, CAM_READ, &adress, 1, 100);
	status |= HAL_I2C_Master_Receive(p_I2C, CAM_READ, data, 1, 100);
	return status;
}


HAL_StatusTypeDef camera_init(DCMI_HandleTypeDef* dcmi_handle, I2C_HandleTypeDef* i2c_handle, CAM_resolution resolution, CAM_format format){

	HAL_StatusTypeDef status;
	uint8_t mode = resolution + format;
	uint8_t read_value;

	// Load static parameters about image transmission
	p_dcmi = dcmi_handle;
	p_I2C = i2c_handle;


	// Power-up camera
	HAL_GPIO_WritePin(CAM_PWR_PORT, CAM_PWR_PIN, GPIO_PIN_SET);
	HAL_Delay(300);

	// Enable camera
	HAL_GPIO_WritePin(CAM_PWDN_PORT, CAM_PWDN_PIN, GPIO_PIN_SET);
	HAL_Delay(300);

	// Reset camera
	HAL_GPIO_WritePin(CAM_RESET_PORT, CAM_RESET_PIN, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(CAM_RESET_PORT, CAM_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(100);


	// Initialization common for all modes
	status = camera_write(CAM_COM7, 0x80);			// Reset all registers
	status |= camera_write(CAM_CLKRC, 0x01);		// Set clock pre-scaler /2, since A/C converter operates up to 12 MHz and input CLK is 24 MHz
	status |= camera_write(CAM_DBLV, 0x0A);			// Bypass PLL

	// Enable scaling for resolutions smaller than VGA
	if (resolution != CAM_VGA) {
		status |= camera_write(CAM_COM3, 0x08);
	}

	// Settings depending on choice of mode
	switch (mode) {
	// VGA - YUV
	case 0x00:
		status |= camera_write(CAM_COM7, 0x00);		// Set output format
		break;

	// VGA - RGB565
	case 0x01:
		status |= camera_write(CAM_COM7, 0x04);		// Set output format
		status |= camera_write(CAM_COM15, 0xD0);	// Set 565 RGB option
		break;

	// CIF - YUV
	case 0x10:
		status |= camera_write(CAM_COM7, 0x20);		// Set output format
		break;

	// CIF - RGB565
	case 0x11:
		status |= camera_write(CAM_COM7, 0x24);		// Set output format
		status |= camera_write(CAM_COM15, 0xD0);	// Set 565 RGB option
		break;

	// QVGA - YUV
	case 0x20:
		status |= camera_write(CAM_COM7, 0x10);		// Set output format
		break;

	// QVGA - RGB565
	case 0x21:
		status |= camera_write(CAM_COM7, 0x14);		// Set output format
		status |= camera_write(CAM_COM15, 0xD0);	// Set 565 RGB option
		break;

	// QCIF - YUV
	case 0x30:
		status |= camera_write(CAM_COM7, 0x08);		// Set output format
		break;

	// QCIF - RGB565
	case 0x31:
		status |= camera_write(CAM_COM7, 0x0C);		// Set output format
		status |= camera_write(CAM_COM15, 0xD0);	// Set 565 RGB option
		break;
	}


	//status |= camera_write(CAM_COM8, 0x8F);		// Automatic exposure & gain control
	status |= camera_write(CAM_RSVD, 0x84);			// Colours correction

	return status;
}


HAL_StatusTypeDef camera_capture_photo(uint8_t* destination_adress, uint32_t size) {
	HAL_StatusTypeDef status;

	// Begin transmission of data from camera to memory
	status = HAL_DCMI_Start_DMA(p_dcmi, DCMI_MODE_SNAPSHOT, destination_adress, size);
	HAL_Delay(5000);

	// End transmission
	status |= HAL_DCMI_Stop(p_dcmi);

	return status;
}

HAL_StatusTypeDef camera_shut_down() {
	HAL_StatusTypeDef status;
	// Disable camera
	HAL_GPIO_WritePin(CAM_PWDN_PORT, CAM_PWDN_PIN, GPIO_PIN_RESET);
	HAL_Delay(300);

	// Power-down camera
	HAL_GPIO_WritePin(CAM_PWR_PORT, CAM_PWR_PIN, GPIO_PIN_RESET);
	HAL_Delay(300);

	return status;
}

