# Experiência Interativa da Fórmula E no Roblox

## Integrantes
- **Nome:** Andrey | **RM:** 555339
- **Nome:** Henrique | **RM:** 554493
- **Nome:** Oliver | **RM:** 554954
- **Nome:** Pedro Gutierre | **RM:** 555445
- **Nome:** William | **RM:** 555132

## Visão Geral
Este projeto visa criar uma experiência interativa e imersiva para simulações de corridas da Fórmula E no ambiente virtual do Roblox. O uso de um ESP32, uma matriz de LED e um display LCD trazem uma camada de realismo, simulando a sequência de largada e a contagem de voltas. Além disso, há uma integração com MQTT e Wi-Fi para envio e recepção de mensagens, proporcionando uma experiência de corrida mais dinâmica.

## Componentes Utilizados
- **ESP32**
- **Matriz de LED (MAX7219)**
- **Display LCD (I2C)**
- **Conexão Wi-Fi e MQTT**

## Funcionalidades Principais
- **Simulação da sequência de largada:** Utilizando a matriz de LED, o sistema exibe um círculo em cada painel, simulando o início da corrida.
- **Contagem de voltas:** O display LCD exibe a volta atual e o número total de voltas.
- **Modo Safety Car:** O display LCD exibe uma mensagem sempre que o safety car é ativado, pausando a contagem de voltas.
- **Conexão MQTT:** O sistema recebe comandos como "largada" e "aumentar volta" via MQTT.

## Configuração do Ambiente

### Instalação de Bibliotecas
Certifique-se de que as seguintes bibliotecas estejam instaladas no seu Arduino IDE:
- **MATRIX7219:** Para controlar a matriz de LED.
- **LiquidCrystal_I2C:** Para controlar o display LCD via I2C.
- **PubSubClient:** Para gerenciar a conexão MQTT.
- **WiFi:** Para conectar o ESP32 à rede Wi-Fi.

### Montagem do Hardware

#### Conexões da Matriz de LED (MAX7219):
- **DIN:** Pino 5 do ESP32
- **CLK:** Pino 19 do ESP32
- **CS:** Pino 18 do ESP32
- **VCC e GND** conectados à alimentação apropriada do ESP32

#### Conexões do Display LCD (I2C):
- **SDA:** Pino 21 do ESP32
- **SCL:** Pino 22 do ESP32
- **VCC e GND** conectados à alimentação apropriada do ESP32

### Configuração do MQTT
- **Broker MQTT:** `mqtt-dashboard.com`
- **Tópicos MQTT:**
  - `/reblox/largada`
  - `/reblox/safety_car_on`
  - `/reblox/safety_car_off`
  - `/reblox/increase_lap`

## Execução

Para simular e testar o projeto, você pode utilizar o simulador online Wokwi. Acesse o projeto através do seguinte link:

[Simulador do Projeto no Wokwi](https://wokwi.com/projects/398724617714971649)
