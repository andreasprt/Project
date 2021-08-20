void bacaEncoder()
{
  stateA = digitalRead(faseA); // baca status awal dari fase A
   // kalo kondisi state fase A sekarang dan sebelumnya berbeda, berarti ada pulsa yang masuk guys
   if (stateA != stateAend){     
     // kalo state fase B berbeda dengan state fase A, berarti encoder berputar searah jarum jam
     if (digitalRead(faseB) != stateA) { 
       counter ++;
     } else {
       counter --;
     }
     //Serial.println(counter);
     sudutraw = counter;
   } 
   stateAend = stateA; //update state dari fase
   sudut = sudutraw / 5.57;
}
