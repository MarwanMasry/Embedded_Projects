 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller
 *              - Dio Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Dio_PBcfg.h"

#include "Dio_cfg.h"
/* AUTOSAR Version checking between Dio_PBcfg.h and Dio_cfg.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_CFG_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.h and Dio_Types.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_CFG_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_CFG_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_CFG_SW_PATCH_VERSION))
  #error "The SW version of Dio_cfg.h does not match the expected version"
#endif

/*******************************************************************************
 *                      Public Global Variables Definitions                    *
 *******************************************************************************/
/* PB structure used with Dio_Init API */
const Dio_ConfigType Dio_Configuration =
{
  /* configured DIO Channels */
  {
    DioConf_LED1_PORT_NUM,DioConf_LED1_CHANNEL_NUM,
    DioConf_SW1_PORT_NUM,DioConf_SW1_CHANNEL_NUM
  },
  
  /* No configured DIO Ports */ 
    /*
  {
  },
    */
  
 /* No configured DIO Groups*/
   /*
  {
  }
   */
};
