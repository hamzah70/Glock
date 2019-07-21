#include <ESP8266WiFi.h>
#include<stdlib.h>
#include<FirebaseArduino.h>
#include <WiFiManager.h>    
//#include<Servo.h>
#include<Stepper.h>

// https://github.com/tzapu/WiFiManager

#define FIREBASE_HOST "location-db-22d0d.firebaseio.com"
#define AUTH "5nEf1hvCX6OUtfEy2xf4nw9f44dZzp9yupeJKYcg"
#define FIREBASE_JSONBUFFER_SIZE JSON_OBJECT_SIZE(128)


const char* ssid="ONEPLUS";
const char* password = "hamzahakhtar";
float Current_Latitude, Current_Longitude, Current_Speed;
float LatHome , LongHome ;
float LatSchool , LongSchool; 
float LatTuition , LongTuition;
float LatPlayground , LongPlayground ;
float LatRelative , LongRelative ;
float LatFriend , LongFriend ;
float LatCo_curricular , LongCo_curricular ;
int ledPin = 13;

//Servo myservo;

const int stepsPerRevolution = 200;  

Stepper myStepper(64, D1, D2, D5, D6);  //Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


float LatDifference = 0.0005;
float LongDifference = 0.0005;
float angle_rotated = 0;

void setup() {
  Firebase.begin(FIREBASE_HOST, AUTH);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  //myservo.attach(2);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println(); 
  Serial.print("Connecting");

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  digitalWrite( ledPin , HIGH);
  Serial.println();
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  Serial.println(WiFi.status());
  

  LatHome = Firebase.getString("LOCATION:/GLOCK/LatHome").substring(1, -1).toFloat(); 
  //Float l = LatHome.toFloat();
  LongHome = Firebase.getString("LOCATION:/GLOCK/LongHome").substring(1,Firebase.getString("LOCATION:/GLOCK/LongHome").length()-1).toFloat(); 
  LatSchool = Firebase.getString("LOCATION:/GLOCK/LatSchool").substring(1,Firebase.getString("LOCATION:/GLOCK/LatSchool").length()-1).toFloat();
  LongSchool = Firebase.getString("LOCATION:/GLOCK/LongSchool").substring(1, Firebase.getString("LOCATION:/GLOCK/LongSchool").length()-1).toFloat();
  LatTuition = Firebase.getString("LOCATION:/GLOCK/LatTuition").substring(1, Firebase.getString("LOCATION:/GLOCK/LatTuition").length()-1).toFloat();
  LongTuition = Firebase.getString("LOCATION:/GLOCK/LongTuition").substring(1, Firebase.getString("LOCATION:/GLOCK/LongTuition").length()-1).toFloat();
  LatPlayground = Firebase.getString("LOCATION:/GLOCK/LatPlayground").substring(1, Firebase.getString("LOCATION:/GLOCK/LatPlayground").length()-1).toFloat();
  LongPlayground = Firebase.getString("LOCATION:/GLOCK/LongPlayground").substring(1, Firebase.getString("LOCATION:/GLOCK/LongPlayground").length()-1).toFloat();
  LatRelative = Firebase.getString("LOCATION:/GLOCK/LatRelative").substring(1, Firebase.getString("LOCATION:/GLOCK/LatRelative").length()-1).toFloat();
  LongRelative = Firebase.getString("LOCATION:/GLOCK/LongRelative").substring(1, Firebase.getString("LOCATION:/GLOCK/LongRelative").length()-1).toFloat();
  LatFriend = Firebase.getString("LOCATION:/GLOCK/LatFriend").substring(1, Firebase.getString("LOCATION:/GLOCK/LatFriend").length()-1).toFloat();
  LongFriend = Firebase.getString("LOCATION:/GLOCK/LongFriend").substring(1,Firebase.getString("LOCATION:/GLOCK/LongFriend").length()-1).toFloat();
  LatCo_curricular = Firebase.getString("LOCATION:/GLOCK/LatCo_curricular").substring(1, Firebase.getString("LOCATION:/GLOCK/LatCo_curricular").length()-1).toFloat();
  LongCo_curricular = Firebase.getString("LOCATION:/GLOCK/LongCo_curricular").substring(1, Firebase.getString("LOCATION:/GLOCK/LongCo_curricular").length()-1).toFloat();
  

}

