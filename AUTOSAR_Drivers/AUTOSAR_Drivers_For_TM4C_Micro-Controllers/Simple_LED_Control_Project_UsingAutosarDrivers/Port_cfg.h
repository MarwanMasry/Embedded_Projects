 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller 
 *              - Port Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                          Pre-Compile Configuration                          *
 *******************************************************************************/
/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                   (STD_ON)

/* Pre-processor switch to enable / disable the use of the function Port_SetPinDirection(). */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-processor switch to enable / disable the use of the function Port_SetPinMode(). */   
#define PORT_SET_PIN_MODE_API                   (STD_ON)   

/* Pre-processor switch to enable / disable the API to read out the modules version information */   
#define PORT_VERSION_INFO_API                   (STD_ON)  
      
/* Number of the configured Channels */
#define PORT_CONFIGURED_CHANNLES                (43U)
   

/* Channel Index in the array of structures in Port_PBcfg.c */
#define PORT_CONFIG_PA0_INDEX                           (uint8)0
#define PORT_CONFIG_PA1_INDEX                           (uint8)1
#define PORT_CONFIG_PA2_INDEX                           (uint8)2
#define PORT_CONFIG_PA3_INDEX                           (uint8)3
#define PORT_CONFIG_PA4_INDEX                           (uint8)4
#define PORT_CONFIG_PA5_INDEX                           (uint8)5
#define PORT_CONFIG_PA6_INDEX                           (uint8)6
#define PORT_CONFIG_PA7_INDEX                           (uint8)7

#define PORT_CONFIG_PB0_INDEX                           (uint8)8
#define PORT_CONFIG_PB1_INDEX                           (uint8)9
#define PORT_CONFIG_PB2_INDEX                           (uint8)10
#define PORT_CONFIG_PB3_INDEX                           (uint8)11
#define PORT_CONFIG_PB4_INDEX                           (uint8)12
#define PORT_CONFIG_PB5_INDEX                           (uint8)13
#define PORT_CONFIG_PB6_INDEX                           (uint8)14
#define PORT_CONFIG_PB7_INDEX                           (uint8)15

#define PORT_CONFIG_PC0_INDEX                           (uint8)16
#define PORT_CONFIG_PC1_INDEX                           (uint8)17
#define PORT_CONFIG_PC2_INDEX                           (uint8)18
#define PORT_CONFIG_PC3_INDEX                           (uint8)19
#define PORT_CONFIG_PC4_INDEX                           (uint8)20
#define PORT_CONFIG_PC5_INDEX                           (uint8)21
#define PORT_CONFIG_PC6_INDEX                           (uint8)22
#define PORT_CONFIG_PC7_INDEX                           (uint8)23

#define PORT_CONFIG_PD0_INDEX                           (uint8)24
#define PORT_CONFIG_PD1_INDEX                           (uint8)25
#define PORT_CONFIG_PD2_INDEX                           (uint8)26
#define PORT_CONFIG_PD3_INDEX                           (uint8)27
#define PORT_CONFIG_PD4_INDEX                           (uint8)28
#define PORT_CONFIG_PD5_INDEX                           (uint8)29
#define PORT_CONFIG_PD6_INDEX                           (uint8)30
#define PORT_CONFIG_PD7_INDEX                           (uint8)31

#define PORT_CONFIG_PE0_INDEX                           (uint8)32
#define PORT_CONFIG_PE1_INDEX                           (uint8)33
#define PORT_CONFIG_PE2_INDEX                           (uint8)34
#define PORT_CONFIG_PE3_INDEX                           (uint8)35
#define PORT_CONFIG_PE4_INDEX                           (uint8)36
#define PORT_CONFIG_PE5_INDEX                           (uint8)37

#define PORT_CONFIG_PF0_INDEX                           (uint8)38
#define PORT_CONFIG_LED1_CHANNEL_INDEX                  (uint8)39
#define PORT_CONFIG_PF2_INDEX                           (uint8)40
#define PORT_CONFIG_PF3_INDEX                           (uint8)41
#define PORT_CONFIG_SW1_CHANNEL_INDEX                   (uint8)42

   
/* Configured ID's of TM4C123GH6PM Ports */
#define PORT_CONFIG_PORT_A_PIN_0_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_1_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_2_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_3_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_4_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_5_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_6_PORT_NUM		PORT_PORTA_ID
#define PORT_CONFIG_PORT_A_PIN_7_PORT_NUM		PORT_PORTA_ID

#define PORT_CONFIG_PORT_B_PIN_0_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_1_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_2_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_3_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_4_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_5_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_6_PORT_NUM 		PORT_PORTB_ID
#define PORT_CONFIG_PORT_B_PIN_7_PORT_NUM 		PORT_PORTB_ID

#define PORT_CONFIG_PORT_C_PIN_0_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_1_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_2_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_3_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_4_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_5_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_6_PORT_NUM 		PORT_PORTC_ID
#define PORT_CONFIG_PORT_C_PIN_7_PORT_NUM 		PORT_PORTC_ID

#define PORT_CONFIG_PORT_D_PIN_0_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_1_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_2_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_3_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_4_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_5_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_6_PORT_NUM 		PORT_PORTD_ID
#define PORT_CONFIG_PORT_D_PIN_7_PORT_NUM 		PORT_PORTD_ID

#define PORT_CONFIG_PORT_E_PIN_0_PORT_NUM 		PORT_PORTE_ID
#define PORT_CONFIG_PORT_E_PIN_1_PORT_NUM 		PORT_PORTE_ID
#define PORT_CONFIG_PORT_E_PIN_2_PORT_NUM 		PORT_PORTE_ID
#define PORT_CONFIG_PORT_E_PIN_3_PORT_NUM 		PORT_PORTE_ID
#define PORT_CONFIG_PORT_E_PIN_4_PORT_NUM 		PORT_PORTE_ID
#define PORT_CONFIG_PORT_E_PIN_5_PORT_NUM 		PORT_PORTE_ID

