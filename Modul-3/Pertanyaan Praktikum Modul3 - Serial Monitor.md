# Praktikum Sistem Tertanam Modul 3 - Protokol Komunikasi (UART - Serial LED)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

#  Deskripsi Percobaan

Percobaan ini bertujuan untuk memahami komunikasi **Serial (UART)** antara komputer dan Arduino, serta mengontrol LED menggunakan input dari **keyboard melalui Serial Monitor**.

---

# Rangkaian

| Komponen | Pin Arduino |
| -------- | ----------- |
| LED      | 12          |
| GND      | GND         |

---

# Alur Sistem

```
Keyboard → Serial Monitor → Arduino (UART) → LED
```

---

# Jawaban Pertanyaan Praktikum

## 1. Proses dari Input Keyboard hingga LED Menyala/Mati

Proses kerja sistem adalah sebagai berikut:

1. User mengetik karakter pada keyboard (misalnya '1' atau '0')
2. Data dikirim melalui Serial Monitor ke Arduino menggunakan komunikasi UART
3. Arduino membaca data menggunakan `Serial.read()`
4. Data dibandingkan menggunakan percabangan
5. Arduino mengeksekusi `digitalWrite()`
6. LED menyala atau mati sesuai perintah

### Diagram Alur

```
Input Keyboard
      ↓
Serial Monitor
      ↓
Serial.available()
      ↓
Serial.read()
      ↓
Percabangan (if-else)
      ↓
digitalWrite()
      ↓
LED ON / OFF
```

---

## 2. Fungsi Serial.available()

Digunakan untuk mengecek apakah ada data yang tersedia pada buffer serial sebelum dibaca.

### Jika digunakan:

* Program aman dari pembacaan data kosong
* Data valid dan stabil

### Jika tidak digunakan:

* Arduino bisa membaca data kosong
* Nilai bisa acak (-1)
* Program menjadi tidak stabil

Kesimpulan:
`Serial.available()` berfungsi sebagai pengaman sebelum membaca data.

---

## 3. Program Modifikasi (LED Blink saat input '2')

### Source Code

```cpp
const int PIN_LED = 12;

bool blinkMode = false;
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1' ON, '0' OFF, '2' BLINK");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      blinkMode = false;
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED ON");
    }
    else if (data == '0') {
      blinkMode = false;
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED OFF");
    }
    else if (data == '2') {
      blinkMode = true;
      Serial.println("LED BLINK");
    }
  }

  if (blinkMode) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }
  }
}
```

---

## 🧾 Penjelasan Kode

### Inisialisasi Pin

Menentukan pin LED sebagai output.

### Variabel Blink

* `blinkMode` → status mode berkedip
* `previousMillis` → menyimpan waktu sebelumnya
* `interval` → jeda waktu kedip

### Setup

* `Serial.begin(9600)` → memulai komunikasi serial
* `pinMode()` → mengatur pin sebagai output

### Pembacaan Serial

* `Serial.available()` → cek data masuk
* `Serial.read()` → membaca data

### Kontrol LED

* '1' → LED ON
* '0' → LED OFF
* '2' → LED BLINK

### Logika millis()

Mengatur kedip LED tanpa menghentikan program.

---

## 4. Perbandingan delay() vs millis()

| Aspek        | delay()    | millis()     |
| ------------ | ---------- | ------------ |
| Cara kerja   | Blocking   | Non-blocking |
| Respons      | Lambat     | Cepat        |
| Multitasking | Tidak bisa | Bisa         |

### delay()

* Program berhenti sementara
* Tidak bisa membaca input

### millis()

* Program tetap berjalan
* Bisa membaca input secara real-time

Kesimpulan:
`millis()` lebih baik digunakan karena sistem menjadi responsif dan tidak terblokir.

---

## Ilustrasi

```
delay():
[BLINK] ---- STOP ---- [BLINK]

millis():
[BLINK] [READ INPUT] [BLINK]
```

---

# Kesimpulan

Pada praktikum ini, komunikasi UART digunakan untuk mengontrol LED melalui input keyboard. Penggunaan `Serial.available()` penting untuk menjaga kestabilan sistem. Implementasi `millis()` membuat sistem lebih responsif dibandingkan `delay()`.

---