int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
int f=0;
int g=0;
int h=0;
int i=0;

int angle_to_step(int x){
  float z = x/0.17142;
  int y = (int) z;
  return y;
}


void loop() {
  Current_Latitude = Firebase.getString("LOCATION:/Location/Latitude").substring(1,Firebase.getString("LOCATION:/Location/Latitude").length()-1).toFloat();
  Current_Longitude = Firebase.getString("LOCATION:/Location/Longitude").substring(1,Firebase.getString("LOCATION:/Location/Longitude").length()-1).toFloat();
  Current_Speed = Firebase.getString("LOCATION:/Location/Speed").substring(1,Firebase.getString("LOCATION:/Location/Speed").length()-1).toFloat();
  myStepper.setSpeed(100);
  Serial.println(Current_Latitude,6);
  Serial.println(Current_Longitude,6);
//  Current_Speed = 2.0;
   if(Current_Speed>1.0){
    float angle = 160;
    if(h==0){
      h=1;
      a=0,b=0,c=0,d=0,e=0,f=0,g=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  
  else if(abs(Current_Latitude-LatHome) <= LatDifference && abs(Current_Longitude-LongHome) <= LongDifference){
    float angle = 0;
    if(a==0){
      Serial.println("a=0 first");
      a=1;
      b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
        myStepper.setSpeed(1000);
        myStepper.step(1);
        delay(25);}
    }

    }
  else if(abs(Current_Latitude-LatSchool) <= LatDifference && abs(Current_Longitude-LongSchool) <= LongDifference){
    float angle = 40;
    if(b==0){
      Serial.println("b=0 second");
      b=1;
      a=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  else if(abs(Current_Latitude-LatTuition) <= LatDifference && abs(Current_Longitude-LongTuition) <= LongDifference){
    float angle = 80;
    Serial.println("c=0 third");
    if(c==0){
      c=1;
      a=0,b=0,d=0,e=0,f=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  else if(abs(Current_Latitude-LatPlayground) <= LatDifference && abs(Current_Longitude-LongPlayground) <= LongDifference){
    float angle = 120;
    Serial.println("d=0 fourth");
    if(d==0){
      d=1;
      a=0,b=0,c=0,e=0,f=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  else if(abs(Current_Latitude-LatRelative) <= LatDifference && abs(Current_Longitude-LongRelative) <= LongDifference){
    float angle = 240;
    Serial.println("e=0 fifth");
    if(e==0){
      e=1;
      a=0,b=0,c=0,d=0,f=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  else if(abs(Current_Latitude-LatFriend) <= LatDifference && abs(Current_Longitude-LongFriend) <= LongDifference){
    float angle = 280;
    Serial.println("f=0 sixth");
    if(f==0){
      f=1;
      a=0,b=0,c=0,d=0,e=0,g=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  else if(abs(Current_Latitude-LatCo_curricular) <= LatDifference && abs(Current_Longitude-LongCo_curricular) <= LongDifference){
    float angle = 320;
    Serial.println("g=0 seventh");
    if(g==0){
      g=1;
      a=0,b=0,c=0,d=0,e=0,f=0,h=0,i=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
    }

  }
  
  else{
    float angle = 200;
//    Serial.println("hello");
    if(i==0){
       Serial.println("hello");
      i=1;
      a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;
      int angle_final = angle - angle_rotated;
      int angle_rotated = angle;
      int x=angle_to_step(angle_final);
      //myStepper.step(x);
      for(int k=0;k<x;k++){
      myStepper.setSpeed(1000);
      myStepper.step(1);
      delay(25);}
      //delay(10000);
    }
    

  }
}
