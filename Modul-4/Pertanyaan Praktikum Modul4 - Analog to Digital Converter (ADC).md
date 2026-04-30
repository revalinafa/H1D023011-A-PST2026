# Praktikum Sistem Tertanam  
## Modul 4 - Analog to Digital Converter (ADC) dan Pulse Width Modulation (PWM)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Deskripsi Percobaan

Pada praktikum ini dilakukan pembacaan nilai analog dari **potensiometer** menggunakan **ADC Arduino**, kemudian nilai tersebut digunakan untuk mengontrol sudut **servo motor** menggunakan sinyal **PWM**.

---

# Konfigurasi Rangkaian

## Wiring Komponen

| Komponen      | Pin       | Arduino |
| ------------- | --------- | ------- |
| Potensiometer | Kiri      | GND     |
| Potensiometer | Tengah    | A0      |
| Potensiometer | Kanan     | 5V      |
| Servo         | VCC       | 5V      |
| Servo         | GND       | GND     |
| Servo         | Signal    | Pin 9   |

---

# Diagram Alur Sistem

```mermaid
flowchart LR
A[Potensiometer] --> B[ADC Arduino]
B --> C[Data ADC]
C --> D[Mapping Sudut Servo]
D --> E[Servo Motor]
```

---

# Jawaban Pertanyaan Praktikum

## 1. Fungsi analogRead()

Fungsi `analogRead()` digunakan untuk membaca nilai tegangan analog dari potensiometer dan mengubahnya menjadi data digital (ADC) dengan rentang nilai 0 sampai 1023.

---

## 2. Fungsi map()

Fungsi `map()` digunakan untuk mengubah rentang nilai ADC (0–1023) menjadi rentang sudut servo.

Tanpa `map()`, nilai ADC tidak bisa langsung digunakan untuk mengontrol servo karena memiliki skala yang berbeda.

---

## 3. Program Modifikasi (Servo 30° - 150°)

## Kode Program

```cpp
#include <Servo.h>

Servo myservo;

// Pin
const int potensioPin = A0;
const int servoPin = 9;

int pos = 0;
int val = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {

  // Baca ADC
  val = analogRead(potensioPin);

  // Mapping ke sudut 30 - 150 derajat
  pos = map(val, 0, 1023, 30, 150);

  // Gerakkan servo
  myservo.write(pos);

  // Monitoring
  Serial.print("ADC: ");
  Serial.print(val);
  Serial.print(" | Sudut: ");
  Serial.println(pos);

  delay(15);
}
```

---

# Penjelasan Kode

## Library

- `Servo.h` → untuk mengontrol servo motor

## Setup

- `myservo.attach(9)` → menghubungkan servo ke pin 9
- `Serial.begin(9600)` → komunikasi serial

## Loop

### Membaca ADC
```cpp
val = analogRead(potensioPin);
```

### Mapping
```cpp
pos = map(val, 0, 1023, 30, 150);
```

### Output Servo
```cpp
myservo.write(pos);
```

---

# Hasil Pengamatan

| ADC | Sudut Servo |
|-----|------------|
| 0   | 30°        |
| 512 | 90°        |
| 1023| 150°       |

---

# Kesimpulan

Potensiometer menghasilkan sinyal analog yang dibaca oleh ADC Arduino, kemudian dikonversi menggunakan fungsi `map()` agar sesuai dengan kebutuhan servo. Dengan membatasi rentang sudut servo menjadi 30° hingga 150°, gerakan servo menjadi lebih terkontrol dan tidak mencapai batas ekstremnya.
