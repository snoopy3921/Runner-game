#include "scr_manager.h"
#include "oled_gui.h"
#include "system.h"
#include "os_msg.h"
#include "main.h"
#include "gui_port.h"
#include "game.h"
#include "eeprom.h"
#include "math.h"
#include <string>

static const uint8_t signGameOver[] = { // 90x20
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xc3, 0xf1, 0x00, 0xbf, 0xf0, 0x3f, 0x9c, 0x77, 0xfd, 0xfe, 0x00, 
	0x3c, 0xe7, 0x3d, 0xc3, 0xbc, 0x00, 0x71, 0xdc, 0x77, 0x01, 0xe7, 0x00, 0x38, 0xe7, 0x1d, 0xc3, 
	0xb8, 0x00, 0x71, 0xdc, 0x77, 0x01, 0xe7, 0x80, 0x38, 0xe7, 0x1d, 0xe7, 0xb8, 0x00, 0x71, 0xdc, 
	0x77, 0x01, 0xe7, 0x80, 0x38, 0x07, 0x1d, 0xff, 0xb8, 0x00, 0x71, 0xdc, 0x77, 0x01, 0xe7, 0x80, 
	0x38, 0x07, 0x1d, 0xff, 0xbc, 0x00, 0x71, 0xdc, 0x77, 0x81, 0xe7, 0x00, 0x39, 0xe7, 0x1d, 0xdb, 
	0xbf, 0xc0, 0x71, 0xdc, 0x77, 0xf9, 0xfe, 0x00, 0x38, 0xe7, 0xfd, 0xc3, 0xbc, 0x00, 0x71, 0xcf, 
	0xe7, 0x81, 0xff, 0x00, 0x38, 0xe7, 0xfd, 0xc3, 0xb8, 0x00, 0x71, 0xc7, 0xe7, 0x01, 0xc3, 0x80, 
	0x38, 0xe7, 0x3d, 0xc3, 0xb8, 0x00, 0x71, 0xc7, 0xe7, 0x01, 0xc3, 0x80, 0x38, 0xe7, 0x1d, 0xc3, 
	0xb8, 0x00, 0x71, 0xc7, 0xc7, 0x01, 0xc3, 0x80, 0x38, 0xe7, 0x1d, 0xc3, 0xbc, 0x00, 0x71, 0xc3, 
	0x87, 0x01, 0xc3, 0x80, 0x1f, 0xc7, 0x1d, 0xc3, 0xbf, 0xf0, 0x3f, 0x83, 0x87, 0xfd, 0xc3, 0x80, 
	0x0f, 0x86, 0x19, 0x81, 0x9f, 0xf0, 0x1f, 0x03, 0x83, 0xfc, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

static const uint8_t imgPlayer[] = { // 20x20
    0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x90, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x7e, 0x67, 0xe0, 0xff, 0x6f, 0xf0, 0x7e, 0xf7, 
    0xe0, 0x30, 0x00, 0xc0, 0x1c, 0xf3, 0x80, 0x08, 0x01, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0xf8, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x60, 0x00
};

typedef enum
{
    TURN_LEFT,
    TURN_RIGHT,
    GO_AHEAD // Default
} turn_t;

class column
{
private:
    /* data */
    uint8_t w;
    int16_t x;
    float depth;
    obj_canvas cv;

public:
    column(/* args */);
    ~column();

    int16_t getX() { return x; }
    void setX(int16_t val) { x = val; }
    float getDepth() { return depth; }
    void setDepth(float val) { depth = val; }

    float getScale() { return (float)(FROM_EYES_TO_SCR) / (FROM_EYES_TO_SCR + getDepth()); }

    obj_canvas getCanvas() { return cv; }

    void init()
    {
        cv.init();
        x = (rand() % (SCR_WIDTH * 4)) - (SCR_WIDTH * 3 / 2) ;
        w = MAX_COLUMN_WIDTH;
        depth = (rand() % (MAX_DEPTH / 2)) + MAX_DEPTH / 2;
    }
    void deinit()
    {
        cv.deinit();
    }

    void draw()
    {
        cv.canvas_fillRoundRect(SCR_WIDTH_CENTER - (SCR_WIDTH_CENTER - x) * getScale() - w / 2, (SCR_HEIGHT_CENTER - w) * getScale(), w * getScale(), w * 4 * getScale(), 2);
        cv.setFade(getDepth() / (MAX_DEPTH / 4));
    }
};
column::column(/* args */) {}
column::~column() {}

class star
{
private:
    /* data */

    int16_t x;
    uint8_t h;
    float depth;

    obj_canvas cv;

public:
    star(/* args */);
    ~star();

    int16_t getX() { return x; }
    void setX(int16_t val) { x = val; }
    float getDepth() { return depth; }
    void setDepth(float val) { depth = val; }
    uint8_t getH() { return h; }
    void setH(int16_t val) { h = val; }

    float getScale() { return (float)(FROM_EYES_TO_SCR) / (FROM_EYES_TO_SCR + getDepth()); }

    obj_canvas getCanvas() { return cv; }

    void init()
    {
        cv.init();
        x = (rand() % (SCR_WIDTH * 3/4)) + SCR_WIDTH / 4;
        h = (rand() % MAX_STAR_HIGH);
        depth = rand() % MAX_DEPTH;
    }
    void deinit()
    {
        cv.deinit();
    }

    void draw()
    {
        cv.canvas_drawRect(SCR_WIDTH_CENTER - (SCR_WIDTH_CENTER - x) * getScale(), h * getScale(), 1, 1);
    }
};
star::star(/* args */) {}
star::~star() {}

static column columns[MAX_NUM_COLUMN];
static star stars[MAX_NUM_STAR];
static uint32_t score;
static uint32_t game_state;

static uint32_t turn_tick;
uint8_t game_update_rate;

game_setting_t setting;


static turn_t direction;

static void drawColumns(void);
static void updateColumns(turn_t turn_type);
static void initColumns(bool state);

static void drawStars(void);
static void updateStars(turn_t turn_type);
static void initStars(bool state);

static void handleGame(uint8_t state);

static void rank_ranking();

static void setup_function(msg_t *msg)
{
    // Read setting data
    eeprom_read(	EEPROM_SETTING_START_ADDR, \
                    (uint8_t*)&setting, \
                    sizeof(setting));

    game_state = GAME_STATE_PLAY;
    
    score = 0;
    turn_tick = 0;
    direction = GO_AHEAD;
    

    initColumns(true);
    initStars(true);

    bmp1.init(0, 0, 90, 20);
    bmp1.setBmp(signGameOver);    
    bmp1.setAllign(ALIGN_HORIZONMID);
    bmp1.setAllign(ALIGN_VERTICALMID);
    bmp1.addState(STATE_DISABLE);

    lb1.init(0, 0);

    os_task_post_msg_pure(TASK_TIMER_ID, 57 - setting.speed);
}
static void loop_funtion(msg_t *msg)
{
    handleGame(game_state);
}

static void event_function(msg_t *msg)
{
    switch (msg->sig)
    {
    case AC_DISPLAY_BUTTON_MODE_LONG_PRESSED:
        scr_curr_set_stt(SCR_STT_READY); // Set back to ready state to make loop_func stop
        os_task_post_msg_pure(TASK_TIMER_ID, OS_CFG_DELAY_MAX - 1); // Stop timer
        initColumns(false);
        initStars(false);
        bmp1.deinit();
        lb1.deinit();
        rank_ranking();
        scr_shift(SCR_MENU_GAME);
        break;
    case AC_DISPLAY_BUTTON_UP_PRESSED:
        if(game_state != GAME_STATE_OVER && !setting.silent) os_task_post_msg_pure(TASK_BUZZER_ID, AC_BUZZER_PLAY_TONE_MOVE);
        direction = TURN_RIGHT;
        turn_tick = 0;
        break;
    case AC_DISPLAY_BUTTON_DOWN_PRESSED:
        if(game_state != GAME_STATE_OVER && !setting.silent) os_task_post_msg_pure(TASK_BUZZER_ID, AC_BUZZER_PLAY_TONE_MOVE);
        direction = TURN_LEFT;
        turn_tick = 0;
        break;
    case AC_DISPLAY_GAME_UPDATE:
        switch (game_state)
        {
        case GAME_STATE_PLAY:
            updateColumns(direction);
            updateStars(direction);
            drawColumns();
            drawStars();
            lb1.print(score);
            break;
        case GAME_STATE_OVER:
            updateColumns(GO_AHEAD);
            updateStars(GO_AHEAD);
            drawColumns();
            drawStars();
            lb1.print(score);
            break;
        default:
            break;
        }


        break;
    default:
        break;
    }
}

void scr_main_game_register(void)
{
    scr_reg(SCR_MAIN_GAME, nullptr, nullptr, setup_function, loop_funtion, event_function);
}

static void initColumns(bool state)
{
    column *cl = columns;
    if (state == true)
        for (int i = 0; i < MAX_NUM_COLUMN; i++)
        {
            cl->init();
            cl++;
        }
    else
        for (int i = 0; i < MAX_NUM_COLUMN; i++)
        {
            cl->deinit();
            cl++;
        }
}
static void updateColumns(turn_t turn_type)
{
    if(game_state != GAME_STATE_OVER) score += STEP_DEPTH;
    column *cl = columns;
    switch (turn_type)
    {
    case TURN_LEFT:
        for (int i = 0; i < MAX_NUM_COLUMN; i++)
        {
            cl->setDepth(cl->getDepth() - STEP_DEPTH);
            cl->setX((cl->getX() + STEP_X_TO_TURN));
            cl++;
        }
        break;
    case TURN_RIGHT:
        for (int i = 0; i < MAX_NUM_COLUMN; i++)
        {
            cl->setDepth(cl->getDepth() - STEP_DEPTH);
            cl->setX((cl->getX() - STEP_X_TO_TURN));
            cl++;
        }
        break;
    default:
        for (int i = 0; i < MAX_NUM_COLUMN; i++)
        {
            cl->setDepth(cl->getDepth() - STEP_DEPTH);
            cl++;
        }
        break;
    }
}
static void drawColumns(void)
{
    column *cl = columns;
    for (int i = 0; i < MAX_NUM_COLUMN; i++)
    {
        if (cl->getDepth() <= 0)
        {
            if (cl->getX() <= SCR_WIDTH_CENTER + (MAX_COLUMN_WIDTH / 2) && cl->getX() >= SCR_WIDTH_CENTER - (MAX_COLUMN_WIDTH / 2))
            {
                if(game_state != GAME_STATE_OVER && !setting.silent) os_task_post_msg_pure(TASK_BUZZER_ID, AC_BUZZER_PLAY_TONE_DEATH);
                os_task_post_msg_pure(TASK_TIMER_ID, 70); // Slow timer
                game_state = GAME_STATE_OVER;
                bmp1.clearState(STATE_DISABLE);
            }
            cl->setX((rand() % (SCR_WIDTH * 4)) - (SCR_WIDTH * 3 / 2) );
            cl->setDepth((rand() % (MAX_DEPTH / 2)) + MAX_DEPTH / 2);
        }

        cl->draw();
        cl++;
    }
}

static void drawStars(void)
{
    star *st = stars;
    for (int i = 0; i < MAX_NUM_STAR; i++)
    {
        if (st->getDepth() <= 0)
        {
            st->setX((rand() % (SCR_WIDTH * 3/4)) + SCR_WIDTH / 4);
            st->setDepth((rand() % (MAX_DEPTH / 4)) + MAX_DEPTH / 4);
        }
        st->draw();
        st++;
    }
}
static void updateStars(turn_t turn_type)
{
    star *st = stars;
    switch (turn_type)
    {
    case TURN_LEFT:
        for (int i = 0; i < MAX_NUM_STAR; i++)
        {
            st->setDepth(st->getDepth() - STEP_DEPTH);
            st->setX((st->getX() + STEP_X_TO_TURN));
            st++;
        }
        break;
    case TURN_RIGHT:
        for (int i = 0; i < MAX_NUM_STAR; i++)
        {
            st->setDepth(st->getDepth() - STEP_DEPTH);
            st->setX((st->getX() - STEP_X_TO_TURN));
            st++;
        }
        break;
    default:
        for (int i = 0; i < MAX_NUM_STAR; i++)
        {
            st->setDepth(st->getDepth() - STEP_DEPTH);
            st++;
        }
        break;
    }
}
static void initStars(bool state)
{
    star *st = stars;
    if (state == true)
        for (int i = 0; i < MAX_NUM_STAR; i++)
        {
            st->init();
            st++;
        }
    else
        for (int i = 0; i < MAX_NUM_STAR; i++)
        {
            st->deinit();
            st++;
        }
}

static void handleGame(uint8_t state)
{
    switch (state)
    {
    case GAME_STATE_PLAY:
        /* code */
        turn_tick++;
        if (turn_tick > setting.speed)
        {
            direction = GO_AHEAD;
            turn_tick = 0;
        }
        break;
    case GAME_STATE_OVER:
        /* code */
        break;
    
    default:
        break;
    }
}

/*****************************************************************************/
/* Handle - game over */
/*****************************************************************************/
static void rank_ranking() {
        // Read score 1st, 2nd, 3rd
    eeprom_read(	EEPROM_SCORE_START_ADDR, \
                    (uint8_t*)&chart, \
                    sizeof(chart));
	if (score > chart.score_1st) {
		chart.score_3rd = chart.score_2nd;
		chart.score_2nd = chart.score_1st;
		chart.score_1st = score;
	}
	else if (score > chart.score_2nd) {
		chart.score_3rd = chart.score_2nd;
		chart.score_2nd = score;
	}
	else if (score > chart.score_3rd) {
		chart.score_3rd = score;
	}
    eeprom_write(	EEPROM_SCORE_START_ADDR, \
                    (uint8_t*)&chart, \
                    sizeof(chart));
}