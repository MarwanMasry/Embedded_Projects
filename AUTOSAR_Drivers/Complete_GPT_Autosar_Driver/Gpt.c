 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Gpt.h"
#include "Gpt_Registers.h"

/* Include Det module only in case the development are enabled */
#if (GPT_DEV_ERROR_DETECT == STD_ON)

/* AUTOSAR  Det Module */
#include "Det.h"
/* AUTOSAR Version checking between Det and GPT Modules */
#if ((DET_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/
   
/* Array to hold the status of each Timer that is configured */
STATIC Gpt_ChannelStatus Gpt_ChannelStatusArray [GPT_CONFIGURED_TIMER_CHANNELS]\
                                                              = {UNINITIALIZED};

/* Pointer to hold the address of Configuration Structure */
STATIC const Gpt_ConfigChannel * Gpt_ConfigChannels_Ptr = NULL_PTR;

/* Monitoring the status of the driver as a hole */
STATIC uint8 Gpt_Status = GPT_NOT_INITIALIZED;
   
/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/

/*******************************************************************************
* Service Name: Gpt_GetVersionInfo
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version
* 				    information of this module.
* Return value: None
* Description: Function to get the version information of this module.
*******************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)

void Gpt_GetVersionInfo
(
    Std_VersionInfoType *versioninfo
)
{
    boolean error = FALSE;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_VERSION_INFO_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input pointer is not Null pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_VERSION_INFO_SID,
            GPT_E_PARAM_POINTER
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
        /* Copy the vendor Id */
        versioninfo->vendorID         = (uint16)GPT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID         = (uint16)GPT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
    }
    else
    {
        /* Do Nothing */
    }
}

#endif

/*******************************************************************************
* Service Name: Gpt_Init
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr | Pointer to a selected configuration structure
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the hardware timer module.
*******************************************************************************/
void Gpt_Init
(
    const Gpt_ConfigType* ConfigPtr 
)
{
    boolean error = FALSE;
    uint8 i = ZERO;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_INIT_SID,
            GPT_E_ALREADY_INITIALIZED
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input pointer is not Null pointer */
    if (NULL_PTR == ConfigPtr)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_INIT_SID,
            GPT_E_PARAM_POINTER
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
        /* Initialize the Driver */
        Gpt_Status = GPT_INITIALIZED;
        
        /* Save the address of Configuration Structure*/
        Gpt_ConfigChannels_Ptr = ConfigPtr->GptChannels;
        
        /* Loop to all configured Timer and initialize them */
        for( i = ZERO ; i < GPT_CONFIGURED_TIMER_CHANNELS ; i++)
        {
          /* Set the crossponding timer to be initialized */
          Gpt_ChannelStatusArray[i] = INITIALIZED;
          
          /* In case of we are configuring Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[i].ChannelID )
          {
             /* Disable the SysTick Timer by Clear the ENABLE Bit */
             SYSTICK_CTRL_REG    = ZERO;
             /* Clear the Current Reload value */
             SYSTICK_RELOAD_REG  = ZERO ;
             /* Clear the Current Register value */
             SYSTICK_CURRENT_REG = ZERO;  
             
             /* Choose the clock source According to the Configuration */
             if( PIOSC_DIV_BY_4 == Gpt_ConfigChannels_Ptr[i].ChannelClkSourceRef)
             {
                CLEAR_BIT(SYSTICK_CTRL_REG, GPT_CLK_SOURCE_BIT_POSITION); 
             }
             else if( SYSTEM_CLOCK == Gpt_ConfigChannels_Ptr[i].ChannelClkSourceRef)
             {
                SET_BIT(SYSTICK_CTRL_REG, GPT_CLK_SOURCE_BIT_POSITION); 
             }
             else
             {
                    /* Do Nothing */
             }
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          }   
        }
    }
    else
    {
        /* Do Nothing */
    }

}

/*******************************************************************************
* Service Name: Gpt_DeInit
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Deinitializes all hardware timer channels.
*******************************************************************************/
#if (GPT_DEINIT_API == STD_ON)

