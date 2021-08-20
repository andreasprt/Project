#define faseA 29
#define faseB 28

//------------- aktuator --------------------------------

#define pwm1 PB_5 //pin Lpwm
#define pwm2 PB_0 //pin Rpwm 
#define relay1 PA_7 //relay 1
#define relay2 PA_6 //relay 2

#define jmlData 200
#define speed 70
int counter = 0;
int stateA;
int stateAend;


byte dummy1 = 31;
byte dummy2 = 17;
float sudutraw;
int sudut, setSudut = 0;

//---------------------parsing dan waktu-------------------
String dataIn;
String dt[10];
boolean parsing = false;
byte mulai, konting, hitung, nextHtg, MAVhtg;

int waktu;
int data[1000];
unsigned long startTime;
unsigned long waktunow;
unsigned long endTime;
unsigned long duration;
byte timerRunning;
boolean timer = false;

void bacaEncoder();
void parsingData();
void deteksiData();

void setup() {
  Serial.begin(115200);
  dataIn = "";

  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(faseA, INPUT_PULLUP);
  pinMode(faseB, INPUT_PULLUP);
  pinMode(dummy1, INPUT_PULLUP);
  pinMode(dummy2, INPUT_PULLUP);

  stateAend = digitalRead(faseA);
}

void loop() {
  bacaEncoder();

  //kontingBro();
  deteksiData();
  if (dt[0] == "a") {
    dt[0] = "";
    setSudut = dt[1].toInt();
    setSudut = constrain(setSudut, -20, 20);
    //bacaEncoder();
    digitalWrite(relay2, 1);

    while (sudut != setSudut ) {
      bacaEncoder();

      //  Serial.println(sudut);

      if (setSudut > sudut) {


        analogWrite(pwm2, 200); analogWrite(pwm1, 0);
        analogWrite(pwm2, 0);
        // Serial.println("Kanan");
      }
      if (setSudut < sudut) {


        analogWrite(pwm1, 200); analogWrite(pwm2, 0);
        analogWrite(pwm1, 0);
        // Serial.println("Kiri");
      }


      analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);

    }
    dt[0] = "b";
  }
  if (dt[0] == "b") {
    dt[0] = "";
    Serial.println("Lepas");
    digitalWrite(relay2, 0);
    baca();
  }
  if (dt[0] == "c") {
    dt[0] = "";
    for (int i = 0; i < jmlData; i++) {
      Serial.print(i);
      Serial.print(",");
      Serial.print(data[i]);
      Serial.println();
    }
  }
}

void baca() {
  bacaEncoder();
  sudut = constrain(sudut, -setSudut, setSudut);
  data[0] = sudut;
  unsigned long t = 0;
  int i = 1;
  while (i <= jmlData) {
    bacaEncoder();
    sudut = constrain(sudut, -setSudut, setSudut);
    if (millis() - t > 200) {
      data[i] = sudut;
      Serial.print(i);
      Serial.print(",");
      Serial.print(sudut);
      Serial.println();
      i++;
      t = millis();
    }
  }
}
