<script setup>
import { ref } from "vue";
import Button from "./Button.vue";

defineProps({
  msg: String,
});

const count = ref(0);

const serverHello = ref({});

fetch(`/api/v1/hello`)
  .then((r) => r.json())
  .then(({ message }) => {
    serverHello.value = message;
  });
</script>

<template>
  <!-- <h1>{{ serverHello }}</h1> -->
  <pre :style="{ marginLeft: '3em', marginBottom: '5em' }">
░██████╗░███████╗███╗░░██╗██╗██╗░░░██╗░██████╗
██╔════╝░██╔════╝████╗░██║██║██║░░░██║██╔════╝
██║░░██╗░█████╗░░██╔██╗██║██║██║░░░██║╚█████╗░
██║░░╚██╗██╔══╝░░██║╚████║██║██║░░░██║░╚═══██╗
╚██████╔╝███████╗██║░╚███║██║╚██████╔╝██████╔╝
░╚═════╝░╚══════╝╚═╝░░╚══╝╚═╝░╚═════╝░╚═════╝░
</pre
  >

  <div class="grid">
    <div></div>
    <div class="cell">
      <Button tone="#f00" offset="2.75em" colorIndex="0" />
    </div>
    <div></div>

    <div class="cell">
      <Button tone="#0f0" offset="2.25em" colorIndex="1" />
    </div>
    <div></div>
    <div class="cell"><Button tone="#00f" colorIndex="2" /></div>

    <div></div>
    <div class="cell">
      <Button tone="#f0f" offset="-1.5em" colorIndex="3" />
    </div>
    <div></div>
  </div>
</template>

<style scoped>
.grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  grid-template-rows: repeat(3, 1fr);
}
</style>
