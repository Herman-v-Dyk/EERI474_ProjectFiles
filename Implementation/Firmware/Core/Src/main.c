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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "ssd1306.h"
#include "test.h"
#include<stdbool.h>
#include<stdio.h>
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};
RTC_DateTypeDef gDate;
RTC_TimeTypeDef gTime;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim21;

/* USER CODE BEGIN PV */
char time[10];
char today[15];
char today_year[5];
char temp[5];
char hour[2];
char min[2];
char date[2];
char month[2];
char year[2];
float time_pressed = 0;
u_int8_t disp_mode = 0;
u_int8_t set_hour = 0;
u_int8_t set_min = 0;
u_int8_t set_date = 0;
u_int8_t set_month = 0;
u_int8_t set_year = 0;
u_int8_t doNothing = 0;
bool buttonPressed = false;
bool buttonPressed_set = false;//"button" for when in settings mode
bool disp_changed = false;//Used to clear the display only if the display mode is changed---CANNOT CLEAR IN INTERRUPT, ITS TO FAST AND THE WHOLE DISPLAY ARE NOT CLEARED
bool standby_tim_start = false;

//MAX30205 settings
const uint8_t max30205_addr = 0x90;//From datasheet, A0, A1, A2 = GND
const uint8_t max30205_conf = 0x44;//From datasheet, select all functions to be active (Highlighted in datasheet)
const uint8_t max30205_sleep = 0x01;
float sens_temp = 00.0;//Variable to store the temperature from MAX30205

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM21_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void set_time (void)
{
	sTime.Hours = 0x00;
	sTime.Minutes = 0x00;
	sTime.Seconds = 0x00;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.WeekDay = 01;
	sDate.Month = 0x01;
	sDate.Date = 0x01;
	sDate.Year = 0x20;
	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
}

void get_time(void)
{
	//Get current time from RTC
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	//Get current date from RTC
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
}

