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

  <ResetButton />

  <div class="grid">
    <div></div>
    <div class="cell">
      <Button tone="#f00" toneDisabled="#a00" offset="3.75vw" colorIndex="0" />
    </div>
    <div></div>

    <div class="cell">
      <Button tone="#0f0" toneDisabled="#0a0" offset="2.25vw" colorIndex="1" />
    </div>
    <div></div>
    <div class="cell">
      <Button tone="#00f" toneDisabled="#00a" colorIndex="2" />
    </div>

    <div></div>
    <div class="cell">
      <Button tone="#ff0" toneDisabled="#aa0" offset="-3.25vw" colorIndex="3" />
    </div>
    <div></div>
  </div>
</template>

<script>
import Button from "./Button.vue";
import ResetButton from "./ResetButton.vue";

export default {
  name: "Game",
  components: { Button, ResetButton },
};
</script>

<style scoped>
.grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  grid-template-rows: repeat(3, 1fr);
}
</style>
