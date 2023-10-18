<template>
  <button
    class="my-button"
    :style="{ backgroundColor: tone, marginLeft: offset }"
  ></button>
</template>

<script>
export default {
  name: "Button",
  props: ["tone", "offset"],
};
</script>

<style>
.my-button {
  width: 20vw;
  height: 10vw;
  transform: skew(-15deg);
}
</style>
