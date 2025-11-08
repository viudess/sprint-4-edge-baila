# ⚽💓 Baila — Medidor de Batimentos Cardíacos

Este projeto faz parte da iniciativa **Baila**, um aplicativo criado para **ajudar jovens jogadoras de futebol** a monitorar seu bem-estar físico e emocional.  
O sistema apresentado aqui consiste em um **medidor de batimentos cardíacos** conectado via **Wi-Fi e MQTT**, que envia os dados em tempo real para um **dashboard de acompanhamento**.

---

## 👥 Participantes do Grupo

- **Kazys Tatarunas** – RM: 564020  
- **Eduardo Viudes** – RM: 564075  
- **Frederico de Paula** – RM: 562109 
- **Victor Tadashi** – RM: 563582  

---

## 🧠 Contexto do Projeto

O **Baila** busca promover o **autoconhecimento corporal e a saúde emocional** das jogadoras, permitindo que elas e seus treinadores acompanhem parâmetros importantes como:
- Batimentos cardíacos
- Nível de esforço durante os treinos
- Condição física e variações de desempenho

Este módulo IoT faz parte dessa proposta, sendo responsável pela **coleta e envio dos dados vitais** para a nuvem.

---

## ⚙️ Tecnologias Utilizadas

- **ESP32** — Microcontrolador principal  
- **Sensor DHT22** — Coleta temperatura e umidade do ambiente  
- **Sensor de batimentos cardíacos (simulado)** — Pode ser substituído futuramente por um sensor real, como o **PulseSensor**  
- **LDR (Sensor de luminosidade)** — Mede a intensidade luminosa (usado como exemplo de sensor adicional)  
- **MQTT (Protocolo de comunicação)** — Envia os dados para o **broker** e o **dashboard**  
- **FIWARE / Orion Context Broker** — Responsável pela gestão dos dados IoT  
- **Dashboard (FIWARE ou Grafana)** — Visualiza em tempo real as informações coletadas  

---

## 🔌 Esquema de Conexões (Hardware)

O circuito é composto pelos seguintes componentes:

| Componente | Pino do ESP32 | Função |
|-------------|----------------|--------|
| DHT22 | 15 | Temperatura / Umidade |
| LDR | 34 | Nível de luminosidade |
| LED | 2 | Indicador de estado |
| Sensor de batimentos | (simulado) | Frequência cardíaca |

---

## 🖼️ Imagens do Projeto

### 🧩 Montagem no Arduino / ESP32

<img width="552" height="694" alt="image" src="https://github.com/user-attachments/assets/bcd5f4f2-87fd-47e7-8836-1c3947e73f47" />

### 📊 Dashboard de Monitoramento

<img width="1097" height="746" alt="image" src="https://github.com/user-attachments/assets/b734388c-ab9b-440b-b775-83343a4cfa89" />

---

## 🛰️ Comunicação MQTT

O dispositivo se conecta a um **broker MQTT** e publica/recebe mensagens conforme a estrutura abaixo:

| Tipo | Tópico | Exemplo de Mensagem |
|------|---------|---------------------|
| **Publicação** | `TEF/device014/attrs/b` | `75` *(nível de luz ou batimentos)* |
| **Subscrição** | `TEF/device014/cmd` | `ON` / `OFF` *(controle de LED)* |

> 🔐 Broker utilizado: `54.172.140.81`  
> Porta: `1883`

---

## 🧾 Estrutura do Código

O código principal realiza as seguintes funções:

1. Inicializa o Wi-Fi e o MQTT  
2. Lê os sensores (DHT22 e LDR)  
3. Publica os dados periodicamente (a cada 4 segundos)  
4. Recebe comandos MQTT (como ligar/desligar o LED)  
5. Garante reconexão automática caso perca o Wi-Fi ou o broker  

---

## 🚀 Como Executar

1. **Instale as bibliotecas necessárias** no Arduino IDE:  
   - WiFi.h  
   - PubSubClient.h  
   - DHT.h  

2. **Configure a rede Wi-Fi e o broker MQTT** nas variáveis:  
   const char* WIFI_SSID = "Wokwi-GUEST";  
   const char* WIFI_PASS = "";  
   const char* MQTT_BROKER = "54.172.140.81";  

3. **Carregue o código no ESP32**  
   Conecte via USB e selecione a placa **ESP32 Dev Module**.

4. **Monitore a saída serial (115200 baud)**  
   Você verá as mensagens de conexão e envio de dados:

   🔌 Inicializando sistema...  
   ✅ Conectado ao Wi-Fi!  
   ✅ Conectado ao broker!  
   📤 Enviando para MQTT: 75  

---

## 📡 Exemplo de Leitura e Publicação

📤 Enviando para MQTT: 82  
📤 Enviando para MQTT: 78  
📤 Enviando para MQTT: 75  

Esses valores representam a variação simulada dos **batimentos cardíacos**, que podem ser acompanhados em tempo real no **dashboard do projeto Baila**.

---

## 💡 Melhorias Futuras

- Integração com **sensor de batimentos real (PulseSensor ou MAX30102)**  
- Envio de dados para a **nuvem FIWARE completa**  
- Interface mobile no app **Baila**  
- Alertas automáticos de **fadiga ou anomalias cardíacas**

---

## 👩‍💻 Equipe e Créditos

**Projeto:** Baila — Apoio às jovens jogadoras de futebol  
**Desenvolvido por:** Viudes e equipe FIAP  
**Orientação:** Professores do curso de Engenharia de Software — FIAP  
**Ano:** 2025

---

📍 *"Cuidar do corpo é jogar com o coração."* 💙⚽
