void parsingData()
{
 
  int j = 0;
  dt[j] = "";
  for (int i = 1; i < dataIn.length(); i++)
  {
    if ((dataIn[i] == ']') || (dataIn[i] == ',') || (dataIn[i] == '['))
    {
      j++;
      dt[j] = ""; //inisialisasi variabel array dt[j]
    }
    else
    {
      dt[j] = dt[j] + dataIn[i];
    }
  }
}

void deteksiData()
{
  if (Serial.available() > 0)
      {
        char inChar = (char)Serial.read();
        //char inChar = *udr;
        dataIn += inChar;
        if (inChar == '\n') {
           parsing = true;
        }
      }

      if (parsing)
      {
        parsingData();
        parsing = false;
        dataIn = "";
      }
}
