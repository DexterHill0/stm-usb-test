#include "main.h"

#include "usb_host.h"

#define USARTx USART1
#define USARTx_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET() __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET() __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN GPIO_PIN_9
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_AF GPIO_AF7_USART1
#define USARTx_RX_PIN GPIO_PIN_10
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_AF GPIO_AF7_USART1

// // #define LED_PIN GPIO_PIN_13
// // #define LED_GPIO_PORT GPIOC
// // #define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

// // USBD_HandleTypeDef USBD_Device;

// // USE_HAL_HCD_REGISTER_CALLBACKS

// // static void Error_Handler(void);

// void BSP_LED_On(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
//     HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
// }

// // USBH_HandleTypeDef;

UART_HandleTypeDef UartHandle;

int _write(int file, char *ptr, int len) {
    UNUSED(file);

    return HAL_UART_Transmit(&UartHandle, (uint8_t *)ptr, len, 0xFFFF);
}

// #define LED_BUILTIN GPIOC, GPIO_PIN_13

// #define GPIOx_CLK_ENABLE(__INDEX__)       \
//     do {                                  \
//         if ((__INDEX__) == GPIOA)         \
//             __HAL_RCC_GPIOA_CLK_ENABLE(); \
//         else if ((__INDEX__) == GPIOB)    \
//             __HAL_RCC_GPIOB_CLK_ENABLE(); \
//         else if ((__INDEX__) == GPIOC)    \
//             __HAL_RCC_GPIOC_CLK_ENABLE(); \
//         else if ((__INDEX__) == GPIOD)    \
//             __HAL_RCC_GPIOD_CLK_ENABLE(); \
//     } while (0)

// #define GPIOx_CLK_DISABLE(__INDEX__)       \
//     do {                                   \
//         if ((__INDEX__) == GPIOA)          \
//             __HAL_RCC_GPIOA_CLK_DISABLE(); \
//         else if ((__INDEX__) == GPIOB)     \
//             __HAL_RCC_GPIOB_CLK_DISABLE(); \
//         else if ((__INDEX__) == GPIOC)     \
//             __HAL_RCC_GPIOC_CLK_DISABLE(); \
//         else if ((__INDEX__) == GPIOD)     \
//             __HAL_RCC_GPIOD_CLK_DISABLE(); \
//     } while (0)

// #define BSP_LED_Blink(__GPIOX__, __GPIOPIN__, __DELAY__) \
//     do {                                                 \
//         BSP_LED_On(__GPIOX__, __GPIOPIN__);              \
//         HAL_Delay(__DELAY__);                            \
//         BSP_LED_Off(__GPIOX__, __GPIOPIN__);             \
//         HAL_Delay(__DELAY__);                            \
//     } while (1)

// void BSP_LED_Off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
//     HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
// }

// void BSP_LED_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
//     GPIO_InitTypeDef GPIO_InitStruct;

//     /* Enable the GPIO_LED Clock */
//     GPIOx_CLK_ENABLE(GPIOx);

//     /* Configure the GPIO_LED pin */
//     GPIO_InitStruct.Pin = GPIO_Pin;
//     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//     GPIO_InitStruct.Pull = GPIO_PULLUP;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

//     HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

//     HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
// }

void UART_Init(void) {
    UartHandle.Instance = USARTx;

    UartHandle.Init.BaudRate = 9600;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&UartHandle) != HAL_OK) {
        printf("HAL_UART_Init Error!\n");
        Error_Handler();
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef GPIO_InitStruct;

    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();

    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();

    GPIO_InitStruct.Pin = USARTx_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = USARTx_TX_AF;

    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Alternate = USARTx_RX_AF;

    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();

    HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
    HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}

// int main(void) {
//     HAL_Init();

//     BSP_LED_Init(LED_BUILTIN);

//     SystemClock_Config();

//     UART_Init();

//     // USB INIT
//     __HAL_RCC_GPIOB_CLK_ENABLE();
//     __HAL_RCC_GPIOA_CLK_ENABLE();

//     MX_USB_HOST_Init();

//     HAL_Delay(1000);

//     printf("Starting!\n");

//     while (1) {
//         MX_USB_HOST_Process();
//     }
// }

// // void OTG_FS_IRQHandler(void) {
// //     printf("Interrupt!\n");
// //     USER_HAL_HCD_IRQHandler();
// // }

// void Error_Handler(void) {
//     // BSP_LED_On(LED_BUILTIN);

//     __disable_irq();
//     while (1) {
//         printf("ERRORFAULT\n");
//     }
// }

extern HCD_HandleTypeDef hhcd_USB_OTG_FS;

void SysTick_Handler(void) {
    HAL_IncTick();
}

void NMI_Handler(void) {
}

void HardFault_Handler(void) {
    while (1) {
        printf("HARDFAULT\n");
    }
    // BSP_LED_Blink(GPIOC, GPIO_PIN_13, 500);
}

void MemManage_Handler(void) {
    while (1) {
        printf("MEMMANAGE\n");
    }
}

void BusFault_Handler(void) {
    while (1) {
        printf("BUSFAULT\n");
    }
}

void UsageFault_Handler(void) {
    while (1) {
        printf("USAGEFAULT\n");
    }
}

void SVC_Handler(void) {
}

void DebugMon_Handler(void) {
}

void PendSV_Handler(void) {
}

void OTG_FS_IRQHandler(void) {
    /* USER CODE BEGIN OTG_FS_IRQn 0 */

    /* USER CODE END OTG_FS_IRQn 0 */
    HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
    /* USER CODE BEGIN OTG_FS_IRQn 1 */

    /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_MspInit(void) {
    /* USER CODE BEGIN MspInit 0 */

    /* USER CODE END MspInit 0 */

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init*/

    /* USER CODE BEGIN MspInit 1 */

    /* USER CODE END MspInit 1 */
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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

    UART_Init();

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USB_HOST_Init();

    printf("Starting...\n");
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */
        MX_USB_HOST_Process();

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

    /*Configure GPIO pin : PB15 */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
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
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
