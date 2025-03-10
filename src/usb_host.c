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

#include "custom_usbh_audio.h"
// #include "custom_usbh_audio.h"
// #include "usbh_audio.h"
#include "usbh_core.h"

/* USER CODE BEGIN Includes */

void print_array(uint8_t *data_arr, uint8_t data_length) {
    printf("[");
    for (int i = 0; i < data_length; i++) {
        printf("%d,", data_arr[i]);
    }
    printf("]\n");
}

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

    if (USBH_RegisterClass(&hUsbHostFS, USBH_CUSTOM_AUDIO_CLASS) != USBH_OK) {
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

    // printf("LENGTH %d %d %d\n", hUsbHostFS.device.Data[0], hUsbHostFS.device.Data[1], hUsbHostFS.device.Data[2]);

    // print_array(&hUsbHostFS.device.Data, USBH_MAX_DATA_BUFFER);

    // print_array(((AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData)->microphone.buf, ((AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData)->microphone.total_length);
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
            USBH_AUDIO_SetFrequency(&hUsbHostFS, 44100, 1, 16);
            printf("suck my huge cock (device connected and active)\n");
            printf("Microphone Sample Rate: %lu Hz\n", ((AUDIO_HandleTypeDef *)hUsbHostFS.pActiveClass->pData)->microphone.frequency);
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
