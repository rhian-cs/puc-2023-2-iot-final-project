# IoT Frontend

## Installation

This app requires `node` and `npm` to be installed.

Install dependencies:

```console
npm install
```

Run the app in development mode:

```console
npm run dev
```

Build and run the app for production:

```console
npm run build
npm start
```

## Events

MQTT Topic: `com.stonkstoys.game.genius`

Events:

```mermaid
sequenceDiagram
Client->>ESP32: reset

ESP32->>Client: beeps: "1"
ESP32->>Client: your_turn

Client->>ESP32: input: "1"
ESP32->>Client: accept_input: "1"

ESP32->>Client: beeps: "1"
ESP32->>Client: beeps: "2"
ESP32->>Client: your_turn

Client->>ESP32: input: "1"
ESP32->>Client: accept_input
Client->>ESP32: input: "2"
ESP32->>Client: accept_input

ESP32->>Client: beeps: "1"
ESP32->>Client: beeps: "2"
ESP32->>Client: beeps: "3"
ESP32->>Client: your_turn

Client->>ESP32: input: "2"
ESP32->>Client: reject_input
```
