#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// === CONFIGURAÇÕES DO SENSOR DHT22 ===
#define DHT_PIN 15
#define DHT_TYPE DHT22
DHT dhtSensor(DHT_PIN, DHT_TYPE);

// === CONFIGURAÇÕES DE REDE E MQTT ===
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";
const char* MQTT_BROKER = "54.172.140.81";
const int MQTT_PORT = 1883;

const char* TOPIC_SUB = "TEF/device014/cmd";
const char* TOPIC_PUB = "TEF/device014/attrs/b";
const char* CLIENT_ID = "fiware_014";

// === DEFINIÇÃO DE PINOS ===
const int PIN_LED = 2;
const int PIN_LDR = 34;

// === OBJETOS GLOBAIS ===
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// === VARIÁVEIS ===
bool ledState = false;

// === FUNÇÕES AUXILIARES ===
void iniciarSerial() {
  Serial.begin(115200);
  Serial.println("🔌 Inicializando sistema...");
}

void conectarWiFi() {
  Serial.print("🔗 Conectando ao Wi-Fi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\n✅ Conectado ao Wi-Fi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("🔄 Tentando conexão com o broker MQTT... ");
    if (mqttClient.connect(CLIENT_ID)) {
      Serial.println("✅ Conectado ao broker!");
      mqttClient.subscribe(TOPIC_SUB);
    } else {
      Serial.print("❌ Falha, código: ");
      Serial.println(mqttClient.state());
      delay(2500);
    }
  }
}

// === CALLBACK MQTT ===
void mqttMensagemRecebida(char* topic, byte* message, unsigned int length) {
  String comando;
  for (unsigned int i = 0; i < length; i++) {
    comando += (char)message[i];
  }
  comando.trim();

  Serial.print("📨 Comando recebido [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(comando);

  if (comando.equalsIgnoreCase("ON")) {
    digitalWrite(PIN_LED, HIGH);
    ledState = true;
  } else if (comando.equalsIgnoreCase("OFF")) {
    digitalWrite(PIN_LED, LOW);
    ledState = false;
  }
}

// === ENVIO DOS DADOS ===
void publicarDados() {
  float temperatura = dhtSensor.readTemperature();
  float umidade = dhtSensor.readHumidity();
  int leituraLdr = analogRead(PIN_LDR);
  int nivelLuz = map(leituraLdr, 0, 4095, 0, 100);

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("⚠️ Erro ao ler o DHT22!");
    return;
  }
/*
  String dados = "{\"temp\":" + String(temperatura, 1) +
                 ",\"umid\":" + String(umidade, 1) +
                 ",\"lum\":" + String(nivelLuz) + "}";

  Serial.print("📤 Enviando para MQTT: ");
  Serial.println(dados);
  */
  String dados = String(nivelLuz) ;

  Serial.print("📤 Enviando para MQTT: ");
  Serial.println(dados);
  mqttClient.publish(TOPIC_PUB, dados.c_str());
}

// === SETUP ===
void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  iniciarSerial();
  conectarWiFi();

  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqttMensagemRecebida);

  dhtSensor.begin();
  Serial.println("🚀 Sistema inicializado com sucesso!");
}

// === LOOP PRINCIPAL ===
void loop() {
  if (!mqttClient.connected()) {
    conectarMQTT();
  }

  mqttClient.loop();
  publicarDados();
  delay(4000);
}
