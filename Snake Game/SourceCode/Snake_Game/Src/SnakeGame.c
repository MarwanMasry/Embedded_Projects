 /******************************************************************************
 *
 * Module: Snake game Module
 *
 * File Name: SnakeGame.c
 *
 * Description: Source file for the Snake game.
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "SnakeGame.h"
#include "PrintingHelperFunction.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "main.h"
#include "stm32f4xx_hal.h"


/*******************************************************************************
 *                          Private Function Prototype	                       *
 *******************************************************************************/
/**
 * @fn     HandleUserCommand_Task
 * @brief  Continuous task that handle user commands user for the game.
 *
 */
static void HandleUserCommand_Task(void *pvParameters);

/**
 * @fn     DrawScreen_Task
 * @brief  Periodic one that is responsible for drawing game screen.
 *
 */
static void DrawScreen_Task(void *pvParameters);

/**
 * @fn     welcomeScreen
 * @brief  Function that Print welcome screen and busy wait until user enters
 * 		   start button
 */
static void welcomeScreen(void);


/**
 * @fn     placeItem
 * @brief  Function to put Enemy or power-up Items at any random place in the game
 *
 * @param type:  Enemy or power-up Items
 */
static void placeItem
(
	uint8 type
);

/**
 * @fn    drawBorder
 * @brief Function to draw the border of the snake Game.
 *
 */
static void drawBorder(void);

/**
 * @fn    drawSnake
 * @brief Function to draw the snake
 *
 */
static void drawSnake(void);

/**
 * @fn     resetScreen
 * @brief  Function that reset the screen and redraw it with new snake,power and enemy Items
 *
 */
static void resetScreen(void);

/**
 * @fn    resetSnake
 * @brief Function to Reset the snake shake to starting state and save the score
 *
 */
static void resetSnake(void);

/**
 * @fn    rand
 * @brief XOR-Shift Pseudo Random Numbers Generator
 *
 * @return Random value
 */
static uint32 rand(void);


/*******************************************************************************
 *                     			 Externs needed       				           *
 *******************************************************************************/
extern UART_HandleTypeDef huart3;


/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/
static xSemaphoreHandle PrintingSharedResuource_Mutex;

SnakeDir dir = DIR_RIGHT;

Point snake[DX*DY] =
{
    {DX/2,DY/2},
    {DX/2+1, DY/2},
    {DX/2+2, DY/2}
};

static uint8  screen[DX*DY] = {0};
static uint32 timeInSec = 0;
static uint8  UART_InputCommand = 0;
static uint32 Game_Speed =0;
static uint32 snakelen = 3;
static uint32 highestScore = 0;
static uint32 latestScore = 0;
static uint32 currentScore = 0;
static uint8  placeSpecialItemFlag = 1;


/*******************************************************************************
 *                     vApplicationTickHook Definitions                        *
 *******************************************************************************/
void vApplicationTickHook( void )
{
	static int iCount = 0;

	/* Count the number of ticks */
	iCount++;

	/* If the number of ticks reach configTICK_RATE_HZ then we reach 1 second*/
	if( iCount >= configTICK_RATE_HZ )
	{
		timeInSec++;
		iCount = 0;
	}

    /* Put Special Power item at random place in the screen every 10 seconds */
    if( (timeInSec != 0 && (timeInSec%10 == 0)) && placeSpecialItemFlag == 1 )
    {
    	placeItem(SPECIAL_POWER_CHAR);
    	placeSpecialItemFlag =0 ;
    }

}
/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/

/**
 * @fn    SnakeGame_Start
 * @brief This function will do all the initialization needed for the game and create
 * 	      tasks needed for the game and schedule them.
 * 	      NOTE: any code beyond this function won't be reached.
 *
 */
