# 📘 Praktikum Sistem Tertanam Modul 1 - Perulangan
**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Jawaban Pertanyaan Praktikum

## 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

Rangkaian 5 LED running menggunakan 5 buah LED yang dihubungkan ke pin digital Arduino dengan resistor sebagai pembatas arus.

Konfigurasi rangkaian:
<img width="990" height="774" alt="schematic 5 LED" src="https://github.com/user-attachments/assets/91d348ca-12cb-48eb-b8b3-eadf6d43b5f6" />


| No | LED | Pin Arduino |
|----|-----|-------------|
| 1  | LED 1 | Pin 2 |
| 2  | LED 2 | Pin 3 |
| 3  | LED 3 | Pin 4 |
| 4  | LED 4 | Pin 5 |
| 5  | LED 5 | Pin 6 |

Skema rangkaian:

```
Arduino UNO

Pin 2 ---- Resistor ---- LED 1 ---- GND
Pin 3 ---- Resistor ---- LED 2 ---- GND
Pin 4 ---- Resistor ---- LED 3 ---- GND
Pin 5 ---- Resistor ---- LED 4 ---- GND
Pin 6 ---- Resistor ---- LED 5 ---- GND
```

Semua kaki negatif LED dihubungkan ke GND Arduino.

---

## 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!

Program menggunakan perulangan **for** untuk menyalakan LED secara berurutan dari pin kecil ke pin besar.

```cpp
for (int ledPin = 2; ledPin < 8; ledPin++) {
  digitalWrite(ledPin, HIGH);
  delay(timer);
  digitalWrite(ledPin, LOW);
}
```

Penjelasan:
- Program mulai dari pin 2
- LED dinyalakan satu per satu
- Setelah menyala, LED dimatikan
- Program berpindah ke pin berikutnya
- Proses ini membuat efek LED berjalan dari kiri ke kanan

---

## 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!

Program menggunakan perulangan **for** dengan decrement untuk menghidupkan LED dari pin besar ke kecil.

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--) {
  digitalWrite(ledPin, HIGH);
  delay(timer);
  digitalWrite(ledPin, LOW);
}
```

Penjelasan:
- Program mulai dari pin terbesar
- LED menyala satu per satu
- Program bergerak ke pin lebih kecil
- Efek LED berjalan dari kanan ke kiri

---

## 4. Program Tiga LED Kanan dan Tiga LED Kiri Bergantian

# 💻 Program Modifikasi

```cpp
int timer = 300; 

void setup() {

  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }

}

void loop() {

  // Tiga LED kiri menyala
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  delay(timer);

  // Tiga LED kanan menyala
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  delay(timer);

}
```

---

# 🔍 Penjelasan Kode

### Menentukan Timer
```cpp
int timer = 300;
```
Menentukan kecepatan perpindahan LED

---

### Setup Arduino
```cpp
void setup()
```
Fungsi awal dijalankan sekali

---

### Inisialisasi Pin LED
```cpp
for (int ledPin = 2; ledPin <= 7; ledPin++)
```
Mengatur pin 2 sampai 7 sebagai output

---

### Menyalakan LED Kiri
```cpp
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
```
Menyalakan tiga LED kiri

---

### Mematikan LED Kanan
```cpp
digitalWrite(5, LOW);
digitalWrite(6, LOW);
digitalWrite(7, LOW);
```
Mematikan LED kanan

---

### Delay
```cpp
delay(timer);
```
Menunggu sebelum berpindah

---

### Menyalakan LED Kanan
```cpp
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
digitalWrite(7, HIGH);
```
Menyalakan tiga LED kanan

---

### Mematikan LED Kiri
```cpp
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
```
Mematikan LED kiri

---

# Kesimpulan

Pada praktikum perulangan sistem tertanam ini, digunakan struktur perulangan **for** untuk mengontrol LED secara berurutan. Program mampu menghasilkan efek LED berjalan dari kiri ke kanan dan kembali dari kanan ke kiri dengan mengatur urutan pin digital Arduino. Selain itu, dilakukan modifikasi program untuk menyalakan tiga LED kiri dan tiga LED kanan secara bergantian. Dengan menggunakan perulangan, program menjadi lebih efisien dan mudah dikembangkan. Praktikum ini membantu memahami konsep dasar perulangan serta implementasinya dalam pengendalian perangkat keras pada sistem tertanam.
