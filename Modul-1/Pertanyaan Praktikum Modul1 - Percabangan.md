# 📘 Praktikum Sistem Tertanam  Modul 1 - Percabangan 
**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin 

# Jawaban Pertanyaan Praktikum

## 1. Pada kondisi apa program masuk ke blok if?

Program masuk ke blok **if** ketika nilai `timeDelay` kurang dari atau sama dengan 100.

```cpp
if (timeDelay <= 100)
```

Artinya LED sudah berkedip sangat cepat sehingga program melakukan reset.

---

## 2. Pada kondisi apa program masuk ke blok else?

Program masuk ke blok **else** ketika nilai `timeDelay` lebih dari 100.

```cpp
else {
  timeDelay -= 100;
}
```

Artinya LED akan semakin cepat.

---

## 3. Apa fungsi dari perintah delay(timeDelay)?

Perintah:

```cpp
delay(timeDelay);
```

Berfungsi untuk memberikan jeda waktu sebelum program melanjutkan ke baris berikutnya.

Semakin besar delay → LED semakin lambat  
Semakin kecil delay → LED semakin cepat  

---

## 4. Modifikasi Program:
Lambat → Cepat → Sedang → Mati

---

# 💻 Program Modifikasi

```cpp
const int ledPin = 11;   
int timeDelay = 1000;    

bool slowing = false;    

void setup() {
  pinMode(ledPin, OUTPUT);  
}

void loop() {

  digitalWrite(ledPin, HIGH);   
  delay(timeDelay);             

  digitalWrite(ledPin, LOW);    
  delay(timeDelay);             

  if (!slowing) {
    timeDelay -= 100;           

    if (timeDelay <= 200) {
      slowing = true;           
    }
  } 
  
  else {
    timeDelay += 100;           

    if (timeDelay >= 600) {
      digitalWrite(ledPin, LOW); 
      delay(3000);               
      
      timeDelay = 1000;          
      slowing = false;           
    }
  }
}
```

---

# 🔍 Penjelasan Kode

### Menentukan Pin LED
```cpp
const int ledPin = 11;
```
Menentukan pin yang digunakan LED

---

### Menentukan Delay Awal
```cpp
int timeDelay = 1000;
```
Menentukan kecepatan awal LED

---

### Variabel Status
```cpp
bool slowing = false;
```
Menentukan arah perubahan kecepatan

---

### Setup Arduino
```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
}
```
Mengatur pin LED sebagai output

---

### Menyalakan LED
```cpp
digitalWrite(ledPin, HIGH);
```
Menyalakan LED

---

### Mematikan LED
```cpp
digitalWrite(ledPin, LOW);
```
Mematikan LED

---

### Mempercepat LED
```cpp
timeDelay -= 100;
```
Mengurangi delay agar LED semakin cepat

---

### Memperlambat LED
```cpp
timeDelay += 100;
```
Menambah delay agar LED menjadi sedang

---

### Reset Program
```cpp
timeDelay = 1000;
```
Mengembalikan ke kondisi awal

---

# Kesimpulan

Pada praktikum percabangan sistem tertanam ini, program Arduino menggunakan struktur kontrol if-else untuk mengatur kecepatan kedipan LED secara bertahap. Variabel timeDelay berfungsi sebagai pengatur waktu nyala dan mati LED, di mana nilai yang semakin kecil membuat LED berkedip semakin cepat. Program awal menunjukkan alur perubahan dari lambat menuju cepat kemudian langsung reset, sedangkan pada program modifikasi dilakukan perubahan alur menjadi lambat → cepat → sedang → mati sehingga menghasilkan transisi yang lebih halus dan terstruktur. Dengan menggunakan percabangan serta pengaturan nilai delay secara dinamis, sistem dapat mengontrol perilaku LED secara otomatis sesuai kondisi yang ditentukan. Praktikum ini membantu memahami konsep dasar percabangan serta implementasinya dalam pengendalian perangkat keras pada sistem tertanam.
