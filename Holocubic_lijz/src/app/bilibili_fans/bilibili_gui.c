#include "bilibili_gui.h"

#include "lv_port_indev.h"
#include "lvgl.h"


LV_FONT_DECLARE(myFont)

// lv_obj_t *clock_text = NULL;
lv_obj_t *bilibili_gui = NULL;
lv_obj_t *follower_label = NULL;

static lv_style_t default_style;
static lv_style_t label_style;


void bilibili_gui_init(long follower){
    //lv_obj_t * lable = lv_obj_create(NULL, NULL);

        // 初始化屏幕
    bilibili_gui = lv_obj_create(NULL, NULL);
    lv_obj_add_style(bilibili_gui, LV_BTN_PART_MAIN, &default_style);
    lv_scr_load(bilibili_gui);
    // 初始化默认样式
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));

    lv_style_init(&label_style);
    lv_style_set_text_opa(&label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);


    // 创建标签
    lv_obj_t *label = lv_label_create(bilibili_gui, NULL);
    lv_label_set_text(label, "hello world !");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -10); // 居中对齐
    lv_obj_set_size(label, 150, 150);


    lv_obj_add_style(follower_label, LV_LABEL_PART_MAIN, &label_style);
    lv_label_set_text(follower_label, follower);
    lv_obj_align(follower_label, NULL, LV_ALIGN_OUT_BOTTOM_LEFT, 15, -95);
}


void bilibili_gui_start(lv_scr_load_anim_t anim_type)
{
    display_init();
}

/*
 * 其他函数请根据需要添加
 */

// void display_bilibili(const char *file_name, lv_scr_load_anim_t anim_type)
// {

// }

void bilibili_gui_del(void) 
{
    if (NULL != bilibili_gui)
    {
        lv_obj_clean(bilibili_gui);
        bilibili_gui = NULL;
    }
}

// void display_init()
// {
//     lv_obj_t *act_obj = lv_scr_act();
//     if (act_obj == bilibili_gui)
//     {
//         return;
//     }
//     lv_obj_clean(act_obj);
// }