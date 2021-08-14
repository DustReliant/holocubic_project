#include "bilibili_gui.h"

#include "lv_port_indev.h"
#include "lvgl.h"

// #include "img_ico.c"
// #include "bilibili_ico.c"
// #include "../../lib/lv_lib_split_jpg/lv_sjpg.h"

// LV_IMG_DECLARE( small_image_sjpg );
// LV_IMG_DECLARE( wallpaper_jpg );

LV_FONT_DECLARE(myFont);


// lv_obj_t *clock_text = NULL;
lv_obj_t *bilibili_gui = NULL;
lv_obj_t *follower_label = NULL;
lv_obj_t *img_gui = NULL;

lv_obj_t *label = NULL;
lv_obj_t *label1 = NULL;
lv_obj_t *label2 = NULL;
lv_obj_t *label3 = NULL;


static lv_style_t default_style;
static lv_style_t label_style;        //用户ID样式
static lv_style_t label1_style;       //昵称样式
static lv_style_t label2_style;       //粉丝数样式
static lv_style_t label3_style;       //粉丝数目（number）值样式
static lv_style_t style_img0;         //头像样式


void bilibili_gui_init(const char* data_card_fans , const char* data_card_name){
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
	lv_style_set_text_font(&label3_style, LV_STATE_DEFAULT, &lv_font_montserrat_30);
	lv_style_set_text_letter_space(&label3_style, LV_STATE_DEFAULT, 2);
    //头像样式
    lv_style_init(&style_img0);
    lv_style_set_image_recolor(&style_img0, LV_STATE_DEFAULT, lv_color_make(0x52, 0x19, 0x19));
	lv_style_set_image_recolor_opa(&style_img0, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_img0, LV_STATE_DEFAULT, 232);

    // 创建标签
    label = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, &label_style);
    //lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -10); // 居中对齐
	lv_obj_set_pos(label, 6, 169);//位置
    lv_obj_set_size(label, 70, 0);//
    // lv_label_set_text(label, "hello world !");
    lv_label_set_text(label, "用户ID：");
	lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

    //创建用户昵称对象
    label1 = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &label1_style);
	lv_obj_set_pos(label1, 67, 169);
	lv_obj_set_size(label1, 200, 0);
    //lv_label_set_text(label1, "溜马小哥");
    lv_label_set_text_fmt(label1, "%s", data_card_name);//参数
	lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);
    
    //创建粉丝数对象
    label2 = lv_label_create(bilibili_gui, NULL);
    lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &label2_style);
	lv_obj_set_pos(label2, 6, 209);
	lv_obj_set_size(label2, 60, 0);
    lv_label_set_text(label2, "粉丝数：");
	lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label2, LV_LABEL_ALIGN_CENTER);

    //创建“number(粉丝数)”对象
    label3 = lv_label_create(bilibili_gui, NULL);
    lv_label_set_text_fmt(label3, "%s", data_card_fans);//参数
	lv_label_set_long_mode(label3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(label3, LV_LABEL_ALIGN_CENTER);
    lv_obj_add_style(label3, LV_LABEL_PART_MAIN, &label3_style);
	lv_obj_set_pos(label3, 67, 209);
	lv_obj_set_size(label3, 70, 0);

    //创建 头像
    //
	//创建一个IMG对象并加载SD卡中的jpg图片解码显示///
	//
	// lv_obj_t * objpg =  lv_img_create(bilibili_gui, NULL);				// 创建一个IMG对象 
	// lv_img_set_src(objpg, "S:/image/x.bin");					// 加载SD卡中的JPG图片
	// lv_obj_align(objpg, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);			// 重新设置对齐
    // lv_obj_t *img0 = lv_img_create(bilibili_gui, NULL);
    // lv_obj_add_style(img0, LV_IMG_PART_MAIN, &style_img0);
    // lv_obj_set_pos(img0, 68, 30);
    // lv_obj_set_size(img0, 100, 100);
    // lv_obj_set_click(img0, true);
    // //lv_img_set_src(img0,&app_bilibili);
    // lv_img_set_pivot(img0, 24,25);
    // lv_img_set_angle(img0, 0);
}


void bilibili_gui_start(lv_scr_load_anim_t anim_type)
{
    
}

/*
 * 其他函数请根据需要添加
 */

// void display_bilibili(const char *file_name, lv_scr_load_anim_t anim_type)
// {

// }

void bilibili_obj_del(void) 
{
    if (NULL != label)
    {
        lv_obj_clean(label);
        lv_obj_clean(label1);
        lv_obj_clean(label2);
        lv_obj_clean(label3);
        label = NULL;
        label1 = NULL;
        label2 = NULL;
        label3 = NULL;
    }

}

void bilibili_gui_del(void) 
{
    bilibili_obj_del();

    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (NULL != bilibili_gui)
    {
        lv_obj_clean(bilibili_gui);
        bilibili_gui = NULL;
    }

    if (NULL != img_gui)
    {
        lv_obj_clean(img_gui);
        img_gui = NULL;
    }
    
    lv_obj_clean(act_obj); // 清空此前页面
}

// void bilibili_display_init()
// {
//     lv_obj_t *act_obj = lv_scr_act();
//     if (act_obj == bilibili_gui)
//     {
//         return;
//     }
//     lv_obj_clean(act_obj);
// }