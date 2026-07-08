#include "ela_button.h"
#include <string.h>

#define BUTTON_NUM      1                     // 按键数量


/* ======== MultiButton 核心定义（内嵌） ======== */

#define TICKS_INTERVAL          5             // ms -- 与TIM5溢出周期一致
#define DEBOUNCE_TICKS          2             // MAX 7 -- 2 tick x 5ms = 10ms消抖
#define SHORT_TICKS             (300 / TICKS_INTERVAL)
#define LONG_TICKS              (2000 / TICKS_INTERVAL)
#define PRESS_REPEAT_MAX_NUM    15

/* 按键事件类型 */
typedef enum
{
    BTN_PRESS_DOWN      = 0,
    BTN_PRESS_UP,
    BTN_PRESS_REPEAT,
    BTN_SINGLE_CLICK,
    BTN_DOUBLE_CLICK,
    BTN_LONG_PRESS_START,
    BTN_LONG_PRESS_HOLD,
    BTN_EVENT_COUNT,
    BTN_NONE_PRESS
} ButtonEvent;

/* 按键状态机状态 */
typedef enum
{
    BTN_STATE_IDLE      = 0,
    BTN_STATE_PRESS,
    BTN_STATE_RELEASE,
    BTN_STATE_REPEAT,
    BTN_STATE_LONG_HOLD
} ButtonState;

/* 前向声明 */
typedef struct _Button Button;

/* 按键回调函数类型 */
typedef void (*BtnCallback)(Button *handle, void *user_data);

/* 按键结构体 */
struct _Button
{
    uint16_t ticks;
    uint8_t  repeat : 4;
    uint8_t  event : 4;
    uint8_t  state : 3;
    uint8_t  debounce_cnt : 3;
    uint8_t  active_level : 1;
    uint8_t  button_level : 1;
    uint8_t  button_id;
    uint8_t  (*hal_button_level)(uint8_t button_id);
    BtnCallback cb[BTN_EVENT_COUNT];
    void     *user_data;
    struct _Button *next;
};

/* 按键链表头 */
static Button *head_handle = NULL;

/* 按键句柄 */
static Button btn_handle[BUTTON_NUM + 1];

/* button hlp start */

/****
 * @ 原型: void OnPress(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 按键按下回调函数，
 *        由 ela_button.c 在消抖确认按下后自动调用。
 *        翻转 MCU_LED 状态。
 * @ tips: 允许修改内部功能 —
 *        此函数为弱定义，可在 elaco_main.c 中覆盖
 ********/
__weak void OnPress(void)
{
    static uint8_t led_state = 0;   // MCU_LED状态
    led_state = !led_state;

    if (led_state)
        HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                          GPIO_PIN_RESET); // 亮
    else
        HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                          GPIO_PIN_SET);   // 灭
}

/****
 * @ 原型: void OnLongPress(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 按键长按回调函数，
 *        由 ela_button.c 在消抖确认长按后自动调用。
 *        翻转 MCU_LED 状态。
 * @ tips: 允许修改内部功能 —
 *        此函数为弱定义，可在 elaco_main.c 中覆盖
 ********/
__weak void OnLongPress(void)
{
    ;
}

/****
 * @ 原型: static void Button_PressHandler(
 *            Button *handle, void *user_data)
 * @ 输入: Button *handle: 触发事件的按键句柄
 *         void *user_data: 用户数据（未使用）
 * @ 输出: void
 * @ 说明: MultiButton按下事件的内部回调，
 *        过滤释放抖动后调用 OnPress()
 ********/
static void Button_PressHandler(Button *handle,
                                void *user_data)
{
    (void)handle;
    (void)user_data;

    /* 只接受 IDLE -> PRESS 的首次按下，
       排除释放抖动导致的 RELEASE -> REPEAT */
    if (handle->state == BTN_STATE_IDLE)
    {
        OnPress();
    }
}