void SnakeGame_Start(void)
{
	PrintingSharedResuource_Mutex  = xSemaphoreCreateMutex();

	/* Create two Tasks:
	 *   - Periodic one that is responsible for drawing game screen.
	 *   - Continuous one that responsible for handling user commands for the game.
	 */
	xTaskCreate( HandleUserCommand_Task, "User Command Handling Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( DrawScreen_Task, "Screen Drawer Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	/* Show welcome screen and reset the screen then start the scheduler */
	welcomeScreen();
	resetScreen();

	/* Start the scheduler */
	vTaskStartScheduler();
}

/**
 * @fn     HandleUserCommand_Task
 * @brief  Continuous task that handle user commands user for the game.
 *
 */
static void HandleUserCommand_Task(void *pvParameters)
{
	for(;;)
	{

		/* Receive User input form the user command */
		HAL_UART_Receive(&huart3, &UART_InputCommand, 1,100);


		/* Allow all moves direction expect moves that is opposite current direction */
		switch(UART_InputCommand)
        {
            case 'w':
            case 'W':
                if(dir!= DIR_DOWN)
                {
                    dir = DIR_UP;
                }
                break;

            case 'a':
            case 'A':
                if(dir!= DIR_RIGHT)
                {
                    dir = DIR_LEFT;
                }
                break;

            case 's':
			case 'S':
                if(dir!= DIR_UP)
                {
                    dir = DIR_DOWN;
                }
                break;

            case 'd':
            case 'D':
                if(dir!= DIR_LEFT)
                {
                    dir = DIR_RIGHT;
                }
                break;

            default:
            	break;
            	/* Do nothing*/
        }

	}

	/* Shouldn't reach here but if we reach here, delete the task */
	vTaskDelete(NULL);
}

/**
 * @fn     DrawScreen_Task
 * @brief  Periodic one that is responsible for drawing game screen.
 *
 */
static void DrawScreen_Task(void *pvParameters)
{
	uint32 i = 0;
	uint8 removeTail = 1;

	/* Initial game speed */
	Game_Speed = INITIAL_GAME_SPEED;

	for(;;)
	{

		xSemaphoreTake(PrintingSharedResuource_Mutex,portMAX_DELAY);
		{
			/* Print current score */
			print_Str("\n\rCurrent Score: ");
			print_Dec(currentScore);
			print_Str("\n\r");
			/*
			 *  Print current Time, This is critical section so we must take care that ISR corrupt
			 *  timeInISR value
			 */
			print_Str("Elapsed Time since start of the game: ");

			portENTER_CRITICAL();
			print_Dec(timeInSec);
			portEXIT_CRITICAL();

			print_Str(" Seconds \n\r");

			/* print screen row by row */
			for(i=0; i < DY ;i++)
			{
				print_Buff((char*)(screen+(DX*i)), DX);
				print_Str("\n\r");
			}
			print_Str("\n\r\n\r");

		}
		xSemaphoreGive(PrintingSharedResuource_Mutex);

		/* Make task periodic for a variable time to control the speed of the game */
		vTaskDelay(Game_Speed/portTICK_RATE_MS);

		/* Update new snake co-ordinates according to new direction */
		switch(dir)
		{
			case DIR_RIGHT:
				snake[snakelen].x = snake[snakelen-1].x+1;
				snake[snakelen].y = snake[snakelen-1].y;
				break;

			case DIR_LEFT:
				snake[snakelen].x = snake[snakelen-1].x-1;
				snake[snakelen].y = snake[snakelen-1].y;
				break;

			case DIR_UP:
				snake[snakelen].x = snake[snakelen-1].x;
				snake[snakelen].y = snake[snakelen-1].y-1;
				break;

			case DIR_DOWN:
				snake[snakelen].x = snake[snakelen-1].x;
				snake[snakelen].y = snake[snakelen-1].y+1;
				break;

			default:
				break;
		}

		removeTail = 1;

		/* See the new pixel which the snake moves to and see if this a
		 * legal move or not
		 */
		switch(screen[(DX*(snake[snakelen].y))+snake[snakelen].x])
		{
		/* If you hit yourself or the border or and enemy then game is over and
		 * print welcome screen again and restart again.
		 */
			case SNAKE_CHAR:
			case BORDER_CHAR:
			case ENEMY_CHAR:
				xSemaphoreTake(PrintingSharedResuource_Mutex,portMAX_DELAY);
				{
					print_Str("<<<<<<<<<<<<  GAME OVER :(  >>>>>>>>>>>>\n\r");
				}
				xSemaphoreGive(PrintingSharedResuource_Mutex);

				resetSnake();
				welcomeScreen();
				resetScreen();
				placeSpecialItemFlag =1;

				UART_InputCommand = 0; /* reset command*/

				/* Controlling the speed of the next game speed in case of
				 * losing,return initial speed
				 */
				Game_Speed = INITIAL_GAME_SPEED;
				continue;

		/* If you hit a power character then don't remove tail,update score and place another
		 * power character
		 */
			case POWER_CHAR:
				removeTail = 0;
				/* update the score*/
				currentScore ++;
				placeItem(POWER_CHAR);
				break;

		/* If you hit a special power character then don't remove tail, update the score
		 * by 10 points and trigger flag to place another special power character
		 */
			case SPECIAL_POWER_CHAR:
				removeTail = 0;
				/* update the score*/
				currentScore += 10;
				placeSpecialItemFlag =1;
				break;

			default:
				break;
				/* Do Nothing */
		}

		/* set head */
		screen[DX*snake[snakelen].y+snake[snakelen].x] = SNAKE_CHAR;

		/* When the snake is moving so the tail will move one pixel[remove tail]
		 * then move all of the snake co-oridnate one pixel
		 */
		if(removeTail)
		{
			/* remove tail */
			screen[(DX*(snake->y))+(snake->x)] = ' ';

			/* move all snake co-oridnes one pixel */
			for(i=0;i<snakelen;i++)
			{
				snake[i] = snake[i+1];
			}
		}
		else
		{
			/* If we don't remove the tail, which mean that we ate a power up then we need increase the
			 * length and leave the snake as it is without removing its tail
			 */
			snakelen++;
		}

		if(currentScore >= WIN_SCORE)
		{
			xSemaphoreTake(PrintingSharedResuource_Mutex,portMAX_DELAY);
			{
				print_Str("<<<<<<<<<<<<  YOU WIN :)  >>>>>>>>>>>>\n\r");
			}
			xSemaphoreGive(PrintingSharedResuource_Mutex);

			resetSnake();
			welcomeScreen();
			resetScreen();
			placeSpecialItemFlag =1;

			UART_InputCommand = 0; /* reset command*/

			/* Controlling the speed of the next game speed in case of winning*/
			if(Game_Speed > 100)
			{
				Game_Speed -= 100;
			}
			else
			{
				Game_Speed = 50; /* This is the maximum speed */
			}
		}
	}

	/* Shouldn't reach here but if we reach here, delete the task */
	vTaskDelete(NULL);
}


/**
 * @fn     welcomeScreen
 * @brief  Function that Print welcome screen and busy wait until user enters
 * 		   start button
 */
static void welcomeScreen(void)
{

	xSemaphoreTake(PrintingSharedResuource_Mutex,portMAX_DELAY);
	{
		if(highestScore != 0)
		{

			print_Str("Your Score History:\n\r  -Highest Score achieved : ");
			print_Dec(highestScore);

			print_Str("\n\r  -Latest Score achieved : ");
			print_Dec(latestScore);
			print_Str("\n\r\n\r");

		}

		print_Str("****** Welcome to the Snake Game!!! ******\n\r\n\r");
		print_Str("Game Controls to move the snake:\n\r   -'w' for UP\n\r   -'a' for Left\n\r   -'s'for Down\n\r   -'d' for right");
		print_Str("\n\r\n\r");
		print_Str("Game Information:\n\r   -Collecting '$' Power-ups will increase your score by 1.\n\r");
		print_Str("   -Collecting '@' Special Power-ups will increase your score by 10.\n\r");
		print_Str("   -You will lose if you eat yourself or hit the enemy 'X'.");
		print_Str("\n\r\n\r");
		print_Str("Press X to start the game...\n\r");
	}
	xSemaphoreGive(PrintingSharedResuource_Mutex);

    /* Receive command from the user using interrupt */
	do
	{
		HAL_UART_Receive(&huart3, &UART_InputCommand, 1,100);
	}while(UART_InputCommand != 'X' && UART_InputCommand != 'x');

	/* reset command*/
	UART_InputCommand = 0;
}


/**
 * @fn     placeItem
 * @brief  Function to put Enemy or power-up Items at any random place in the game
 *
 * @param type:  Enemy or power-up Items
 */
static void placeItem(uint8 type)
{
    uint8 done =0;
    uint32 x,y;

    /* Loop until we found an empty place to put Item*/
    while(!done)
    {
    	/* Generate any random x,y that is not the border */
        x = 1 + rand()%(DX-2);
        y = 1 + rand()%(DY-2);

        /* if place is empty put item*/
        if (screen[DX*y+x] == ' ')
        {
            screen[DX*y+x] = type;
            done = 1;
        }
    }
}

/**
 * @fn    drawBorder
 * @brief Function to draw the border of the snake Game.
 *
 */
static void drawBorder(void)
{
    uint32 i = 0;

    /* Draw top row */
    for(i=0; i<DX; i++)
    {
        screen[i] = BORDER_CHAR;
    }

    /* Draw bottom row */
    for(i=0; i<DX; i++)
    {
        screen[DX*(DY-1)+i] = BORDER_CHAR;
    }

    /* Draw left row */
	for(i=0; i<DY; i++)
    {
        screen[DX*i] = BORDER_CHAR;
    }

    /* Draw right row */
	for(i=0; i<DY; i++)
    {
        screen[DX*i + DX-1] = BORDER_CHAR;
    }
}

/**
 * @fn    drawSnake
 * @brief Function to draw the snake
 *
 */
static void drawSnake(void)
{
    uint16 i =0;

    /*
     *  Loop through the snake point by point then make a pointer point
	 * to each point then Put snake Character in this place
	 */
    for(i=0; i<snakelen; i++)
    {
        Point *p = snake+i;
        screen[(DX*(p->y))+(p->x)] = SNAKE_CHAR;
    }
}

/**
 * @fn     resetScreen
 * @brief  Function that reset the screen and redraw it with new snake,power and enemy Items
 *
 */
static void resetScreen(void)
{
	uint32 i;
	/* Clear all the screen buffer */
    for( i = 0; i<DX*DY ; i++)
    {
    	screen[i]= ' ';
    }

    /* Draw the border */
    drawBorder();
    /* Put Power item at random place in the screen */
    placeItem(POWER_CHAR);

    /* Put Enemy item at random place in the screen */
    placeItem(ENEMY_CHAR);
    /* Draw the snake */
    drawSnake();
}

/**
 * @fn    resetSnake
 * @brief Function to Reset the snake shake to starting state and save the score
 *
 */
static void resetSnake(void)
{
	/* Save the current score */
    latestScore = currentScore;

    /* Update the current score */
    if(latestScore > highestScore)
    {
        highestScore = latestScore;
    }

    /* Initialize all Global Variables */
    snakelen = 3;
    currentScore = 0;

    snake[0].x = DX/2;
    snake[0].y = DY/2;
    snake[1].x = DX/2+1;
    snake[1].y = DY/2;
    snake[2].x = DX/2+2;
    snake[2].y = DY/2;

    dir = DIR_RIGHT;
}

/**
 * @fn    rand
 * @brief XOR-Shift Pseudo Random Numbers Generator
 *
 * @return Random value
 */
static uint32 rand(void)
{
	static uint32 z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
	uint32 b;
	b  = ((z1 << 6) ^ z1) >> 13;
	z1 = ((z1 & 4294967294U) << 18) ^ b;
	b  = ((z2 << 2) ^ z2) >> 27;
	z2 = ((z2 & 4294967288U) << 2) ^ b;
	b  = ((z3 << 13) ^ z3) >> 21;
	z3 = ((z3 & 4294967280U) << 7) ^ b;
	b  = ((z4 << 3) ^ z4) >> 12;
	z4 = ((z4 & 4294967168U) << 13) ^ b;
	return(z1 ^ z2 ^ z3 ^ z4);
}
