//Function turns on all the LEDs in the list --> only the pointer to the first memory address of the list is parsed to the function, so cannot do traditional array iterations


void turn_on_LEDS(int list_nos[]) {
  DateTime current_time = rtc.now();
  int check_night_mode = night_mode(current_time);
  if (colour_random && (check_night_mode == 1)){          // Can only use the multi-coloured mode if colour_random = true and not in night mode                         
    for (int i = 2; i <= list_nos[0] + 1; i++) {          // the number of elements in the array is stored in the first element of the array
      //Serial.print(list_nos[i]);
      //Serial.print(" ");
      leds[list_nos[i]] = CRGB (colour_definitions[list_nos[1]].r, colour_definitions[list_nos[1]].g, colour_definitions[list_nos[1]].b);
    }
    //Serial.print("  ");
  }
  else {     
    for (int i = 2; i <= list_nos[0] + 1; i++) {          // the number of elements in the array is stored in the first element of the array
      //Serial.print(list_nos[i]);
      //Serial.print(" ");
      leds[list_nos[i]] = CRGB (red_intensity, green_intensity, blue_intensity);
    }
    //Serial.print("  ");
  }
}


void reset_LEDs(){
  for (int i = 0; i < NUM_LEDS; i++) {      //Resets all the LEDs
    leds[i] = CRGB (0, 0, 0);
  }
}
