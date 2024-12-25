# STM32H7_OV7670
Solution for single-shot imagery capture with OV7670 camera. Data are being processed by NUCLEO-H7A3ZI-Q microcontoller board. Library was created and tested in STM32CubeIDE environment using DCMI and DMA technologies. This approach enables user to obtain color (RGB565) and black-and-white (from YUV composition) images. 

>[!NOTE]
> YUV image still contains chrominance bits. BW mode (luminance only) will be implemented later to reduce the image size, therefore lowering required transmission time.

Pinout[^1]: 

| Function                   | Label on camera | Microcontroller pin | Board port | Board pin |
|----------------------------|-----------------|---------------------|------------|-----------|
| Horizontal synchronization | HS              | PA4                 | CN7        | 17        |
| Pixel clock                | PCLK            | PA6                 | CN7        | 12        |
| Vertical synchronization   | VS              | PG9                 | CN7        | 20        |
| Parallel data line 0       | D0              | PC6                 | CN7        |  1        |
| Parallel data line 1       | D1              | PC7                 | CN7        | 11        |
| Parallel data line 2       | D2              | PB13                | CN7        |  5        |
| Parallel data line 3       | D3              | PC9                 | CN8        |  4        |
| Parallel data line 4       | D4              | PE4                 | CN9        | 16        |
| Parallel data line 5       | D5              | PD3                 | CN9        | 10        |
| Parallel data line 6       | D6              | PE5                 | CN9        | 18        |
| Parallel data line 7       | D7              | PE6                 | CN9        | 20        |
| System clock input         | MCLK            | PA8                 | CN10       |  4        |
| Power supply               | 3V3             | PA5                 | CN7        | 10        |
| I2C data line              | SDA             | PB9                 | CN7        |  4        |
| I2C clock input            | SCL             | PB8                 | CN7        |  2        |
| Reset                      | RST             | PD15                | CN7        | 18        |
| Power down mode            | PWDN            | PD14                | CN7        | 16        |

## Supported camera modes
Manufacturer states that camera supports following resolutions, for which `CAM_resolution` enum is defined:
| Resolution      | Enum     |
|-----------------|----------|
| VGA   (640x480) | CAM_VGA  |
| CIF   (352x288) | CAM_CIF  |
| QVGA  (320x240) | CAM_QVGA |
| QCIF  (176x144) | CAM_QCIF |

In same fashion, enum for output format `CAM_format` is specified:

| Format  | Enum    |
|---------|---------|
| YUV     | CAM_YUV |
| RGB 565 | CAM_RGB |


## Algorithm description
Depending on desired camera mode, size of allocated image buffer is
$size = width \cdot height \cdot 2.$
since every pixel has size of 2 Bytes [^2].

Then cameras's registers are set in function `camera_init(DCMI_HandleTypeDef*, I2C_HandleTypeDef*, CAM_resolution, CAM_format)`, which outputs status variable of HAL_StatusTypeDef type (HAL_OK = 0x00). After initialization program enters `while(1)` loop where is "waiting" for user button interrupt `HAL_GPIO_EXTI_Callback` on GPIO pin 13. 

> [!IMPORTANT]
> For some reason STM32CubeIDE keeps rewriting interrupt handler definition in `stm32h7xx_it.c` file. Hence, for correct operation rewrite handler as follows:
> ```
> void EXTI15_10_IRQHandler(void) {
>   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
> }
> ```

Once button is pressed, single image is being stored in memory via DMA. How to access and extract saved memory content is described on webpage[^3]. 

## Acknowledgment
This project wouldn't be possible without help of additional sources[^4][^5][^6].

# Sources:
[^1]: User manual: UM2408 STM32H7 Nucleo-144 boards (MB1363). Online. V(5.0). 2021. Available from: https://www.st.com/resource/en/user_manual/um2408-stm32h7-nucleo144-boards-mb1363-stmicroelectronics.pdf.
[^2]: HAOYU Electronics: OV7670 Implementation Guide. Online. V(1.0). 2005. Available from: https://www.haoyuelectronics.com/Attachment/OV7670%20+%20AL422B(FIFO)%20Camera%20Module(V2.0)/OV7670%20Implementation%20Guide%20(V1.0).pdf.
[^3]: DigiKey TechForum: Using a Camera Module with the B-U585I-IOT02A Discovery Board. Online. 2023. Available from: https://forum.digikey.com/t/using-a-camera-module-with-the-b-u585i-iot02a-discovery-board/27245.
[^4]: Introduction to digital camera interface (DCMI) for STM32 MCUs: Application note - AN5020. Online. 2017. Available from: https://www.st.com/resource/en/application_note/an5020-digital-camera-interface-dcmi-on-stm32-mcus-stmicroelectronics.pdf.
[^5]: APARICIO, Jorge. Hacking the OV7670 camera module (SCCB cheat sheet inside): An in-depth look of the OV7670 camera module. Online. 2012. Available from: http://embeddedprogrammer.blogspot.com/2012/07/hacking-ov7670-camera-module-sccb-cheat.html.
[^6]: IWATAKE2222. DigitalCamera_STM32. GitHub repository. 2017. Available from: https://github.com/iwatake2222/DigitalCamera_STM32.git.
