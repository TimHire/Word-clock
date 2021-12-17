// Fucntion that returns a 1 if Daylight Saving Time is active
// All times worked out from when normal times to allow for automatic time changing


int time_skips(DateTime current_time) {    
  int DST = 0;
  int month = current_time.month();
  int day = current_time.day();
  int hour = current_time.hour();

  int year = current_time.year(); // DS3231 uses two digit year (required here)
  int x = (year + year / 4 + 2) % 7; // remainder will identify which day of month is Sunday by subtracting x from the one or two week window. First two weeks for March and first week for November

  if (month == 3 && day == (14 - x) && hour >= 2) {
    DST = 1; // Daylight Savings Time is TRUE (add one hour)
  }
  if ((month == 3 && day > (14 - x)) || month > 3) {
    DST = 1;
  }
  if (month == 11 && day == (7 - x) && hour >= 2) {
    DST = 0; // daylight savings time is FALSE (Standard time)
  }
  if ((month == 11 && day > (7 - x)) || month > 11 || month < 3) {
    DST = 0;
  }
  return DST;
}
