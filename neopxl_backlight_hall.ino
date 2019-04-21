//neopxl_backlight_hall

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 6   //Digita pin I/O
//#define PIXEL_PIN 2		//Digita pin I/O
#define PIXEL_COUNT 6
//#define PIXEL_COUNT 8
Adafruit_NeoPixel lighting = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB+ NEO_KHZ800);
long previousMillis =0;
long previousMillis2 =0;

int interval =100;

int hallsensor=1;
volatile byte counter;

int angka=0;

 {

   //Each rotation, this interrupt function is run twice, so take that into consideration for

   //calculating RPM

   //Update count

      counter++;

 }
void setup (){
    Serial.begin(9600);
    lighting.begin();
    lighting.show();

  counter=0;
}
void loop (){

    if(millis()-previousMillis>interval){
            detachInterrupt(hallsensor);


    angka+=1;
    if(angka>(1000/interval)){

      detachInterrupt(hallsensor);
      // cli  ();
      // rpm=60*1000/(millis()-passedTime)*counter;
      rpm=counter*60;
      passedTime=millis();
      // Serial.print("RPM = ");
      // Serial.println(rpm);

      counter=0;
      attachInterrupt(hallsensor, isr, FALLING);
      

      Serial.print("angka= ");
      Serial.println(rpm);
      angka=0;
    }


    previousMillis=currentMillis;
    }
}