// RECEIVER
#include <SPI.h>
#include <LoRa.h>

// Definisi pin LoRa ke ESP32
#define ss 5
#define rst 14
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("ESP32 LoRa Receiver");

  // Konfigurasi pin LoRa
  LoRa.setPins(ss, rst, dio0);

  // Inisialisasi LoRa pada frekuensi 433 MHz
  if (!LoRa.begin(433E6)) {
    Serial.println("Gagal mendeteksi modul LoRa. Cek kabel!");
    while (1);
  }
  
  Serial.println("LoRa Siap Menerima Pesan...");
}

void loop() {
  // Mengecek apakah ada paket yang masuk
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // Paket diterima
    Serial.print("Paket diterima: '");

    // Membaca isi paket
    while (LoRa.available()) {
      String loRaData = LoRa.readString();
      Serial.print(loRaData); 
    }

    // Mencetak RSSI (Received Signal Strength Indicator)
    Serial.print("' | Kualitas Sinyal (RSSI): ");
    Serial.println(LoRa.packetRssi());
  }
}