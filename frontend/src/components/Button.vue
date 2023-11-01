<template>
  <button
    class="my-button"
    :style="{
      ...buttonStyles,
      marginLeft: offset,
    }"
    :disabled="locked"
    @click="publishClick"
  ></button>
</template>

<script>
import axios from "axios";

export default {
  name: "Button",
  props: ["tone", "toneDisabled", "offset", "colorIndex", "locked"],
  methods: {
    async publishClick() {
      const payload = `input:${this.colorIndex}`;
      this.$emit("click");
      await axios.post("/publish?data=" + payload);
    },
  },
  computed: {
    buttonStyles() {
      return this.locked ? this.disabledStyles : this.enabledStyles;
    },
    enabledStyles() {
      return {
        backgroundColor: this.tone,
      };
    },
    disabledStyles() {
      return {
        backgroundColor: this.toneDisabled,
      };
    },
  },
};
</script>

<style>
.my-button,
.my-button:disabled {
  width: 20vw;
  height: calc(10vw + 5px);
  transform: skew(-15deg);

  box-shadow: inset -5px -8px 4px 0px rgba(0, 0, 0, 0.75);
  border: 2px solid #111;
  border-radius: 12px;
}

.my-button:active {
  margin-top: 5px;
  height: calc(10vw);
  box-shadow: inset -3px -3px 4px 0px rgba(0, 0, 0, 0.75);
}
.my-button:disabled {
  cursor: not-allowed;
  margin-top: 0 !important;
  height: calc(10vw + 5px) !important;
}
</style>
