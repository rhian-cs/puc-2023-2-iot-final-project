<template>
  <button
    class="my-button"
    :style="{
      backgroundColor: tone,
      marginLeft: offset,
    }"
    @click="publishClick"
  ></button>
</template>

<script>
import axios from "axios";

export default {
  name: "Button",
  props: ["tone", "toneDisabled", "offset", "colorIndex"],
  methods: {
    async publishClick() {
      const payload = `${this.colorIndex}`;
      this.$emit("click");
      await axios.post("/publish?data=" + payload);
    },
  },
};
</script>

<style>
.my-button {
  width: 20vw;
  height: calc(10vw + 5px);
  transform: skew(-15deg);

  box-shadow: inset -5px -8px 4px 0px rgba(0, 0, 0, 0.75);
  border: 2px solid #111;
  border-radius: 12px;
}

.my-button:active:not(.my-button:disabled) {
  margin-top: 5px;
  height: calc(10vw);
  box-shadow: inset -3px -3px 4px 0px rgba(0, 0, 0, 0.75);
}
.my-button:disabled {
  cursor: not-allowed;
  margin-top: 0 !important;
  height: calc(10vw + 5px) !important;
  border: 0;
}
</style>
