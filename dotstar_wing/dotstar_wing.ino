// Adafruit_DotStarMatrix example for single DotStar LED matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>

//Longrunner board with ATmega328P
//Setttings:
//Board: Arduino Mini
//Processor:ATmega328P
//Programmer:ArduinoISP

#define DATAPIN    11
#define CLOCKPIN   13


#define SHIFTDELAY 80
#define BRIGHTNESS 40

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)
//   DOTSTAR_BGR  Pixels are wired for BGR bitstream (APA102-2020 DotStars)

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
                                  8, 8, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_BOTTOM     + DS_MATRIX_LEFT +
                                  DS_MATRIX_COLUMNS + DS_MATRIX_ZIGZAG,
                                  DOTSTAR_BGR);

const uint16_t primaryColors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

const uint16_t adaColors[] = {
  matrix.Color(255, 0, 0),   //A red
  matrix.Color(150, 0, 255), //U purple
  matrix.Color(255, 125, 0), //D orange
  matrix.Color(200, 255, 0), //A yellowish
  matrix.Color(150, 0, 255), //U purple
  matrix.Color(0, 255, 0),   //F green
  matrix.Color(255, 65, 0),  //T reddish
  matrix.Color(255, 0, 220), //I pink
  matrix.Color(0, 255, 225), //R blue
  matrix.Color(200, 255, 0),
  matrix.Color(150, 0, 255), //U purple
  matrix.Color(255, 0, 220), //I pink
  matrix.Color(200, 255, 0),
  matrix.Color(255, 65, 0),  //T reddish
  matrix.Color(255, 220, 0)  //! orange/yellow
};

char string4print[] = "I LOVE YOU!";
//char string4print[] = "MARICILLE ROCKS";


void setup() {
  Serial.begin(115200);
 
  // uncomment to have wait
  while (!Serial) delay(500); 

  Serial.println("\nDotstar Matrix Wing");
  Serial.println(DATAPIN);
  Serial.println(CLOCKPIN);
  matrix.begin();
  matrix.setFont(&TomThumb);
  matrix.setTextWrap(false);
  matrix.setBrightness(BRIGHTNESS);

  for (byte i = 0; i < 3; i++) {
    matrix.fillScreen(primaryColors[i]);
    matrix.show();
    delay(750);
  }
}

int x = matrix.width()-5;
int pass = 0;

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 5); // Sets location of letters when printing
  for (byte i = 0; i < strlen(string4print); i++) {
    // set the color
    matrix.setTextColor(adaColors[i]);
    // write the letter
    matrix.print(string4print[i]);
//    Serial.println(String(i));
//    Serial.println(adaColors[i]);
    Serial.println(string4print[i]);
//    delay(200);
  }
Serial.println("X value");
Serial.println(x);
  if (--x < -50) { 
    x = matrix.width()-5; //Start cursor at beginning
  }

  matrix.show();
  delay(SHIFTDELAY);
}
