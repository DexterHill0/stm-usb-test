/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file            : usb_host.c
 * @version         : v1.0_Cube
 * @brief           : This file implements the USB Host
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

#include "usb_host.h"

#include "usbh_audio.h"
#include "usbh_core.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);
// static USBH_StatusTypeDef USBH_AUDIO_InputStream(USBH_HandleTypeDef *phost);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * Init USB host library, add supported class and start the library
 * @retval None
 */
void MX_USB_HOST_Init(void) {
    /* USER CODE BEGIN USB_HOST_Init_PreTreatment */

    /* USER CODE END USB_HOST_Init_PreTreatment */

    /* Init host Library, add supported class and start the library. */
    if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK) {
        printf("USBH_Init Error\n");
        Error_Handler();
    }
    if (USBH_RegisterClass(&hUsbHostFS, USBH_AUDIO_CLASS) != USBH_OK) {
        printf("USBH_RegisterClass Error\n");
        Error_Handler();
    }
    if (USBH_Start(&hUsbHostFS) != USBH_OK) {
        printf("USBH_Start Error\n");
        Error_Handler();
    }

    /* USER CODE BEGIN USB_HOST_Init_PostTreatment */

    /* USER CODE END USB_HOST_Init_PostTreatment */
}

// static USBH_StatusTypeDef USBH_AUDIO_InputStream(USBH_HandleTypeDef *phost) {
//     /* Prevent unused argument(s) compilation warning */
//     UNUSED(phost);

//     printf("PROCESS\n");

//     USBH_StatusTypeDef status = USBH_BUSY;

//     return status;
// }

/*
 * Background task
 */
void MX_USB_HOST_Process(void) {
    /* USB Host Background task */
    USBH_Process(&hUsbHostFS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id) {
    /* USER CODE BEGIN CALL_BACK_1 */
    switch (id) {
        case HOST_USER_SELECT_CONFIGURATION:
            break;

        case HOST_USER_DISCONNECTION:
            Appli_state = APPLICATION_DISCONNECT;
            break;

        case HOST_USER_CLASS_ACTIVE:
            printf("suck my huge cock (device connected and active)\n");
            Appli_state = APPLICATION_READY;
            break;

        case HOST_USER_CONNECTION:
            Appli_state = APPLICATION_START;
            break;

        default:
            break;
    }

    printf("STATE %d\n", Appli_state);

    // if (Appli_state == APPLICATION_READY) {
    //     AUDIO_HandleTypeDef *AUDIO_Handle = (AUDIO_HandleTypeDef *)phost->pActiveClass->pData;

    //     // uint8_t *buf = malloc(200);

    //     if (USBH_IsocReceiveData(phost, AUDIO_Handle->microphone.buf, AUDIO_Handle->microphone.total_length, AUDIO_Handle->microphone.Pipe) != USBH_OK) {
    //         printf("USBH_IsocReceiveData\n");
    //         Error_Handler();
    //     }

    //     printf("BUF[0] %d\n", AUDIO_Handle->microphone.buf[0]);
    // }

    /* USER CODE END CALL_BACK_1 */
}

/**
 * @}
 */

/**
 * @}
 */
