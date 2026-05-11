#include <Arduino.h>

const int ledMerah = 13;
const int ledKuning = 12;
const int ledHijau = 11;

const int tombol = 2;


const int segA = 10;
const int segB = 9;
const int segC = 8;
const int segD = 7;
const int segE = 6;
const int segF = 5;
const int segG = 4;


int angka[10][7] = {

  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};


void tampilAngka(int nilai);

void setup() {

  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  pinMode(tombol, INPUT_PULLUP);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  Serial.begin(9600);

  // Kondisi awalnya lampu hijau terys
  digitalWrite(ledHijau, HIGH);
}

void loop() {

  if (digitalRead(tombol) == LOW) {

    Serial.println("Tombol ditekan");

    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, HIGH);

//jeda dulu lampu kuning 2 detik
    delay(2000);

    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, HIGH);

    for (int i = 9; i >= 0; i--) {

      tampilAngka(i);

      Serial.print("Countdown: ");
      Serial.println(i);

      delay(1000);
    }

    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);

    // Matikan seven segment
    tampilAngka(0);
  }
}

void tampilAngka(int nilai) {

  digitalWrite(segA, angka[nilai][0]);
  digitalWrite(segB, angka[nilai][1]);
  digitalWrite(segC, angka[nilai][2]);
  digitalWrite(segD, angka[nilai][3]);
  digitalWrite(segE, angka[nilai][4]);
  digitalWrite(segF, angka[nilai][5]);
  digitalWrite(segG, angka[nilai][6]);
}