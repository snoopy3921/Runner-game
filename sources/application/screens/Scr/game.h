#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>
#include "gui_port.h"
/**
  *****************************************************************************
  * EEPROM define address.
  *
  *****************************************************************************
  */
#define EEPROM_START_ADDR           (0X0000)
#define EEPROM_END_ADDR             (0X1000)

#define EEPROM_SCORE_START_ADDR     (0X0010)

#define EEPROM_SETTING_START_ADDR   (0X0100)




extern obj_label lb1, lb2, lb3, lb4, lb5 ;
extern obj_group gr1, gr2;
extern obj_bmp bmp1, bmp2, bmp3, bmp4;
extern obj_canvas cv1, cv2, cv3;
extern oled_anim an1, an2, an3;


#define GAME_STATE_PLAY		(0)
#define GAME_STATE_OVER		(1)

/*  Defines  */
#define SCR_WIDTH 128
#define SCR_HEIGHT 64

#define SCR_WIDTH_CENTER SCR_WIDTH / 2
#define SCR_HEIGHT_CENTER SCR_HEIGHT / 2

#define FROM_EYES_TO_SCR 32
#define MAX_DEPTH 32 * 4

#define MAX_STAR_HIGH 128

#define MAX_COLUMN_WIDTH 24

#define STEP_X_TO_TURN 2
#define STEP_DEPTH 1

#define MAX_NUM_COLUMN 8
#define MAX_NUM_STAR 30

typedef struct {
  /* score data */
  uint32_t score_1st;
  uint32_t score_2nd;
  uint32_t score_3rd;
} game_chart_t;

typedef struct {
  /* setting data */
  bool silent;
  uint8_t speed;
} game_setting_t;

extern game_chart_t chart;
extern game_setting_t setting;

extern uint8_t game_update_rate;


#endif