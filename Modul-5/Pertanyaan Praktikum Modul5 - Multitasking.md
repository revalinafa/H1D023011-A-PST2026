# Praktikum Pemrograman Sistem Tertanam

## Modul 5 - Real-Time Operating System (RTOS) dan Multitasking

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Deskripsi Percobaan

Pada praktikum ini dilakukan implementasi **Real-Time Operating System (RTOS)** menggunakan **FreeRTOS pada Arduino** untuk menjalankan beberapa task secara multitasking. Sistem dirancang untuk menjalankan tiga task secara concurrent, yaitu:

* Task 1: Mengontrol LED pada pin 8 (blink cepat)
* Task 2: Mengontrol LED pada pin 9 (blink lebih lambat)
* Task 3: Menampilkan nilai counter pada Serial Monitor

---

# Konfigurasi Rangkaian

## Wiring Komponen

| Komponen | Pin Arduino | Keterangan    |
| -------- | ----------- | ------------- |
| LED 1    | Pin 8       | Output Task 1 |
| LED 2    | Pin 9       | Output Task 2 |
| Resistor | Seri LED    | 220Ω          |
| GND      | GND         | Ground        |

---
<img width="720" height="1280" alt="WhatsApp Image 2026-05-04 at 09 25 a59" src="https://github.com/user-attachments/assets/47527bdf-aa36-479f-a6b1-2197d185b98b" />

# Diagram Alur Sistem

1. Inisialisasi Serial Communication
2. Membuat task menggunakan `xTaskCreate()`
3. Menjalankan scheduler (`vTaskStartScheduler()`)
4. Task berjalan secara multitasking:

   * Task 1 → LED 1 berkedip
   * Task 2 → LED 2 berkedip
   * Task 3 → Counter bertambah di Serial Monitor

---

# Jawaban Pertanyaan Praktikum

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task berjalan secara **concurrent (bergantian sangat cepat)**.

Mekanismenya adalah:

* FreeRTOS menggunakan **scheduler** untuk mengatur eksekusi task
* Semua task memiliki prioritas yang sama (priority = 1)
* Scheduler menggunakan metode **time slicing**
* CPU berpindah dari satu task ke task lain dalam waktu sangat cepat

Fungsi penting:

```cpp
vTaskDelay()
```

Digunakan untuk memberi jeda pada task sehingga task lain mendapat kesempatan untuk dieksekusi.

Dengan demikian, meskipun terlihat berjalan bersamaan, sebenarnya task dieksekusi secara **bergantian dengan sangat cepat**.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Langkah-langkah:

### 1. Membuat fungsi task baru

```cpp
void Task4(void *pvParameters) {
  while(1) {
    Serial.println("Task 4 berjalan");
    vTaskDelay(400 / portTICK_PERIOD_MS);
  }
}
```

### 2. Menambahkan task ke dalam `setup()`

```cpp
xTaskCreate(
  Task4,
  "task4",
  128,
  NULL,
  1,
  NULL
);
```

### 3. Scheduler tetap dijalankan

```cpp
vTaskStartScheduler();
```

Penjelasan:
Task baru akan dimasukkan ke dalam scheduler dan dijalankan bersama task lain. Jika memiliki prioritas yang sama, maka task akan berbagi waktu CPU. Jika prioritas lebih tinggi, task tersebut akan lebih sering dieksekusi.

---

## 3. Modifikasi Program (Potensiometer untuk Mengatur Kecepatan LED)

## Kode Program

```cpp
#include <Arduino_FreeRTOS.h>

// Pin
const int potPin = A0;
int delayTask1 = 200;
int delayTask2 = 300;

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskReadPot(void *pvParameters);

void setup() {
  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
  xTaskCreate(TaskReadPot, "taskPot", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);

  while (1) {
    digitalWrite(8, HIGH);
    vTaskDelay(delayTask1 / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(delayTask1 / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(9, OUTPUT);

  while (1) {
    digitalWrite(9, HIGH);
    vTaskDelay(delayTask2 / portTICK_PERIOD_MS);
    digitalWrite(9, LOW);
    vTaskDelay(delayTask2 / portTICK_PERIOD_MS);
  }
}

void TaskReadPot(void *pvParameters) {
  while (1) {
    int nilai = analogRead(potPin);

    int mappedDelay = map(nilai, 0, 1023, 100, 1000);

    delayTask1 = mappedDelay;
    delayTask2 = mappedDelay + 100;

    Serial.print("ADC: ");
    Serial.print(nilai);
    Serial.print(" | Delay: ");
    Serial.println(mappedDelay);

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
```

---

# Penjelasan Kode

## TaskReadPot

### Membaca nilai analog

```cpp
int nilai = analogRead(potPin);
```

### Mapping nilai

```cpp
int mappedDelay = map(nilai, 0, 1023, 100, 1000);
```

Fungsi dari bagian ini adalah untuk mengubah nilai potensiometer menjadi delay yang akan digunakan untuk mengatur kecepatan kedipan LED.

---

# Hasil Pengamatan

| Nilai ADC | Delay (ms) | Kecepatan LED |
| --------- | ---------- | ------------- |
| 0         | 100        | Sangat cepat  |
| 512       | ~500       | Sedang        |
| 1023      | 1000       | Lambat        |

Hasil menunjukkan bahwa:

* Nilai ADC kecil menghasilkan delay kecil → LED berkedip cepat
* Nilai ADC besar menghasilkan delay besar → LED berkedip lambat

---

# Kesimpulan

FreeRTOS memungkinkan sistem embedded menjalankan beberapa task secara multitasking. Task berjalan secara **concurrent**, bukan paralel. Scheduler mengatur pembagian waktu CPU antar task. Penggunaan potensiometer memungkinkan kontrol dinamis terhadap kecepatan LED dan Sistem menjadi lebih fleksibel dan responsif terhadap input eksternal

---
