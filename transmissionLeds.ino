#include "FastLED.h"
#include "math.h"
#define NUM_LEDS 450
#define DATA_PIN 6
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];
int incomingByte = 0;
boolean beat;
int bright;
void setup() {
 Serial.begin(9600); 
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  mcgillColor();
  colorSwipe();
  randomPoint();
  randomPoint();

  partStrip();
  createBullet();
  theaterChase();
  
  reactBeatFull();
  //createBulletBis();

  //partStrip();
  //colorWipe();
  // createBullet();
  // reactBeatFull();
  //partStripLiving();
  //partStrip();
  //testFreq();
  //theaterChase();
}
void mcgillColor(){
 int count = 0;
 int red = 0;
 int white = 0;
 while(count < 25){
   if(count%2 == 0){
        int red = 255;
        int white = 0;
   }
    else{
         int red = 0;
         int white = 255;
    }
   int countbis = 0;
   for(int i = 0 ; i < NUM_LEDS; i++){
         if(countbis == 20){
            if(red == 0){
               red = 255;
            }
            else{
               red = 0; 
            }
            countbis = 0;
         }
         else{
           countbis++;
         }
         leds[i].setHSV(0,red,255);
   }
    FastLED.show();
    delay(400);
    count++;
 }
}
void colorSwipe(){
 int count = 0;
 int change = random(1,1000);
 int colorRandom = random(1,255);
 int rep = 0;
 while(rep < 3){
    for(int i = 0 ; i < NUM_LEDS;i++){
       leds[i].setHSV(((count+i+colorRandom)%255),255,((count+i+150)%255));
    }
    FastLED.show();
    delay(1);
    if(count == change){
       count--; 
       change--;
    }
    else{
       count++; 
    }
    if(count == 0){
      rep++;
      colorRandom = random(1,255);
      change = random(1,350);
    }
 }
}
void randomPoint(){
 for(int i = 0 ; i < 450 ; i++){
      leds[i].setHSV(0,0,0);
 }
 FastLED.show();
 int count = 0;
 int on1[150];
 //int on2[220]
 int color = random(1,255);
 for(int i = 0; i < 150 ; i++){
  on1[i] = i; 
 }
 /*for(int i = 0 ; i < 440 ; i++){
   if(i<220){
     on1[i] = i;
   }
   else{
     on2[i] = i;
   }
 } */
 for (int i = 0; i < 150; i++) {
    int j = i + random(1,2000) % (150 - i);
    int temp = on1[i];
    on1[i] = on1[j];
    on1[j] = temp;
  }
 while(count < 150){
     
     //int pos = count < 220:on1[count]?on2[count];
     leds[on1[count]*3].setHSV(color,255,255);
     leds[on1[count]*3+1].setHSV(color,255,255);
     leds[on1[count]*3+2].setHSV(color,255,255);
     FastLED.show();
     count++;
     delay(10);
 }
}
void partStripLiving(){
 int count = 0; 
 while(count < 500){
  updateBeat(); 
  if(beat){
    for(int i = 0 ; i < NUM_LEDS ; i++){
         leds[i].setHSV(0,0,0);
    }
   int color = random(1,255);
   switch(random(1,5)){
    case 1:
      for(int i = 0 ; i < 150; i++){
         leds[i].setHSV(color,255,255);
      }
      break;
    case 2:
      for(int i =150;i<250; i++){
         leds[i].setHSV(color,255,255);
      }
      break;
    case 3:
      for(int i =250;i<400; i++){
         leds[i].setHSV(color,255,255);
      }
      break;
    case 4:         
      for(int i =400;i<450; i++){
         leds[i].setHSV(color,255,255);
      }
      break;
    default:
      break;
   }
    FastLED.show();
  }
  count++;
 }
}
void updateBeat(){
 beat = false;
 if (Serial.available() >= 1){ // this was == 4, more than one command may be waiting
       Serial.read();
        beat = true;
       
       //bright = random(1,255);
       /*String num = "";
       while(1>0){
        char b = Serial.read(); 
        if(b == ' '){
           break; 
        }
        else{
          num = num+b;
        }
       }
       if(bright < num.toInt()){
          bright = bright +20; 
          if(bright>255){
             bright = 255; 
          }
       }else{
          bright=bright -5;
       }*/
     }
     //float freq=atof(cadena);  
}
void testFreq(){
  bright = 255;
  int count = 0;
  while(count<10000){
     updateBeat();
     for(int i = 0 ; i < NUM_LEDS ; i ++){
         leds[i].setHSV(255,255,bright);
       }   
     FastLED.show();
  }
}
void colorWipe() {
  int color = random(1,255);
  int brightness = 255;
  for(int i=0; i<NUM_LEDS;i++) {
      updateBeat();
      if(beat){
        brightness = 255;
        for(int i = 0 ; i < NUM_LEDS ; i ++){
            leds[i].setHSV(color,255,brightness);
        }
      }
      leds[i].setHSV(color,255,brightness);
      FastLED.show();
      delay(15);
      brightness = brightness -5;
  }
}
void theaterChase() {
  int color = 255;
  int count = 0;
  int brightness = 255;
  while(count < 2){
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing    
      for (int q=0; q < 3; q++) {
        updateBeat();
        if(beat){
           color = random(1,255); 
        }
        for (int i=0; i < NUM_LEDS; i=i+3) {
          leds[i+q].setHSV(color,255,brightness);
        }
        FastLED.show();
        for(int i = 0 ; i < 10;i++){
            updateBeat();
            if(beat){
                 color = random(1,255); 
                for (int i=0; i < NUM_LEDS; i=i+3) {
                    leds[i+q].setHSV(color,255,brightness);
                }
            }
            FastLED.show();
            delay(1);
        }
        for (int i=0; i < NUM_LEDS; i=i+3) {
          leds[i+q].setHSV(0,0,0);
          //turn every third pixel off
        }
      }
    }
    count++;
  }
}
void partStrip(){
  int count = 0;
  int color = 255;
  int brightness = 255;
  while(count < 1000){
   updateBeat(); 
   if(random(1,20) == 2){
      for(int o = 0 ; o<NUM_LEDS ; o++){
           leds[o].setHSV(0,0,0);
      }
      int divide = random(0,4);
      color = random(1,255);
      for(int i = divide *(NUM_LEDS/5) ; i < divide *(NUM_LEDS/5) + NUM_LEDS/5 ; i++){
           leds[i].setHSV(color,255,brightness);
      }
    }
    FastLED.show();
    count++;
  }
}
/*void theaterChase() {
  int count = 0;
  int color = 255;
  for (int j=0; j<1000; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
           leds[i+q].setHSV(color,255,255);
      }
      while(count <1001){
        updateBeat();
        if(beat){
          color = random(1,255);  
          for (int i=0; i < NUM_LEDS; i=i+3) {
              leds[i+q].setHSV(color,255,255);
          }
        }
        //FastLED.show();
        if(count%1000== 0){
          for (int i=0; i < NUM_LEDS;i=i+3) {
                leds[i+q].setHSV(0,0,0);
          }
          count = 1;
          for (int i=0; i < NUM_LEDS; i=i+3) {
                leds[i+q].setHSV(color,255,255);
          }
         FastLED.show();
         
          //delay(50);
         
  
        }
        count++;
      }
      count = 0;
    }
  }
}*/
void createBullet(){
 int count = 0; 
 int countBullet = 0;
 int bullet[(NUM_LEDS-50)/6];
 int colorBullet[(NUM_LEDS-50)/6];

 for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
    bullet[p] = -1;
 }
 while(count < 1500){
     updateBeat();
     int brightness = 255;
     if(random(1,25) == 3){
         bullet[countBullet%(((NUM_LEDS-50)/6)-1)] = (NUM_LEDS/2);
         colorBullet[countBullet%(((NUM_LEDS-50)/6)-1)] = random(1,255);
         countBullet++;

     }
    for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
        if(bullet[p] != -1){
            switch(bullet[p]){
              case (NUM_LEDS/2):
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                   leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))].setHSV(colorBullet[p],255,brightness);
                  break;
              case (NUM_LEDS/2)+1:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))].setHSV(colorBullet[p],255,brightness);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+1].setHSV(colorBullet[p],255,brightness/2);
                  break;
              case (NUM_LEDS/2)+2:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))].setHSV(colorBullet[p],255,brightness);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+1].setHSV(colorBullet[p],255,brightness/2);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+2].setHSV(colorBullet[p],255,brightness/4);
                  break;
              case (NUM_LEDS/2)+3:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[bullet[p]-3].setHSV(colorBullet[p],255,brightness/8);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))].setHSV(colorBullet[p],255,brightness);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+2].setHSV(colorBullet[p],255,brightness/2);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+3].setHSV(colorBullet[p],255,brightness/4);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+1].setHSV(colorBullet[p],255,brightness/8);
                  break;
              case NUM_LEDS:
                  bullet[p] = -1;
                  break;
              default: 
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[bullet[p]-3].setHSV(colorBullet[p],255,brightness/8);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))].setHSV(colorBullet[p],255,brightness);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+1].setHSV(colorBullet[p],255,brightness/2);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+2].setHSV(colorBullet[p],255,brightness/4);
                  leds[(NUM_LEDS/2)-(bullet[p]%(NUM_LEDS/2))+3].setHSV(colorBullet[p],255,brightness/8);
                  break;
              }
        }
     
     }
     FastLED.show();
     for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
        if(bullet[p] != -1 ){
               bullet[p]++;
        }
     }
     count++;
   }
}
void createBulletVariant(){
 int count = 0; 
 int countBullet = 0;
 int bullet[(NUM_LEDS-50)/6];
 int colorBullet[(NUM_LEDS-50)/6];
 for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
    bullet[p] = -1;
 }
 while(count < 1500){
     updateBeat();
     int brightness = 255;
     if(beat){
         bullet[countBullet%(((NUM_LEDS-50)/6)-1)] = 200;
         colorBullet[countBullet%(((NUM_LEDS-50)/6)-1)] = random(1,255);
         countBullet++;
      
     }
    for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
        if(bullet[p] != -1){
            switch(bullet[p]){
              case 200:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                   leds[199-(bullet[p]%200)].setHSV(colorBullet[p],255,brightness);
                  break;
              case 201:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[199-(bullet[p]%200)].setHSV(colorBullet[p],255,brightness);
                  leds[199-(bullet[p]%200)+1].setHSV(colorBullet[p],255,brightness/2);
                  break;
              case 202:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[199-(bullet[p]%200)].setHSV(colorBullet[p],255,brightness);
                  leds[199-(bullet[p]%200)+1].setHSV(colorBullet[p],255,brightness/2);
                  leds[199-(bullet[p]%200)+2].setHSV(colorBullet[p],255,brightness/4);
                  break;
              case 203:
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[bullet[p]-3].setHSV(colorBullet[p],255,brightness/8);
                  leds[199-(bullet[p]%200)].setHSV(colorBullet[p],255,brightness);
                  leds[199-(bullet[p]%200)+2].setHSV(colorBullet[p],255,brightness/2);
                  leds[199-(bullet[p]%200)+3].setHSV(colorBullet[p],255,brightness/4);
                  leds[199-(bullet[p]%200)+1].setHSV(colorBullet[p],255,brightness/8);
                  break;
              case NUM_LEDS-50:
                  bullet[p] = -1;
                  break;
              default: 
                  leds[bullet[p]].setHSV(colorBullet[p],255,brightness);
                  leds[bullet[p]-1].setHSV(colorBullet[p],255,brightness/2);
                  leds[bullet[p]-2].setHSV(colorBullet[p],255,brightness/4);
                  leds[bullet[p]-3].setHSV(colorBullet[p],255,brightness/8);
                  leds[199-(bullet[p]%200)].setHSV(colorBullet[p],255,brightness);
                  leds[199-(bullet[p]%200)+1].setHSV(colorBullet[p],255,brightness/2);
                  leds[199-(bullet[p]%200)+2].setHSV(colorBullet[p],255,brightness/4);
                  leds[199-(bullet[p]%200)+3].setHSV(colorBullet[p],255,brightness/8);
                  break;
              }
        }
     
     }
     FastLED.show();
     for (int p = 0 ; p < (NUM_LEDS-50)/6 ; p++){
        if(bullet[p] != -1 ){
               bullet[p]++;
        }
     }
     count++;
   }
}
void bulletLiving(){
 int count = 0;
 while(count < 3000){
    updateBeat();
    if(beat){
       
    }
 }
}
void reactBeatFull(){
  int count = 0;
  int brightness = 255;
  int color = 255;
  while(count < 500){
      updateBeat();
      if(beat){ 
        brightness = 255;
        color = random(1,255);
      }
      if(brightness > 0 ){
          brightness = brightness -5; 
      }
      for(int p = 0 ; p < NUM_LEDS ; p++){
            leds[p].setHSV(color,255,brightness);
      }
      FastLED.show();
      count++;
  }
}
