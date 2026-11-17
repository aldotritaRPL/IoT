#include <ESP32Servo.h>

const int JUMLAH_SERVO = 14;

// Array pin GPIO ESP32 yang terhubung ke 14 servo
const int servoPins[JUMLAH_SERVO] = {
  13, 12,             // 2 Servo Atas
  14, 27, 26, 25, 33, // 5 Servo Kiri
  32, 15,             // 2 Servo Bawah
  2,  4,  16, 17, 18  // 5 Servo Kanan
};

Servo myServos[JUMLAH_SERVO];

void setup() {
  Serial.begin(115200);
  Serial.println("Memulai Mode Air Mancur Berdansa...");

  // Alokasi timer PWM ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Inisialisasi semua servo
  for (int i = 0; i < JUMLAH_SERVO; i++) {
    myServos[i].setPeriodHertz(50);
    myServos[i].attach(servoPins[i], 500, 2400);
    myServos[i].write(90); // Posisi awal tegak lurus (90 derajat)
  }
  
  delay(1000);
}

void loop() {
  // Pola 1: Efek Gelombang Berjalan (Wave Effect) memutar mengelilingi board
  for (int t = 0; t < 360; t += 5) {
    for (int i = 0; i < JUMLAH_SERVO; i++) {
      // Menggunakan fungsi sinus dengan pergeseran fase (phase shift) tiap servo
      // Hasilnya membuat gerakan naik-turun yang mengalir seperti gelombang air
      int angle = 90 + 70 * sin(radians(t + (i * 25))); 
      myServos[i].write(angle);
    }
    delay(25);
  }

  // Pola 2: Gerakan Bergantian Kiri dan Kanan (Saling Berbalasan)
  for (int repeat = 0; repeat < 3; repeat++) {
    // Sisi Kiri / Ganjil naik
    for (int i = 0; i < JUMLAH_SERVO; i += 2) {
      myServos[i].write(30);
    }
    // Sisi Kanan / Genap turun
    for (int i = 1; i < JUMLAH_SERVO; i += 2) {
      myServos[i].write(150);
    }
    delay(400);

    // Tukar posisi
    for (int i = 0; i < JUMLAH_SERVO; i += 2) {
      myServos[i].write(150);
    }
    for (int i = 1; i < JUMLAH_SERVO; i += 2) {
      myServos[i].write(30);
    }
    delay(400);
  }

  // Pola 3: Efek Mekar / Berkumpul (の中心 / Menuju ke tengah lalu menyebar)
  for (int pos = 40; pos <= 140; pos += 4) {
    for (int i = 0; i < JUMLAH_SERVO; i++) {
      // Servo ganjil dan genap bergerak berlawanan arah
      if (i % 2 == 0) {
        myServos[i].write(pos);
      } else {
        myServos[i].write(180 - pos);
      }
    }
    delay(20);
  }
}
