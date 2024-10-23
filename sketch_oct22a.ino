#define BLYNK_TEMPLATE_ID "TMPL33gIt6gPI"
#define BLYNK_TEMPLATE_NAME "Inhalation Toxins"
#define BLYNK_AUTH_TOKEN "TTp4zcvaY3UaPeh9RdS8gBDNRmROfFt8"
#define gas 34

#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi credentials
const char* ssid = "SEMINAR HALL";
const char* password = "SEMI@2023M";
char auth[] = BLYNK_AUTH_TOKEN;

#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0; 

// Custom values for heart rate and SpO2
int32_t customHeartRate = 75; // Default value
int32_t customSpO2 = 95; // Default value

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  pinMode(gas,INPUT);

  // Set up WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");

  // Set up Blynk
  Blynk.begin(auth, ssid, password);
}

void loop() {
  int g= analogRead(gas);
  // Generate random values for heart rate and SpO2
  customHeartRate = random(65, 86); // Heart rate between 65 and 85
  customSpO2 = random(90, 103); // SpO2 between 90 and 102

  // Display generated results in Serial Monitor
  Serial.print("Heart Rate: ");
  Serial.print(customHeartRate);
  
  Serial.print(" bpm, SpO2: ");
  Serial.print(customSpO2);
  Serial.println();

  Serial.print(" Gas ");
  Serial.print(g);
  Serial.println();

  // Report to Blynk periodically
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    // Send custom Heart Rate and SpO2 to Blynk
    Blynk.virtualWrite(V0, customHeartRate);   // Send custom Heart Rate to Virtual Pin 0
    Blynk.virtualWrite(V1, customSpO2);         // Send custom SpO2 to Virtual Pin 1
    Blynk.virtualWrite(V2, gas);

    // Log event for low heart rate
    if (customHeartRate < 80) {
//      Blynk.logEvent("low_heart_rate", "Warning: Low heart rate detected. Consult a doctor if necessary.");
    }

    tsLastReport = millis();
  }

  Blynk.run();
  delay(5000); // Delay for next measurement
}
