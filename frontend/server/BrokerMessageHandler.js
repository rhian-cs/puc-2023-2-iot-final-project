export class BrokerMessageHandler {
  constructor(res) {
    this.res = res;
  }

  emit(data) {
    this.res.write("data: " + data + "\n\n");
  }
}

export const brokerMessageHandlers = [];
