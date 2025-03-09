/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_CONF__H__
#define __USBH_CONF__H__
#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/*----------   -----------*/
#define USBH_MAX_NUM_ENDPOINTS 2U

/*----------   -----------*/
#define USBH_MAX_NUM_INTERFACES 10U

/*----------   -----------*/
#define USBH_MAX_NUM_CONFIGURATION 1U

/*----------   -----------*/
#define USBH_KEEP_CFG_DESCRIPTOR 1U

/*----------   -----------*/
#define USBH_MAX_NUM_SUPPORTED_CLASS 1U

/*----------   -----------*/
#define USBH_MAX_SIZE_CONFIGURATION 256U

/*----------   -----------*/
#define USBH_MAX_DATA_BUFFER 512U

/*----------   -----------*/
#define USBH_DEBUG_LEVEL 0U

/*----------   -----------*/
#define USBH_USE_OS 0U

/****************************************/
/* #define for FS and HS identification */
#define HOST_HS 0
#define HOST_FS 1

/* Memory management macros */

/** Alias for memory allocation. */
#define USBH_malloc malloc

/** Alias for memory release. */
#define USBH_free free

/** Alias for memory set. */
#define USBH_memset memset

/** Alias for memory copy. */
#define USBH_memcpy memcpy

/* DEBUG macros */

#if (USBH_DEBUG_LEVEL > 0U)
#define USBH_UsrLog(...)     \
    do {                     \
        printf(__VA_ARGS__); \
        printf("\n");        \
    } while (0)
#else
#define USBH_UsrLog(...) \
    do {                 \
    } while (0)
#endif

#if (USBH_DEBUG_LEVEL > 1U)

#define USBH_ErrLog(...)     \
    do {                     \
        printf("ERROR: ");   \
        printf(__VA_ARGS__); \
        printf("\n");        \
    } while (0)
#else
#define USBH_ErrLog(...) \
    do {                 \
    } while (0)
#endif

#if (USBH_DEBUG_LEVEL > 2U)
#define USBH_DbgLog(...)     \
    do {                     \
        printf("DEBUG : ");  \
        printf(__VA_ARGS__); \
        printf("\n");        \
    } while (0)
#else
#define USBH_DbgLog(...) \
    do {                 \
    } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __USBH_CONF__H__ */
