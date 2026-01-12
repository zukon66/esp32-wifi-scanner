#include <WiFi.h>

// Sifreleme tipini okunabilir bir metne cevirir.
String encryptionTypeToString(wifi_auth_mode_t type) {
  switch (type) {
    case WIFI_AUTH_OPEN:
      return "Open";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2-Enterprise";
#if defined(WIFI_AUTH_WPA3_PSK)
    case WIFI_AUTH_WPA3_PSK:
      return "WPA3";
#endif
#if defined(WIFI_AUTH_WPA2_WPA3_PSK)
    case WIFI_AUTH_WPA2_WPA3_PSK:
      return "WPA2/WPA3";
#endif
#if defined(WIFI_AUTH_WAPI_PSK)
    case WIFI_AUTH_WAPI_PSK:
      return "WAPI";
#endif
    default:
      return "Unknown";
  }
}

void setup() {
  Serial.begin(115200);

  // Istasyon moduna al ve onceki baglantilari temizle.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  delay(100);

  Serial.println("Wi-Fi tarama basladi...");
}

void loop() {
  // Synchronous tarama yapiliyor (bloklayici).
  int networkCount = WiFi.scanNetworks();

  if (networkCount <= 0) {
    Serial.println("Ag bulunamadi.");
  } else {
    Serial.printf("Toplam ag sayisi: %d\n", networkCount);

    for (int i = 0; i < networkCount; i++) {
      String ssid = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);
      wifi_auth_mode_t auth = WiFi.encryptionType(i);

      Serial.printf("%d) SSID: %s | RSSI: %d dBm | Sifreleme: %s\n",
                    i + 1,
                    ssid.c_str(),
                    rssi,
                    encryptionTypeToString(auth).c_str());
    }
  }

  // Bir sonraki tarama icin 5 saniye bekle.
  delay(5000);
}