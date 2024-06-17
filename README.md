# Experiência Interativa da Fórmula E no Roblox com Arduino

## Integrantes

- **Nome**: Andrey
- **RM**: 555339
- **Nome**: Henrique
- **RM**: 554493
- **Nome**: Oliver
- **RM**: 554954
- **Nome**: Pedro Gutierre
- **RM**: 555445
- **Nome**: William
- **RM**: 555132


## Visão Geral

Este projeto tem como objetivo criar uma experiência interativa e imersiva para simulações de corridas da Fórmula E no ambiente virtual do Roblox. Utilizamos o Arduino para adicionar uma camada de realismo, simulando a sequência de largada e a contagem de voltas, proporcionando aos usuários uma compreensão mais profunda e envolvente do esporte.

## Componentes Utilizados

- **Arduino Uno R3**
- **LED Matrix Display (MAX7219)**
- **LCD Display (I2C)**
- **Buzzer**

## Configuração do Ambiente

### Instalação de Bibliotecas

Certifique-se de que você tem as seguintes bibliotecas instaladas no seu Arduino IDE:

- **LedControl**: Para controlar o display de LED.
- **LiquidCrystal_I2C**: Para controlar o display LCD via I2C.

Para instalar essas bibliotecas, vá para **Sketch > Include Library > Manage Libraries...** e procure pelos nomes das bibliotecas. Clique em **Install** para adicioná-las ao seu ambiente.

### Montagem do Hardware

1. **Conexões do Display de LED (MAX7219)**:
   - DIN: Pin 11
   - CLK: Pin 13
   - CS: Pin 10
   - Conecte a alimentação (VCC e GND) aos pinos apropriados no Arduino.

2. **Conexões do Display LCD (I2C)**:
   - SDA: Pin A4
   - SCL: Pin A5
   - Conecte a alimentação (VCC e GND) aos pinos apropriados no Arduino.

3. **Buzzer**:
   - Conecte o pino positivo do buzzer ao Pin 9 do Arduino.
   - Conecte o pino negativo do buzzer ao GND do Arduino.

## Execução

Para simular e testar o projeto, você pode utilizar o simulador online Wokwi. Acesse o projeto através do seguinte link:

[Simulador do Projeto no Wokwi](https://wokwi.com/projects/398724617714971649)

## Contribuição

Contribuições são bem-vindas! Se você tiver sugestões ou encontrar bugs, por favor, abra uma issue ou faça um fork deste repositório e envie um pull request.

