
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

/*______Assign names to colors and pressure_______*/
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410



//nilai temperartur min yang ditampilkan
#define MINTEMP 22

//nilai temperartur max yang ditampilkan
#define MAXTEMP 50

#define valve A14
#define motor A15

int n;
int bil[100];
int mod[100];
int x;
int k = 1;
#define akurasi 70 //dalam persen

//the colors we will be using
int camColors[] = {0x480F,
                   0x400F, 0x400F, 0x400F, 0x4010, 0x3810, 0x3810, 0x3810, 0x3810, 0x3010, 0x3010,
                   0x3010, 0x2810, 0x2810, 0x2810, 0x2810, 0x2010, 0x2010, 0x2010, 0x1810, 0x1810,
                   0x1811, 0x1811, 0x1011, 0x1011, 0x1011, 0x0811, 0x0811, 0x0811, 0x0011, 0x0011,
                   0x0011, 0x0011, 0x0011, 0x0031, 0x0031, 0x0051, 0x0072, 0x0072, 0x0092, 0x00B2,
                   0x00B2, 0x00D2, 0x00F2, 0x00F2, 0x0112, 0x0132, 0x0152, 0x0152, 0x0172, 0x0192,
                   0x0192, 0x01B2, 0x01D2, 0x01F3, 0x01F3, 0x0213, 0x0233, 0x0253, 0x0253, 0x0273,
                   0x0293, 0x02B3, 0x02D3, 0x02D3, 0x02F3, 0x0313, 0x0333, 0x0333, 0x0353, 0x0373,
                   0x0394, 0x03B4, 0x03D4, 0x03D4, 0x03F4, 0x0414, 0x0434, 0x0454, 0x0474, 0x0474,
                   0x0494, 0x04B4, 0x04D4, 0x04F4, 0x0514, 0x0534, 0x0534, 0x0554, 0x0554, 0x0574,
                   0x0574, 0x0573, 0x0573, 0x0573, 0x0572, 0x0572, 0x0572, 0x0571, 0x0591, 0x0591,
                   0x0590, 0x0590, 0x058F, 0x058F, 0x058F, 0x058E, 0x05AE, 0x05AE, 0x05AD, 0x05AD,
                   0x05AD, 0x05AC, 0x05AC, 0x05AB, 0x05CB, 0x05CB, 0x05CA, 0x05CA, 0x05CA, 0x05C9,
                   0x05C9, 0x05C8, 0x05E8, 0x05E8, 0x05E7, 0x05E7, 0x05E6, 0x05E6, 0x05E6, 0x05E5,
                   0x05E5, 0x0604, 0x0604, 0x0604, 0x0603, 0x0603, 0x0602, 0x0602, 0x0601, 0x0621,
                   0x0621, 0x0620, 0x0620, 0x0620, 0x0620, 0x0E20, 0x0E20, 0x0E40, 0x1640, 0x1640,
                   0x1E40, 0x1E40, 0x2640, 0x2640, 0x2E40, 0x2E60, 0x3660, 0x3660, 0x3E60, 0x3E60,
                   0x3E60, 0x4660, 0x4660, 0x4E60, 0x4E80, 0x5680, 0x5680, 0x5E80, 0x5E80, 0x6680,
                   0x6680, 0x6E80, 0x6EA0, 0x76A0, 0x76A0, 0x7EA0, 0x7EA0, 0x86A0, 0x86A0, 0x8EA0,
                   0x8EC0, 0x96C0, 0x96C0, 0x9EC0, 0x9EC0, 0xA6C0, 0xAEC0, 0xAEC0, 0xB6E0, 0xB6E0,
                   0xBEE0, 0xBEE0, 0xC6E0, 0xC6E0, 0xCEE0, 0xCEE0, 0xD6E0, 0xD700, 0xDF00, 0xDEE0,
                   0xDEC0, 0xDEA0, 0xDE80, 0xDE80, 0xE660, 0xE640, 0xE620, 0xE600, 0xE5E0, 0xE5C0,
                   0xE5A0, 0xE580, 0xE560, 0xE540, 0xE520, 0xE500, 0xE4E0, 0xE4C0, 0xE4A0, 0xE480,
                   0xE460, 0xEC40, 0xEC20, 0xEC00, 0xEBE0, 0xEBC0, 0xEBA0, 0xEB80, 0xEB60, 0xEB40,
                   0xEB20, 0xEB00, 0xEAE0, 0xEAC0, 0xEAA0, 0xEA80, 0xEA60, 0xEA40, 0xF220, 0xF200,
                   0xF1E0, 0xF1C0, 0xF1A0, 0xF180, 0xF160, 0xF140, 0xF100, 0xF0E0, 0xF0C0, 0xF0A0,
                   0xF080, 0xF060, 0xF040, 0xF020, 0xF800,
                  };

