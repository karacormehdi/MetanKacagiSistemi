#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

// --- WIFI AND MAIL SETTINGS (REFILL OUT) ---
#define WIFI_SSID "Wifi Name"        
#define WIFI_PASSWORD "Wifi Password"  

#define GONDEREN_EMAIL "Your Mail"
#define GONDEREN_SIFRE "16 characters" 

#define ALICI_EMAIL "Recevier Mail" 

// --- HARDWARE PINS ---
#define SENSOR_PIN A0   
#define FAN_PIN    5    // D1
#define BUZZER_PIN D2   // D2

#define ROLE_ACIK   LOW   
#define ROLE_KAPALI HIGH  

// --- FIXED THRESHOLD VALUE SETTING ---
// We fixed it here because you asked for it.
// Sensor 890 does not trigger a dispersion alarm.
int esikDeger = 890;      

bool mailGonderildi = false; 

SMTPSession smtp;

// --- EMAIL SENDING FUNCTION ---
void mailAt() {
  ESP_Mail_Session session;
  session.server.host_name = "smtp.gmail.com";
  session.server.port = 465;
  session.login.email = GONDEREN_EMAIL;
  session.login.password = GONDEREN_SIFRE;
  session.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "GAZ ALARM SISTEMI-GAS ALARM SYSTEM";
  message.sender.email = GONDEREN_EMAIL;
  message.subject = "ACIL DURUM: GAZ KACAGI TESPIT EDILDI!-EMERGENCY: GAS LEAK DETECTED!  >>MEHDI KARAÇOR GAZ KAÇAĞI UYGULAMASI<<";
  message.addRecipient("Kullanici", ALICI_EMAIL);
  
  String htmlMsg = "<div style=\"color:red;\"><h1>TEHLIKE! GAZ SEVIYESI YUKSEK!,DANGER! HIGH GAS LEVELS!</h1><p>Sistem fani acti. Lutfen kontrol edin.-The system fan is active. Please check it.</p></div>";
  message.html.content = htmlMsg.c_str();

  Serial.println(">> Mail sunucusuna baglaniliyor...-Connecting to the email sender...");
  if (!smtp.connect(&session)) return;
  if (!MailClient.sendMail(&smtp, &message)) Serial.println("Mail Hatasi:-Mail Error:" + smtp.errorReason());
  else Serial.println(">> MAIL BASARIYLA GONDERILDI!-EMAIL SENT SUCCESSFULLY!");
}

void setup() {
  Serial.begin(9600);
  
  pinMode(SENSOR_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(FAN_PIN, ROLE_KAPALI); 
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("\n--------------------------------");
  Serial.print("Wi-Fi Baglaniliyor:-Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi BAGLANDI!-Wi-Fi CONNECTED!");

  // --- CALIBRATION (We are waiting for the sensor to warm up) ---
  Serial.println("Sensor isiniyor... (10 sn)-The sensor is getting warm... (10 sec)");
  delay(10000); 

  // We'll stop the automatic calculation; we'll use the 890 you provided.
  Serial.print("Ayarlanan Sabit Esik Degeri:-Set Fixed Threshold Value: "); 
  Serial.println(esikDeger);
  
  Serial.println("SISTEM HAZIR! Gaz bekleniyor...-SYSTEM READY! Waiting for gas...");
  Serial.println("--------------------------------");
}

void loop() {
  int anlikDeger = analogRead(SENSOR_PIN);
  
  // --- PRINTING TO THE SCREEN ---
  Serial.print("Anlik:Momentary: ");
  Serial.print(anlikDeger);
  Serial.print("  |  Hedef Esik:-Target Threshold: ");
  Serial.println(esikDeger);

  // --- IF GAS IS AVAILABLE (890 and above) ---
  if (anlikDeger >= esikDeger) {
    Serial.println("!!! GAZ ALGILANDI !!!-!!! GAS DETECTED !!!");
    
    digitalWrite(FAN_PIN, ROLE_ACIK);   
    digitalWrite(BUZZER_PIN, HIGH);     
    
    if (mailGonderildi == false) {
      mailAt();
      mailGonderildi = true; 
    }

    delay(100); digitalWrite(BUZZER_PIN, LOW);
    delay(100); digitalWrite(BUZZER_PIN, HIGH);
    delay(500); 
  } 
  
  // --- NO GAS (Return to Normal) ---
  else {
    digitalWrite(FAN_PIN, ROLE_KAPALI); 
    digitalWrite(BUZZER_PIN, LOW);      
    
    // Reset the system when the gas level drops below 850.
    // (Let the area between 890 and 850 be a safe zone so that it doesn't keep opening and closing frequently.)
    if (mailGonderildi == true && anlikDeger < 850) {
       mailGonderildi = false; 
       Serial.println("--- ORTAM NORMALE DONDU ---/--- THE SITUATION HAS RETURNED TO NORMAL ---");
    }
  }
  
  delay(500); 
}