 # Praktikum Modul 2 - Pemrograman GPIO (Push Button & Counter)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Jawaban Pertanyaan Praktikum

## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan!

Rangkaian menggunakan 7-Segment 1 digit dan 2 push button yang dihubungkan ke Arduino dengan konfigurasi berikut:
<img width="971" height="764" alt="image" src="https://github.com/user-attachments/assets/cdac989e-917d-4f5d-8296-f7c96254298d" />

### 🔌 Seven Segment

| Segment | Pin Arduino |
|---------|-------------|
| a | 7 |
| b | 6 |
| c | 5 |
| d | 11 |
| e | 10 |
| f | 8 |
| g | 9 |
| dp | 4 |

Setiap pin segment dihubungkan dengan resistor 220Ω.

Common Cathode → GND Arduino

---

### 🔘 Push Button

| Komponen | Pin Arduino |
|----------|------------|
| Button UP | 3 |
| Button DOWN | 2 |

Kedua push button:
- Satu kaki → pin Arduino  
- Satu kaki → GND  

Menggunakan mode `INPUT_PULLUP` (tanpa resistor eksternal)

---

## 2. Mengapa menggunakan INPUT_PULLUP? Apa keuntungannya?

Mode `INPUT_PULLUP` digunakan agar pin memiliki nilai default HIGH.

### Cara kerja:
- Tidak ditekan → HIGH  
- Ditekan → LOW  

### Keuntungan:
- Tidak perlu resistor eksternal
- Menghindari kondisi floating (noise)
- Rangkaian lebih sederhana
- Lebih stabil untuk pembacaan input

---

## 3. Jika salah satu LED segment tidak menyala, apa penyebabnya?

### Dari sisi Hardware:
- Kabel salah sambung
- Resistor tidak terpasang / rusak
- LED segment rusak
- Pin Arduino rusak
- Ground tidak terhubung

### Dari sisi Software:
- Salah mapping pin
- Data `digitPattern` salah
- Logika HIGH/LOW terbalik
- Kesalahan indeks array
- Fungsi display tidak dipanggil

---


## 4. Program Modifikasi Counter dengan Increment & Decrement

```cpp
#include <Arduino.h>

const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
const int btnUp = 3;
const int btnDown = 2;

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,0,1,1,0},
  {1,1,1,0,1,1,1,0},
  {0,0,1,1,1,1,1,0},
  {1,0,0,1,1,1,0,0},
  {0,1,1,1,1,0,1,0},
  {1,0,0,1,1,1,1,0},
  {1,0,0,0,1,1,1,0}
};

int currentDigit = 0;

bool lastUpState = HIGH;
bool lastDownState = HIGH;

void displayDigit(int num)
{
  for(int i=0; i<8; i++)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup()
{
  for(int i=0; i<8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  displayDigit(currentDigit);
}

void loop()
{
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown);

  if(lastUpState == HIGH && upState == LOW)
  {
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0;
    displayDigit(currentDigit);
  }

  if(lastDownState == HIGH && downState == LOW)
  {
    currentDigit--;
    if(currentDigit < 0) currentDigit = 15;
    displayDigit(currentDigit);
  }

  lastUpState = upState;
  lastDownState = downState;
}
```

---

# 🔍 Penjelasan Kode

- Library Arduino: untuk fungsi dasar
- Pin Segment: menentukan koneksi
- Push Button: input kontrol
- Data Digit: pola angka 0–F
- Counter: menyimpan nilai
- displayDigit: menampilkan angka
- Setup: inisialisasi pin
- Loop: membaca tombol dan mengontrol counter

---

# Kesimpulan

Push button digunakan sebagai input untuk mengontrol counter pada seven segment. Dengan dua tombol, sistem dapat melakukan increment dan decrement nilai. Mode INPUT_PULLUP membuat rangkaian lebih sederhana dan stabil.