Adafruit_AMG88xx amg;


#define AMG_COLS 8
#define AMG_ROWS 8
float pixels[AMG_COLS * AMG_ROWS];
float pixels2[AMG_COLS * AMG_ROWS];

#define INTERPOLATED_COLS 30  //24
#define INTERPOLATED_ROWS 30  //24


float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f);
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
float cubicInterpolate(float p[], float x);
float bicubicInterpolate(float p[], float x, float y);
void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols,
                       float *dest, uint8_t dest_rows, uint8_t dest_cols);
void findmod(int bil[], int n, int mod[]);

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println("\n\nAMG88xx Interpolated Thermal Camera!");

  pinMode(motor, OUTPUT);
  pinMode(valve, OUTPUT);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  colorbar();

  // default settings
  if (!amg.begin()) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1) {
      delay(1);
    }
  }

  Serial.println("-- Thermal Camera Test --");
}

float pix_max, pos_x, pos_y;

void loop() {
  //read all the pixels
  amg.readPixels(pixels2);
  for (int i = 0; i < 64; i++) {
    pixels[i] = (pixels2[((((int)(i / 8) * 8) + 7) - (i % 8))]) + 2.5; //error +2.5c
    // Serial.println(pixels[i]);
  }
  //#ifdef DEBUG
  //  Serial.print("[");
  //  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
  //    Serial.print(pixels[(i - 1)]);
  //    Serial.print(", ");
  //    if ( i % 8 == 0 ) Serial.println();
  //  }
  //  Serial.println("]");
  //  Serial.println();
  //#endif

  float dest_2d[INTERPOLATED_ROWS * INTERPOLATED_COLS];

  // int32_t t = millis();
  interpolate_image(pixels, AMG_ROWS, AMG_COLS, dest_2d, INTERPOLATED_ROWS, INTERPOLATED_COLS);
  //#ifdef DEBUG
  //  Serial.print("Interpolation took "); Serial.print(millis() - t); Serial.println(" ms");
  //#endif



  uint16_t boxsize = min(tft.width() / INTERPOLATED_COLS, tft.height() / INTERPOLATED_COLS);
  //uint16_t boxsize = 20;
  drawpixels(dest_2d, INTERPOLATED_ROWS, INTERPOLATED_COLS, boxsize, boxsize, false);

  tft.setTextColor(WHITE);
  tft.setCursor(20, 430);
  tft.setTextSize(3);
  tft.fillRect(10, 430, 120, 30, BLACK );
  tft.print("MAX:");
  tft.fillRect(70, 430, 120, 30, BLACK );
  tft.print(pix_max);
  tft.print(" C");
  tft.drawCircle(pos_x, pos_y, 6, 0);
  tft.drawCircle(pos_x, pos_y, 5, 0);
  tft.drawLine(pos_x, pos_y - 3, pos_x, pos_y + 3, 0);
  tft.drawLine(pos_x - 3, pos_y, pos_x + 3, pos_y, 0);
  pix_max = 0;

  if (k >= akurasi) {
    //tft.setCursor(0, 420);
    tft.fillRect(260, 420, 50, 50, GREEN );
    digitalWrite(motor, 0);
    digitalWrite(valve, 1);
  }
  else {
    tft.fillRect(260, 420, 50, 50, RED );
    digitalWrite(motor, 1);
    digitalWrite(valve, 0);
  }
  Serial.println(k);


}

