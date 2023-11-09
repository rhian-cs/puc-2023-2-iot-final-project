export const listenToMQTT = ({ onMessage }) => {
  if (!!window.EventSource) {
    console.log("Init");

    var source = new EventSource("/sse");

    source.addEventListener(
      "message",
      function (e) {
        console.log(e.data);
        onMessage(e.data);
      },
      false
    );

    source.addEventListener(
      "open",
      function (e) {
        console.log("Connected");
      },
      false
    );

    source.addEventListener(
      "error",
      function (e) {
        if (e.eventPhase == EventSource.CLOSED) source.close();
        if (e.target.readyState == EventSource.CLOSED) {
          console.error("Disconnected");
        } else if (e.target.readyState == EventSource.CONNECTING) {
          console.error("Connecting...");
        }
      },
      false
    );
  } else {
    console.log("Your browser doesn't support SSE");
  }
};
