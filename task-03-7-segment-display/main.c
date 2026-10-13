/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
//#define LED0 GPIOC, GPIO_PIN_6
//#define LED1 GPIOC, GPIO_PIN_7
//#define LED2 GPIOC, GPIO_PIN_8
//#define LED3 GPIOC, GPIO_PIN_9
//#define LED4 GPIOE, GPIO_PIN_4
//#define LED5 GPIOD, GPIO_PIN_3
//#define LED6 GPIOE, GPIO_PIN_5
//#define LED7 GPIOE, GPIO_PIN_6
//#define LED_R GPIOD, GPIO_PIN_13
//#define LED_G GPIOB, GPIO_PIN_8
//#define LED_B GPIOD, GPIO_PIN_12
#define JOY_RT GPIOE, GPIO_PIN_0
#define JOY_LT GPIOE, GPIO_PIN_1
#define JOY_DN GPIOE, GPIO_PIN_2
#define JOY_UP GPIOE, GPIO_PIN_3
#define JOY_OK GPIOE, GPIO_PIN_15

#define DIG1 GPIOB, GPIO_PIN_2
#define DIG2 GPIOB, GPIO_PIN_3
#define DIG3 GPIOB, GPIO_PIN_4
#define DIG4 GPIOB, GPIO_PIN_5

#define PART_OF_DIG_A GPIOG, GPIO_PIN_0
#define PART_OF_DIG_B GPIOG, GPIO_PIN_1
#define PART_OF_DIG_C GPIOG, GPIO_PIN_2
#define PART_OF_DIG_D GPIOG, GPIO_PIN_3
#define PART_OF_DIG_E GPIOG, GPIO_PIN_4
#define PART_OF_DIG_F GPIOG, GPIO_PIN_5
#define PART_OF_DIG_G GPIOG, GPIO_PIN_6
#define PART_OF_DIG_DP GPIOG, GPIO_PIN_9

#define MAX_NUM 9
#define NUMBER_OF_DIGS 4
#define NUMBER_OF_PODS 8
#define DELAY_TIME 50

#define DIG_DELAY 1000
#define JOY_DELAY 50
#define DELAY_FOR_HOLDING 250
//#define NUMBER_OF_LEDS 8


typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} digs_t;
digs_t digs[NUMBER_OF_DIGS] = {
		  {DIG1},
	      {DIG2},
	      {DIG3},
	      {DIG4},
};

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} pod_t;
pod_t pods[NUMBER_OF_PODS] = {
		  {PART_OF_DIG_A},
	      {PART_OF_DIG_B},
	      {PART_OF_DIG_C},
	      {PART_OF_DIG_D},
		  {PART_OF_DIG_E},
		  {PART_OF_DIG_F},
		  {PART_OF_DIG_G},
		  {PART_OF_DIG_DP},
};


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void display_digit_0(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_E, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
}
void display_digit_1(){
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
}
void display_digit_2(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_E, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_3(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_4(){
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_5(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_6(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_E, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_7(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
}
void display_digit_8(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_E, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_digit_9(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_SET);
}
void display_clear(){
	HAL_GPIO_WritePin(PART_OF_DIG_A, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_B, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_C, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_D, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_E, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_F, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PART_OF_DIG_G, GPIO_PIN_RESET);
}

void (*display[MAX_NUM+1])() = {
    display_digit_0,
    display_digit_1,
    display_digit_2,
    display_digit_3,
    display_digit_4,
    display_digit_5,
    display_digit_6,
    display_digit_7,
    display_digit_8,
    display_digit_9
};
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  int8_t cur_num = 0;
  int8_t direction = 1;
  uint32_t counter_for_dig = 0;
  uint32_t counter_for_joy = 0;
  int8_t dig_id=3;
  uint32_t hold_counter_left = 0;
  uint32_t hold_counter_right = 0;

  uint8_t last_left = GPIO_PIN_SET;
  uint8_t last_right = GPIO_PIN_SET;
  HAL_GPIO_WritePin (digs[dig_id].port, digs[dig_id].pin, GPIO_PIN_SET);
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_Delay(DELAY_TIME);
	  counter_for_dig+=DELAY_TIME;
	  counter_for_joy+=DELAY_TIME;
	  if (DIG_DELAY <= counter_for_dig)
	  {
		  display_clear();
	      display[cur_num]();
	      cur_num += direction;
	      if(cur_num > MAX_NUM) cur_num = 0;
	      if(cur_num == -1 && direction == -1) cur_num = MAX_NUM;
	      counter_for_dig=0;
	  }

	  if (HAL_GPIO_ReadPin(JOY_OK) == GPIO_PIN_RESET) {
		  direction = -1;
	  } else {
		  direction = 1;
	  }
	  if(counter_for_joy >= JOY_DELAY)
	  {
	      uint8_t left_now  = HAL_GPIO_ReadPin(JOY_LT);
	      uint8_t right_now = HAL_GPIO_ReadPin(JOY_RT);

	      if(left_now == GPIO_PIN_RESET)
	      {
	          hold_counter_left += DELAY_TIME;

	          if(last_left == GPIO_PIN_SET ||
	             hold_counter_left >= DELAY_FOR_HOLDING)
	          {
	              HAL_GPIO_WritePin(digs[dig_id].port,
	                                digs[dig_id].pin,
	                                GPIO_PIN_RESET);

	              if(dig_id > 0)
	                  dig_id--;

	              HAL_GPIO_WritePin(digs[dig_id].port,
	                                digs[dig_id].pin,
	                                GPIO_PIN_SET);

	              if(hold_counter_left >= DELAY_FOR_HOLDING)
	                  hold_counter_left = DELAY_TIME;
	          }
	      }
	      else
	      {
	          hold_counter_left = 0;
	      }

	      if(right_now == GPIO_PIN_RESET)
	      {
	          hold_counter_right += JOY_DELAY;

	          if(last_right == GPIO_PIN_SET ||
	             hold_counter_right >= DELAY_FOR_HOLDING)
	          {
	              HAL_GPIO_WritePin(digs[dig_id].port,
	                                digs[dig_id].pin,
	                                GPIO_PIN_RESET);

	              if(dig_id < NUMBER_OF_DIGS - 1)
	                  dig_id++;

	              HAL_GPIO_WritePin(digs[dig_id].port,
	                                digs[dig_id].pin,
	                                GPIO_PIN_SET);

	              if(hold_counter_right >= DELAY_FOR_HOLDING)
	                  hold_counter_right = JOY_DELAY;
	          }
	      }

	      else
	      {
	          hold_counter_right = 0;
	      }

	      last_left = left_now;
	      last_right = right_now;

	      counter_for_joy = 0;
	  }
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

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	//__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	HAL_PWREx_EnableVddIO2();

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	for (int i=0; i<NUMBER_OF_DIGS;i++){
		  HAL_GPIO_WritePin (digs[i].port, digs[i].pin, GPIO_PIN_RESET);
	}
	for (int i=0; i<NUMBER_OF_PODS;i++){
		  HAL_GPIO_WritePin (pods[i].port, pods[i].pin, GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(JOY_LT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(JOY_UP, GPIO_PIN_SET);
	HAL_GPIO_WritePin(JOY_RT, GPIO_PIN_SET);
	HAL_GPIO_WritePin(JOY_DN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(JOY_OK, GPIO_PIN_SET);




	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_12 | GPIO_PIN_13;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}
/**
* LED0 = PC6
* LED1 = PC7
* LED2 = PC8
* LED3 = PC9
* LED4 = PE4
* LED5 = PD3
* LED6 = PE5
* LED7 = PE6
*
* LED_R = PD13
* LED_B = PD12
* LED_G = PB8
*
* JOY_RT = PE0
* JOY_LT = PE1
* JOY_DN = PE2
* JOY_UP = PE3
* JOY_OK = PE15
*/

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
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	while(1);
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
