#include "arduinoFFT.h"
#include "LinkedList.h"

const int sensorPin = 0;
const int ledPin = 2;
int lightVal;
int lightCal;

LinkedList<int> readingWindow = LinkedList<int>();
arduinoFFT FFT = arduinoFFT();

const int WINLEN = 64;
const uint16_t samples = 64;
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

double vReal[samples];
double vImag[samples];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup() {
  // put your setup code here, to run once:
//  pinMode(ledPin, OUTPUT);
  lightCal = analogRead(sensorPin);

//  serial setup
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Ready");
}


void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(2, HIGH);
//  delay(1000);
//  digitalWrite(2, LOW);
//  delay(1000);
    lightVal = analogRead(sensorPin);
//    add to window



    readingWindow.add(lightVal);
    if (readingWindow.size() > WINLEN){
      readingWindow.remove(0);
      for (int i = 0; i<WINLEN; i++){
//        Serial.print(readingWindow.get(i));
          vReal[i] = readingWindow.get(i);
      }
    }
    
    double x = FFT.MajorPeak(vReal, samples, samplingFrequency);
    Serial.println(x);
    delay(10);
    
    
}
