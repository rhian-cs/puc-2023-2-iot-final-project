import express from "express";
import path from "path";
import homepageRouter from "./homepageRouter.js";
import assetsRouter from "./assetsRouter.js";
import "./mqtt.js";
import {
  BrokerMessageHandler,
  brokerMessageHandlers,
} from "./BrokerMessageHandler.js";
import { TOPIC, mqttClient } from "./mqtt.js";

const port = process.env.PORT || 3000;
const publicPath = path.join(path.resolve(), "public");
const distPath = path.join(path.resolve(), "dist");

const app = express();

app.get("/api/v1/hello", (_req, res) => {
  res.json({ message: "Hello, world!" });
});

app.get("/sse", (req, res) => {
  res.writeHead(200, {
    "Content-Type": "text/event-stream",
    "Cache-Control": "no-cache",
    Connection: "keep-alive",
  });

  brokerMessageHandlers.push(new BrokerMessageHandler(res));
});

app.post("/publish", (req, res) => {
  try {
    mqttClient.publish(TOPIC, req.query.data);
    res.status(200).json({ message: "OK" });
  } catch (e) {
    console.error(e);
    res.status(500).json({ error: e.message });
  }
});

if (process.env.NODE_ENV === "production") {
  app.use("/", express.static(distPath));
} else {
  app.use("/", express.static(publicPath));
  app.use("/src", assetsRouter);
}

app.use(homepageRouter);

app.listen(port, () => {
  console.log("Server listening on port", port);
});
