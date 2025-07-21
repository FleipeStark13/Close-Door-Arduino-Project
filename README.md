<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/5af5ff92-812a-4623-9bbb-3e62b283fc10" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/826c1a09-ef1b-4437-bee7-c907ae35c22b" />
<img width="1200" height="1600" alt="image" src="https://github.com/user-attachments/assets/f4cc0113-b6a0-4137-a24d-42f6e7f9c5cc" />

# 🔐 Projeto: Fechadura Eletrônica Inteligente com ESP32 + Controle por Telegram e Infravermelho

Este projeto tem como objetivo criar uma **tranca elétrica digital inteligente**, controlada tanto por um **bot do Telegram** quanto por um **controle remoto infravermelho**, utilizando um **ESP32** como microcontrolador principal.

## 🎯 Objetivo
Desenvolver um sistema seguro e acessível para **abrir e fechar portas remotamente**, com indicações visuais de status e fácil integração com tecnologias do dia a dia. O projeto é ideal para uso residencial, comercial ou para aprendizado em IoT.

## 🔧 Componentes Utilizados

- 1x ESP32 DevKit
- 1x Tranca elétrica 12V
- 1x Módulo relé 5V
- 1x Transistor C945
- 2x LEDs (vermelho e verde) para sinalização de status da porta
- 1x Receptor infravermelho (IR)
- Fonte 12V para a tranca e 5V USB para o ESP32

## 💡 Funcionalidades

- **Abrir/Fechar porta via Telegram**: comandos como `/open` e `/close` são interpretados por um bot Telegram autenticado.
- **Controle remoto IR**: botões específicos disparam a abertura ou fechamento da tranca.
- **Indicação por LEDs**: LED vermelho indica porta aberta; verde, porta fechada.
- **Execução paralela**: duas tarefas distintas usando os dois núcleos do ESP32 (IR + Telegram).
- **Segurança**: somente um chat ID autorizado pode enviar comandos.

## 📡 Tecnologias & Bibliotecas

- [ESP32](https://www.espressif.com/en/products/socs/esp32)
- `WiFi.h`, `WiFiClientSecure.h`
- [UniversalTelegramBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- `IRremote.h`
- `ArduinoJson.h`
- FreeRTOS (via `xTaskCreatePinnedToCore`)

## 🧠 Próximos Passos

- Integração com **reconhecimento de voz**
- Inclusão de **display LCD** para feedback visual
- Logs em nuvem (ex: Firebase, Thingspeak)

## 🖼️ Esquemático do Projeto

<img width="600" height="800" alt="image" src="https://github.com/user-attachments/assets/de2a5ca8-a6bf-4c33-b9fd-5914dd74d79d" />


## 🔐 Segurança

O projeto usa verificação de `chat_id` no bot Telegram para evitar comandos não autorizados.

---

## 📂 Código-fonte

Todo o código-fonte do projeto está disponível aqui:  
👉 [GitHub Repo](https://github.com/FleipeStark13/Close-Door-Arduino-Project)

---

Se tiver dúvidas, sugestões ou quiser colaborar, fique à vontade para abrir uma issue ou me chamar no LinkedIn! 😄

[![Instagram](https://img.shields.io/badge/Instagram-%23E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/fleipekkj.md/)
[![Website](https://img.shields.io/badge/Website-000000?style=for-the-badge&logo=About.me&logoColor=white)](https://felipeliandro.com.br)
[![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow?style=for-the-badge)](#)


