// May need to upload to the Arduino up to 3-4 times to get rid of the delay in uploading, so the time is accurate

#include <FastLED.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

struct RGB_stc {
  byte r;
  byte g;
  byte b;
};
RGB_stc colour_definitions[22] = {{255, 128, 0}, {0, 255, 255}, {178, 102, 255}, {0, 102, 204}, {255, 255, 0}, {255, 0, 0}, {0, 204, 0}, {255, 0, 127}, {51, 51, 255}, {204, 153, 255}, {255, 255, 0}, {255, 128, 0}, {0, 255, 255}, {178, 102, 255}, {0, 102, 204}, {255, 255, 0}, {255, 0, 0}, {0, 204, 0}, {255, 0, 127}, {51, 51, 255}, {204, 153, 255}, {255, 255, 0}}; 
bool colour_random = false;       // Keeps track on whether multi-colour mode is enabled --> turns off in night mode but should automatically go back during the day

#define LED_PIN     7             // Pin connected to the LED strip
#define NUM_LEDS    119            // Number of LEDs being used in the LED strip
CRGB leds[NUM_LEDS];              // Creating the instance for the LED strip to be controlled by the library
#define LED_1_PIN   5            // The 4 stand-alone LEDs at the bottom for giving minute accuracy
#define LED_2_PIN   4
#define LED_3_PIN   3
#define LED_4_PIN   2

RTC_DS1307 rtc;
const int RX_PIN = 10;
const int TX_PIN = 9;
const int BLUETOOTH_BAUD_RATE = 9600;
SoftwareSerial BTserial(RX_PIN, TX_PIN); // RX, TX

// the first number is the number of elements in the array --> could also store the information in a structure
// the second number in the array is the index for random colour from RGB colour_definitions
int it_is[] = {4, 0, 0, 1, 2, 3};   
int twenty[] = {7, 1, 15, 16, 17, 18, 19, 20, 21};
int half[] = {4, 2, 10, 12, 13, 14};
int ten[] = {4, 3, 22, 23, 24, 25};
int quarter[] = {8, 4, 26, 27, 28, 29, 30, 31, 32, 33};
int five[] = {5, 5, 41, 42, 43, 44, 45};
int to[] = {2, 6, 39, 40};
int past[] = {5, 7, 34, 35, 36, 37, 38};
int one[] = {4, 8, 46, 47, 48, 49};
int four[] = {5, 9, 50, 51, 52, 53, 54};
int two[] = {4, 10, 55, 56, 57, 58};
int five_n[] = {5, 11, 66, 67, 68, 69, 70};
int six[] = {4, 12, 62, 63, 64, 65};
int ten_n[] = {3, 13, 59, 60, 61};
int three[] = {6, 14, 71, 72, 73, 74, 75, 76};
int seven[] = {6, 15, 77, 78, 79, 80, 81, 82};
int twelve[] = {7, 16, 88, 89, 90, 91, 92, 93, 94};
int nine[] = {5, 17, 83, 84, 85, 86, 87};
int eight[] = {6, 18, 95, 96, 97, 98, 99, 100};
int eleven[] = {7, 19, 101, 102, 103, 104, 105, 106, 107};
int o_clock[] = {7, 20, 112, 113, 114, 115, 116, 117, 118, 119};
int happy_bday[] = {10, 21, 4, 5, 6, 7, 8, 9, 108, 109, 110, 111};


int RGB_day_intensity[3] = {200, 200, 200};
int RGB_night_intensity[3] = {15, 15, 15};
int START_NIGHT[2] = {22, 0};               // Two values are hours and minutes
int END_NIGHT[2] = {6, 0};
bool DST_status = false;                    // Keeps track whether DST has already been calibrated for
bool minute_LEDs_on = true;                 // Allows for the minute LEDs to be turned off in night mode


void setup() {
  pinMode(LED_1_PIN, OUTPUT);               // Declaring the pins used to control the minute LEDs
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);

  BTserial.begin(BLUETOOTH_BAUD_RATE);
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  //while (!Serial);
  //Serial.begin(9600);
  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    //Serial.println("RTC is NOT running!");
  }

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));             // Automatically sets the RTC time from the last computer compile time --> ends up 9s out
  rtc.adjust(DateTime(2021, 7, 22, 11, 0, 0));
  DateTime current_time = rtc.now();                          // Gets the computer time from the RTC
  //Serial.println("");  Serial.print("Current time is ");
  //print_time(current_time);

  DST_status = bool(time_skips(current_time));
  int compile_time_offset = 11;                     // Takes into account the time to compile the code so the seconds are accurate
  change_time(current_time, compile_time_offset, false);   // Need to check if the laptop time has taken into account of DST or not --> needs to not be so can be added during the loop
 
  reset_LEDs();
  FastLED.show();  
  delay(50);
  //Serial.print("Clock has initialised, normalised time is ");
  //print_time(rtc.now());  

}


void loop() {
  DateTime current_time = rtc.now();
  change_time(current_time, 0, false);                     // Gives opportunity to check whether has just tranitioned to DST
  DateTime revised_time = rtc.now();
  //print_time(revised_time);

  check_bluetooth();

  int second = revised_time.second();                 // Filtering the times so the LEDs are not reset repeatedly
  if (second % 4 == 0) {        // ((second >= 0 && second < 2) || (second >= 30 && second < 32))
    change_LEDS(revised_time);
  }
  delay(990);
}
