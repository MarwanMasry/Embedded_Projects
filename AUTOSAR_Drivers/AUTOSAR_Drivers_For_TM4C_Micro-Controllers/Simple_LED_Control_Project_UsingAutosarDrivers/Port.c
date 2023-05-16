 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Port.h"
/* All Microcontroller Registers need for Port Driver */
#include "Port_Registers.h"  

/* Include Det module only in case the development are enabled */
#if (PORT_DEV_ERROR_DETECT == STD_ON) 

/* AUTOSAR  Det Module */
#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif   
   
/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/
STATIC const Port_ConfigPin * Port_Channels_Ptr = NULL_PTR;   
STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;   

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
   
/******************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
*******************************************************************************/
void Port_Init
( 
    const Port_ConfigType* ConfigPtr 
)
{
         boolean error = FALSE;
         uint8 i = ZERO;
         /* point to the required Port Registers base address */
         volatile uint32 *PortBaseRegister_Ptr = NULL_PTR; 
         volatile uint32 delay = 0;
 
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)

        /* check if the input configuration pointer is not a NULL_PTR */
        if( NULL_PTR == ConfigPtr)
        {
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_INIT_SID,
                PORT_E_PARAM_CONFIG
            );            
            error = TRUE;
        }
        else
        {
            /* Do Nothing */        
        }
        
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
          
	if(FALSE == error)
        {
            /*
            * Set the module state to initialized and point to the PB configuration
            * structure using a global pointer. This global pointer is global to be
            * used by other functions to read the PB configuration structures.
            */
            PORT_Status      = PORT_INITIALIZED;
            /* address of the first Channels structure --> Channels[0] */
            Port_Channels_Ptr = ConfigPtr->channels;
            
            /*
            *  Loop through all the configured pin and configure them according
            *  to PB configuration structure.
            */
            for( i = ZERO ; i < PORT_CONFIGURED_CHANNLES ; i++ )
            {
                /* Get the Port base address according to the port number */
                 switch(Port_Channels_Ptr[i].port_num)
                {
                    case  PORT_PORTA_ID:
                             /* PORTA Base Address */
                             PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                             break;
                             
                    case  PORT_PORTB_ID:
                            /* PORTB Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                             break;
                             
                    case  PORT_PORTC_ID:
                            /* PORTC Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                            break;
                            
                    case  PORT_PORTD_ID:
                            /* PORTD Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                            break;
                            
                    case  PORT_PORTE_ID:
                            /* PORTE Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                            break;
                            
                    case  PORT_PORTF_ID:
                           /* PORTF Base Address */
                           PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                           break;
                           
                    default:
                            ;/* Do Nothing */
                }
                
                /* Enable clock for PORT and allow time for clock to start*/
                SYSCTL_REGCGC2_REG |= (1<<Port_Channels_Ptr[i].port_num);
                delay = SYSCTL_REGCGC2_REG;

                /* If we configure PC0 to PC3 we do nothing as this is JTAG Pins */
                if( (PORT_PORTC_ID == Port_Channels_Ptr[i].port_num) && (PORT_PIN3_ID >= Port_Channels_Ptr[i].pin_num) )
                {
                    /* Do Nothing ...  this is the JTAG pins */
                }                
                 /* If we configure PD7 or PF0 We need to Unlock Them */
                else if( ((PORT_PORTD_ID == Port_Channels_Ptr[i].port_num) && (PORT_PIN7_ID == Port_Channels_Ptr[i].pin_num)) \
                 || ((PORT_PORTF_ID == Port_Channels_Ptr[i].port_num) && (PORT_PIN0_ID == Port_Channels_Ptr[i].pin_num)) )
                {
                    /* Unlock the GPIOCR register */  
                    *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_LOCK_REG_OFFSET) = PORT_UNLOCK_VALUE;
                    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                    SET_BIT 
                    ( 
                        *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_COMMIT_REG_OFFSET), 
                        (Port_Channels_Ptr[i].pin_num) 
                     );  
                }
                else
                {
                    /* Do Nothing ... No need to unlock the commit register for this pin */
                }
                
                /* configure Any Pin except PC0 to PC3  */
                if( !((PORT_PORTC_ID == Port_Channels_Ptr[i].port_num) && (PORT_PIN3_ID >= Port_Channels_Ptr[i].pin_num)) )
                {      
                    /* Configure pin as input in case of default ,Input direction and ADC Mode */
                    if( (PORT_PIN_IN == Port_Channels_Ptr[i].pin_direction)\
                    || (PORT_DEFAULT_DIRECTION == Port_Channels_Ptr[i].pin_direction)\
                    || (PORT_PIN_MODE_ADC == Port_Channels_Ptr[i].pin_mode)  )
                    {
                        /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                         );            
                        
                        if( PULL_UP == Port_Channels_Ptr[i].resistor_setup )
                        {
                            /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                            SET_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_PULL_UP_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                            );       
                        }
                        else if( PULL_DOWN == Port_Channels_Ptr[i].resistor_setup)
                        {
                          /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                            SET_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_PULL_DOWN_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                            );    
                        }
                        else
                        {
                             /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                            CLEAR_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_PULL_UP_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                            ); 
                            /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                            CLEAR_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_PULL_DOWN_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                            );   
                        }
                    }
                    /* Configure pin as output in case of output direction */
                    else if( PORT_PIN_OUT == Port_Channels_Ptr[i].pin_direction )
                    {
                         /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                        SET_BIT
                        (
                           *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                          (Port_Channels_Ptr[i].pin_num) 
                         );               
                        
                        if(Port_Channels_Ptr[i].initial_value == STD_HIGH)
                        {
                            /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                            SET_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DATA_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                             );         
                        }
                        else
                        {
                            /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                            CLEAR_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DATA_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                             );        
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                    
                                    
                    /* Set the PMCx bits for this pin according to the mode of the configured Pin */
                    *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET) =\
                                  (*(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET)\
                                & (~(CLEAR_PCTL_BITS_MUSK << ((Port_Channels_Ptr[i].pin_num) * FOUR))) )\
                                | ((Port_Channels_Ptr[i].pin_mode) << ((Port_Channels_Ptr[i].pin_num) * FOUR));                                   

                    
                    if( (PORT_PIN_MODE_DIO ==  Port_Channels_Ptr[i].pin_mode)\
                      ||(PORT_PIN_MODE_DEFAULT ==  Port_Channels_Ptr[i].pin_mode) ) 
                    {
                        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        SET_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );
                        
                        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                         );
                            
                        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );

                    }
                    else if(PORT_PIN_MODE_ADC == Port_Channels_Ptr[i].pin_mode)
                    {
                        /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );
                        
                        /* Sit the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        SET_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                         );                    
                            
                        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );

                         /* Clear the PMCx bits for this pin  */
                        *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET) &= \
                                                                ~(CLEAR_PCTL_BITS_MUSK << ((Port_Channels_Ptr[i].pin_num) * FOUR));
                    
                    }
                    else if ( (PORT_PIN_MODE_1 <= Port_Channels_Ptr[i].pin_mode)\
                           && (PORT_PIN_MODE_14 >= Port_Channels_Ptr[i].pin_mode))
                    {
                        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        SET_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );
                        
                        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        CLEAR_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                         );
                            
                        /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        SET_BIT
                        (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                            (Port_Channels_Ptr[i].pin_num)
                        );
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
	}
        else
        {
            /* Do Nothing */
        }

}
   
