void check_bluetooth(){
  char input;
  if (BTserial.available())  {
    input = BTserial.read();
  }
  if (input == 'y'){                  // Allows for the reseting of the bluetooth bus if something goes wrong
    ;
  }
  else if (input == 't'){
    // Changing the time of the word clock
    //Serial.println("Changing the time");
    int time_in[6];
    if (BTserial.available()){
      for (int i=0; i<6; i++){
        time_in[i] = BTserial.read();
      }
    }
    DateTime bluetooth_time = DateTime(2000 + time_in[0], time_in[1], time_in[2], time_in[3], time_in[4], time_in[5]);
    change_time(bluetooth_time, 2, true);                             // Currently adding 1 second offset for the transmission time
    //Serial.println("Time reset");
  } 
  
  else if (input == 'i'){
    //Serial.println("Changing the LED intensity");
    char mode;
    if (BTserial.available())  {
      mode = BTserial.read();
    }
    if (mode == 'd'){
      // Changing the daylight intensity
      //Serial.println("Changing day intensity");
      int new_day_intensity;
      if (BTserial.available())  {
        new_day_intensity = BTserial.read();
      }
      RGB_day_intensity[0] = new_day_intensity;
      RGB_day_intensity[1] = new_day_intensity;
      RGB_day_intensity[2] = new_day_intensity;
      //Serial.print("New intensity: ");
      //Serial.println(new_day_intensity);
    } else if (mode == 'n'){
      // Changing the night time intensity
      //Serial.println("Changing night intensity");
      int new_night_intensity;
      if (BTserial.available())  {
        new_night_intensity = BTserial.read();
      }
      RGB_night_intensity[0] = new_night_intensity;
      RGB_night_intensity[1] = new_night_intensity;
      RGB_night_intensity[2] = new_night_intensity;
      //Serial.print("New intensity: ");
      //Serial.println(new_night_intensity);
    }
    colour_random = false;
  } 
  
  else if (input == 'c'){
    // changing the colour of the LEDs
    //Serial.println("Changing the colour");
    char random_colours;
    if (BTserial.available())  {
      random_colours = BTserial.read();
    }
    if (random_colours == 'a'){
      // Not on random colour mode
      int new_colours[3];
      if (BTserial.available())  {
        for (int i=0; i<3; i++){
          new_colours[i] = BTserial.read();
        }
      }
      RGB_day_intensity[0] = new_colours[0];
      RGB_day_intensity[1] = new_colours[1];
      RGB_day_intensity[2] = new_colours[2];
      RGB_night_intensity[0] = int(new_colours[0] * 0.1);
      RGB_night_intensity[1] = int(new_colours[1] * 0.1);
      RGB_night_intensity[2] = int(new_colours[2] * 0.1);
      //Serial.println("Not random colour mode");
      //Serial.println(RGB_day_intensity[0]);
      //Serial.println(RGB_night_intensity[0]);
      colour_random = false;
    } else if (random_colours == 'b'){
      // Need random colours for each word
      colour_random = not colour_random;
      //Serial.println("Random colour mode");
    }
  } 
  
  else if (input == 's'){
    // Change the start and end times of night mode
    //Serial.println("Changing the night mode times");
    char start_end;
    int new_time[2];
    if (BTserial.available())  {
      start_end = BTserial.read();
      for (int i=0; i<2; i++){
        new_time[i] = BTserial.read();
      }
    }
    if (start_end == 's'){
      //Serial.println("Changing start time");
      START_NIGHT[0] = new_time[0];
      START_NIGHT[1] = new_time[1];
    } else if (start_end == 'e'){
      //Serial.println("Changing end time");
      END_NIGHT[0] = new_time[0];
      END_NIGHT[1] = new_time[1];
    }
    //Serial.println(START_NIGHT[0]);
    //Serial.println(END_NIGHT[0]);
  }
  
  //BTserial.flush();                 // Makes the program wait for the f command to be sent --> not sure if this works
  BTserial.write('f');              // Returns 1 if the command has been received successfully
}
