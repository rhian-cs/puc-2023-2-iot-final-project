<template>
  <button @click="publishClick">Reset</button>
</template>

<script>
import axios from "axios";

export default {
  name: "ResetButton",
  methods: {
    async publishClick() {
      this.$emit("click");
      await axios.post("/publish?data=4");
    },
  },
};
</script>

<style scoped>
button {
  position: absolute;
  right: 5vw;
  top: 5vw;
}

button,
button:disabled {
  color: black;
  font-size: 2vw;
  background-color: aquamarine;
  width: 15vw;
  height: calc(7.5vw + 5px);

  box-shadow: inset -5px -8px 4px 0px rgba(0, 0, 0, 0.75);
  border: 2px solid #111;
  border-radius: 12px;
}

button:active {
  margin-top: 5px;
  height: calc(7.5vw);
  box-shadow: inset -3px -3px 4px 0px rgba(0, 0, 0, 0.75);
}
button:disabled {
  cursor: not-allowed;
  margin-top: 0 !important;
  height: calc(7.5vw + 5px) !important;
}
</style>
