#  Praktikum Sistem Tertanam  
## Modul 4 - Analog to Digital Converter (ADC) dan Pulse Width Modulation (PWM)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Deskripsi Percobaan

Pada praktikum ini dilakukan pembacaan nilai analog dari **potensiometer** menggunakan **ADC Arduino**, kemudian nilai tersebut digunakan untuk mengatur kecerahan **LED** menggunakan sinyal **PWM (Pulse Width Modulation)**.

---

# Konfigurasi Rangkaian

## Wiring Komponen

| Komponen      | Pin       | Arduino |
| ------------- | --------- | ------- |
| Potensiometer | Kiri      | GND     |
| Potensiometer | Tengah    | A0      |
| Potensiometer | Kanan     | 5V      |
| LED (+)       | Anoda     | Pin 9 (PWM) |
| LED (-)       | Katoda    | GND     |
| Resistor      | Seri LED  | 220Ω    |

---

# Diagram Alur Sistem

<img width="1178" height="269" alt="image" src="https://github.com/user-attachments/assets/a51bb025-302e-4ae3-b9e7-17f166ccc4a1" />

---

# Jawaban Pertanyaan Praktikum

## 1. Mengapa LED bisa diatur dengan analogWrite()

LED dapat diatur kecerahannya karena fungsi `analogWrite()` menggunakan metode PWM (Pulse Width Modulation), yaitu mengatur lama waktu sinyal HIGH dan LOW dalam satu periode.

Semakin lama sinyal HIGH (duty cycle besar), maka LED akan terlihat semakin terang.

---

## 2. Hubungan ADC dan PWM

Nilai ADC (0–1023) dikonversi menjadi nilai PWM (0–255) menggunakan fungsi `map()`.

Hal ini dilakukan karena ADC memiliki resolusi 10-bit, sedangkan PWM hanya 8-bit.

---

## 3. Program Modifikasi (PWM 50 - 200)

## Kode Program

```cpp
#include <Arduino.h>

// Pin
const int potPin = A0;
const int ledPin = 9;

int nilaiADC = 0;
int pwm = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Baca ADC
  nilaiADC = analogRead(potPin);

  // Mapping
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // Batasi hanya 50 - 200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } else {
    analogWrite(ledPin, 0); // LED mati
  }

  // Monitoring
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}
```

---

# Penjelasan Kode

## Setup

- `pinMode(ledPin, OUTPUT)` → LED sebagai output
- `Serial.begin(9600)` → komunikasi serial

## Loop

### Membaca ADC
```cpp
nilaiADC = analogRead(potPin);
```

### Mapping
```cpp
pwm = map(nilaiADC, 0, 1023, 0, 255);
```

### Seleksi Rentang PWM
```cpp
if (pwm >= 50 && pwm <= 200)
```

- LED hanya aktif pada kecerahan sedang
- Di luar itu LED dimatikan

---

# Hasil Pengamatan

| ADC | PWM | Kondisi LED |
|-----|-----|------------|
| 0   | 0   | Mati       |
| 200 | 50  | Mulai nyala |
| 512 | 127 | Normal     |
| 800 | 200 | Maks sedang |
| 1023| 255 | Mati       |

---

# Kesimpulan

PWM memungkinkan pengaturan kecerahan LED dengan mengatur duty cycle sinyal digital. Nilai ADC dari potensiometer dapat dikonversi menjadi PWM menggunakan fungsi `map()`. Dengan pembatasan rentang PWM, LED hanya menyala pada tingkat kecerahan tertentu sehingga lebih terkontrol.
