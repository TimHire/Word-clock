char daysOfTheWeek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};             // Two dimensional array as a string of characters is stored as an array

void print_time(DateTime current_time) {                    // Replaced creating a new instance of the time with now = rtc.now() with parsing in current_time into the parameters of the function
  /*Serial.print(current_time.year(), DEC);
  Serial.print('/');
  Serial.print(current_time.month(), DEC);
  Serial.print('/');
  Serial.print(current_time.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[current_time.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(current_time.hour(), DEC);
  Serial.print(':');
  Serial.print(current_time.minute(), DEC);
  Serial.print(':');
  Serial.print(current_time.second(), DEC);
  Serial.println();*/
  delay(40);
}
