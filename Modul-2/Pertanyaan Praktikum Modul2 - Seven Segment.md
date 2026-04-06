# Praktikum Modul 2 - Pemrograman GPIO (7 Segment)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Jawaban Pertanyaan Praktikum

## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan!

Rangkaian menggunakan 7-Segment 1 digit yang dihubungkan ke Arduino dengan konfigurasi berikut:
<img width="998" height="775" alt="image" src="https://github.com/user-attachments/assets/1fee49dc-1b2f-4ad2-883a-9f073bf482ac" />


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

Setiap pin segment dihubungkan melalui resistor 220Ω ke Arduino untuk membatasi arus.

Common Cathode → GND Arduino

---

## 2. Apa yang terjadi jika nilai num lebih dari 15?

Jika nilai num lebih dari 15, maka program akan mencoba mengakses array di luar batas:

digitPattern[num][i]

Karena array hanya memiliki indeks 0 sampai 15, maka jika lebih dari 15:

- Program dapat menampilkan angka tidak sesuai
- Segment menyala tidak beraturan
- Program bisa mengalami error

Hal ini disebut Array Out of Bound.

---

## 3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!

Program ini menggunakan Common Anode.

Hal ini dapat dilihat pada kode berikut:

digitalWrite(segmentPins[i], !digitPattern[num][i]);

Tanda ! menunjukkan bahwa logika dibalik:

- 1 menjadi LOW  
- 0 menjadi HIGH  

Pada Common Anode:

- LOW → LED menyala  
- HIGH → LED mati  

---

## 4. Program Modifikasi agar Tampilan berjalan dari F ke 0

```cpp
#include <Arduino.h>

const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, //0
  {0,1,1,0,0,0,0,0}, //1
  {1,1,0,1,1,0,1,0}, //2
  {1,1,1,1,0,0,1,0}, //3
  {0,1,1,0,0,1,1,0}, //4
  {1,0,1,1,0,1,1,0}, //5
  {1,0,1,1,1,1,1,0}, //6
  {1,1,1,0,0,0,0,0}, //7
  {1,1,1,1,1,1,1,0}, //8
  {1,1,1,1,0,1,1,0}, //9
  {1,1,1,0,1,1,1,0}, //A
  {0,0,1,1,1,1,1,0}, //b
  {1,0,0,1,1,1,0,0}, //C
  {0,1,1,1,1,0,1,0}, //d
  {1,0,0,1,1,1,1,0}, //E
  {1,0,0,0,1,1,1,0}  //F
};

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
}

void loop()
{
  for(int i=15; i>=0; i--)
  {
    displayDigit(i);
    delay(1000);
  }
}
```

---

# 🔍 Penjelasan Kode

### Library Arduino
Digunakan untuk memanggil fungsi Arduino

### Pin Segment
Menentukan pin Arduino yang digunakan untuk 7 segment

### Data Pola Digit
Menyimpan pola angka 0 sampai F

### Fungsi Display
Menampilkan angka sesuai input

### Setup Arduino
Mengatur pin sebagai output

### Perulangan Mundur
Menampilkan angka dari F ke 0

### Delay
Memberi jeda 1 detik

---

# Kesimpulan

Pada praktikum modul 2 ini, digunakan 7-segment display untuk menampilkan angka 0 sampai F menggunakan Arduino. Program memanfaatkan array untuk menyimpan pola segment dan fungsi untuk menampilkan angka secara efisien. Penggunaan perulangan memungkinkan tampilan berjalan otomatis. Pada modifikasi program, arah tampilan diubah dari F ke 0 dengan mengubah perulangan menjadi mundur. Praktikum ini membantu memahami penggunaan GPIO Arduino serta pengendalian perangkat output digital seperti 7-segment display.
