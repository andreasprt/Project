void kanan()
{
  for(int i = 0; i<=200; i++)
  {
    analogWrite(pwm1, 0);
  analogWrite(pwm2, 200);  
  }
  
}

void kiri()
{
  for(int i = 0; i<=200; i++)
  {
    analogWrite(pwm1, 200);
  analogWrite(pwm2, 0);  
  }
}
