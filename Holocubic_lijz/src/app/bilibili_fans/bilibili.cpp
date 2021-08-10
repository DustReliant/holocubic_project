#include "bilibili.h"
#include "bilibili_gui.h"
#include "../sys/app_contorller.h"
#include "../../common.h"

#include <ArduinoJson.h>

String UID = "344470052";
//String Url = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;   // 粉丝数
const char* host = "api.bilibili.com";

long follower = 0;   // 粉丝数
long face = 0; //
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
    //String url = "/x/web-interface/card?mid=" + UID + "&jsonp=jsonp"; // B站粉丝数
    String url = "/x/relation/stat?vmid=" + UID + "&jsonp=jsonp"; // B站粉丝数

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
    //获得json格式的数据
 
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
    face = data["face"]; // 
    follower = data["follower"]; // 
    Serial.println("face: ");
    Serial.println(face);
    Serial.println("follower: ");
    Serial.println(follower);

    //bilibili_gui_init(follower);   不能执行这个显示函数
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
