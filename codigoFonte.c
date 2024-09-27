#include <MATRIX7219.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "mqtt-dashboard.com";

int buzzer = 23;

const char* topic_largada = "/reblox/largada";
const char* topic_safety_car_on = "/reblox/safety_car_on";
const char* topic_safety_car_off = "/reblox/safety_car_off";
const char* topic_increase_lap = "/reblox/increase_lap";

WiFiClient espClient;
PubSubClient client(espClient);

int voltaAtual = 0;
int voltasTotais = 10;

MATRIX7219 panel1(5, 18, 19, 4);
MATRIX7219 panel2(4, 16, 17, 4);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

unsigned long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.println((char)payload[i]);
  }



  // Verifica se o tópico é o de largada e, se for, chama a função largada
  if (String(topic) == topic_largada) {
    largada();
  }
  if (String(topic) == topic_increase_lap) {
    aumentarVolta();
  }
  if (String(topic) == topic_safety_car_on) {
    safetyCar(true);
  }
  if (String(topic) == topic_safety_car_off) {
    safetyCar(false);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.subscribe(topic_largada);
      client.subscribe(topic_safety_car_on);
      client.subscribe(topic_safety_car_off);
      client.subscribe(topic_increase_lap);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  panel1.begin();
  panel2.begin();
  lcd.init();
  lcd.backlight();

  // Inicializa o Wi-Fi e MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  lcd.setCursor(5, 0);
  lcd.print("e Prix");
  lcd.setCursor(4, 1);
  lcd.print("Sao Paulo");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Aqui pode ser adicionado o código para publicar mensagens MQTT, se necessário
  unsigned long now = millis();
  if (now - lastMsg > 2000) { // Publica uma mensagem a cada 2 segundos
    lastMsg = now;
    String msg = "Volta Atual: " + String(voltaAtual);
    client.publish("/reblox/status", msg.c_str());
  }

  delay(500);
}

void aumentarVolta() {
  if (voltaAtual >= voltasTotais) {
    lcd.print("Fim de Corrida");
  }else{
    voltaAtual += 1;
    exibirVolta();
  }
}

void exibirVolta() {
  lcd.clear();
  lcd.print("Volta: ");
  lcd.print(voltaAtual);
  lcd.print("/");
  lcd.print(voltasTotais);
}

void safetyCar(bool on) {
  if (on) {
    lcd.clear();
    lcd.print("Safety Car ativo");
  } else {
    exibirVolta();
  }

}

void largada() {
  for (int i = 1; i < 5; i++) {
    circulo(panel2, i);
    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    delay(500);
    delay(1000);
  }
  tone(buzzer, 1000);
  for (int i = 1; i < 5; i++) {
    circulo(panel1, i);
    delay(100);
  }


  delay(500);

  exibirVolta();

  delay(2000);
  panel1.clear();
  panel2.clear();
  noTone(buzzer);



}

void circulo(MATRIX7219& panel, int panelIndex) {
  uint8_t pattern[] = {
    0b00111100,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100
  };

  for (int row = 0; row < 8; row++) {
    panel.setRow(row + 1, pattern[row], panelIndex);
  }
}
