// Function allows for the definition of when to dim the LEDs

int night_mode(DateTime current_time){
  if ((current_time.hour() >= START_NIGHT[0] && current_time.minute() >= START_NIGHT[1]) || (current_time.hour() <= END_NIGHT[0] && current_time.minute() <= END_NIGHT[1])){
    minute_LEDs_on = false;                                   // Turns off the minute LEDs in nigh mode as too bright
    return 1;
  }
  else {
    minute_LEDs_on = true;
    return 0;
  }
}
