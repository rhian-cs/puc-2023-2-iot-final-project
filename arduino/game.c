#include "WiFi.h"
#include <PubSubClient.h>
#define GAMESIZE 10
#define NUMBER_OF_COLORS 4
#define PIN_LED_YELLOW 1
#define PIN_LED_RED 2
#define PIN_LED_BLUE 3
#define PIN_LED_GREEN 4
#define PIN_BUZZER 5
#define PIN_DISPLAY 6
#define BIP_BIP_SPEED 500

int *colorsSequence;
int *inputSequence;
const char* ssid = "PUCPCALDAS";
const char* mqttServer = "com.stonkstoys.game.genius";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA); 
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao Wifi");
  }

  Serial.println("Conectado ao Wifi");
  Serial.println("Configurando MQTT Broker..."); 
  client.setServer(mqttServer,1883);
  Serial.println("MQTT Broker configurado...");

  colorsSequence = (int *)malloc(GAMESIZE * sizeof(int));
  inputSequence = (int *)malloc(GAMESIZE * sizeof(int));

  srand(time(NULL));
  for (int i = 0; i < GAMESIZE; i++){
    int random = rand() % NUMBER_OF_COLORS + 1;
    colorsSequence[i] = random;
  }
  client.subscribe(mqttServer);

  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_DISPLAY, OUTPUT);
}

void loop() 
{  
  if(!client.connected()){
    reconnect();
  }
  playGame();
}

void playGame(){
  int inputColorCode;
  int gameCurrentLenght = 0;
  int turns = 0;
  int score = 0;
  int step = 0;
  int gameOver = 0;

  while (turns < GAMESIZE && !gameOver){
    for (int i = 0; i <= turns; i++){
      switch(colorsSequence[i]){
        case 0:
          digitalWrite(PIN_LED_YELLOW, HIGH);
          // add buzzer / calculate frequency based on i value
          break;
        case 1:
          digitalWrite(PIN_LED_RED, HIGH);
          // add buzzer / calculate frequency based on i value
          break;
        case 2:
          digitalWrite(PIN_LED_BLUE, HIGH);
          // add buzzer / calculate frequency based on i value
          break;
        case 3:
          digitalWrite(PIN_LED_GREEN, HIGH);
          // add buzzer / calculate frequency based on i value
          break;
      }

      delay(BIP_BIP_SPEED);

      switch(colorsSequence[i]){
        case 0:
          digitalWrite(PIN_LED_YELLOW, LOW);
          // desligate buzzer
          break;
        case 1:
          digitalWrite(PIN_LED_RED, LOW);
          // desligate buzzer
          break;
        case 2:
          digitalWrite(PIN_LED_BLUE, LOW);
          // desligate buzzer
          break;
        case 3:
          digitalWrite(PIN_LED_GREEN, LOW);
          // desligate buzzer
          break;
      }
    }

    for (int i = 0; i <= turns; i++){
      // maybe this value can come as char
      inputSequence[i] = 
      //sprintf(inputSequence[i]);

      if(inputSequence != -1){
        step++;
        for(int j = 0; j < step; j++){
          if(inputSequence[j] != colorsSequence[j]){
            gameOver = 1;
          }
          else{
            score++;
          }
        }
      }
      else i--;
    }
    step=0;
    turns++;
    delay(2000);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect(mqttServer)) {
      Serial.println("Connecting MQTT server...");
    } else {
      Serial.print("Failed: ");
      Serial.print(client.state());
      delay(3000);
    }
  }
}
