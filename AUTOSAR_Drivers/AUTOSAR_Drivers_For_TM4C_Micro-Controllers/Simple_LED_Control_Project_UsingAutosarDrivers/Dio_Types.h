 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Types.h
 *
 * Description: Header file that has all the needed type declerations 
 *              - Dio Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define DIO_TYPES_SW_MAJOR_VERSION              (1U)
#define DIO_TYPES_SW_MINOR_VERSION              (0U)
#define DIO_TYPES_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_TYPES_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_TYPES_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_TYPES_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and DIO Types */
#if ((DIO_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (DIO_TYPES_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (DIO_TYPES_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
   
/* DIO Pre-Compile Configuration Header file */
#include "Dio_Cfg.h"

/* AUTOSAR Version checking between DIO_Cfg.h and Dio_Types.h files */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between DIO_Cfg.h and Dio_Types.h files */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_TYPES_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_TYPES_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif
   

/*******************************************************************************
 *                             Types Deceleration	                       *
 *******************************************************************************/   
/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

/* Structure for Dio_ChannelGroup */
typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;

typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	Dio_PortType Port_Num;
	/* Member contains the ID of the Channel*/
	Dio_ChannelType Ch_Num;
}Dio_ConfigChannel;

/*
 * Description    : Data Structure required for initializing the Dio Driver.
 *  
 * Important Note : The #if used bellow is a must because if any of these array 
 *                  have a size of zero you will have error :
 *                  [ Error[Pe070]: incomplete type is not allowed ]
 *                  After search, I think this error depends on IAR compiler 
 *                  it doesn't allow a  array of size zero as a structure member
 *                  other compilers allows it like GCC
 */
typedef struct
{
  #if   (DIO_CONFIGURED_CHANNLES != ZERO)
	 Dio_ConfigChannel       Channels[DIO_CONFIGURED_CHANNLES];
  #endif
  
  #if   (DIO_CONFIGURED_PORTS != ZERO)      
         Dio_PortType            Ports[DIO_CONFIGURED_PORTS];
  #endif
  
  #if   (DIO_CONFIGURED_GROUPS != ZERO)           
         Dio_ChannelGroupType    ChannelGroups[DIO_CONFIGURED_GROUPS];
  #endif
         
} Dio_ConfigType;

/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* ID's of TM4C123GH6PM Ports */
#define DIO_PORTA_ID                          (Dio_PortType)0
#define DIO_PORTB_ID                          (Dio_PortType)1
#define DIO_PORTC_ID                          (Dio_PortType)2
#define DIO_PORTD_ID                          (Dio_PortType)3
#define DIO_PORTE_ID                          (Dio_PortType)4
#define DIO_PORTF_ID                          (Dio_PortType)5 
   


#endif /* DIO_TYPES_H_ */
