#include <FastLED.h>

#define datapin_one 10
#define datapin_two 11
#define clockpin 5
#define numLeds_one 20
#define numLeds_two 19

CRGB leds_1[numLeds_one];
CRGB leds_2[numLeds_two]; 

long colours[6] = {0xffa500, 0xff0000, 0x800080, 0x0000ff , 0x00ffff}; //green , red , blue , yellow , pink , paleblue 
//                  h         a         g           f         e


// Define sensor_pin numbers
int sensor_pin_01 = 2,
    sensor_pin_02 = 3,
    sensor_pin_03 = 4,
    sensor_pin_04 = 5,
    sensor_pin_05 = 6;

String old_output = "nnnnn",
       output = "";

int threshold = 0;
int serial_input = 0;
double num_y[] = {0,0,0,0,0};

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  // Mark pins as Input
  pinMode(sensor_pin_01, INPUT);
  pinMode(sensor_pin_02, INPUT);
  pinMode(sensor_pin_03, INPUT);
  pinMode(sensor_pin_04, INPUT);
  pinMode(sensor_pin_05, INPUT);

  FastLED.addLeds<WS2812B, datapin_one, RGB>(leds_1, numLeds_one);
  FastLED.addLeds<WS2812B, datapin_two, RGB>(leds_2, numLeds_two);
}

