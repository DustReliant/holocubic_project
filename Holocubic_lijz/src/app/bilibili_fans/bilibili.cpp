#include "bilibili.h"
#include "bilibili_gui.h"
#include "../sys/app_contorller.h"
#include "../../network.h"
#include "../../common.h"

#include <ArduinoJson.h>

//String UID = "344470052";
//String Url = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;   // 粉丝数
//String Url = "http://api.bilibili.com/x/web-interface/card?mid=" + UID;   // 粉丝数
const char* host = "api.bilibili.com";

long follower = NULL;   // 粉丝数
long face = NULL; //
String fans="";
/**************************修改部分************************************************/


/******************************修改部分********************************************/

void bilibili_init(void){
    Serial.println("B站粉丝获取开始");


    //创建TCP连接
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)){
        Serial.println("Connection failed");  //网络请求无响应打印连接失败
        return;
    }
    //URL请求地址
    String url = "/x/web-interface/card?mid=" + UID + "&jsonp=jsonp"; // B站粉丝数 方案1 请求头
    //String url = "/x/relation/stat?vmid=" + g_cfg.UID + "&jsonp=jsonp"; // B站粉丝数 方案2 请求头

    //发送网络请求
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
       "Host: " + host + "\r\n" +
       "Connection: close\r\n\r\n");
    delay(2000);
    //定义answer变量用来存放请求网络服务器后返回的数据
    String answer;
    while(client.available()){
        String line = client.readStringUntil('\r');
        answer += line;
    }
    //断开服务器连接
    client.stop();
    Serial.println();
    Serial.println("closing connection");
    // 方案1   获得json格式的数据
    /**************************新增json数据解析************/

    // Stream& input;

    //Bilibili bilibili;

    // String jsonAnswer;
    // int jsonIndex;
    // //找到有用的返回数据位置i 返回头不要
    // for (int i = 0; i < answer.length(); i++) {
    // if (answer[i] == '{') {
    //         jsonIndex = i;
    //         break;
    //     }
    // }
    // jsonAnswer = answer.substring(jsonIndex);
    // Serial.println();
    // Serial.println("JSON answer: ");
    // Serial.println(jsonAnswer); 
    // StaticJsonDocument<2048> doc;
    // deserializeJson(doc, jsonAnswer);

    // int code = doc["code"]; // 0
    // const char* message = doc["message"]; // "0"
    // int ttl = doc["ttl"]; // 1

    // JsonObject data = doc["data"];

    // JsonObject data_card = data["card"];
    // const char* data_card_mid = data_card["mid"]; // "344470052"
    // const char* data_card_name = data_card["name"]; // "溜马小哥"
    // bool data_card_approve = data_card["approve"]; // false
    // const char* data_card_sex = data_card["sex"]; // "男"
    // const char* data_card_rank = data_card["rank"]; // "10000"
    // const char* data_card_face = data_card["face"];
    // const char* data_card_DisplayRank = data_card["DisplayRank"]; // "0"
    // int data_card_regtime = data_card["regtime"]; // 0
    // int data_card_spacesta = data_card["spacesta"]; // 0
    // const char* data_card_birthday = data_card["birthday"]; // nullptr
    // const char* data_card_place = data_card["place"]; // nullptr
    // const char* data_card_description = data_card["description"]; // nullptr
    // int data_card_article = data_card["article"]; // 0

    // int data_card_fans = data_card["fans"]; // 577
    // int data_card_friend = data_card["friend"]; // 111
    // int data_card_attention = data_card["attention"]; // 111
    // const char* data_card_sign = data_card["sign"]; // "骑着蜗牛也要冲"

    // JsonObject data_card_level_info = data_card["level_info"];
    // int data_card_level_info_current_level = data_card_level_info["current_level"]; // 4
    // int data_card_level_info_current_min = data_card_level_info["current_min"]; // 0
    // int data_card_level_info_current_exp = data_card_level_info["current_exp"]; // 0
    // int data_card_level_info_next_exp = data_card_level_info["next_exp"]; // 0

    // JsonObject data_card_pendant = data_card["pendant"];
    // int data_card_pendant_pid = data_card_pendant["pid"]; // 0
    // const char* data_card_pendant_name = data_card_pendant["name"]; // nullptr
    // const char* data_card_pendant_image = data_card_pendant["image"]; // nullptr
    // int data_card_pendant_expire = data_card_pendant["expire"]; // 0
    // const char* data_card_pendant_image_enhance = data_card_pendant["image_enhance"]; // nullptr
    // const char* data_card_pendant_image_enhance_frame = data_card_pendant["image_enhance_frame"]; // nullptr

    // JsonObject data_card_nameplate = data_card["nameplate"];
    // int data_card_nameplate_nid = data_card_nameplate["nid"]; // 0
    // const char* data_card_nameplate_name = data_card_nameplate["name"]; // nullptr
    // const char* data_card_nameplate_image = data_card_nameplate["image"]; // nullptr
    // const char* data_card_nameplate_image_small = data_card_nameplate["image_small"]; // nullptr
    // const char* data_card_nameplate_level = data_card_nameplate["level"]; // nullptr
    // const char* data_card_nameplate_condition = data_card_nameplate["condition"]; // nullptr

    // JsonObject data_card_Official = data_card["Official"];
    // int data_card_Official_role = data_card_Official["role"]; // 0
    // const char* data_card_Official_title = data_card_Official["title"]; // nullptr
    // const char* data_card_Official_desc = data_card_Official["desc"]; // nullptr
    // int data_card_Official_type = data_card_Official["type"]; // -1

    // int data_card_official_verify_type = data_card["official_verify"]["type"]; // -1
    // const char* data_card_official_verify_desc = data_card["official_verify"]["desc"]; // nullptr

    // JsonObject data_card_vip = data_card["vip"];
    // int data_card_vip_type = data_card_vip["type"]; // 0
    // int data_card_vip_status = data_card_vip["status"]; // 0
    // int data_card_vip_due_date = data_card_vip["due_date"]; // 0
    // int data_card_vip_vip_pay_type = data_card_vip["vip_pay_type"]; // 0
    // int data_card_vip_theme_type = data_card_vip["theme_type"]; // 0

    // JsonObject data_card_vip_label = data_card_vip["label"];
    // const char* data_card_vip_label_path = data_card_vip_label["path"]; // nullptr
    // const char* data_card_vip_label_text = data_card_vip_label["text"]; // nullptr
    // const char* data_card_vip_label_label_theme = data_card_vip_label["label_theme"]; // nullptr
    // const char* data_card_vip_label_text_color = data_card_vip_label["text_color"]; // nullptr
    // int data_card_vip_label_bg_style = data_card_vip_label["bg_style"]; // 0
    // const char* data_card_vip_label_bg_color = data_card_vip_label["bg_color"]; // nullptr
    // const char* data_card_vip_label_border_color = data_card_vip_label["border_color"]; // nullptr

    // int data_card_vip_avatar_subscript = data_card_vip["avatar_subscript"]; // 0
    // const char* data_card_vip_nickname_color = data_card_vip["nickname_color"]; // nullptr
    // int data_card_vip_role = data_card_vip["role"]; // 0
    // const char* data_card_vip_avatar_subscript_url = data_card_vip["avatar_subscript_url"]; // nullptr
    // int data_card_vip_vipType = data_card_vip["vipType"]; // 0
    // int data_card_vip_vipStatus = data_card_vip["vipStatus"]; // 0

    // bool data_following = data["following"]; // true
    // int data_archive_count = data["archive_count"]; // 37
    // int data_article_count = data["article_count"]; // 0
    // int data_follower = data["follower"]; // 577


    // fans = data_card_fans;
    // Serial.println("粉丝数（follower）: ");
    // char data_card_fans[10] = {0};
    // sprintf(data_card_fans, "%d", follower);
    // bilibili_gui_init(data_card_fans);   //
    // Serial.println(fans);


    //方案2 
    /**************************新增json数据解析************/
    String jsonAnswer;
    int jsonIndex;
    //找到有用的返回数据位置i 返回头不要
    for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
            jsonIndex = i;
            break;
        }
    }
    jsonAnswer = answer.substring(jsonIndex);
    Serial.println();
    Serial.println("JSON answer: ");
    Serial.println(jsonAnswer); 
    StaticJsonDocument<256> doc;
    deserializeJson(doc, jsonAnswer);
    JsonObject data = doc["data"];
    JsonObject data_card = data["card"];
    //face = data["follower"]; // 
    face = data_card["fans"]; // 
    follower = data["follower"];
    
    Serial.println("face: ");
    Serial.println(face);
    
    Serial.println("粉丝数（follower）: ");
    Serial.println(follower);
    
    char data_card_fans[10] = {0};
    sprintf(data_card_fans, "%ld", follower);
    // bilibili_gui_init(data_card_fans);   //
    bilibili_gui_init(data_card_fans);

    /**************************方案2结束**************************/
}

void bilibili_process(AppController *sys,
                          const Imu_Action *act_info)
{
    if (RETURN == act_info->active)
    {
        Serial.println("123");
        sys->app_exit(); // 退出APP
        return;
    }
    // delay(300);
}

void bilibili_exit_callback(void){
    Serial.println("B站退出");
}

void bilibili_event_notification(APP_EVENT event){
    

}

APP_OBJ bilibili_app = {"Media", &app_bilibili, bilibili_init,
                     bilibili_process, bilibili_exit_callback,
                     bilibili_event_notification};