void Gpt_DeInit( void )
{
    boolean error = FALSE;
    uint8   i     = ZERO;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_DEINIT_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Loop to all configured Timer */
    for( i = ZERO ; i < GPT_CONFIGURED_TIMER_CHANNELS ; i++)
    {
        /* If you found any timer that is still running report to DET */
        if( RUNNING ==  Gpt_ChannelStatusArray[i] )
        {
           /* Report to DET  */
            Det_ReportError
           (        
                GPT_MODULE_ID,
                GPT_INSTANCE_ID,
                GPT_DEINIT_SID,
                GPT_E_BUSY
            );
            error = TRUE;
        }
        else
        {
            /* Do Nothing */
        }
    }
 
#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
        /* De-Initialize the Driver */
        Gpt_Status = GPT_NOT_INITIALIZED;
        
        /* Make the global pointer point to null again */
        Gpt_ConfigChannels_Ptr = NULL_PTR;

        /* Loop to all configured Timer and initialize them */
        for( i = ZERO ; i < GPT_CONFIGURED_TIMER_CHANNELS ; i++)
        {
          /* Set the crossponding timer to be Un-initialized */
          Gpt_ChannelStatusArray[i] = UNINITIALIZED;
          
          /* In case of we are De-initing Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[i].ChannelID )
          {
             /* Disable the SysTick Timer by Clear the ENABLE Bit, Disable Interrupts*/
             SYSTICK_CTRL_REG    = ZERO;
             /* Clear the Current Reload value */
             SYSTICK_RELOAD_REG  = ZERO ;
             /* Clear the Current Register value */
             SYSTICK_CURRENT_REG = ZERO;    
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[i].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          }   
        }
    }
    else
    {
        /* Do Nothing */
    }

}

#endif

/*******************************************************************************
* Service Name: Gpt_GetTimeElapsed
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType | Elapsed timer value (in number of ticks)
* Description: Returns the time already elapsed.
*******************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON) 

Gpt_ValueType Gpt_GetTimeElapsed
(
    Gpt_ChannelType Channel
)
{
    boolean error = FALSE;
    Gpt_ValueType output = ZERO;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_TIME_ELAPSED_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_TIME_ELAPSED_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
          /* In case of we are making calculation for Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
          {
               /*
                * If Systick's state is:
                *    - Running it will return elapsed time. 
                *    - Stopped it will return elapsed time at moment of stopping. 
                *    - Initialized it will return zero.
                *    - Expired it will return the target time.
                */
                if(  (RUNNING ==  Gpt_ChannelStatusArray[Channel])\
                  || (STOPPED ==  Gpt_ChannelStatusArray[Channel]))
                {
                    output = SYSTICK_RELOAD_REG - SYSTICK_CURRENT_REG;
                }
                else if( EXPIRED ==  Gpt_ChannelStatusArray[Channel] )
                {
                    output = SYSTICK_RELOAD_REG;
                }
                else if ( INITIALIZED ==  Gpt_ChannelStatusArray[Channel] )
                {
                    output = ZERO;
                }
                else
                {
                    /* Do Nothing */
                }
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          }   
    }
    else
    {
        /* Do Nothing */
    }
    
    return output;
}

#endif

/*******************************************************************************
* Service Name: Gpt_GetTimeRemaining
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType | Remaining timer value (in number of ticks)
* Description: Returns the time remaining until the target time is reached.
*******************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON) 

Gpt_ValueType Gpt_GetTimeRemaining
(
    Gpt_ChannelType Channel
)
{
    boolean error = FALSE;
    Gpt_ValueType output = ZERO;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_TIME_REMAINING_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_GET_TIME_REMAINING_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
          /* In case of we are making calculation for Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
          {
               /*
                * If Systick's state is:
                *    - Running it will return remaining time. 
                *    - Stopped it will return remaining time at moment of stopping.
                *    - Initialized it will return zero.
                *    - Expired it will return ZERO.
                */
                if(  (RUNNING ==  Gpt_ChannelStatusArray[Channel])\
                  || (STOPPED ==  Gpt_ChannelStatusArray[Channel]))
                {
                    output = SYSTICK_CURRENT_REG;
                }
                else if( EXPIRED ==  Gpt_ChannelStatusArray[Channel] )
                {
                    output = ZERO;
                }
                else if ( INITIALIZED ==  Gpt_ChannelStatusArray[Channel] )
                {
                    output = ZERO;
                }
                else
                {
                    /* Do Nothing */
                }
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          }   
    }
    else
    {
        /* Do Nothing */
    }
    
    return output;
}

