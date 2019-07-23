#include <FastLED.h>

#define datapin_one 10
#define datapin_two 11
#define clockpin 5
#define numLeds 24
#define mosfet_pin A5

CRGB leds_1[numLeds];
CRGB leds_2[numLeds]; // -1 on BB

long colours[6] = {0xffff00,0x00ff00,0x00ffff,0x0000ff,0x800080,0xff0000}; 
                  // a          g         f       e         d         c
                  
// a        h        c        d        e        f        g 
// red      orange   yellow   green    cyan     blue     purple
// 0xff0000 0xffa500 0xffff00 0x00ff00 0x00ffff 0x0000ff 0x800080


// Define sensor_pin numbers
int sensor_pin_01 = 2,
    sensor_pin_02 = 3,
    sensor_pin_03 = 4,
    sensor_pin_04 = 5,
    sensor_pin_05 = 6,
    sensor_pin_06 = 7;

String old_output = "nnnnnn",
       output = "";

int threshold = 0;
int serial_input = 0;
double num_y[] = {0,0,0,0,0,0};

double  start_time,
        reset_threshold = 5000,
        last_interaction,
        interaction_threshold = 0;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  // Mark pins as Input
  pinMode(sensor_pin_01, INPUT);
  pinMode(sensor_pin_02, INPUT);
  pinMode(sensor_pin_03, INPUT);
  pinMode(sensor_pin_04, INPUT);
  pinMode(sensor_pin_05, INPUT);
  pinMode(sensor_pin_06, INPUT);

  /*pinMode(mosfet_pin, OUTPUT);
  analogWrite(mosfet_pin, 255);
  */
  start_time = millis();

  FastLED.addLeds<WS2812B, datapin_one, RGB>(leds_1, numLeds);
  FastLED.addLeds<WS2812B, datapin_two, RGB>(leds_2, numLeds);
}

// Main Loop
void loop(){

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
  if (digitalRead(sensor_pin_06) == 1) {
    if(num_y[0] == 0) num_y[0] = current_millis;    
    if (current_millis - num_y[0] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[0] = 0;
  }
  
  if (digitalRead(sensor_pin_05) == 1) {
    if(num_y[1] == 0) num_y[1] = current_millis;    
    if (current_millis - num_y[1] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[1] = 0;
  }
  
  if (digitalRead(sensor_pin_04) == 1) {
    if(num_y[2] == 0) num_y[2] = current_millis;    
    if (current_millis - num_y[2] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[2] = 0;
  }
  
  if (digitalRead(sensor_pin_03) == 1) {
    if(num_y[3] == 0) num_y[3] = current_millis;    
    if (current_millis - num_y[3] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[3] = 0;
  }
  
  if (digitalRead(sensor_pin_02) == 1) {
    if(num_y[4] == 0) num_y[4] = current_millis;    
    if (current_millis - num_y[4] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[4] = 0;
  }
  
  if (digitalRead(sensor_pin_01) == 1) {
    if(num_y[5] == 0) num_y[5] = current_millis;    
    if (current_millis - num_y[5] >= threshold) output += 'y';
    else output += "n";  
  }
  else {
    output += 'n';
    num_y[5] = 0;
  }
  
  // Send the output if there is a change in sensor readings
  if(old_output != output){
    old_output = output;
    control_leds(output);
    output = 'A' + output;
    Serial.println(output);
    last_interaction = millis();
  }

  // If enough time has passed, reset the sensors.
  //if(millis() - start_time >= reset_threshold && millis() - last_interaction >= interaction_threshold) reset_sensors();
  
  delay(10);        // delay in between reads for stability
}

// Function that closes the gate on the mosfet, cutting power to the sensors so that they can re-calibrate
/*void reset_sensors(){
  analogWrite(mosfet_pin, 0);
  delay(2000);
  analogWrite(mosfet_pin, 255);
  start_time = millis();
  delay(200);
}*/

void control_leds(String sensorString){
  for(int i = 0; i < sensorString.length(); i++){
    if(sensorString.charAt(i) == 'y'){
      for(int j = i*4; j < i*4+3; j++){
        leds_1[j] = colours[i];
        leds_2[j] = colours[i];
        FastLED.show();
      }
    }else{
      for(int j = i*4; j < i*4+3; j++){
        leds_1[j] = CRGB::Black;
        leds_2[j] = CRGB::Black;
        FastLED.show();
      }
    }
  }
}

void pattern_one(){
  for(int j = 0; j < 6; j++){
    for(int i = j*4; i < j*4+3; i++){
      leds_1[i] = colours[j];
      leds_2[i] = colours[j];
      FastLED.show();
    }
    delay(50);
  
    for(int i = j*4; i < j*4+3; i++){
      leds_1[i] = CRGB::Black;
      leds_2[i] = CRGB::Black;
      FastLED.show();
    }
    delay(50);
  }
  
  for(int j = 5; j >= 0; j--){
    for(int i = j*4; i < j*4+3; i++){
      leds_1[i] = colours[j];
      leds_2[i] = colours[j];
      FastLED.show();
    }
    delay(50);
  
    for(int i = j*4; i < j*4+3; i++){
      leds_1[i] = CRGB::Black;
      leds_2[i] = CRGB::Black;
      FastLED.show();
    }
    delay(50);
  }
}

void pattern_two(){
  String patternString = "ynynyn";
  for(int j = 0; j < 6; j++){
    if(patternString.charAt(j)=='y'){
      for(int i = j*4; i < j*4+3; i++){
        leds_1[i] = colours[j];
        leds_2[i] = colours[j];
        FastLED.show();
      }
    }else{  
      for(int i = j*4; i < j*4+3; i++){
        leds_1[i] = CRGB::Black;
        leds_2[i] = CRGB::Black;
        FastLED.show();
      }
    }
  }
  delay(400);
  
  patternString = "nynyny";
  for(int j = 0; j < 6; j++){
    if(patternString.charAt(j)=='y'){
      for(int i = j*4; i < j*4+3; i++){
        leds_1[i] = colours[j];
        leds_2[i] = colours[j];
        FastLED.show();
      }
    }else{  
      for(int i = j*4; i < j*4+3; i++){
        leds_1[i] = CRGB::Black;
        leds_2[i] = CRGB::Black;
        FastLED.show();
      }
    }
  }
  delay(400);
  for(int i = 0; i < 24; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    FastLED.show();
  }
}

