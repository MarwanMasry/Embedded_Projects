/*
 * Project_Functions.c
 *
 *  Created on: Sep 10, 2021
 *      Author: marwan
 */



/* headers needed */
#include <stdio.h>
#include <ctype.h>
#include "Global_Variables.h"


/* Project Functions Implementation */

////////////////////////////////////////////////////////////////////////////////

void print_Vehicle_Control_system_List(void)
{
	//Doesn't clear Eclipse console clear only when running the program in CMD
//	system("cls");

	printf("\n/////////////////////////////////////////////////////////////////\n\n");
	printf("<Vehicle Control System List>\n");
	printf("a. Turn on the vehicle engine \n");
	printf("b. Turn off the vehicle engine \n");
	printf("c. Quit the system \n\n");
}

////////////////////////////////////////////////////////////////////////////////

void taking_Input_VCS_List(void)
{
	printf("Please enter your selection [a or b or c] ?  ");
	scanf(" %c",&VCS_selection);

	//If the user enter a character which is a capital make it small character
	//and make all my processing on small characters only
	VCS_selection = tolower(VCS_selection);
}


////////////////////////////////////////////////////////////////////////////////

void Print_Sensors_set_menu(void)
{
	printf("\n/////////////////////////////////////////////////////////////////\n\n");
	printf("<Sensors Set Menu>\n");
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color \n");
	printf("c. Set the room temperature (Temperature Sensor) \n");

	// If the the macros in Global_Variables.h is 1 then we can have Engine Temperature option
	#if  WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("d. Set the engine temperature (Engine Temperature Sensor) \n\n");
	#endif
}


////////////////////////////////////////////////////////////////////////////////


void taking_Input_SS_Menu(void)
{
	// If the the macros in Global_Variables.h is 1 then display a or b or c or d , If not print a or b or c
	#if  WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("Please enter your selection [a or b or c or d] ?  ");
	#else
	printf("Please enter your selection [a or b or c ] ?  ");
	#endif

	scanf(" %c",&SS_selection);

	//If the user enter a character which is a capital make it small character
	//and make all my processing on small characters only
	SS_selection = tolower(SS_selection);
}



////////////////////////////////////////////////////////////////////////////////

void check_Vehicle_Speed(void)
{
	//here we check if the speed of the vechile is 30 we turn down the AC and increase the room , engine TEMP
	if(My_Vehicle.speed == 30)
	{
		if(My_Vehicle.AC == OFF)
			My_Vehicle.AC = ON;

		My_Vehicle.room_temp = My_Vehicle.room_temp*(5.0/4) + 1;

		// If the the macros in Global_Variables.h is 1 then we can have Engine Temperature option
		#if  WITH_ENGINE_TEMP_CONTROLLER == 1

		if(My_Vehicle.Engine_Temp_Controller == OFF)
				My_Vehicle.Engine_Temp_Controller = ON;

		My_Vehicle.engine_temp = My_Vehicle.engine_temp*(5.0/4) + 1;

		#endif

	}
}

////////////////////////////////////////////////////////////////////////////////

void Display_Vehicle_State(void)
{
	printf("<Vehicle State>\n");
	printf("Engine state : %s \n",My_Vehicle.Engine?"ON":"OFF");
	printf("AC : %s \n",My_Vehicle.AC?"ON":"OFF");
	printf("Vehicle Speed : %lf KM/H \n",My_Vehicle.speed);
	printf("Room Temperature : %lf C\n",My_Vehicle.room_temp);

	// If the the macros in Global_Variables.h is 1 then we can have Engine Temperature option
	#if  WITH_ENGINE_TEMP_CONTROLLER == 1

	printf("Engine Temperature Controller State. : %s \n",My_Vehicle.Engine_Temp_Controller?"ON":"OFF");
	printf("Engine Temperature : %lf C\n\n",My_Vehicle.engine_temp);

	#endif
}


////////////////////////////////////////////////////////////////////////////////

void processing_traffic_light_color(void)
{
	char traffic_light_colour;

	//We will loop until the user enter only one of three options G,Y,R
	do{

		printf("\nPlease Enter the Traffic Light Color [G or Y or R] ? ");
		scanf(" %c",&traffic_light_colour);

		//If the user enter a character which is a capital make it small character
		//and make all my processing on small characters only
		traffic_light_colour = tolower(traffic_light_colour);

		switch(traffic_light_colour)
		{
		case'g':
			My_Vehicle.speed=100;
			break;

		case'y':
			My_Vehicle.speed=30;
			break;

		case'r':
			My_Vehicle.speed=0;
			break;
		default:
			//In case user entered any input rather than g,y,r
			printf("You entered undefined input ,Try again..\n");
			break;
		}

	//Breaks out of the loop if the user enter the g Or y Or r
	}while(traffic_light_colour!='g' && traffic_light_colour!='r' && traffic_light_colour!='y' );

	//Before display ,We need to check if the speed is equal to 30 because certain processing is needed
	check_Vehicle_Speed();
	Display_Vehicle_State();
}



////////////////////////////////////////////////////////////////////////////////

void Processing_Room_Temperature_Data(void)
{
	//We will loop until the user enter a positive temperature NO negative numbers allowed
	do{
			printf("\nPlease Enter the Room Temperature : ");
			scanf(" %lf",&My_Vehicle.room_temp);

			//check if Room TEMP <10  or Room TEMP >10
			if( (My_Vehicle.room_temp <10 && My_Vehicle.room_temp > 0) || My_Vehicle.room_temp >30 )
			{
				My_Vehicle.AC = ON;
				My_Vehicle.room_temp = 20;
			}
			else
			{
				//check if the input is negative number so that we can loop untill positive number is given
				if(My_Vehicle.room_temp > 0)
				{
					My_Vehicle.AC = OFF;
				}
			}

			//check if the input is negative number so that we can loop untill positive number is given
			if(My_Vehicle.room_temp < 0)
			{
				//In case user entered any input rather than  a negative temperature
				printf("You entered undefined input ,Try again..\n");
			}

		//Breaks out of the loop if the user enter a positive temperature
		}while(My_Vehicle.room_temp < 0 );

		//Before display ,We need to check if the speed is equal to 30 because certain processing is needed
		check_Vehicle_Speed();
		Display_Vehicle_State();

}


////////////////////////////////////////////////////////////////////////////////

void Processing_Engine_Temperature_Data(void)
{
	//We will loop until the user enter a positive temperature NO negative numbers allowed
	do{
				printf("\nPlease Enter the Engine Temperature : ");
				scanf(" %lf",&My_Vehicle.engine_temp);

				//check if Engine TEMP <100  or Engine TEMP >150
				if( (My_Vehicle.engine_temp <100 && My_Vehicle.engine_temp > 0) || My_Vehicle.engine_temp >150 )
				{
					My_Vehicle.Engine_Temp_Controller = ON;
					My_Vehicle.engine_temp = 125;
				}
				else
				{
					//check if the input is negative number so that we can loop untill positive number is given
					if(My_Vehicle.engine_temp > 0)
					{
						My_Vehicle.Engine_Temp_Controller = OFF;
					}
				}

				//check if the input is negative number so that we can loop untill positive number is given
				if(My_Vehicle.engine_temp < 0)
				{
					//In case user entered any input rather than  a negative temperature
					printf("You entered undefined input ,Try again..\n");
				}

			//Breaks out of the loop if the user enter a positive temperature
			}while(My_Vehicle.engine_temp < 0 );

		//Before display ,We need to check if the speed is equal to 30 because certain processing is needed
			check_Vehicle_Speed();
			Display_Vehicle_State();
}


////////////////////////////////////////////////////////////////////////////////
