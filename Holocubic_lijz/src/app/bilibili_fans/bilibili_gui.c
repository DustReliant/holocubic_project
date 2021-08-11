#include "bilibili_gui.h"

#include "lv_port_indev.h"
#include "lvgl.h"


LV_FONT_DECLARE(myFont)

// lv_obj_t *clock_text = NULL;
lv_obj_t *bilibili_gui = NULL;
lv_obj_t *follower_label = NULL;

static lv_style_t default_style;
static lv_style_t label_style;
static lv_style_t label1_style;
static lv_style_t label2_style;
static lv_style_t label3_style;


void bilibili_gui_init(const char* data_card_fans){
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
    //“用户ID”样式
    lv_style_init(&label_style);
    lv_style_set_text_opa(&label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    //lv_style_set_text_color(&label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);//字体颜色白色
    lv_style_set_text_color(&label_style, LV_STATE_DEFAULT, lv_color_make(0x04, 0xff, 0x00));//字体颜色
    lv_style_set_text_font(&label_style, LV_STATE_DEFAULT, &myFont);
    //用户昵称样式
    lv_style_init(&label1_style);
    lv_style_set_text_color(&label1_style, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x9c, 0xf0));
	lv_style_set_text_font(&label1_style, LV_STATE_DEFAULT, &myFont);
	lv_style_set_text_letter_space(&label1_style, LV_STATE_DEFAULT, 2);
    //粉丝数样式
    lv_style_init(&label2_style);
    lv_style_set_text_opa(&label2_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&label2_style, LV_STATE_DEFAULT, lv_color_make(0x04, 0xff, 0x00));//字体颜色
    lv_style_set_text_font(&label2_style, LV_STATE_DEFAULT, &myFont);
    //“number”样式
    lv_style_init(&label3_style);
    lv_style_set_text_color(&label3_style, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_text_font(&label3_style, LV_STATE_DEFAULT, &lv_font_montserrat_20);
	lv_style_set_text_letter_space(&label3_style, LV_STATE_DEFAULT, 2);



    // 创建标签
    lv_obj_t *label = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &label_style);
    //lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -10); // 居中对齐
	lv_obj_set_pos(label, 6, 169);//位置
    lv_obj_set_size(label, 70, 0);//
    // lv_label_set_text(label, "hello world !");
    lv_label_set_text(label, "用户ID：");
	lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

    //创建用户昵称对象
    lv_obj_t *label1 = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &label1_style);
	lv_obj_set_pos(label1, 67, 169);
	lv_obj_set_size(label1, 200, 0);
    lv_label_set_text(label1, "溜马小哥");
	lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);
    
    //创建粉丝数对象
    lv_obj_t *label2 = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &label2_style);
	lv_obj_set_pos(label2, 6, 209);
	lv_obj_set_size(label2, 60, 0);
    lv_label_set_text(label2, "粉丝数：");
	lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label2, LV_LABEL_ALIGN_CENTER);

    //创建“number(粉丝数)”对象
    lv_obj_t *label3 = lv_label_create(bilibili_gui, NULL);
    //lv_label_set_text(label3, "578");
    lv_label_set_text_fmt(label3, "%s", data_card_fans);//参数
	lv_label_set_long_mode(label3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label3, LV_LABEL_ALIGN_CENTER);
    lv_obj_add_style(label3, LV_LABEL_PART_MAIN, &label3_style);
	lv_obj_set_pos(label3, 67, 209);
	lv_obj_set_size(label3, 70, 0);
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