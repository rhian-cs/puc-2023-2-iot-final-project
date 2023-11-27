#include "WiFi.h"
#include <PubSubClient.h>
#include <TaskScheduler.h>
#define GAMESIZE 10
#define NUMBER_OF_COLORS 4
#define PIN_LED_YELLOW 18
#define PIN_LED_RED 2
#define PIN_LED_BLUE 4
#define PIN_LED_GREEN 17
#define PIN_BUZZER 19
// #define PIN_DISPLAY 6

const char *ssid = "ssid";
const char *password = "password";
const char *mqttServer = "server";
const int mqttPort = 1883;
const char *mqttTopic = "com.stonkstoys.game.genius";
int *colorsSequence;
int *inputSequence;

WiFiClient espClient;
PubSubClient client(espClient);
Scheduler scheduler;

int isReceiving = 0;
int commandBuffer = -1;
int gameStarted = 0;

void playGame();
Task playGameTask(1000, TASK_FOREVER, &playGame);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to Wifi...");
  }
  Serial.println("Wifi connected");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  colorsSequence = (int *)malloc(GAMESIZE * sizeof(int));
  inputSequence = (int *)malloc(GAMESIZE * sizeof(int));

  srand(time(NULL));
  for (int i = 0; i < GAMESIZE; i++)
  {
    int random = rand() % NUMBER_OF_COLORS + 1;
    colorsSequence[i] = random;
  }
  client.subscribe(mqttTopic);

  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  //  pinMode(PIN_DISPLAY, OUTPUT);

  reconnect();
  testLeds();
  scheduler.addTask(playGameTask);
  playGameTask.enableDelayed(500);
  blinkToCallUser();
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  scheduler.execute();

  client.loop();
}

void playGame()
{

  int inputColorCode;
  int gameCurrentLenght = 0;
  int turns = 0;
  int score = 0;
  int step = 0;
  int gameOver = 0;

  while (turns < GAMESIZE && !gameOver)
  {
    for (int i = 0; i <= turns; i++)
    {
      sing(colorsSequence[i]);
    }
    delay(500);
    blinkToCallUser();

    for (int i = 0; i <= turns; i++)
    {
      client.loop();
      Serial.println("Awaiting User's command");
      while (!isReceiving)
      {
        delay(100);
        client.loop();
      }
      inputSequence[i] = commandBuffer;
      isReceiving = 0;
      sing(inputSequence[i]);

      if (inputSequence[i] != -1)
      {
        step++;
        for (int j = 0; j < step; j++)
        {
          if (inputSequence[j] != colorsSequence[j])
          {
            gameOver = 1;
          }
          else
          {
            score++;
          }
        }
      }
      else
        i--;
    }
    step = 0;
    turns++;
    delay(2000);
    Serial.print("score");
    Serial.print(score);
    Serial.println();
  }

  for (int i = 0; i < 10; i++)
    blinkToCallUser();

  Serial.println("Restarting ESP32...");
  ESP.restart();
  playGameTask.disable();
  playGameTask.forceNextIteration();
}

void sing(int color)
{
  switch (color)
  {
  case 1:
    digitalWrite(PIN_LED_YELLOW, HIGH);
    tone(PIN_BUZZER, 261);
    delay(700);
    digitalWrite(PIN_LED_YELLOW, LOW);
    noTone(PIN_BUZZER);
    delay(700);
    break;
  case 2:
    digitalWrite(PIN_LED_RED, HIGH);
    tone(PIN_BUZZER, 293);
    delay(700);
    digitalWrite(PIN_LED_RED, LOW);
    noTone(PIN_BUZZER);
    delay(700);
    break;
  case 3:
    digitalWrite(PIN_LED_BLUE, HIGH);
    tone(PIN_BUZZER, 329);
    delay(700);
    digitalWrite(PIN_LED_BLUE, LOW);
    noTone(PIN_BUZZER);
    delay(700);
    break;
  case 4:
    digitalWrite(PIN_LED_GREEN, HIGH);
    tone(PIN_BUZZER, 349);
    delay(700);
    digitalWrite(PIN_LED_GREEN, LOW);
    noTone(PIN_BUZZER);
    delay(700);
    break;
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, mqttTopic) == 0)
  {
    if (payload[0] == 48) // input 0
    {
      Serial.println("RED pressed");
      commandBuffer = 2;
      isReceiving = 1;
    }
    else if (payload[0] == 49) // input 1
    {
      Serial.println("GREEN pressed");
      commandBuffer = 4;
      isReceiving = 1;
    }
    else if (payload[0] == 50) // input 2
    {
      Serial.println("BLUE pressed");
      commandBuffer = 3;
      isReceiving = 1;
    }
    else if (payload[0] == 51) // input 3
    {
      Serial.println("YELLOW pressed");
      commandBuffer = 1;
      isReceiving = 1;
    }
    else if (payload[0] == 52) // input 4
    {
      Serial.println("Reset Game");
      Serial.println("Restarting ESP32...");
      ESP.restart();
    }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Conectando ao servidor MQTT...");
    if (client.connect("ESP32Client"))
    {
      Serial.println("Conectado ao servidor MQTT");
      client.subscribe(mqttTopic);
    }
    else
    {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando reconectar em 5 segundos...");
      delay(5000);
    }
  }
}

void blinkToCallUser()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(PIN_LED_YELLOW, HIGH);
    digitalWrite(PIN_LED_RED, HIGH);
    digitalWrite(PIN_LED_BLUE, HIGH);
    digitalWrite(PIN_LED_GREEN, HIGH);
    delay(50);
    digitalWrite(PIN_LED_YELLOW, LOW);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);
    digitalWrite(PIN_LED_GREEN, LOW);
    delay(50);
  }
}

void testLeds()
{
  Serial.println("Testing LEDs");
  digitalWrite(PIN_LED_YELLOW, HIGH);
  Serial.println("- YELLOW");
  delay(500);
  digitalWrite(PIN_LED_YELLOW, LOW);
  delay(500);
  digitalWrite(PIN_LED_RED, HIGH);
  Serial.println("- RED");
  delay(500);
  digitalWrite(PIN_LED_RED, LOW);
  delay(500);
  digitalWrite(PIN_LED_BLUE, HIGH);
  Serial.println("- BLUE");
  delay(500);
  digitalWrite(PIN_LED_BLUE, LOW);
  delay(500);
  digitalWrite(PIN_LED_GREEN, HIGH);
  Serial.println("- GREEN");
  delay(500);
  digitalWrite(PIN_LED_GREEN, LOW);
  delay(500);

  digitalWrite(PIN_LED_YELLOW, HIGH);
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  delay(500);

  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
  delay(500);
}