void drawpixels(float *p, uint8_t rows, uint8_t cols, uint8_t boxWidth, uint8_t boxHeight, boolean showVal) {
  int colorTemp;
  int warna[128];
  int i = 0;
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      float val = get_point(p, rows, cols, x, y);
      if (val >= MAXTEMP) colorTemp = MAXTEMP;
      else if (val <= MINTEMP) colorTemp = MINTEMP;
      else colorTemp = val;

      uint8_t colorIndex = map(colorTemp, MINTEMP, MAXTEMP, 0, 255);
      colorIndex = constrain(colorIndex, 0, 255);
      //draw the pixels!
      uint16_t color;
      color = val * 2;
      tft.fillRect(boxWidth * x + 10, boxHeight * y + 90, boxWidth, boxHeight, camColors[colorIndex]);
      if (y == -x + rows || y == x || x == rows / 2 || y == rows / 2) {
        //tft.fillRect(boxWidth * x, boxHeight * y + 90, boxWidth, boxHeight, camColors[colorIndex]);
        warna[i] = camColors[colorIndex];
        i++;
      }

      if (pix_max < val) {
        pix_max = val;
        pos_x = boxWidth * x + 10;
        pos_y = boxHeight * y + 90;
      }


      if (showVal) {
        tft.setCursor(boxWidth * y + boxWidth / 2 - 12, 40 + boxHeight * x + boxHeight / 2 - 4);
        tft.setTextColor(WHITE);  tft.setTextSize(1);
        tft.print(val, 1);
      }
    }
  }
  findmod(warna, 100, mod);
}


#include <Arduino.h>

float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y);
void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y,
               float f);
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols,
                      int8_t x, int8_t y);
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols,
                      int8_t x, int8_t y);
float cubicInterpolate(float p[], float x);
float bicubicInterpolate(float p[], float x, float y);
void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols,
                       float *dest, uint8_t dest_rows, uint8_t dest_cols);

float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {
  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;
  if (x >= cols)
    x = cols - 1;
  if (y >= rows)
    y = rows - 1;
  return p[y * cols + x];
}

void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y,
               float f) {
  if ((x < 0) || (x >= cols))
    return;
  if ((y < 0) || (y >= rows))
    return;
  p[y * cols + x] = f;
}

// src is a grid src_rows * src_cols
// dest is a pre-allocated grid, dest_rows*dest_cols
void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols,
                       float *dest, uint8_t dest_rows, uint8_t dest_cols) {
  float mu_x = (src_cols - 1.0) / (dest_cols - 1.0);
  float mu_y = (src_rows - 1.0) / (dest_rows - 1.0);

  float adj_2d[16]; // matrix for storing adjacents

  for (uint8_t y_idx = 0; y_idx < dest_rows; y_idx++) {
    for (uint8_t x_idx = 0; x_idx < dest_cols; x_idx++) {
      float x = x_idx * mu_x;
      float y = y_idx * mu_y;
      // Serial.print("("); Serial.print(y_idx); Serial.print(", ");
      // Serial.print(x_idx); Serial.print(") = "); Serial.print("(");
      // Serial.print(y); Serial.print(", "); Serial.print(x); Serial.print(") =
      // ");
      get_adjacents_2d(src, adj_2d, src_rows, src_cols, x, y);
      /*
        Serial.print("[");
        for (uint8_t i=0; i<16; i++) {
        Serial.print(adj_2d[i]); Serial.print(", ");
        }
        Serial.println("]");
      */
      float frac_x = x - (int)x; // we only need the ~delta~ between the points
      float frac_y = y - (int)y; // we only need the ~delta~ between the points
      float out = bicubicInterpolate(adj_2d, frac_x, frac_y);
      // Serial.print("\tInterp: "); Serial.println(out);
      set_point(dest, dest_rows, dest_cols, x_idx, y_idx, out);
    }
  }
}

// p is a list of 4 points, 2 to the left, 2 to the right
float cubicInterpolate(float p[], float x) {
  float r = p[1] + (0.5 * x *
                    (p[2] - p[0] +
                     x * (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] +
                          x * (3.0 * (p[1] - p[2]) + p[3] - p[0]))));
  /*
    Serial.print("interpolating: [");
    Serial.print(p[0],2); Serial.print(", ");
    Serial.print(p[1],2); Serial.print(", ");
    Serial.print(p[2],2); Serial.print(", ");
    Serial.print(p[3],2); Serial.print("] w/"); Serial.print(x); Serial.print("
    = "); Serial.println(r);
  */
  return r;
}

