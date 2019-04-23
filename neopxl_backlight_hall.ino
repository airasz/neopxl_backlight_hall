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
int interval2=0;
int hallsensor=1;
volatile byte counter;
bool bfire=false;
int rpm;

int rev;

int r=40;
int g=0;
int b=0;
int angka=0;
void isr()
 {

   //Each rotation, this interrupt function is run twice, so take that into consideration for

   //calculating RPM

   //Update count

      counter++;
      bfire=true;
 }
void setup (){
    Serial.begin(9600);
    lighting.begin();
    lighting.show();

  counter=0;
}
int speed;
void loop (){
if(bfire){
  // cli();
  // fire();
}

    if(millis()-previousMillis>interval){
        detachInterrupt(hallsensor);
        angka+=1;
        if(angka>(1000/interval)){

          detachInterrupt(hallsensor);
          // cli  ();
          // rpm=60*1000/(millis()-passedTime)*counter;
          rpm=counter*60;     // result 200-1200rpm
          speed=counter;  
          if (counter<1){counter=1; }
          if(counter>8){counter=8;}
          // passedTime=millis();
          Serial.print("counter = ");
          Serial.println(counter);

          counter=1;
          attachInterrupt(hallsensor, isr, FALLING);

          Serial.print("rev= ");
          Serial.println(rev);
          
          angka=0;
        }

        previousMillis=millis();
    }


    if(millis()-previousMillis2>interval2){
        fire();
        // counter=1;
        previousMillis2=millis();
    }
}
void fire(){
  for (int q=0; q<PIXEL_COUNT;q++){
    	 r=random(10, 120);
    	 g=random(0, 15);
    	 if(r<80){ g=0;}
    	// if (r>40) {g=r-60;}
    	 b=0; 
    	uint32_t c =lighting.Color (r,g,b);
	    lighting.setPixelColor(q, c);
   //strip.setPixelColor(q,c);
    	
      lighting.show();
      bfire=0;
      // interval2=random(5,70);
       rev=(speed-6)*(-20);
      interval2=random(5,rev);
      // sei();

    }}  