// Main Loop
void loop() {  

  //delay(1000);
  //pattern_one();
  //delay(1000);
  //pattern_two();

  double current_millis = millis();

  if(Serial.available()){
    serial_input = Serial.parseInt();

    switch(serial_input){
      case 1:
        pattern_one();
        break;
      case 2: 
        pattern_two();
        break;
      default:
        threshold = serial_input;
        break;
    }
  }
  
  output = "";
  
  // read the input pin:
  if (digitalRead(sensor_pin_01) == 1) {
    if(num_y[0] == 0) num_y[0] = current_millis;    
    if (current_millis - num_y[0] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[0] = 0;
  }
  
  if (digitalRead(sensor_pin_02) == 1) {
    if(num_y[1] == 0) num_y[1] = current_millis;    
    if (current_millis - num_y[1] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[1] = 0;
  }
  
  if (digitalRead(sensor_pin_03) == 1) {
    if(num_y[2] == 0) num_y[2] = current_millis;    
    if (current_millis - num_y[2] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[2] = 0;
  }
  
  if (digitalRead(sensor_pin_04) == 1) {
    if(num_y[3] == 0) num_y[3] = current_millis;    
    if (current_millis - num_y[3] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[3] = 0;
  }
  
  if (digitalRead(sensor_pin_05) == 1) {
    if(num_y[4] == 0) num_y[4] = current_millis;    
    if (current_millis - num_y[4] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[4] = 0;
  }
  
  // Send the output if there is a change in sensor readings
  if(old_output != output){
    old_output = output;
    control_leds(output);
    Serial.println(output);
  }
  
  delay(10);        // delay in between reads for stability
}

void control_leds(String sensorString){
  for(int i = 0; i < sensorString.length(); i++){ // iterate through the output string
    if(sensorString.charAt(i) == 'y'){            // if we find a 'y' in the string
      for(int j = i*4; j < i*4+3; j++){           // Iterate through the correct leds_1 leds
        leds_1[j] = colours[i];                   // and turn them on
        FastLED.show();
      }
      if(i == 0){                                 // As for leds_2, if the first char in a string is 'y'
        for(int j = i; j < 3; j++){               
          leds_2[j] = colours[i];                 // turn on the first three leds
          FastLED.show();
        }
      }else{                                      // if we are not at the first char, 
        for(int j = i*4-1; j < i*4+2; j++){       // iterate through the correct leds in intervals of four 
          leds_2[j] = colours[i];                 // and turn them on
          FastLED.show();
        }
      }
    }else{                                        // if we find an 'n'
      for(int j = i*4; j < i*4+3; j++){           // Iterate through the correct leds_1 leds
        leds_1[j] = CRGB::Black;                  // and turn them off
        FastLED.show();
      }
      if(i == 0){                                 // As for leds_2, if the first char in a string is 'y'
        for(int j = i; j < 3; j++){               
          leds_2[j] = CRGB::Black;                // turn off the first three leds
          FastLED.show();
        }
      }else{                                      // if we are not at the first char, 
        for(int j = i*4-1; j < i*4+2; j++){       // iterate through the correct leds in intervals of four 
          leds_2[j] = CRGB::Black;                // and turn them off
          FastLED.show();
        }
      }
    }
  }
}

void pattern_one(){
  for(int i = 0; i = 5; i++){
    for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = colours[i];                 
        FastLED.show();
      }
    if(i == 0){                               
      for(int j = i; j < 3; j++){               
        leds_2[j] = colours[i];               
        FastLED.show();
      }
    }else{                                      
      for(int j = i*4-1; j < i*4+2; j++){       
        leds_2[j] = colours[i];                 
        FastLED.show();
      }
    }
    delay(50);
      
    for(int j = i*4; j < i*4+3; j++){           
      leds_1[j] = CRGB::Black;                  
      FastLED.show();
    }
    if(i == 0){                                 
      for(int j = i; j < 3; j++){               
        leds_2[j] = CRGB::Black;                
        FastLED.show();
      }
    }else{                                      
      for(int j = i*4-1; j < i*4+2; j++){       
        leds_2[j] = CRGB::Black;                
        FastLED.show();
      }
    }
    delay(50);
  }
  delay(100);
  
  for(int i = 4; i >=4; i--){
    for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = colours[i];                 
        FastLED.show();
      }
    if(i == 0){                               
      for(int j = i; j < 3; j++){               
        leds_2[j] = colours[i];               
        FastLED.show();
      }
    }else{                                      
      for(int j = i*4-1; j < i*4+2; j++){       
        leds_2[j] = colours[i];                 
        FastLED.show();
      }
    }
    delay(50);
      
    for(int j = i*4; j < i*4+3; j++){           
      leds_1[j] = CRGB::Black;                  
      FastLED.show();
    }
    if(i == 0){                                 
      for(int j = i; j < 3; j++){               
        leds_2[j] = CRGB::Black;                
        FastLED.show();
      }
    }else{                                      
      for(int j = i*4-1; j < i*4+2; j++){       
        leds_2[j] = CRGB::Black;                
        FastLED.show();
      }
    }
    delay(50);
  }
}

void pattern_two(){
  String patternString = "nynyn";
  for(int i = 0; i < 5; i++){ 
    if(patternString.charAt(i) == 'y'){           
      for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = colours[i];                   
        FastLED.show();
      }
      if(i == 0){                                 
        for(int j = i; j < 3; j++){               
          leds_2[j] = colours[i];                 
          FastLED.show();
        }
      }else{                                      
        for(int j = i*4-1; j < i*4+2; j++){       
          leds_2[j] = colours[i];                 
          FastLED.show();
        }
      }
    }else{                                        
      for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = CRGB::Black;                  
        FastLED.show();
      }
      if(i == 0){                                 
        for(int j = i; j < 3; j++){               
          leds_2[j] = CRGB::Black;                
          FastLED.show();
        }
      }else{                                      
        for(int j = i*4-1; j < i*4+2; j++){       
          leds_2[j] = CRGB::Black;                
          FastLED.show();
        }
      }
    }
  }
  delay(400);

  patternString = "ynyny";
  for(int i = 0; i < 5; i++){ 
    if(patternString.charAt(i) == 'y'){           
      for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = colours[i];                   
        FastLED.show();
      }
      if(i == 0){                                 
        for(int j = i; j < 3; j++){               
          leds_2[j] = colours[i];                 
          FastLED.show();
        }
      }else{                                      
        for(int j = i*4-1; j < i*4+2; j++){       
          leds_2[j] = colours[i];                 
          FastLED.show();
        }
      }
    }else{                                        
      for(int j = i*4; j < i*4+3; j++){           
        leds_1[j] = CRGB::Black;                  
        FastLED.show();
      }
      if(i == 0){                                 
        for(int j = i; j < 3; j++){               
          leds_2[j] = CRGB::Black;                
          FastLED.show();
        }
      }else{                                      
        for(int j = i*4-1; j < i*4+2; j++){       
          leds_2[j] = CRGB::Black;                
          FastLED.show();
        }
      }
    }
  }
  delay(400);
  for(int i = 0; i < 24; i++){
    leds_1[i] = CRGB::Black;
    if(i < 23) leds_2[i] = CRGB::Black;
    FastLED.show();
  }
}

