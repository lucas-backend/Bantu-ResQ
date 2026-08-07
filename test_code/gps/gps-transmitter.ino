// GPS Transmitter
#include <SPI.h>
#include <LoRa.h>
#include <TinyGPSPlus.h>

// Definisi Pin LoRa
#define ss 5
#define rst 14
#define dio0 2

// Definisi Pin GPS (Menggunakan Hardware Serial 2)
#define RXPin 16
#define TXPin 17
#define GPSBaud 9600 // Baudrate standar modul NEO-M8N

// Membuat objek GPS dan Serial
TinyGPSPlus gps;
HardwareSerial gpsSerial(2); 

unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Memulai komunikasi dengan GPS
  gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  Serial.println("Memulai ESP32 LoRa + GPS Transmitter");

  // Inisialisasi LoRa
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) { // Sesuaikan frekuensi jika perlu
    Serial.println("Gagal mendeteksi modul LoRa. Cek kabel!");
    while (1);
  }
  Serial.println("LoRa Berhasil Diinisialisasi!");
}

void loop() {
  // 1. Selalu baca data dari GPS setiap ada data masuk
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // 2. Kirim data via LoRa setiap 5 detik
  if (millis() - lastSendTime > 5000) {
    
    // Cek apakah GPS sudah mendapat sinyal (fix)
    if (gps.location.isValid()) {
      // Format data: Lat, Lng
      String payload = "Lat: " + String(gps.location.lat(), 6) + 
                       " | Lng: " + String(gps.location.lng(), 6);
      
      Serial.print("Mengirim: ");
      Serial.println(payload);

      // Kirim paket LoRa
      LoRa.beginPacket();
      LoRa.print(payload);
      LoRa.endPacket();
      
    } else {
      Serial.println("Mencari sinyal satelit GPS... (Pastikan di luar ruangan)");
      
      // Opsional: Tetap kirim status pencarian ke receiver
      LoRa.beginPacket();
      LoRa.print("Menunggu Fix GPS...");
      LoRa.endPacket();
    }
    
    lastSendTime = millis();
  }
}