/******************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
*******************************************************************************/  
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

void Port_SetPinDirection
(
    Port_PinType Pin, 
    Port_PinDirectionType Direction
)
{
         boolean error = FALSE;
         /* point to the required Port Registers base address */
         volatile uint32 *PortBaseRegister_Ptr = NULL_PTR;
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)

        /* Check if this function is called and the module is uninitialized */
        if( PORT_NOT_INITIALIZED == PORT_Status)
        {
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID,
                PORT_E_UNINIT
            );            
            error = TRUE;
        }
        else
        {
            /* Do Nothing */        
        }
        
        /* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNLES <= Pin)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID,
                PORT_E_PARAM_PIN
            );            
            error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        /* The service called when the mode is unchangeable */
	if (CANNOT_CHANAGE_PIN_DIRECTION == Port_Channels_Ptr[Pin].direction_changeability)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_DIRECTION_SID,
                PORT_E_DIRECTION_UNCHANGEABLE
            );            
            error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
          
	if(FALSE == error)
        {            
            /* Get the Port base address according to the port number */
            switch(Port_Channels_Ptr[Pin].port_num)
            {
                case  PORT_PORTA_ID:
                        /* PORTA Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTB_ID:
                        /* PORTB Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTC_ID:
                        /* PORTC Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTD_ID:
                        /* PORTD Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                        break;
                
                case  PORT_PORTE_ID:
                        /* PORTE Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTF_ID:
                        /* PORTF Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                        break;
                
                default:
                        ;/* Do Nothing */
            }
            
            /* configure Any Pin except PC0 to PC3  */
            if( !((PORT_PORTC_ID == Port_Channels_Ptr[Pin].port_num) && (PORT_PIN3_ID >= Port_Channels_Ptr[Pin].pin_num)))
            {      
                /* Configure pin as input in case of default ,Input direction and ADC Mode */
                if( (PORT_PIN_IN == Direction )\
                 || (PORT_DEFAULT_DIRECTION ==Direction)\
                 || (PORT_PIN_MODE_ADC == Direction)  )
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    CLEAR_BIT
                    (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                            (Port_Channels_Ptr[Pin].pin_num)
                    );            
                }
                /* Configure pin as output in case of output direction */
                else if(PORT_PIN_OUT == Direction)
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT
                    (
                            *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                            (Port_Channels_Ptr[Pin].pin_num) 
                    );               
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
        else
        {
            /* Do Nothing */
        }
}