#endif

/*******************************************************************************
* Service Name: Gpt_StartTimer
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel ,
*                  Value   | Target time in number of ticks.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts a timer channel.
*******************************************************************************/
void Gpt_StartTimer
( 
    Gpt_ChannelType Channel,
    Gpt_ValueType Value 
)
{
    boolean error = FALSE;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_START_TIMER_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_START_TIMER_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

    /* Check if input Value is within range */
    if (   (GPT_CONFIGURED_TIMER_CHANNELS > Channel)\
      && ( (Value > Gpt_ConfigChannels_Ptr[Channel].ChannelTickValueMax)\
      ||   ( ZERO == Value) )  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_START_TIMER_SID,
            GPT_E_PARAM_VALUE
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* If you start a timer that is running report a DET error  */
    if(  (GPT_CONFIGURED_TIMER_CHANNELS > Channel)\
      && ( RUNNING ==  Gpt_ChannelStatusArray[Channel]) )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_START_TIMER_SID,
            GPT_E_BUSY
        );
        error = TRUE;    
    }
    else
    {
        /* No Action Required */
    }
     

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
        /* The state of the selected timer channel shall be changed to running */
        Gpt_ChannelStatusArray[Channel] = RUNNING;
        
          /* In case of we are Starting Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
          {
                /* Set the Reload value to count n miliseconds */ 
                SYSTICK_RELOAD_REG  = Value - ONE ;
                /* Enable the SysTick Timer (ENABLE = 1) */
                SYSTICK_CTRL_REG |=( ONE << GPT_ENABLE_BIT_POSITION ) ;    

          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          }   
    }
    else
    {
        /* Do Nothing */
    }

}

/*******************************************************************************
* Service Name: Gpt_StopTimer
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stops a timer channel.
*******************************************************************************/
void Gpt_StopTimer
(
    Gpt_ChannelType Channel
)
{
    boolean error = FALSE;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_STOP_TIMER_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_STOP_TIMER_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
        if (   ( INITIALIZED ==  Gpt_ChannelStatusArray[Channel] )\
            || ( STOPPED ==  Gpt_ChannelStatusArray[Channel] )\
            || ( EXPIRED ==  Gpt_ChannelStatusArray[Channel] ))
        {
            /* Do Nothing */
        }
        else if( RUNNING ==  Gpt_ChannelStatusArray[Channel])
        {
             /* The state of the selected timer channel shall be changed to Stopped */
             Gpt_ChannelStatusArray[Channel] = STOPPED;
            
              /* In case of we are Stopping Systick timer */
              if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
              {
                    /* Disable the SysTick Timer (ENABLE = 1) */
                    SYSTICK_CTRL_REG &= ~( ONE << GPT_ENABLE_BIT_POSITION ) ;    
              }
              else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
              {
                    /* Will be configured in next SW releases */
              }
              else
              {
                    /* Do Nothing */
              }
        }
        else
        {
            /* Do Nothing*/
        }
    }
    else
    {
        /* Do Nothing */
    }

}

/*******************************************************************************
* Service Name: Gpt_EnableNotification
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables the interrupt notification for a channel 
*             (relevant in normal mode).
*******************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) 

void Gpt_EnableNotification
(
    Gpt_ChannelType Channel
)
{
    boolean error = FALSE;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_ENABLE_NOTIFICATION_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_ENABLE_NOTIFICATION_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    if(NULL_PTR == Gpt_ConfigChannels_Ptr[Channel].Gpt_Notification_Ptr)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_ENABLE_NOTIFICATION_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;      
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
          /* In case of we are Enabling the interrupts for Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
          {
                /* Enable SysTick Interrupt (INTEN = 1) */
                SYSTICK_CTRL_REG |=( ONE << GPT_INTEN_BIT_POSITION ) ;    
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          } 
    }
    else
    {
        /* Do Nothing */
    }

}

