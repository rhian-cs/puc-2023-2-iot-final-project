<template>
  <pre :style="{ marginLeft: '3em', marginBottom: '5em' }">
░██████╗░███████╗███╗░░██╗██╗██╗░░░██╗░██████╗
██╔════╝░██╔════╝████╗░██║██║██║░░░██║██╔════╝
██║░░██╗░█████╗░░██╔██╗██║██║██║░░░██║╚█████╗░
██║░░╚██╗██╔══╝░░██║╚████║██║██║░░░██║░╚═══██╗
╚██████╔╝███████╗██║░╚███║██║╚██████╔╝██████╔╝
░╚═════╝░╚══════╝╚═╝░░╚══╝╚═╝░╚═════╝░╚═════╝░
</pre
  >

  <ResetButton @click="lock" />

  <div class="grid">
    <div></div>
    <div class="cell">
      <Button
        :locked="locked"
        tone="#f00"
        toneDisabled="#a00"
        offset="3.75vw"
        colorIndex="0"
        @click="lock"
      />
    </div>
    <div></div>

    <div class="cell">
      <Button
        :locked="locked"
        tone="#0f0"
        toneDisabled="#0a0"
        offset="2.25vw"
        colorIndex="1"
        @click="lock"
      />
    </div>
    <div></div>
    <div class="cell">
      <Button
        :locked="locked"
        tone="#00f"
        toneDisabled="#00a"
        colorIndex="2"
        @click="lock"
      />
    </div>

    <div></div>
    <div class="cell">
      <Button
        :locked="locked"
        tone="#ff0"
        toneDisabled="#aa0"
        offset="-3.25vw"
        colorIndex="3"
        @click="lock"
      />
    </div>
    <div></div>
  </div>
</template>

<script>
import { listenToMQTT } from "../sse";

import Button from "./Button.vue";
import ResetButton from "./ResetButton.vue";

export default {
  name: "Game",
  components: { Button, ResetButton },
  data() {
    return {
      locked: true,
    };
  },
  mounted() {
    // this.locked = false; // TODO: remove me

    listenToMQTT({
      onMessage: (message) => {
        switch (message) {
          case "ok":
            this.locked = false;
            break;
        }
      },
    });
  },
  methods: {
    lock() {
      this.locked = true;
    },
  },
};
</script>

<style scoped>
.grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  grid-template-rows: repeat(3, 1fr);
}
</style>
