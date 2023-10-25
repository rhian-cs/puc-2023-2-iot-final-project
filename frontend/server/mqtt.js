import mqtt from "mqtt";

const MQTT_HOST = "mqtt://test.mosquitto.org";
const TOPIC = "teste123";

const client = mqtt.connect(MQTT_HOST);

client.on("connect", () => {
  client.subscribe(TOPIC, (err) => {
    if (err) {
      console.error("MQTT Subscription Error!", err);
      return;
    }
  });
});

client.on("message", (_topic, message) => {
  message = message.toString(); // message is Buffer

  console.log("MQTT says", message);
  // client.end();
});