#endif 

/*******************************************************************************
* Service Name: Gpt_DisableNotification
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables the interrupt notification for a channel 
*             (relevant in normal mode).
*******************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) 


void Gpt_DisableNotification
( 
    Gpt_ChannelType Channel 
)
{
    boolean error = FALSE;
    
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    
    /* Check if the Driver is initialized before using this function */
    if (GPT_NOT_INITIALIZED == Gpt_Status)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_DISABLE_NOTIFICATION_SID,
            GPT_E_UNINIT
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    /* Check if input Channel is within range */
    if ( GPT_CONFIGURED_TIMER_CHANNELS <= Channel  )
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_DISABLE_NOTIFICATION_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    if(NULL_PTR == Gpt_ConfigChannels_Ptr[Channel].Gpt_Notification_Ptr)
    {
        /* Report to DET  */
        Det_ReportError
       (        
            GPT_MODULE_ID,
            GPT_INSTANCE_ID,
            GPT_DISABLE_NOTIFICATION_SID,
            GPT_E_PARAM_CHANNEL
        );
        error = TRUE;      
    }
    else
    {
        /* No Action Required */
    }

#endif 
    
    /* In-case there are no errors */
    if(FALSE == error)
    {
          /* In case of we are Disabling the interrupts for Systick timer */
          if( GPT_SYSTICK_TIMER_ID == Gpt_ConfigChannels_Ptr[Channel].ChannelID )
          {
                /* Disable SysTick Interrupt (INTEN = 0) */
                SYSTICK_CTRL_REG &= ~( ONE << GPT_INTEN_BIT_POSITION ) ;    
          }
          else if(GPT_16_OR_32_BIT_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_16_OR_32_BIT_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_0_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_1_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_2_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_3_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_4_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else if(GPT_32_OR_64_BIT_WIDE_TIMER_5_ID ==  Gpt_ConfigChannels_Ptr[Channel].ChannelID)
          {
                /* Will be configured in next SW releases */
          }
          else
          {
                /* Do Nothing */
          } 
    }
    else
    {
        /* Do Nothing */
    }
}

#endif 

/*******************************************************************************
* Service Name: Gpt_CalledBySystickISR
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: This function is called when Systick interrupt is fired becasue 
*              we can't have our private resources to be accessed by other .c 
*              files so outside we call this function and here we access what is 
*              is needed
*******************************************************************************/
void Gpt_CalledBySystickISR(void)
{
    if( GPT_CH_MODE_ONESHOT == Gpt_ConfigChannels_Ptr[GPT_CONFIG_SYSTICK_INDEX].ChannelMode)
    {
        /* Mark the timer status as EXPIRED as the timer has finished counting */
        Gpt_ChannelStatusArray[GPT_CONFIG_SYSTICK_INDEX] = EXPIRED ; 
        
        /* Disable the SysTick Timer (ENABLE = 1) */
        SYSTICK_CTRL_REG &= ~( ONE << GPT_ENABLE_BIT_POSITION ) ; 
    }
    else if (GPT_CH_MODE_CONTINUOUS == Gpt_ConfigChannels_Ptr[GPT_CONFIG_SYSTICK_INDEX].ChannelMode)
    {
        /* Do Nothing*/
    }
    else 
    {
       /* Do Nothing*/
    }
    
    /* Check if the Call Back function has an address */
    if( NULL_PTR != (Gpt_ConfigChannels_Ptr[GPT_CONFIG_SYSTICK_INDEX].Gpt_Notification_Ptr) )
    {
        /* call the function in the scheduler using call-back concept */
        (*(Gpt_ConfigChannels_Ptr[GPT_CONFIG_SYSTICK_INDEX].Gpt_Notification_Ptr))();
    }
    else
    {
        /* Do Nothing */
    }
         
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */

}


   