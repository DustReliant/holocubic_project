#include "bilibili.h"
#include "bilibili_gui.h"
#include "../sys/app_contorller.h"
#include "../../common.h"
/**************************修改部分********************************/
//#include <WiFi.h>
//#include <HTTPClient.h>
#include <ArduinoJson.h>

DynamicJsonBuffer jsonBuffer(256); // ArduinoJson V5

String UID = "388994555";
String followerUrl = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;   // 粉丝数

long follower = 0;   // 粉丝数


void getFollower(String url)
{
    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if (httpCode == 200)
    {
        Serial.println("Get OK");
        String resBuff = http.getString();

        // ---------- ArduinoJson V5 ----------
        JsonObject &root = jsonBuffer.parseObject(resBuff);
        if (!root.success())
        {
          Serial.println("parseObject() failed");
          return;
        }

        follower = root["data"]["follower"];
        Serial.print("Fans: ");
        Serial.println(follower);
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %d\n", httpCode);
    }

    http.end();
}
/*******************************修改部分********************************************/

void bilibili_init(void){
    
}

void bilibili_process(AppController *sys,
                          const Imu_Action *act_info)
{
    if (RETURN == act_info->active)
    {
        sys->app_exit(); // 退出APP
        return;
    }
    // delay(300);
}

void bilibili_exit_callback(void){
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, "http://api.bilibili.com/x/relation/stat?vmid="+UID)) {
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    DynamicJsonBuffer jsonBuffer;
    JsonObject& res_json = jsonBuffer.parseObject(payload);
    String follower = res_json["data"]["follower"];
    if(follower!="") {
      bfs=follower;
    }
    jsonBuffer.clear();
  }

}

void bilibili_event_notification(APP_EVENT event){


}

APP_OBJ bilibili_app = {"Media", &app_bilibili, bilibili_init,
                     bilibili_process, bilibili_exit_callback,
                     bilibili_event_notification};
