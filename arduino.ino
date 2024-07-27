#include <Adafruit_AW9523.h>
#include <Wire.h>

Adafruit_AW9523 aw;

const int LED_TC16AT = 1;
const int LED_TC11T = 2;
const int LED_TC16T = 3;
const int LED_TC15T = 4;
const int LED_TC3AT = 5;
const int LED_PILOT = 6;

const int TC16AT_PAUSE = 2000; // milliseconds
const int TC11T_PAUSE = 2000; // milliseconds
const int TC16T_PAUSE = 2000; // milliseconds
const int TC15T_PAUSE = 2000; // milliseconds
const int TC3AT_PAUSE = 2000; // milliseconds
const int TRAIN_PAUSE = 1000; // milliseconds

int brightness = 255;

const int BETWEEN_TRAIN_PAUSE = 5000; // milliseconds

void (*services[])(void) {
   downGwrTrain,
   upSrTrain,
   downGwrTrain,
   upGwrTrain,
   downSrTrain,
   downGwrTrain,
   upGwrTrain,
   upGwrTrain
};

int i = 0;

void downGwrTrain() {
  aw.analogWrite(LED_TC16AT, brightness);
  delay(TC16AT_PAUSE);
  aw.analogWrite(LED_TC11T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC16AT, 0);
  delay(TC11T_PAUSE);
  aw.analogWrite(LED_TC16T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC11T, 0);
  delay(TC16T_PAUSE);
  aw.analogWrite(LED_TC15T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC16T, 0);
  delay(TC15T_PAUSE);
  aw.analogWrite(LED_TC15T, 0);
}

void upGwrTrain() {
  aw.analogWrite(LED_TC15T, brightness);
  delay(TC15T_PAUSE);
  aw.analogWrite(LED_TC16T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC15T, 0);
  delay(TC16T_PAUSE);
  aw.analogWrite(LED_TC11T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC16T, 0);
  delay(TC11T_PAUSE);
  aw.analogWrite(LED_TC16AT, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC11T, 0);
  delay(TC16AT_PAUSE);
  aw.analogWrite(LED_TC16AT, 0);
}

void downSrTrain() {
  aw.analogWrite(LED_TC16AT, brightness);
  delay(TC16AT_PAUSE);
  aw.analogWrite(LED_TC11T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC16AT, 0);
  delay(TC11T_PAUSE);
  aw.analogWrite(LED_TC3AT, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC11T, 0);
  delay(TC3AT_PAUSE);
  aw.analogWrite(LED_TC3AT, 0);
}

void upSrTrain() {
  aw.analogWrite(LED_TC3AT, brightness);
  delay(TC3AT_PAUSE);
  aw.analogWrite(LED_TC11T, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC3AT, 0);
  delay(TC11T_PAUSE);
  aw.analogWrite(LED_TC16AT, brightness);
  delay(TRAIN_PAUSE);
  aw.analogWrite(LED_TC11T, 0);
  delay(TC16AT_PAUSE);
  aw.analogWrite(LED_TC16AT, 0);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);  // wait for serial port to open
  Serial.println("Adafruit AW9523 Constant Current LED test!");
  Serial.println("Wire init");

  if (! aw.begin()) {
    while (1) delay(10);  // halt forever
    Serial.println("AW9523 not found? Check wiring!");
  }

  Serial.println("Setting pinmodes");
  aw.pinMode(LED_TC16AT, AW9523_LED_MODE);
  aw.pinMode(LED_TC11T, AW9523_LED_MODE);
  aw.pinMode(LED_TC16T, AW9523_LED_MODE);
  aw.pinMode(LED_TC15T, AW9523_LED_MODE);
  aw.pinMode(LED_TC3AT, AW9523_LED_MODE);
  aw.pinMode(LED_PILOT, AW9523_LED_MODE);
}

void loop() {
  brightness = analogRead(A0)/4.0;
  Serial.println(brightness);
  aw.analogWrite(LED_PILOT, brightness);
  Serial.println("Next service");
  services[i]();
  i = (i + 1) % (sizeof(services)/sizeof(services)[0]);
  delay(BETWEEN_TRAIN_PAUSE);
}
