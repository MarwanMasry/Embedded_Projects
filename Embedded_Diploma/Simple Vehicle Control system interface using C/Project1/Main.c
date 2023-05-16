/*
 * Main.c
 *
 *  Created on: Sep 10, 2021
 *      Author: marwan
 */


/* headers needed */
#include <stdio.h>
#include "Global_Variables.h"
#include "Project_Functions.h"


/*	Main Functions	*/

int main(void)
{

	/* Two lines to fix the print issues on Eclipse IDE */
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	do{
		//Printing every loop the list of Vehicle control system
		print_Vehicle_Control_system_List();

		//Taking Input from the user according to the above List
		taking_Input_VCS_List();

		switch(VCS_selection)
		{

		case 'a':
			{
				//Turing on the Engine of the Vehicle as soon as you turn it on
				My_Vehicle.Engine = ON;

				do{
				//printing the Menu of Sensor Set
				Print_Sensors_set_menu();
				//Taking Input from the user according to the above List
				taking_Input_SS_Menu();

				switch(SS_selection)
				{
				case 'a':
					//Turing OFF the Engine of the Vehicle as soon as you turn it off
					My_Vehicle.Engine = OFF;
					printf("Turning off the engine \n");
					break;

				case 'b':
					processing_traffic_light_color();
					break;

				case 'c':
					Processing_Room_Temperature_Data();
					break;

				// If the the macros in Global_Variables.h is 1 then we can have Engine Temperature option
				#if  WITH_ENGINE_TEMP_CONTROLLER == 1
				case 'd':
					Processing_Engine_Temperature_Data();
					break;
				#endif


				default:
					//In case user entered any input rather than a,b,c
					printf("You entered undefined input ,Try again..\n");
					break;
				}

				}while(SS_selection != 'a');
			}
			break;

		case 'b':
			//Turing OFF the Engine of the Vehicle as soon as you turn it off
			My_Vehicle.Engine = OFF;
			printf("Turning off the vehicle engine \n");
			break;

		case 'c':
			printf("Quitting The System,Goodbye.....");
			break;

		default:
			//In case user entered any input rather than a,b,c
			printf("You entered undefined input ,Try again..\n");
			break;
		}


	}while( VCS_selection !='c');  //Exists only if the user choose C. Quit the program


	return 0;
}

