 /******************************************************************************
 *
 * Module: Snake game Module
 *
 * File Name: SnakeGame.h
 *
 * Description: Header file for the Snake game.
 *
 *******************************************************************************/
#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                                Definition                                   *
 *******************************************************************************/
/* Two dimensions of the Screen */
#define DX   32
#define DY   16

#define WIN_SCORE   30      /* Required score to win game */
#define POWER_CHAR  36     /* ASCII CODE for $ */
#define ENEMY_CHAR  88     /* ASCII CODE for X */
#define SNAKE_CHAR  111    /* ASCII CODE for o */
#define BORDER_CHAR 35     /* ASCII CODE for # */
#define INITIAL_GAME_SPEED 500
#define SPECIAL_POWER_CHAR '@'
/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
typedef struct
{
    uint16 x, y;
}Point;


typedef enum
{
    DIR_RIGHT,
    DIR_LEFT,
    DIR_UP,
    DIR_DOWN
}SnakeDir;

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/**
 * @fn    SnakeGame_Start
 * @brief This function will do all the initialization needed for the game and create
 * 	      tasks needed for the game and schedule them.
 * 	      NOTE: any code beyond this function won't be reached.
 *
 */
void SnakeGame_Start(void);

#endif /* SNAKEGAME_H_ */
