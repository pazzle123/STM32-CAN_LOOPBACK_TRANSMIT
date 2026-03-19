/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Clear_simbol(uint8_t page, uint8_t col) {
    // Очищаем все 8 страниц (128x64 = 8 страниц по 8 строк)

      Send_command(0xB0 + page);

        // Устанавливаем начальную колонку (младший и старший байты)
      Send_command(0x00 + (col & 0x0F));
      Send_command(0x10 + (col >> 4));
      for(uint8_t i = 0; i < 9; i++) {
              Send_Data(0x00);
       } // 0x00 - все пиксели выключены


}
void Animation(){
	for(int i=0;i<20;++i){
	HAL_Delay(300);
	Clear_simbol(1, 20);
	Clear_simbol(0, 20);
	Clear_simbol(1, 80);
	Clear_simbol(0, 80);
	HAL_Delay(100);
	int	eyes [9] = {
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
			0b111111111111111111,
		};
	Oled_SetCursor(1, 25);
	for(int i = 0; i < 9; i++) {
		      Send_Data(eyes[i]);
		    }
	Oled_SetCursor(0, 25);
			for(int i = 0; i < 9; i++) {
			       Send_Data(eyes[i]);
			    }
	Oled_SetCursor(1, 85);
			for(int i = 0; i < 9; i++) {
					 Send_Data(eyes[i]);
					    }
	Oled_SetCursor(0, 85);
				for(int i = 0; i < 9; i++) {
					Send_Data(eyes[i]);
				}

	HAL_Delay(100);
	Clear_simbol(1, 25);
	Clear_simbol(0, 25);
	Clear_simbol(1, 85);
	Clear_simbol(0, 85);
	HAL_Delay(100);
	Oled_SetCursor(1, 20);
		for(int i = 0; i < 9; i++) {
			     Send_Data(eyes[i]);
	}

	Oled_SetCursor(0, 20);
				for(int i = 0; i < 9; i++) {
				      Send_Data(eyes[i]);
	}


	Oled_SetCursor(1, 80);
			for(int i = 0; i < 9; i++) {
					Send_Data(eyes[i]);
	}
	Oled_SetCursor(0, 80);
					for(int i = 0; i < 9; i++) {
						Send_Data(eyes[i]);
	}
	}
}
void Send_Smile(){
	 int	eyes [9] = {
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
		0b111111111111111111,
	};
	Oled_SetCursor(1, 20);
	for(int i = 0; i < 9; i++) {
	        Send_Data(eyes[i]);
	    }
	Oled_SetCursor(0, 20);
		for(int i = 0; i < 9; i++) {
		        Send_Data(eyes[i]);
		    }
	Oled_SetCursor(1, 80);
		for(int i = 0; i < 8; i++) {
		        Send_Data(eyes[i]);
		}
		Oled_SetCursor(0, 80);
				for(int i = 0; i < 8; i++) {
				        Send_Data(eyes[i]);
				}
	uint8_t	moth [8] = {
				0b11111111,
				0b11111111,
				0b11111111,
				0b11111111,
				0b11111111,
				0b11111111,
				0b11111111,
				0b11111111,
		};
	Oled_SetCursor(5, 20);
		for(int i = 0; i < 8; i++) {
		        Send_Data(moth[i]);
		    }
	Oled_SetCursor(5, 80);
			for(int i = 0; i < 8; i++) {
			        Send_Data(moth[i]);
			}
	Oled_SetCursor(6, 28);
			for(int i = 0; i < 8; i++) {
					  Send_Data(moth[i]);
					   }

	for(int step = 28; step<78;step++){
		Oled_SetCursor(6, step);
		for(int i = 0; i < 8; i++) {
					Send_Data(moth[i]);
					}
		step = step + 2;
	}

}
void Send_command(uint8_t cmd){
	HAL_GPIO_WritePin(GPIOB, DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);
}
void Oled_SetCursor(uint8_t page, uint8_t column) {
    Send_command(0xB0 + page);           // Выбор страницы
    Send_command(0x00 + (column & 0x0F)); // Младшая часть адреса
    Send_command(0x10 + (column >> 4));   // Старшая часть адреса
}

void Send_Data(uint8_t data){
	HAL_GPIO_WritePin(GPIOB, DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &data, 1, 100);
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);
}


void Oled_Clear(void) {
    // Очищаем все 8 страниц (128x64 = 8 страниц по 8 строк)
    for(uint8_t page = 0; page < 8; page++) {
        // Устанавливаем страницу (0-7)
        Send_command(0xB0 + page);

        // Устанавливаем начальную колонку (младший и старший байты)
        Send_command(0x00);  // Младший байт колонки = 0
        Send_command(0x10);  // Старший байт колонки = 0

        // Заполняем все 128 колонок нулями
        for(uint8_t col = 0; col < 128; col++) {
            Send_Data(0x00);  // 0x00 - все пиксели выключены
        }
    }
}
void Oled_Test(void) {
    // Рисуем линию в верхней части
    Send_command(0xB0);  // Page 0
    Send_command(0x00);  // Lower column
    Send_command(0x10);  // Higher column

    for(int i = 0; i < 128; i++) {
        if(i < 20) {
            Send_Data(0x00);  // Белая полоска в начале
        } else {
            Send_Data(0xFF);
        }
    }
}

void Oled_Init(){
	 HAL_GPIO_WritePin(GPIOB, RES_Pin, GPIO_PIN_RESET); // Сброс (низкий уровень)
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(GPIOB, RES_Pin, GPIO_PIN_SET);   // Снимаем сброс (высокий уровень)
	    HAL_Delay(10);


	    Send_command(0xAE); // Display OFF

	    Send_command(0xD5); // Set display clock divide ratio/oscillator frequency
	    Send_command(0x80); // Suggested ratio

	    Send_command(0xA8); // Set multiplex ratio
	    Send_command(0x3F); // 64 lines

	    Send_command(0xD3); // Set display offset
	    Send_command(0x00); // No offset

	    Send_command(0x40); // Set start line

	    Send_command(0x8D); // Charge pump
	    Send_command(0x14); // Enable charge pump

	    Send_command(0x20); // Memory mode
	    Send_command(0x00); // Horizontal mode

	    Send_command(0xA1); // Segment remap
	    Send_command(0xC8); // COM output scan direction

	    Send_command(0xDA); // COM pins hardware configuration
	    Send_command(0x12);

	    Send_command(0x81); // Contrast
	    Send_command(0xCF);

	    Send_command(0xD9); // Pre-charge period
	    Send_command(0xF1);

	    Send_command(0xDB); // VCOMH deselect level
	    Send_command(0x40);

	    Send_command(0xA4); // Display on resume

	    Send_command(0xA6); // Normal display (не инвертировать)

	    Send_command(0x2E); // Deactivate scroll

	    Send_command(0xAF); // Display ON
}
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  Oled_Init();
  HAL_Delay(100);
  Oled_Clear();
  Send_Smile();
  Animation();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RES_Pin|DC_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RES_Pin DC_Pin CS_Pin */
  GPIO_InitStruct.Pin = RES_Pin|DC_Pin|CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
