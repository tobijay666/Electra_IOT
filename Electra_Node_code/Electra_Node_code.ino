#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
//#include <LiquidCrystal_I2C.h>

//----------------------------------------

#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router
#define HC_Echo D6 //--> Defines Echo Pin D0 = GPIO16
#define HC_Trig D5 //--> Defines Echo Pin D1 = GPIO5
//#define MQ2_D 4 //--> Defines Digital Pin of MQ2 D2 = GPIO4
#define Re_Sw1 D7 //--> Defines the Switch 1 of Relay D8 = GPIO15
#define Re_Sw2 D8 //--> Defines the Switch 2 of Relay D6 = GPIO12
//#define Pot 14 //--> Defines the Digital pin of Potentionometer D5 = GPIO14
#define MQ2 A0
#define Buzzer 10

//LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(D4, DHT11); //(sensor pin,sensor type)

//Defining variables
long duration;
float temp;
int LvlSmo;
int distance, initialDistance, currentDistance, i;
String WebRelay1, WebRelay2;
String LightsTime;
String LocksTime;
int StatMo = 0;
int IdRelay1 = 0;
int IdRelay2 = 1;
int IdMosen = 2;
int IdDHT = 3;
int IdSmoke = 4;


  
//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Dialog 4G 139"; //--> Your wifi name or SSID.
const char* password = "BADf4De3"; //--> Your wifi password.
//----------------------------------------

//----------------------------------------Web Server address / IPv4
// If using IPv4, press Windows key + R then type cmd, then type ipconfig (If using Windows OS).
const char *host = "http://electraiot.000webhostapp.com/";
//----------------------------------------

void setup() {
// Open serial communications and wait for port to open:
delay(10000);
Serial.begin(115200);
delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  pinMode(Re_Sw1,OUTPUT); //--> Switch1 Direction output
  digitalWrite(Re_Sw1, LOW); //--> Turn off Switch1

  pinMode(Re_Sw2,OUTPUT); //--> Switch2 Direction output
  digitalWrite(Re_Sw2, LOW); //--> Turn off Switch2

//  pinMode(Pot,OUTPUT); //--> Potentionometer Direction output
//  digitalWrite(Pot, LOW); //--> Turn off potentionometer

//  pinMode(MQ2_D,INPUT); //--> Potentionometer Direction output

  pinMode(HC_Trig,OUTPUT); //--> Potentionometer Direction output
  digitalWrite(HC_Trig, LOW); //--> Turn off potentionometer
  
  pinMode(HC_Echo,INPUT); //--> Potentionometer Direction output
  digitalWrite(HC_Echo, LOW); //--> Turn off potentionometer

//  lcd.begin();
//  lcd.backlight();
//  lcd.clear();  
  dht.begin();
  
  delay(10000); // ---delaying the system for 20s for the smoke sensor to heat up
  //initialDistance = GetDistance();

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
}



float DHT11sensor() {
  //float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0.0;
  }


//  lcd.setCursor(0, 0);
//  lcd.print("T :");
//  lcd.print(t);
  return t;

//  lcd.setCursor(0, 1);
//  lcd.print("H :");
//  lcd.print(h);
}

long GetDistance(){
  //int i=10;
  
  //while( i<=10 ) {
  // Clears the HC_Trig
  digitalWrite(HC_Trig, LOW);
  delayMicroseconds(2);

  // Sets the HC_Trig on HIGH state for 10 micro seconds
  digitalWrite(HC_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_Trig, LOW);

  // Reads the HC_Echo, returns the sound wave travel time in microseconds
  duration = pulseIn(HC_Echo, HIGH);
  long t = pulseIn(HC_Echo, HIGH);
  long cm = t / 29 / 2;
//  lcd.setCursor(9, 1);
//  lcd.print("W :");
//  lcd.print(cm);
//  lcd.print("  ");

  // Calculating the distance
  distance = duration*0.034/2;
  //sumDistance += distance;
  //}
  //int averageDistance= sumDistance/10;
  return distance;

}

int gassensor() {
  int value = analogRead(MQ2);
  Serial.println(value);
  value = map(value, 0, 1024, 0, 100);
  if (value <= 35) {
    digitalWrite(Buzzer, LOW);
  } else if (value > 35) {
    digitalWrite(Buzzer, HIGH);
  }
  
//  lcd.setCursor(9, 0);
//  lcd.print("G :");
//  lcd.print(value);
//  lcd.print("  ");
  return value;
  
}



void loop() { // run over and over


  delay(1000);
  
  currentDistance = GetDistance() + 10;
  if ( currentDistance > 10) {
        StatMo = (int)(currentDistance& 0xFFFFFFFF ) ;
        Serial.println(StatMo);
        String msg1 = Con_Web2(IdMosen,StatMo);
        //Serial.println(msg1);

      }
  
  
  delay(500);
  
  WebRelay1 = Con_Web(IdRelay1);
 
  if (WebRelay1 == "On"){
    digitalWrite(Re_Sw1, HIGH); //--> Turns on Switch
  }
  else if (WebRelay1 == "Off"){
    digitalWrite(Re_Sw1, LOW); //--> Turns off Switch
  }
  delay(500);
  
    WebRelay2 = Con_Web(IdRelay2);
 
  if (WebRelay2 == "On"){
    digitalWrite(Re_Sw2, HIGH); //--> Turns on Switch
  }
  else if (WebRelay2 == "Off"){
    digitalWrite(Re_Sw2, LOW); //--> Turns off Switch
  }
  delay(500);
  temp = DHT11sensor();
  Con_Web3(IdDHT,temp);
  
  delay(500);
  LvlSmo = gassensor();
  Con_Web4(IdSmoke,LvlSmo);

    LightsTime  = Con_Web5(IdRelay1);
    if (LightsTime == "On"){
          digitalWrite(Re_Sw1, HIGH); //--> Turns on Switch
  }
  else if (LightsTime == "Off"){
    digitalWrite(Re_Sw1, LOW); //--> Turns off Switch
  }
    LocksTime = Con_Web5(IdRelay2);
    if (LocksTime == "On"){
          digitalWrite(Re_Sw2, HIGH); //--> Turns on Switch
  }
  else if (LocksTime == "Off"){
    digitalWrite(Re_Sw2, LOW); //--> Turns off Switch
  }
  
  //delay(5000);//only to debug ... remove afterwards

}
