# STM32H7_OV7670 - In progress...
Solution for single-shot imagery capture with OV7670 camera. Data are being processed by NUCLEO-H7A3ZI-Q microcontoller board. Library was created and tested in STM32CubeIDE environment using DCMI and DMA technologies. This approach enables user to obtain RGB565 color images, whereas YUV for black-and-white images. 

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
