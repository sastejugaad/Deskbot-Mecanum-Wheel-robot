
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <Servo.h> 

Servo m1;
Servo m2;
Servo m3;
Servo m4;

/* Set these to your desired credentials. */
const char *ssid = "My_Robot";
const char *password = "iamnotarobot";

ESP8266WebServer server(80);


int cc_speed = 1300;
int cw_speed = 1700;
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/plain", "hello from Robot!");
}

void motor_stop(){
   m1.writeMicroseconds(1500);
   m2.writeMicroseconds(1500);
   m3.writeMicroseconds(1500);
   m4.writeMicroseconds(1500);
   
  }

void motor_forward(){
    m1.writeMicroseconds(cw_speed);
   m2.writeMicroseconds(cc_speed);
   m3.writeMicroseconds(cw_speed);
   m4.writeMicroseconds(cc_speed);
  }

void motor_back(){
  m1.writeMicroseconds(cc_speed);
   m2.writeMicroseconds(cw_speed);
   m3.writeMicroseconds(cc_speed);
   m4.writeMicroseconds(cw_speed);
  }

void motor_left(){

    m1.writeMicroseconds(cc_speed);
   m2.writeMicroseconds(cc_speed);
   m3.writeMicroseconds(cc_speed);
   m4.writeMicroseconds(cc_speed);
   
  }
void motor_right(){
   m1.writeMicroseconds(cw_speed);
   m2.writeMicroseconds(cw_speed);
   m3.writeMicroseconds(cw_speed);
   m4.writeMicroseconds(cw_speed);
  }
void motor_br(){
  // m1.writeMicroseconds(cw_speed);
   m2.writeMicroseconds(cw_speed);
   m3.writeMicroseconds(cc_speed);
  // m4.writeMicroseconds(cw_speed);
  }
void motor_bl(){
   m1.writeMicroseconds(cc_speed);
  // m2.writeMicroseconds(cw_speed);
  // m3.writeMicroseconds(cw_speed);
   m4.writeMicroseconds(cw_speed);
  }
 void motor_fr(){
   m1.writeMicroseconds(cw_speed);
  // m2.writeMicroseconds(cw_speed);
  // m3.writeMicroseconds(cw_speed);
   m4.writeMicroseconds(cc_speed);
  } 
void motor_fl(){
  // m1.writeMicroseconds(cw_speed);
   m2.writeMicroseconds(cc_speed);
   m3.writeMicroseconds(cw_speed);
  // m4.writeMicroseconds(cw_speed);
  }

void motor_sr(){
   m1.writeMicroseconds(cw_speed);
   m2.writeMicroseconds(cw_speed);
   m3.writeMicroseconds(cc_speed);
   m4.writeMicroseconds(cc_speed);
  }
void motor_sl(){
   m1.writeMicroseconds(cc_speed);
   m2.writeMicroseconds(cc_speed);
   m3.writeMicroseconds(cw_speed);
   m4.writeMicroseconds(cw_speed);
  }
  
void speed_high(){
    cw_speed = 2000;
    cc_speed = 1000;
  
}
void speed_med(){
    cw_speed = 1700;
    cc_speed = 1300;
  
}
void speed_low(){
    cw_speed = 1600;
    cc_speed = 1400;
  
}



void setup() {

  m1.attach(15);//d8
  m2.attach(D7);
  m3.attach(D6);
  m4.attach(D5);
  
  
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

 
  server.on("/", handleRoot);
 
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/fw", []() {
    motor_forward();
    server.send(200, "text/plain", "Forward");
  });
  server.on("/bk", []() {
    motor_back();
    server.send(200, "text/plain", "Back");
  });

  server.on("/st", []() {
    motor_stop();
    server.send(200, "text/plain", "Stop");
  });
  server.on("/lt", []() {
    motor_left();
    server.send(200, "text/plain", "Left");
  });
  server.on("/rt", []() {
    motor_right();
    server.send(200, "text/plain", "Right");
  });
  
    server.on("/bl", []() {
    motor_bl();
    server.send(200, "text/plain", "bl");
  });

   server.on("/br", []() {
    motor_br();
    server.send(200, "text/plain", "br");
  });
   server.on("/fl", []() {
    motor_fl();
    server.send(200, "text/plain", "fl");
  });
   server.on("/fr", []() {
    motor_fr();
    server.send(200, "text/plain", "fr");
  });
 server.on("/hs", []() {
    speed_high();
    server.send(200, "text/plain", "fr");
  });
   server.on("/ms", []() {
    speed_med();
    server.send(200, "text/plain", "ms");
  });
   server.on("/ls", []() {
    speed_low();
    server.send(200, "text/plain", "ls");
  });

  server.on("/sr", []() {
    motor_sr();
    server.send(200, "text/plain", "fr");
  });

    server.on("/sl", []() {
    motor_sl();
    server.send(200, "text/plain", "fr");
  });


  server.begin();
  Serial.println("HTTP server started");


  
}

void loop() {
  server.handleClient();
}