#endif
/*******************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
*******************************************************************************/   
 void Port_RefreshPortDirection(void)
 {
         boolean error = FALSE;
         uint8 i = ZERO;
         /* point to the required Port Registers base address */
         volatile uint32 *PortBaseRegister_Ptr = NULL_PTR;
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)

        /* Check if this function is called and the module is uninitialized */
        if( PORT_NOT_INITIALIZED == PORT_Status)
        {
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_REFRESH_PORT_DIRECTION_SID,
                PORT_E_UNINIT
            );            
            error = TRUE;
        }
        else
        {
            /* Do Nothing */        
        }
        
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
          
	if(FALSE == error)
        {
            for( i = ZERO ; i < PORT_CONFIGURED_CHANNLES ; i++ )
            {
                /* Get the Port base address according to the port number */
                 switch(Port_Channels_Ptr[i].port_num)
                {
                    case  PORT_PORTA_ID:
                             /* PORTA Base Address */
                             PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                             break;
                             
                    case  PORT_PORTB_ID:
                            /* PORTB Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                             break;
                             
                    case  PORT_PORTC_ID:
                            /* PORTC Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                            break;
                            
                    case  PORT_PORTD_ID:
                            /* PORTD Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                            break;
                            
                    case  PORT_PORTE_ID:
                            /* PORTE Base Address */
                            PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                            break;
                            
                    case  PORT_PORTF_ID:
                           /* PORTF Base Address */
                           PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                           break;
                           
                    default:
                            ;/* Do Nothing */
                }
                
                /* configure Any Pin except PC0 to PC3  */
                if( !((PORT_PORTC_ID == Port_Channels_Ptr[i].port_num) && (PORT_PIN3_ID >= Port_Channels_Ptr[i].pin_num)))
                {
                  /* Refresh only the pins that is configured as unchangable */
                  if (CANNOT_CHANAGE_PIN_DIRECTION == Port_Channels_Ptr[i].direction_changeability)
                  {
                        /* Configure pin as input in case of default ,Input direction and ADC Mode */
                        if( (PORT_PIN_IN == Port_Channels_Ptr[i].pin_direction)\
                        || (PORT_DEFAULT_DIRECTION == Port_Channels_Ptr[i].pin_direction)\
                        || (PORT_PIN_MODE_ADC == Port_Channels_Ptr[i].pin_mode)  )
                        {
                            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                            CLEAR_BIT
                            (
                                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                                (Port_Channels_Ptr[i].pin_num)
                             );            
                        }
                        /* Configure pin as output in case of output direction */
                        else if(PORT_PIN_OUT ==  Port_Channels_Ptr[i].pin_direction)
                        {
                             /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                            SET_BIT
                            (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIR_REG_OFFSET),
                              (Port_Channels_Ptr[i].pin_num) 
                             );               
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

 /******************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version
*                   information of this module
* Return value: None
* Description: Returns the version information of this module.
*******************************************************************************/   
#if (PORT_VERSION_INFO_API == STD_ON) 
 
void Port_GetVersionInfo
( 
    Std_VersionInfoType* versioninfo
)
{
        boolean error = FALSE;
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_GET_VERSION_INFO_SID,
                PORT_E_PARAM_POINTER
            );
            error = TRUE;
	}
	else
        {
            /* Do Nothing */
        }
        
        /* Check if this function is called and the module is uninitialized */
        if( PORT_NOT_INITIALIZED == PORT_Status)
        {
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_GET_VERSION_INFO_SID,
                PORT_E_UNINIT
            );            
            error = TRUE;
        }
        else
        {
            /* Do Nothing */        
        }
        
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
          
	if(FALSE == error)
        {
            /* Copy the vendor Id */
            versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
            /* Copy the module Id */
            versioninfo->moduleID = (uint16)PORT_MODULE_ID;
            /* Copy Software Major Version */
            versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
            /* Copy Software Minor Version */
            versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
            /* Copy Software Patch Version */
            versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
        else
        {
            /* Do Nothing */
        }
}

#endif
/******************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
                   Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
*******************************************************************************/   
#if (PORT_SET_PIN_MODE_API == STD_ON)

void Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
)
{
         boolean error = FALSE;
         /* point to the required Port Registers base address */
         volatile uint32 *PortBaseRegister_Ptr = NULL_PTR;
         
#if (PORT_DEV_ERROR_DETECT == STD_ON)

        /* Check if this function is called and the module is uninitialized */
        if( PORT_NOT_INITIALIZED == PORT_Status)
        {
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
                PORT_E_UNINIT
            );            
            error = TRUE;
        }
        else
        {
            /* Do Nothing */        
        }
        
        /* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNLES <= Pin)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
                PORT_E_PARAM_PIN
            );            
            error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        /* Port Pin Mode passed not valid */
	if (PORT_PIN_MODE_ADC < Mode)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
                PORT_E_PARAM_INVALID_MODE
            );            
            error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
        /* The service called when the mode is unchangeable */
	if (CANNOT_CHANAGE_PIN_MODE == Port_Channels_Ptr[Pin].mode_changeability)
	{
            /* Report to DET  */
            Det_ReportError
            (
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
		PORT_SET_PIN_MODE_SID,
                PORT_E_MODE_UNCHANGEABLE
            );            
            error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
          
	if(FALSE == error)
        {
                    /* Get the Port base address according to the port number */
            switch(Port_Channels_Ptr[Pin].port_num)
            {
                case  PORT_PORTA_ID:
                        /* PORTA Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTB_ID:
                        /* PORTB Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTC_ID:
                        /* PORTC Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTD_ID:
                        /* PORTD Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                        break;
                
                case  PORT_PORTE_ID:
                        /* PORTE Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                        break;
                
                case  PORT_PORTF_ID:
                        /* PORTF Base Address */
                        PortBaseRegister_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                        break;
                
                default:
                        ;/* Do Nothing */
            }
            
            /* configure Any Pin except PC0 to PC3  */
            if( !((PORT_PORTC_ID == Port_Channels_Ptr[Pin].port_num) && (PORT_PIN3_ID >= Port_Channels_Ptr[Pin].pin_num)))
            {   
                /* Set the PMCx bits for this pin according to the mode of the configured Pin */
                *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET) =\
                (*(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET)\
                                & (~(CLEAR_PCTL_BITS_MUSK << ((Port_Channels_Ptr[Pin].pin_num) * FOUR))) )\
                                | ((Mode) << ((Port_Channels_Ptr[Pin].pin_num) * FOUR));                                   
	
                /* In case of Default mode or DIO mode enter */
                if( (PORT_PIN_MODE_DIO == Mode)\
                 || (PORT_PIN_MODE_DEFAULT == Mode ) ) 
                {
                        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        SET_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        CLEAR_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        CLEAR_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                }
                else if(PORT_PIN_MODE_ADC == Mode)
                {
                        /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        CLEAR_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Sit the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        SET_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );                    
                
                        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        CLEAR_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Clear the PMCx bits for this pin  */
                        *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_CTL_REG_OFFSET) &= \
                                        ~(CLEAR_PCTL_BITS_MUSK << ((Port_Channels_Ptr[Pin].pin_num) * FOUR));
                
                }
                else if ( (PORT_PIN_MODE_1 <= Mode)\
                       && (PORT_PIN_MODE_14 >= Mode))
                {
                        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        SET_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        CLEAR_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
                
                        /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */ 
                        SET_BIT
                        (
                               *(volatile uint32 *)((volatile uint8 *)PortBaseRegister_Ptr + PORT_ALT_FUNC_REG_OFFSET),
                               (Port_Channels_Ptr[Pin].pin_num)
                        );
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
        else 
        {
            /* Do Nothing */
        }
}

#endif   