/****
 * @ 原型: static void Button_LongPressHandler(
 *            Button *handle, void *user_data)
 * @ 输入: Button *handle: 触发事件的按键句柄
 *         void *user_data: 用户数据（未使用）
 * @ 输出: void
 * @ 说明: MultiButton长按事件的内部回调，
 *        调用用户定义的 OnLongPress()
 ********/
static void Button_LongPressHandler(Button *handle,
                                    void *user_data)
{
    (void)handle;
    (void)user_data;

    OnLongPress();
}


/* ======== MultiButton 内部函数 ======== */

#define EVENT_CB(ev) \
    do { \
        if (handle->cb[ev]) \
            handle->cb[ev](handle, handle->user_data); \
    } while(0)


static inline uint8_t button_read_level(Button *handle)
{
    return handle->hal_button_level(handle->button_id);
}


static void Button_Handler(Button *handle)
{
    uint8_t read_gpio_level = button_read_level(handle);

    /* 非空闲状态下累计 tick（防溢出） */
    if (handle->state > BTN_STATE_IDLE)
    {
        if (handle->ticks < UINT16_MAX)
        {
            handle->ticks++;
        }
    }

    /* 消抖处理 */
    if (read_gpio_level != handle->button_level)
    {
        if (++(handle->debounce_cnt) >= DEBOUNCE_TICKS)
        {
            handle->button_level = read_gpio_level;
            handle->debounce_cnt = 0;
        }
    }
    else
    {
        handle->debounce_cnt = 0;
    }

    /* 状态机 */
    switch (handle->state)
    {
    case BTN_STATE_IDLE:
        if (handle->button_level == handle->active_level)
        {
            handle->event = (uint8_t)BTN_PRESS_DOWN;
            EVENT_CB(BTN_PRESS_DOWN);
            handle->ticks = 0;
            handle->repeat = 1;
            handle->state = BTN_STATE_PRESS;
        }
        else
        {
            handle->event = (uint8_t)BTN_NONE_PRESS;
        }
        break;

    case BTN_STATE_PRESS:
        if (handle->button_level != handle->active_level)
        {
            handle->event = (uint8_t)BTN_PRESS_UP;
            EVENT_CB(BTN_PRESS_UP);
            handle->ticks = 0;
            handle->state = BTN_STATE_RELEASE;
        }
        else if (handle->ticks > LONG_TICKS)
        {
            handle->event = (uint8_t)BTN_LONG_PRESS_START;
            EVENT_CB(BTN_LONG_PRESS_START);
            handle->state = BTN_STATE_LONG_HOLD;
        }
        break;

    case BTN_STATE_RELEASE:
        if (handle->button_level == handle->active_level)
        {
            handle->event = (uint8_t)BTN_PRESS_DOWN;
            EVENT_CB(BTN_PRESS_DOWN);

            if (handle->repeat < PRESS_REPEAT_MAX_NUM)
            {
                handle->repeat++;
            }
            handle->event = (uint8_t)BTN_PRESS_REPEAT;
            EVENT_CB(BTN_PRESS_REPEAT);
            handle->ticks = 0;
            handle->state = BTN_STATE_REPEAT;
        }
        else if (handle->ticks > SHORT_TICKS)
        {
            if (handle->repeat == 1)
            {
                handle->event = (uint8_t)BTN_SINGLE_CLICK;
                EVENT_CB(BTN_SINGLE_CLICK);
            }
            else if (handle->repeat == 2)
            {
                handle->event = (uint8_t)BTN_DOUBLE_CLICK;
                EVENT_CB(BTN_DOUBLE_CLICK);
            }
            handle->state = BTN_STATE_IDLE;
        }
        break;

    case BTN_STATE_REPEAT:
        if (handle->button_level != handle->active_level)
        {
            handle->event = (uint8_t)BTN_PRESS_UP;
            EVENT_CB(BTN_PRESS_UP);

            if (handle->ticks < SHORT_TICKS)
            {
                handle->ticks = 0;
                handle->state = BTN_STATE_RELEASE;
            }
            else
            {
                handle->state = BTN_STATE_IDLE;
            }
        }
        else if (handle->ticks > SHORT_TICKS)
        {
            handle->ticks = 0;
            handle->repeat = 0;
            handle->state = BTN_STATE_PRESS;
        }
        break;

    case BTN_STATE_LONG_HOLD:
        if (handle->button_level == handle->active_level)
        {
            handle->event = (uint8_t)BTN_LONG_PRESS_HOLD;
            EVENT_CB(BTN_LONG_PRESS_HOLD);
        }
        else
        {
            handle->event = (uint8_t)BTN_PRESS_UP;
            EVENT_CB(BTN_PRESS_UP);
            handle->state = BTN_STATE_IDLE;
        }
        break;

    default:
        handle->state = BTN_STATE_IDLE;
        break;
    }
}


