#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RV8523.h>

RV8523 rtc;

#define RGBLEDPIN    A3

// 110 LED's für jeden Buchstaben eine.
#define N_LEDS 110

Adafruit_NeoPixel led = Adafruit_NeoPixel(N_LEDS, RGBLEDPIN, NEO_GRB + NEO_KHZ800);

uint32_t farbe = led.Color(0, 200, 0);

// Definition der Wörter
// Jede Zahl steht für die Position im Led led. 
// -1 schließt das Wort ab. 

int ES[] = {10,9,-1};
int IST[] = {7,6,5,-1};

int NACH[] = {35,36,37,38,-1};
int VOR[] = {39,40,41,-1};
int HALB[] = {51,52,53,54,-1};
int UHR[] = {107,108,109,-1};

int FUENF_NV[] ={0,1,2,3,-1};
int ZEHN_NV[] = {11,12,13,14,-1};
int ZWANZIG_NV[] = {15,16,17,18,19,20,21,-1};
int VIERTEL_NV[] = {22,23,24,25,26,27,28,-1};


int EINS[] = {57,58,59,60,-1};
int ZWEI[] = {55,56,57,58,-1};
int DREI[] = {72,73,74,75,-1};
int VIER[] = {84,85,86,87,-1};
int FUENF[] = {66,67,68,69,-1};
int SECHS[] = {100,101,102,103,104,-1};
int SIEBEN[] = {60,61,62,63,64,65,-1};

int ACHT[] = {94,95,96,97,-1};
int NEUN[] = {80,81,82,83,-1};
int ZEHN[] = {90,91,92,93,-1};
int ELF[] = {77,78,79,-1};
int ZWOELF[] = {45,46,47,48,49,-1};


uint8_t sekunde, minute, stunde, tag, monat;
uint16_t jahr;

void setup(){
  led.begin();
  
  // LED Helligkeit set
  led.setBrightness(30);  
  led.show();
  
  // RTC Modul starten.
  rtc.start();
  rtc.get(&sekunde, &minute, &stunde, &tag, &monat, &jahr);
  
}


void loop(){

  rtc.get(&sekunde, &minute, &stunde, &tag, &monat, &jahr);
  
  // Es ist wird immer geschrieben... 
  schreibeWort(ES,farbe);
  schreibeWort(IST,farbe);
  
  // Uhrzeit vor der nächsten vollen stunde
  // Bspw. 3:40 wird zu 20 vor 4
  if (minute >= 30)  stunde++;
   
  // Fünf vor oder Nach   
  if(((minute <= 5) && (minute > 0)) || ((minute >= 55)  && (minute <= 59))) {
     schreibeWort(FUENF_NV,farbe);
     schreibe_vor_oder_nach();
  }
   
  // Zehn vor oder Nach
  if(((minute <= 10) &&  (minute > 5) ) ||(( minute >= 50) && (minute < 55))) {
     schreibeWort(ZEHN_NV,farbe);
     schreibe_vor_oder_nach();
  }
   
  // Fünfzehn vor oder Nach
  if(((minute <= 15) && (minute > 10)) || ((minute >= 45) && (minute < 50 ))) {
     schreibeWort(VIERTEL_NV,farbe);
     schreibe_vor_oder_nach();
  } 
   
  // Zwanzig vor oder nach
  if(((minute <= 20) && (minute > 15)) || ((minute >= 35) && (minute < 45)) ) {
     schreibeWort(ZWANZIG_NV,farbe);
     schreibe_vor_oder_nach();
  }
   
  // Fünf vor oder nach halb 
  if(((minute < 30) && (minute > 20)) || ((minute > 30 ) && (minute < 35)) ) {
     schreibeWort(FUENF_NV,farbe);
     schreibeWort(HALB,farbe);
     // Speziealfall 
     if (minute <= 29) 
      schreibeWort(VOR,farbe);
     else
      schreibeWort(NACH,farbe);
  } 
 
  if (minute == 30){
    schreibeWort(HALB,farbe);
  }
 
  // Die Stunde ausgeben
  switch(stunde){
    case 1:
     schreibeWort(EINS, farbe);
    break;
    case 2:
     schreibeWort(ZWEI, farbe);
    break;
    case 3:
     schreibeWort(DREI, farbe);
    break;
    case 4:
     schreibeWort(VIER, farbe);
    break;
    case 5:
     schreibeWort(FUENF, farbe);
    break;
    case 6:
     schreibeWort(SECHS, farbe);
    break;
    case 7:
     schreibeWort(SIEBEN, farbe);
    break;
    case 8:
     schreibeWort(ACHT, farbe);
    break;
    case 9:
     schreibeWort(NEUN, farbe);
    break;
    case 10:
     schreibeWort(ZEHN, farbe);
    break;
    case 11:
     schreibeWort(ELF, farbe);
    break;
    case 12:
     schreibeWort(ZWOELF, farbe);
    break;    
  }
  
  // Schreibe UHR zu jeder vollen Stunde.
  if (minute == 0){ 
    schreibeWort(UHR,farbe);
  }
  
  delay(30000);
  led.clear();
}

// Hilfsfunktion ist es vor oder nach?
void schreibe_vor_oder_nach(){
  if (minute <= 29) 
    schreibeWort(NACH,farbe);
  else
    schreibeWort(VOR,farbe);
}
 
// Hilfsfuntion zum schreiben der Wörter
void schreibeWort(int arrWort[], uint32_t intColor){
  for(int i = 0; i < led.numPixels() + 1; i++){
    if(arrWort[i] == -1){
      led.show();
      break;
    }else{
      led.setPixelColor(arrWort[i],intColor);
    }
  }
}