// p is a 16-point 4x4 array of the 2 rows & columns left/right/above/below
float bicubicInterpolate(float p[], float x, float y) {
  float arr[4] = {0, 0, 0, 0};
  arr[0] = cubicInterpolate(p + 0, x);
  arr[1] = cubicInterpolate(p + 4, x);
  arr[2] = cubicInterpolate(p + 8, x);
  arr[3] = cubicInterpolate(p + 12, x);
  return cubicInterpolate(arr, y);
}

// src is rows*cols and dest is a 4-point array passed in already allocated!
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols,
                      int8_t x, int8_t y) {
  // Serial.print("("); Serial.print(x); Serial.print(", "); Serial.print(y);
  // Serial.println(")");
  // pick two items to the left
  dest[0] = get_point(src, rows, cols, x - 1, y);
  dest[1] = get_point(src, rows, cols, x, y);
  // pick two items to the right
  dest[2] = get_point(src, rows, cols, x + 1, y);
  dest[3] = get_point(src, rows, cols, x + 2, y);
}

// src is rows*cols and dest is a 16-point array passed in already allocated!
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols,
                      int8_t x, int8_t y) {
  // Serial.print("("); Serial.print(x); Serial.print(", "); Serial.print(y);
  // Serial.println(")");
  float arr[4];
  for (int8_t delta_y = -1; delta_y < 3; delta_y++) { // -1, 0, 1, 2
    float *row = dest + 4 * (delta_y + 1); // index into each chunk of 4
    for (int8_t delta_x = -1; delta_x < 3; delta_x++) { // -1, 0, 1, 2
      row[delta_x + 1] = get_point(src, rows, cols, x + delta_x, y + delta_y);
    }
  }
}

void colorbar() {
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 20);
  tft.print("AMG8833 Thermal Camera");
  for (int i = 0; i < 320; i++) {
    tft.fillRect(i, 50, 1, 25, camColors[(int)(i * 0.8)]);
  }
  tft.setCursor(0, 55);
  tft.setTextSize(2);
  tft.print(MINTEMP);
  tft.print(" C");
  tft.setCursor(270, 55);
  tft.print(MAXTEMP);
  tft.print(" C");

}

void findmod(int bil[], int n, int mod[])
{
  int total[100];
  k = 1;
  x = 0;
  //untuk mengurutkan secara ascending
  for (int c = 0; c < n; c++)
  {
    for (int i = (n - 1); i >= 0; i--)
    {
      if (bil[i] < bil[i - 1])
      {
        int temp;
        temp = bil[i];
        bil[i] = bil[i - 1];
        bil[i - 1] = temp;
      }
    }
  }
  //menghitung berapa kali muncul tiap angka
  for (int c = 0; c < n; c++)
  {
    total[c] = 0;
    for (int i = 0; i < n; i++)
    {
      if (bil[c] == bil[i])
      {
        total[c]++;
      }
    }
  }
  //menentukan nilai yang paling sering muncul
  for (int c = 0; c < n; c++)
  {
    if (total[c] > k)
    {
      k = total[c];
    }
  }
  //jika modus lebih dari satu
  for (int c = 0; c < n; c++)
  {
    if (x == 0)
      mod[x] = 0;
    else
      mod[x] = mod[x - 1];
    if (total[c] == k)
    {
      if (bil[c] != mod[x])
      {
        mod[x] = bil[c];
        x++;
      }
    }
  }
  //Jika Semua angka muncul sama banyak
  int z = 0;
  for (int c = 0; c < n; c++)
  {
    if (total[c] == k)
    {
      z++;
    }
  }
  if (z == n)
  {
    x = 0;
  }
  //findmod(bil, n, mod);
  if (x == 0)
    Serial.print(" “Tidak Ada Modus!” ");
  else
  {
    Serial.print("Modus : ");
    for (int c = 0; c < x; c++)
    {
      Serial.print( mod[c]);
    }
  }
}
