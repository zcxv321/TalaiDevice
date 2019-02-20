#include "True_NB_bc95.h"
#include "TinyGPS++.h"
True_NB_bc95 modem;

String userid = "003027";       /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "615hou2kubpz";                   /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "TRUE NB-IoT";             /*Your private tweet meassage to dashboard*/
String public_tweet = "Data from GPS Sensor";   /*Your public tweet message to dashboard*/
TinyGPSPlus gps;
long start = 0;
char sock[] = "0\0";

float t=0;
int count =0,sig;
float latt,lngg;
String l;
String g;
void setup() {
  
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial1.begin(9600);
  
  delay(3000);
  
  Serial.println("Starting...");
  
  modem.init(Serial1);
  modem.initModem();
  
  Serial.println( "IMEI = " + modem.getIMEI() );
  Serial.println( "IMSI = " + modem.getIMSI() );
  
  while (!modem.register_network());
  delay(1000);
  
  Serial.println( modem.check_ipaddr() );
  modem.create_UDP_socket( 4700, sock);
  sig = modem.check_modem_signal();
  Serial.println(sig);
  
}

void loop() {
   while (Serial2.available()){
    gps.encode(Serial2.read());
  }
  if (millis() - start > 800) {
    String l;
    String g;
    l+=String( gps.location.lat(),7);
    g+=String(gps.location.lng(),7);
    start = millis();
  count++;
// 
//  if(count > 10){
//    count = 0;
//    sig = modem.check_modem_signal();
//    Serial.println("=== signal update ===");
//  }
  //if(gps.location.lat() != 0 || gps.location.lng() != 0){
      Serial.print("Lat:");Serial.println(gps.location.lat());
      Serial.print("Lngg:");Serial.println(gps.location.lng());
      modem.WriteDashboardIoTtweet(userid, key,0 , 0,0 , 0, l, g);
  //}
  // else{
//    Serial.println("GPS NOT UPDATE");
//    t++;
//    modem.WriteDashboardIoTtweet(userid, key,-1 , -1, sig, 0, private_tweet, public_tweet);
//    return;
// } 
  }

     

    /* Send data to IoTtweet dashboard */
    
  
}
