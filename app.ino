#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <HTTPClient.h>
#include <IRremote.h>
#include <esp32-hal-ledc.h> 

const char* ssid = "";
const char* password = "";

int relay = ';

TaskHandle_t Task1;
TaskHandle_t Task2;


// Telegram Bot Configs:
#define BOTtoken ""
#define CHAT_ID ""

#define RECV_PIN ..

volatile byte doorStatus = HIGH; // HIGH - Dor is closed. //LOW - Dor is opened. 

// Set wifi const client.
WiFiClientSecure client;

// Set telegram const bot.
UniversalTelegramBot bot(BOTtoken, client);

// Start IRreciver
IRrecv irrecv(RECV_PIN);
decode_results results;


int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void IRreciverVerifier () {
  if (IrReceiver.decode()) {
    uint32_t d_command = IrReceiver.decodedIRData.command; // Get command pressed.

    if (d_command == 28) {
      handleDoor(false);
      Serial.println("Door opened!");
    }
    if (d_command == 24) {
      handleDoor(true);
      Serial.println("Closing door!");
    }

    Serial.println(d_command);
    IrReceiver.resume();
  }
  delay(100);
}

void handleDoor(bool state) {
  if (state) {
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
}

void Task1Code( void * parameter) {
  for(;;)
  {
    if (millis() > lastTimeBotRan + botRequestDelay) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

      while (numNewMessages) {
        Serial.println("got response");
        handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      }

      lastTimeBotRan = millis();
    }
    delay(50);
  }
}

void Task2Code( void * parameter) {
  for(;;)
  {
    IRreciverVerifier();
    delay(10);
  }
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unautohrized user.", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/close") {
      bot.sendMessage(chat_id, "Closing door...", "");
      handleDoor(true);

    }

    if (text == "/open") {
      bot.sendMessage(chat_id, "Opening door...", "");
      handleDoor(false);
    }

  }
}

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());

  irrecv.enableIRIn();

  xTaskCreatePinnedToCore(
    Task1Code,
    "Task 1 - Bot Telegram",
    10000,
    NULL,
    1,
    &Task1,
    0
  );

  xTaskCreatePinnedToCore(
    Task2Code,
    "Task 2 - IR Reciver",
    10000,
    NULL,
    1,
    &Task2,
    1
  );


}

void loop() {  
}
