#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// Inisialisasi LCD dan RTC
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  // Inisialisasi I2C
  Wire.begin(21, 22);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Inisialisasi RTC
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC Tidak Ada!");
    while (1);
  }

  // Mengatur waktu awal RTC
  // Aktifkan satu kali untuk mengatur waktu.
  // Setelah itu, beri komentar kembali.
  // rtc.adjust(DateTime(2026, 11, 3, 14, 30, 0));

  lcd.setCursor(2, 0);
  lcd.print("JAM DIGITAL");

  lcd.setCursor(3, 1);
  lcd.print("ESP32 + RTC");

  delay(2000);
  lcd.clear();
}

void loop() {

  // Membaca waktu dari RTC
  DateTime skrg = rtc.now();

  // Format jam
  char waktu[9];

  sprintf(waktu, "%02d:%02d:%02d",
          skrg.hour(),
          skrg.minute(),
          skrg.second());

  // Format tanggal
  char tanggal[11];

  sprintf(tanggal, "%02d-%02d-%04d",
          skrg.day(),
          skrg.month(),
          skrg.year());

  // Menampilkan jam
  lcd.setCursor(4, 0);
  lcd.print(waktu);

  // Menampilkan tanggal
  lcd.setCursor(3, 1);
  lcd.print(tanggal);

  // Menampilkan pada Serial Monitor
  Serial.print("Jam: ");
  Serial.print(waktu);

  Serial.print(" | Tanggal: ");
  Serial.println(tanggal);

  delay(1000);
}
