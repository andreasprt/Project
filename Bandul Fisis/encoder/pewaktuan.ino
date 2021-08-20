void startTimer()
{
  if (mulai == LOW  && timer == false) {
    konting=0;
    timer = true ;
    startTime = millis();
    timerRunning = 1;
    Serial.println("-----start timer------");
  }
    
  waktunow = millis() - startTime;
  
  if (waktunow == waktu && timer == true) {
 
    endTime = millis();
    timerRunning = 0;
    duration = endTime - startTime;
    
    timer = false;
    Serial.print("TCCRA || ");
    Serial.print("Durasi || ");
    Serial.println("Count || ");
    
    Serial.print(waktunow);
    Serial.print("     ");
    Serial.print(duration);
    Serial.print("      ");
    Serial.println(konting);
    Serial.println("---stop timer-----");
  }

}