/****
 * @ 原型: static int Button_Start(Button *handle)
 * @ 输入: Button *handle: 按键句柄指针
 * @ 输出: int: 0=成功，-1=已存在，-2=参数错误
 * @ 说明: 将按键句柄注册到扫描链表中
 ********/
static int Button_Start(Button *handle)
{
    Button *target;

    if (!handle) return -2;

    target = head_handle;
    while (target)
    {
        if (target == handle) return -1;
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}


/****
 * @ 原型: static void Button_Ticks(void)
 * @ 输出: void
 * @ 说明: 遍历链表执行所有按键的状态机处理
 ********/
static void Button_Ticks(void)
{
    Button *target = head_handle;

    while (target)
    {
        Button *next = target->next;
        Button_Handler(target);
        target = next;
    }
}

/* button hlp end */
//----------------------------------------------------------------------------------
/* button drv start */

/****
 * @ 原型: static uint8_t Button_ReadPinLevel(uint8_t id)
 * @ 输入: uint8_t id: 按键编号（1）
 * @ 输出: uint8_t: 按键当前GPIO原始电平，
 *        0=RESET，1=SET
 ********/
static uint8_t Button_ReadPinLevel(uint8_t id)
{
    switch (id)
    {
        case 1:
            return (uint8_t)HAL_GPIO_ReadPin(
                SW1_GPIO_Port, SW1_Pin);
        default:
            return 1;
    }
}

/* button drv end */
//----------------------------------------------------------------------------------
/* button usr start */

/****
 * @ 原型: void Button_Init(void)
 * @ 输出: void
 * @ 说明: 初始化按键状态，在主循环开始前调用一次。
 *         SW1为低电平有效（GPIO_PIN_RESET=按下）。
 *         按键消抖确认后自动回调 OnPress()。
 ********/
void Button_Init(void)
{
    int i;

    for (i = 1; i <= BUTTON_NUM; i++)
    {
        memset(&btn_handle[i], 0, sizeof(Button));
        btn_handle[i].event = (uint8_t)BTN_NONE_PRESS;
        btn_handle[i].hal_button_level =
            Button_ReadPinLevel;
        btn_handle[i].button_level =
            (uint8_t)(!GPIO_PIN_RESET);
        btn_handle[i].active_level =
            (uint8_t)GPIO_PIN_RESET;
        btn_handle[i].button_id = (uint8_t)i;
        btn_handle[i].state = BTN_STATE_IDLE;
        btn_handle[i].cb[BTN_PRESS_DOWN] =
            Button_PressHandler;
        btn_handle[i].cb[BTN_LONG_PRESS_START] =
            Button_LongPressHandler;
        btn_handle[i].user_data = NULL;

        Button_Start(&btn_handle[i]);
    }
}


/****
 * @ 原型: void Button_ScanProc(void)
 * @ 输出: void
 * @ 说明: 按键扫描函数，须在5ms定时器中断中周期调用。
 *         检测到按下时自动回调 OnPress()。
 ********/
void Button_ScanProc(void)
{
    Button_Ticks();
}

/* button usr end */
