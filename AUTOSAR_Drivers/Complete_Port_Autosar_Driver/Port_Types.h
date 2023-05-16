 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Types.h
 *
 * Description: Header file that has all the needed type declerations 
 *              - Port Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define PORT_TYPES_SW_MAJOR_VERSION              (1U)
#define PORT_TYPES_SW_MINOR_VERSION              (0U)
#define PORT_TYPES_SW_PATCH_VERSION              (0U)
 
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_TYPES_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/      
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Types */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (PORT_TYPES_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (PORT_TYPES_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
   
/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_TYPES_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_TYPES_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif   
   
/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* ID's of TM4C123GH6PM Ports */
#define PORT_PORTA_ID                          (Port_PinType)0
#define PORT_PORTB_ID                          (Port_PinType)1
#define PORT_PORTC_ID                          (Port_PinType)2
#define PORT_PORTD_ID                          (Port_PinType)3
#define PORT_PORTE_ID                          (Port_PinType)4
#define PORT_PORTF_ID                          (Port_PinType)5 

/* Port ID's of TM4C123GH6PM Pins */
#define PORT_PIN0_ID                           (uint8)0      
#define PORT_PIN1_ID                           (uint8)1
#define PORT_PIN2_ID                           (uint8)2
#define PORT_PIN3_ID                           (uint8)3
#define PORT_PIN4_ID                           (uint8)4
#define PORT_PIN5_ID                           (uint8)5
#define PORT_PIN6_ID                           (uint8)6
#define PORT_PIN7_ID                           (uint8)7
  
/* Unlocking value for PORT F,D,C */
#define PORT_UNLOCK_VALUE                      (uint32)0x4C4F434B   
   
/* Defines needed so select if the pin direction is changeable or not */
#define CAN_CHANAGE_PIN_DIRECTION             (uint8)1 
#define CANNOT_CHANAGE_PIN_DIRECTION          (uint8)0 

/* Defines needed so select if the pin mode is changeable or not */   
#define CAN_CHANAGE_PIN_MODE                  (uint8)1 
#define CANNOT_CHANAGE_PIN_MODE               (uint8)0

/* Defines needed to support all modes of the Pins */
#define PORT_PIN_MODE_DEFAULT                  (Port_PinModeType)0
#define PORT_PIN_MODE_DIO                      (Port_PinModeType)0
#define PORT_PIN_MODE_1                        (Port_PinModeType)1
#define PORT_PIN_MODE_2                        (Port_PinModeType)2
#define PORT_PIN_MODE_3                        (Port_PinModeType)3
#define PORT_PIN_MODE_4                        (Port_PinModeType)4
#define PORT_PIN_MODE_5                        (Port_PinModeType)5
#define PORT_PIN_MODE_6                        (Port_PinModeType)6
#define PORT_PIN_MODE_7                        (Port_PinModeType)7
#define PORT_PIN_MODE_8                        (Port_PinModeType)8
#define PORT_PIN_MODE_9                        (Port_PinModeType)9
#define PORT_PIN_MODE_10                       (Port_PinModeType)10
#define PORT_PIN_MODE_11                       (Port_PinModeType)11
#define PORT_PIN_MODE_12                       (Port_PinModeType)12
#define PORT_PIN_MODE_13                       (Port_PinModeType)13
#define PORT_PIN_MODE_14                       (Port_PinModeType)14
#define PORT_PIN_MODE_ADC                      (Port_PinModeType)15

/* Defines needed in configurations */
#define NO_INITIAL_VALUE                       (uint8)2
#define CLEAR_PCTL_BITS_MUSK                   (uint32)0x0000000F
#define FOUR                                   (uint8)4   
      
/*******************************************************************************
 *                             Types Deceleration	                       *
 *******************************************************************************/  
/* Data type for the symbolic name of a port pin. */
typedef uint8  Port_PinType;

/* Data type for Different port pin modes. */
typedef uint8 Port_PinModeType;

/* Possible directions of a port pin. */
typedef enum 
{
   PORT_PIN_IN , PORT_PIN_OUT ,PORT_DEFAULT_DIRECTION
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    INTERNAL_RESISTOR_OFF  ,PULL_UP,PULL_DOWN
}Port_InternalResistor;


/* Description: Structure to configure each individual PIN:
 *  1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *  2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. do you want the direction of your pin to be changeable in runtime or not
 *  5. the mode of the pin --> DIO , Analog , Mode 1 ... Mode 14
 *  6. do you want the Mode of your pin to be changeable in runtime or not
 *  7. the internal resistor --> Disable, Pull up or Pull down
 *  8. the initial value in case of the pin to be output --> High or LOW
 */
typedef struct 
{
    uint8                        port_num; 
    uint8                        pin_num; 
    Port_PinDirectionType        pin_direction;
    uint8                        direction_changeability;
    Port_PinModeType             pin_mode;
    uint8                        mode_changeability;
    Port_InternalResistor        resistor_setup;
    uint8                        initial_value;
}Port_ConfigPin;

/* Type of the external data structure containing the initialization data for this module. */
typedef struct 
{
    Port_ConfigPin channels[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;
   
#endif /* PORT_TYPES_H_ */
