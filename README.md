# 🔥 IoT Tabanlı Akıllı Gaz Kaçağı ve Müdahale Sistemi

Bu proje, biyogaz üretim tesisleri ve kazan daireleri için geliştirilmiş; gaz kaçağı anında sesli uyarı veren, **otomatik fanı devreye sokan** ve yetkiliye **E-Posta ile bildirim gönderen** akıllı bir iş güvenliği sistemidir.

## 🚀 Özellikler
- **Anlık Gaz Takibi:** MQ serisi sensörler ile ortamdaki gaz seviyesini ölçer.
- **Otonom Müdahale:** Eşik değer aşıldığında röle tetiklenir ve tahliye fanı çalışır.
- **Uzaktan Bildirim:** Wi-Fi (NodeMCU) üzerinden sistem yetkilisine "Acil Durum" maili atar.
- **Sesli Alarm:** Buzzer ile ortamdaki kişileri uyarır.

## 🛠️ Kullanılan Malzemeler
| Malzeme | Model / Açıklama |
|---|---|
| Mikrodenetleyici | NodeMCU ESP8266 (Wi-Fi) |
| Gaz Sensörü | MQ-4 (Metan) veya MQ-135 |
| Röle | 5V Tek Kanal Röle Modülü |
| Fan | 12V DC Tahliye Fanı |
| Güç Kaynağı | 5V Adaptör (NodeMCU) + 12V Adaptör (Fan) |

## 💻 Kurulum ve Kullanım
1. `src` klasöründeki `.ino` dosyasını Arduino IDE ile açın.
2. Kodun içindeki `WIFI_SSID`, `WIFI_PASS` ve `EMAIL` bilgilerini güncelleyin.
3. Kütüphanelerden `ESP Mail Client` kütüphanesini kurun.
4. NodeMCU'ya yükleyin.

## 📂 Proje Raporu
Projenin detaylı TÜBİTAK 2209-A raporuna [buradan](docs/2209-a_sonuc_raporu_Mehdi-KARAÇOR.pdf) ulaşabilirsiniz.

## 🎥 Çalışma Videosu
[buradan](media/prototip_videosu.MP4)

---
**Geliştirici:** Mehdi KARAÇOR
**Lisans:** MIT License
