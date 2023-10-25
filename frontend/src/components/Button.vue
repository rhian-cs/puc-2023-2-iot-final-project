<template>
  <button
    class="my-button"
    :style="{ backgroundColor: tone, marginLeft: offset }"
    @click="publishClick"
  ></button>
</template>

<script>
import axios from "axios";

export default {
  name: "Button",
  props: ["tone", "offset", "colorIndex"],
  methods: {
    async publishClick() {
      const payload = `input:${this.colorIndex}`;
      await axios.post("/publish?data=" + payload);
    },
  },
};
</script>

<style>
.my-button {
  width: 20vw;
  height: 10vw;
  transform: skew(-15deg);
}
</style>
