#include "scr_manager.h"
#include "oled_gui.h"

#include "os_msg.h"
#include "main.h"
#include "game.h"
#include "eeprom.h"
#include "gui_port.h"

static const uint8_t iconLeaderBoard[] = { //100x40
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 
0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x01, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 
0x00, 0x70, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xf0, 0x00, 
0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0xf0, 0x00, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x70, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0x00, 0x70, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
0xf0, 0x00, 0x70, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x70, 
0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xf0, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xf0, 0x01, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0xf0, 0x03, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0xf0, 0x03, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xf0, 0xf0, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 
0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0xf0, 0xf0, 0x00, 0x78, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xf0, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x1c, 0x00, 0xf0, 0xf0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0x00, 0xf0, 0xf0, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xf0, 0xf0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x1c, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
0x1c, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xf0, 
0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

game_chart_t chart;

static void setup_function(msg_t * msg)
{
    eeprom_read(	EEPROM_SCORE_START_ADDR, \
                    (uint8_t*)&chart, \
                    sizeof(chart));

    lb1.init(15, 25);
    lb1.print(chart.score_2nd);

    lb2.init(50, 15);
    lb2.print(chart.score_1st);

    lb3.init(85, 30);
    lb3.print(chart.score_3rd);

    bmp1.init(0, 0, 100, 40);
    bmp1.setAllign(ALIGN_BOTTOMMID);
    bmp1.setBmp(iconLeaderBoard);

    gr1.init();
    gr1.addObj(&lb1, false);
    gr1.addObj(&lb2, false);
    gr1.addObj(&lb3, false);
    gr1.addObj(&bmp1, false);

    gr1.setPosOffset(0, 64);

    an1.init(&gr1, 0, -64, 300);
    os_task_delay(350);

}
static void loop_funtion(msg_t * msg)
{

	
}

static void event_function(msg_t * msg)
{
      switch (msg->sig)
      {
      case AC_DISPLAY_BUTTON_MODE_LONG_PRESSED:
            scr_curr_set_stt(SCR_STT_READY); //Set back to ready state to make loop_func stop
            bmp1.deinit();
            lb1.deinit();
            lb2.deinit();
            lb3.deinit();
            gr1.deinit();
            scr_shift(SCR_MENU_GAME);
            break;
      default:
            break;
      }
}


void scr_chart_game_register( void )
{
    scr_reg(SCR_CHART_GAME, nullptr, nullptr, setup_function, loop_funtion, event_function);
}