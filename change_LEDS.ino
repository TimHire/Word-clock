// Changes the LEDs on the word clock as the times change

int red_intensity, green_intensity, blue_intensity;

void change_LEDS(DateTime current_time) {
  int nightMode = night_mode(current_time);
  if (nightMode == 0){
    red_intensity = RGB_day_intensity[0];
    green_intensity = RGB_day_intensity[1];
    blue_intensity = RGB_day_intensity[2];
  }
  else {
    red_intensity = RGB_night_intensity[0];
    green_intensity = RGB_night_intensity[1];
    blue_intensity = int(RGB_night_intensity[2] * 0.7);               // Coeffcient produces a warmer tone
  }
  
  reset_LEDs();                             // Resets the LEDs
  turn_on_LEDS(it_is);                      // Immediately turns the IT IS lights back on


  int minute = current_time.minute();

  if (minute_LEDs_on){                        // Allows the potential to turn off the minute LEDs when in night mode --> currently not enabled
    int minute_remainder = minute % 5;        // Turning on the minute LEDs at the bottom of the clock
    if (minute % 5 == 0) {
      digitalWrite(LED_1_PIN, LOW);
      digitalWrite(LED_2_PIN, LOW);
      digitalWrite(LED_3_PIN, LOW);
      digitalWrite(LED_4_PIN, LOW);
    }
    if (minute % 5 == 1) {
      digitalWrite(LED_1_PIN, HIGH);
    }
    if (minute % 5 == 2) {
      digitalWrite(LED_2_PIN, HIGH);
    }
    if (minute % 5 == 3) {
      digitalWrite(LED_3_PIN, HIGH);
    }
    if (minute % 5 == 4) {
      digitalWrite(LED_4_PIN, HIGH);
    }
  }
  else if (!minute_LEDs_on){
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, LOW);
    digitalWrite(LED_3_PIN, LOW);
    digitalWrite(LED_4_PIN, LOW);
  }


  if (minute >= 0 && minute < 5) {
    turn_on_LEDS(o_clock);
  }
  if (minute >= 5 && minute < 10) {
    turn_on_LEDS(five);
    turn_on_LEDS(past);
  }
  if (minute >= 10 && minute < 15) {
    turn_on_LEDS(ten);
    turn_on_LEDS(past);
  }
  if (minute >= 15 && minute < 20) {
    turn_on_LEDS(quarter);
    turn_on_LEDS(past);
  }
  if (minute >= 20 && minute < 25) {
    turn_on_LEDS(twenty);
    turn_on_LEDS(past);
  }
  if (minute >= 25 && minute < 30) {
    turn_on_LEDS(twenty);
    turn_on_LEDS(five);
    turn_on_LEDS(past);
  }
  if (minute >= 30 && minute < 35) {
    turn_on_LEDS(half);
    turn_on_LEDS(past);
  }
  if (minute >= 35 && minute < 40) {
    turn_on_LEDS(twenty);
    turn_on_LEDS(five);
    turn_on_LEDS(to);
  }
  if (minute >= 40 && minute < 45) {
    turn_on_LEDS(twenty);
    turn_on_LEDS(to);
  }
  if (minute >= 45 && minute < 50) {
    turn_on_LEDS(quarter);
    turn_on_LEDS(to);
  }
  if (minute >= 50 && minute < 55) {
    turn_on_LEDS(ten);
    turn_on_LEDS(to);
  }
  if (minute >= 55 && minute < 60) {
    turn_on_LEDS(five);
    turn_on_LEDS(to);
  }

  int hour = current_time.hour();
  if (hour % 12 == 11 && minute >= 35 || hour % 12 == 0 && minute < 35) {
    turn_on_LEDS(twelve);
  }
  if (hour % 12 == 0 && minute >= 35 || hour % 12 == 1 && minute < 35) {
    turn_on_LEDS(one);
  }
  if (hour % 12 == 1 && minute >= 35 || hour % 12 == 2 && minute < 35) {
    turn_on_LEDS(two);
  }
  if (hour % 12 == 2 && minute >= 35 || hour % 12 == 3 && minute < 35) {
    turn_on_LEDS(three);
  }
  if (hour % 12 == 3 && minute >= 35 || hour % 12 == 4 && minute < 35) {
    turn_on_LEDS(four);
  }
  if (hour % 12 == 4 && minute >= 35 || hour % 12 == 5 && minute < 35) {
    turn_on_LEDS(five_n);
  }
  if (hour % 12 == 5 && minute >= 35 || hour % 12 == 6 && minute < 35) {
    turn_on_LEDS(six);
  }
  if (hour % 12 == 6 && minute >= 35 || hour % 12 == 7 && minute < 35) {
    turn_on_LEDS(seven);
  }
  if (hour % 12 == 7 && minute >= 35 || hour % 12 == 8 && minute < 35) {
    turn_on_LEDS(eight);
  }
  if (hour % 12 == 8 && minute >= 35 || hour % 12 == 9 && minute < 35) {
    turn_on_LEDS(nine);
  }
  if (hour % 12 == 9 && minute >= 35 || hour % 12 == 10 && minute < 35) {
    turn_on_LEDS(ten_n);
  }
  if (hour % 12 == 10 && minute >= 35 || hour % 12 == 11 && minute < 35) {
    turn_on_LEDS(eleven);
  }


  if (current_time.month() == 9 && current_time.day() == 20) {
    turn_on_LEDS(happy_bday);
  }

  //Serial.print("Time LEDs have been updated at ");
  //print_time(current_time);

  FastLED.show();
}
