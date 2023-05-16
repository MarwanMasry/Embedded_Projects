/*
 * Global_Enums_Structs.h
 *
 *  Created on: Sep 10, 2021
 *      Author: marwan
 */

#ifndef GLOBAL_ENUMS_STRUCTS_H_
#define GLOBAL_ENUMS_STRUCTS_H_


/*	Global Enumeration-Structures Deceleration	*/

//Global Enumeration
	typedef enum
	{
		OFF,ON
	}bool;

//Global Structure
	typedef struct
	{
		bool Engine ;
		bool AC ;
		bool Engine_Temp_Controller ;

		double speed ;
		double room_temp ;
		double engine_temp ;
	}vehicle;




#endif /* GLOBAL_ENUMS_STRUCTS_H_ */