#define PORT_CONFIG_PORT_F_PIN_0_PORT_NUM 		PORT_PORTF_ID
#define PORT_CONFIG_LED1_PORT_NUM                       PORT_PORTF_ID 
#define PORT_CONFIG_PORT_F_PIN_2_PORT_NUM 		PORT_PORTF_ID
#define PORT_CONFIG_PORT_F_PIN_3_PORT_NUM 		PORT_PORTF_ID
#define PORT_CONFIG_SW1_PORT_NUM                        PORT_PORTF_ID 

/* Configured Port ID's of TM4C123GH6PM Pins */
#define PORT_CONFIG_PORT_A_PIN_0_PIN_NUM		PORT_PIN0_ID
#define PORT_CONFIG_PORT_A_PIN_1_PIN_NUM		PORT_PIN1_ID
#define PORT_CONFIG_PORT_A_PIN_2_PIN_NUM		PORT_PIN2_ID
#define PORT_CONFIG_PORT_A_PIN_3_PIN_NUM		PORT_PIN3_ID
#define PORT_CONFIG_PORT_A_PIN_4_PIN_NUM		PORT_PIN4_ID
#define PORT_CONFIG_PORT_A_PIN_5_PIN_NUM		PORT_PIN5_ID
#define PORT_CONFIG_PORT_A_PIN_6_PIN_NUM		PORT_PIN6_ID
#define PORT_CONFIG_PORT_A_PIN_7_PIN_NUM		PORT_PIN7_ID

#define PORT_CONFIG_PORT_B_PIN_0_PIN_NUM 		PORT_PIN0_ID
#define PORT_CONFIG_PORT_B_PIN_1_PIN_NUM 		PORT_PIN1_ID
#define PORT_CONFIG_PORT_B_PIN_2_PIN_NUM 		PORT_PIN2_ID
#define PORT_CONFIG_PORT_B_PIN_3_PIN_NUM 		PORT_PIN3_ID
#define PORT_CONFIG_PORT_B_PIN_4_PIN_NUM 		PORT_PIN4_ID
#define PORT_CONFIG_PORT_B_PIN_5_PIN_NUM 		PORT_PIN5_ID
#define PORT_CONFIG_PORT_B_PIN_6_PIN_NUM 		PORT_PIN6_ID
#define PORT_CONFIG_PORT_B_PIN_7_PIN_NUM 		PORT_PIN7_ID

#define PORT_CONFIG_PORT_C_PIN_0_PIN_NUM 		PORT_PIN0_ID
#define PORT_CONFIG_PORT_C_PIN_1_PIN_NUM 		PORT_PIN1_ID
#define PORT_CONFIG_PORT_C_PIN_2_PIN_NUM 		PORT_PIN2_ID
#define PORT_CONFIG_PORT_C_PIN_3_PIN_NUM 		PORT_PIN3_ID
#define PORT_CONFIG_PORT_C_PIN_4_PIN_NUM 		PORT_PIN4_ID
#define PORT_CONFIG_PORT_C_PIN_5_PIN_NUM 		PORT_PIN5_ID
#define PORT_CONFIG_PORT_C_PIN_6_PIN_NUM 		PORT_PIN6_ID
#define PORT_CONFIG_PORT_C_PIN_7_PIN_NUM 		PORT_PIN7_ID

#define PORT_CONFIG_PORT_D_PIN_0_PIN_NUM 		PORT_PIN0_ID
#define PORT_CONFIG_PORT_D_PIN_1_PIN_NUM 		PORT_PIN1_ID
#define PORT_CONFIG_PORT_D_PIN_2_PIN_NUM 		PORT_PIN2_ID
#define PORT_CONFIG_PORT_D_PIN_3_PIN_NUM 		PORT_PIN3_ID
#define PORT_CONFIG_PORT_D_PIN_4_PIN_NUM 		PORT_PIN4_ID
#define PORT_CONFIG_PORT_D_PIN_5_PIN_NUM 		PORT_PIN5_ID
#define PORT_CONFIG_PORT_D_PIN_6_PIN_NUM 		PORT_PIN6_ID
#define PORT_CONFIG_PORT_D_PIN_7_PIN_NUM 		PORT_PIN7_ID

#define PORT_CONFIG_PORT_E_PIN_0_PIN_NUM 		PORT_PIN0_ID
#define PORT_CONFIG_PORT_E_PIN_1_PIN_NUM 		PORT_PIN1_ID
#define PORT_CONFIG_PORT_E_PIN_2_PIN_NUM 		PORT_PIN2_ID
#define PORT_CONFIG_PORT_E_PIN_3_PIN_NUM 		PORT_PIN3_ID
#define PORT_CONFIG_PORT_E_PIN_4_PIN_NUM 		PORT_PIN4_ID
#define PORT_CONFIG_PORT_E_PIN_5_PIN_NUM 		PORT_PIN5_ID

#define PORT_CONFIG_PORT_F_PIN_0_PIN_NUM 		PORT_PIN0_ID
#define PORT_CONFIG_LED1_CHANNEL_NUM                    PORT_PIN1_ID 
#define PORT_CONFIG_PORT_F_PIN_2_PIN_NUM 		PORT_PIN2_ID
#define PORT_CONFIG_PORT_F_PIN_3_PIN_NUM 		PORT_PIN3_ID
#define PORT_CONFIG_SW1_CHANNEL_NUM                     PORT_PIN4_ID 
   
#endif /* PORT_CFG_H_ */
