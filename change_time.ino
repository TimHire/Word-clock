void change_time(DateTime input_time, int offset, bool reset){
  int DST = time_skips(input_time);
  if (DST == 0 && DST_status == true){ // Checks if has not been calibrated yet
    rtc.adjust(DateTime(input_time.year(), input_time.month(), input_time.day(), input_time.hour() + 1, input_time.minute(), input_time.second() + offset));
    DST_status = false;
  }
  else if (DST == 1 && DST_status == false){ // Checks if has not been calibrated yet
    rtc.adjust(DateTime(input_time.year(), input_time.month(), input_time.day(), input_time.hour() - 1, input_time.minute(), input_time.second() + offset));
    DST_status = true;
  }
  if (reset == true){
    rtc.adjust(DateTime(input_time.year(), input_time.month(), input_time.day(), input_time.hour(), input_time.minute(), input_time.second() + offset));
  }
}