void display_time (void)
{
	//Display time: hh:mm:ss
	sprintf((char*)time, "%02d:%02d", gTime.Hours, gTime.Minutes);
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(35, 40);
	SSD1306_Puts(time, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_date (void)
{
	//Display date: dd-mm-yy
	sprintf((char*)today, "%02d-%02d", gDate.Date, gDate.Month);
	sprintf((char*)today_year, "%d", 2000 + gDate.Year);
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(38, 32);
	SSD1306_Puts(today, &Font_11x18, 1);
	SSD1306_GotoXY(50, 50);
	SSD1306_Puts(today_year, &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

HAL_StatusTypeDef get_temp(uint8_t address, uint8_t config, float *sensor_temperature)
{
	HAL_StatusTypeDef ret;
	uint8_t Data[2];//Will receive 2 bytes from the sensor

	//Send config
	ret = HAL_I2C_Mem_Write(&hi2c3, (uint8_t)(address), 0x01, 1, &config, 1, 50);//0x01 is the config register of MAX30205
	//Check for errors
	if(ret != HAL_OK)
	{
		return ret;
	}

	HAL_Delay(500);

	//Get temperature
	ret = HAL_I2C_Mem_Read(&hi2c3, (uint8_t)(address) | 0x01, 0x00, 1, Data, 2, 50);//(uint8_t)(address) | 0x01 = must add 0x01 to address to read (1), 0x00 is the temp register of MAX30205
	if(ret != HAL_OK)
	{
		return ret;
	}

	//Convert to temperature
	//*sensor_temperature = 0.109*(((Data[0] << 8) | Data[1])*0.00390625) + 33.07;//Add the two received bytes together.
	*sensor_temperature = ((Data[0] << 8) | Data[1])*0.00390625;//Add the two received bytes together.
	return HAL_OK;
}

void display_temp(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	gcvt(sens_temp, 3, temp);//Float to string
	SSD1306_GotoXY(35, 40);
    SSD1306_Puts(temp, &Font_11x18, 1);
    SSD1306_GotoXY(77, 35);
    SSD1306_Puts("o", &Font_7x10, 1);
    SSD1306_GotoXY(85, 40);
    SSD1306_Puts("C", &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_set_hour(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(33, 32);
	SSD1306_Puts("Set Hour", &Font_7x10, 1);
	sprintf(hour, "%d", set_hour);
	SSD1306_GotoXY(60, 45);
	SSD1306_Puts(hour, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_set_min(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(33, 32);
	SSD1306_Puts("Set Min", &Font_7x10, 1);
	sprintf(min, "%d", set_min);
	SSD1306_GotoXY(60, 45);
	SSD1306_Puts(min, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_set_date(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(33, 32);
	SSD1306_Puts("Set Date", &Font_7x10, 1);
	sprintf(date, "%d", set_date);
	SSD1306_GotoXY(60, 45);
	SSD1306_Puts(date, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_set_month(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(33, 32);
	SSD1306_Puts("Set Month", &Font_7x10, 1);
	sprintf(month, "%d", set_month);
	SSD1306_GotoXY(60, 45);
	SSD1306_Puts(month, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void display_set_year(void)
{
	if (disp_changed)
	{
		SSD1306_Clear();
		disp_changed = false;
	}
	SSD1306_GotoXY(33, 32);
	SSD1306_Puts("Set Year", &Font_7x10, 1);
	sprintf(year, "%d", set_year);
	SSD1306_GotoXY(42, 45);
	SSD1306_Puts("20", &Font_11x18, 1);
	SSD1306_GotoXY(65, 45);
	SSD1306_Puts(year, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void polling(void)//Determine time button is pressed.
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0)//Positive logic on button
		{
			buttonPressed = true;
			doNothing = 0;
			HAL_TIM_Base_Start(&htim3);
			time_pressed = __HAL_TIM_GET_COUNTER(&htim3);
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0)
			{
				//Do nothing
			}
			time_pressed = (__HAL_TIM_GET_COUNTER(&htim3) - time_pressed)*0.0001;//To seconds, timer is 100us tick
			//HAL_TIM_Base_Stop(&htim3);
			//HAL_TIM_Base_Init(&htim3);//Used to reset timer 3
		}
	/*else
	{
		doNothing++;
	}

	if (doNothing >= 200)
	{
		SSD1306_OFF();
		HAL_I2C_Mem_Write(&hi2c3, max30205_addr, 0x01, 1, &max30205_sleep, 1, 50);
		//Enter standby-mode
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
		HAL_PWR_EnterSTANDBYMode();
	}*/

	if (buttonPressed)
	{
		//HAL_TIM_Base_Stop_IT(&htim5);
		//standby_tim_start = false;
		if ((time_pressed >= 0.01) && (time_pressed <= 1))
		{
	       //switch display mode
			switch(disp_mode)
			{
			case 0:
				disp_mode = 1;
				buttonPressed = false;
				disp_changed = true;
				break;
			case 1:
				disp_mode = 2;
				buttonPressed = false;
				disp_changed = true;
				break;
			case 2:
				disp_mode = 0;
				buttonPressed = false;
				disp_changed = true;
				break;
			}
		}
		else if ((time_pressed > 1.5) && (time_pressed <= 3) && ((disp_mode == 1) || (disp_mode == 2)))
		{
		   disp_mode = 3;
		   disp_changed = true;
		   buttonPressed = false;
		   HAL_TIM_Base_Stop(&htim2);//stop the timer used for polling the input button
		   get_time();
		   set_hour = gTime.Hours;
		   set_min = gTime.Minutes;
		   set_date = gDate.Date;
		   set_month = gDate.Month;
		   set_year = gDate.Year;
		   HAL_TIM_Base_Start_IT(&htim6);//start the timer used in settings mode
		}
		else if (time_pressed >= 4)
		{
			disp_mode = 8;//Standby Mode
		}
	}

}
void polling_set(void)
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0)//Positive logic on button
		{
			buttonPressed_set = true;
			HAL_TIM_Base_Start(&htim7);
			time_pressed = __HAL_TIM_GET_COUNTER(&htim7);
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==0)
			{
				//Do nothing
			}
			time_pressed = (__HAL_TIM_GET_COUNTER(&htim7) - time_pressed)*0.0001;//To seconds, timer is 100us tick
			HAL_TIM_Base_Stop(&htim7);
			HAL_TIM_Base_Init(&htim7);//Used to reset timer 7
		}
	if (buttonPressed_set)
	{
		if ((time_pressed >= 0.01) && (time_pressed <= 1))
		{
			switch(disp_mode)
			{
			case 3:
				buttonPressed_set = false;
				set_hour++;
				if (set_hour > 23)
				{
					set_hour = 0;
					disp_changed = true;
				}
				break;
			case 4:
				buttonPressed_set = false;
				set_min++;
				if (set_min > 59)
				{
					set_min = 0;
					disp_changed = true;
				}
				break;
			case 5:
				buttonPressed_set = false;
				set_date++;
				if (set_date > 31)
				{
					set_date = 1;
					disp_changed = true;
				}
				break;
			case 6:
				buttonPressed_set = false;
				set_month++;
				if (set_month > 12)
				{
					set_month = 1;
					disp_changed = true;
				}
				break;
			case 7:
				buttonPressed_set = false;
				set_year++;
			    if (set_year > 30)
				{
					set_year = 20;
					disp_changed = true;
				}
				break;
			}
		}
		else if ((time_pressed > 1.5) && (time_pressed <= 3))//Change what are being set
		{
			switch(disp_mode)
			{
			case 3://Go to min to change it
				disp_mode = 4;
				buttonPressed_set = false;
				disp_changed = true;
				break;
			case 4://Go to date to change it
				disp_mode = 5;
				buttonPressed_set = false;
				disp_changed = true;
				break;
			case 5://Go to month to change it
				disp_mode = 6;
				buttonPressed_set = false;
				disp_changed = true;
				break;
			case 6://Go to year to change it
				disp_mode = 7;
				buttonPressed_set = false;
				disp_changed = true;
				break;
			case 7://Exit settings mode and save the time and date
				disp_mode = 0;
				buttonPressed_set = false;
				disp_changed = true;
				sTime.Hours = set_hour;
				sTime.Minutes = set_min;
				if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)//Save the time
				{
					Error_Handler();
				}
				sDate.Date = set_date;
				sDate.Month = set_month;
				sDate.Year = set_year;
				if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)//Save the date
				{
					Error_Handler();
				}
				HAL_TIM_Base_Stop(&htim6);//stop the timer used to monitor the input button while in settings mode
				HAL_TIM_Base_Start_IT(&htim2);//start the timer used to monitor the input button while in display mode
			}
		}
	}
}

/*void read_temp(void)
{
	get_temp(max30205_addr, max30205_conf, &sens_temp);
}*/

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
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_Init(); // Initialize the oled display

  HAL_TIM_RegisterCallback(&htim2, HAL_TIM_PERIOD_ELAPSED_CB_ID,(void*)polling);
  HAL_TIM_RegisterCallback(&htim6, HAL_TIM_PERIOD_ELAPSED_CB_ID,(void*)polling_set);
  //HAL_TIM_RegisterCallback(&htim21, HAL_TIM_PERIOD_ELAPSED_CB_ID,(void*)read_temp);
  HAL_TIM_Base_Start_IT(&htim2);
  //HAL_TIM_Base_Start_IT(&htim21);

  //Initialize variables:
  buttonPressed = false;
  buttonPressed_set = false;
  disp_changed = false;
  standby_tim_start = false;
  disp_mode = 0;
  doNothing = 0;

  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F2)//Backup register for RTC
  {
	  set_time();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*
	  //Standby mode: Check if SB flag is set
	  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)//if the flag are set, MCU woke up from standby mode
	  {
		  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		  //Disable the wakeup pin
		  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);//PA0
	  }*/
	  switch(disp_mode)
	  {
	  case 0://Temp
		  get_temp(max30205_addr, max30205_conf, &sens_temp);
		  display_temp();
		  break;
	  case 1://Time
		  get_time();
		  display_time();
		  break;
	  case 2://Date
		  display_date();
		  break;
	  case 3://Set hour
		  display_set_hour();
		  break;
	  case 4://Set min
		  display_set_min();
		  break;
	  case 5://Set date
		  display_set_date();
		  break;
	  case 6://Set month
		  display_set_month();
		  break;
	  case 7://Set year
		  display_set_year();
		  break;
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C3
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000004;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00000E14;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  /*
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }*/
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 4000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 50;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 400-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65536-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 4000-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 50;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 400-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65536-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM21 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM21_Init(void)
{

  /* USER CODE BEGIN TIM21_Init 0 */

  /* USER CODE END TIM21_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM21_Init 1 */

  /* USER CODE END TIM21_Init 1 */
  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 4000;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 1000;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_ENABLE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM21_Init 2 */

  /* USER CODE END TIM21_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
