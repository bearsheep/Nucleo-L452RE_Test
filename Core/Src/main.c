/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void I2C_Master_Test(void);
void UART_Test(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
  I2C_Master_Test();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    UART_Test();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void I2C_Master_Test(void)
{
    HAL_StatusTypeDef ret;
    uint8_t i2c_rx_buffer[16]={0}, i2c_tx_buffer[16]={0}, register_addr[1];

    /* Random read */
    register_addr[0] = 0x00;
    ret = I2CM_RandomRead(&hi2c3, (uint16_t)0xA0, (uint8_t *)register_addr, (uint8_t *)i2c_rx_buffer, 16);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
    /* Current address read */
    ret = I2CM_CurrentAddrRead(&hi2c3, (uint16_t)0xA0, (uint8_t *)i2c_rx_buffer, 16);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
    /* Sequential bytes write */
    // Write 0x03 to PageSelect(0x7F)
    i2c_tx_buffer[0] = 0x7F;
    i2c_tx_buffer[1] = 0x03;
    ret = I2CM_SequentialBytesWrite(&hi2c3, (uint16_t)0xA0, (uint8_t *)i2c_tx_buffer, 2);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
    HAL_Delay(80);  // HW 6.0: Complete Single or Sequential Write to non-volatile registers timing max = 80ms
    // Read back to check PageSelect(0x7F) = 0x03
    register_addr[0] = 0x7F;
    ret = I2CM_RandomRead(&hi2c3, (uint16_t)0xA0, (uint8_t *)register_addr, (uint8_t *)i2c_rx_buffer, 1);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
    // Write data to byte 254-255(0xEF-0xFF)
    i2c_tx_buffer[0] = 0xFE;
    i2c_tx_buffer[1] = 0x99;
    i2c_tx_buffer[2] = 0xAA;
    ret = I2CM_SequentialBytesWrite(&hi2c3, (uint16_t)0xA0, (uint8_t *)i2c_tx_buffer, 3);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
    HAL_Delay(80);
    // Read back to check byte 254-255(0xEF-0xFF) = 0x99 0xAA
    register_addr[0] = 0xFE;
    ret = I2CM_RandomRead(&hi2c3, (uint16_t)0xA0, (uint8_t *)register_addr, (uint8_t *)i2c_rx_buffer, 2);
    if(ret != HAL_OK)
    {
      Error_Handler();
    }
}

void UART_Test(void)
{
    uint8_t uart_buf[32];
    char Uart_Tx_Method_1[32] = "Method_1\r\n";
    char str_buffer[128];


    strcpy((char *)uart_buf, Uart_Tx_Method_1);
    HAL_UART_Transmit(&huart2, uart_buf, strlen((char *)uart_buf), HAL_MAX_DELAY);
    HAL_Delay(1000);
    strcpy((char *)uart_buf, "Method_2\r\n");
    HAL_UART_Transmit(&huart2, uart_buf, strlen((char *)uart_buf), HAL_MAX_DELAY);
    HAL_Delay(1000);
    sprintf(str_buffer, "Method_3: number = 0x%X\r\n", uart_buf[0]);
    HAL_UART_Transmit(&huart2, (uint8_t *)str_buffer, strlen((char *)str_buffer), HAL_MAX_DELAY);
    HAL_Delay(1000);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
