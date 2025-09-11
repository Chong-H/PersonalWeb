<template>
  <div class="collapsible-code-block">
    <div class="code-preview" v-if="!expanded">
      <pre class="code-block"><code>{{ preview }}</code></pre>
      <el-button type="primary" size="small" @click="expanded = true">展开全部代码</el-button>
    </div>
    <div v-else>
      <pre class="code-block"><code>{{ code }}</code></pre>
      <el-button type="default" size="small" @click="expanded = false">收起</el-button>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'
const props = defineProps({
  code: {
    type: String,
    required: true,
  },
  previewLines: {
    type: Number,
    default: 8,
  },
})
const expanded = ref(false)
const preview = computed(() => {
  const lines = props.code.split('\n')
  if (lines.length <= props.previewLines) return props.code
  return lines.slice(0, props.previewLines).join('\n') + '\n...'
})
</script>

<style scoped>
.collapsible-code-block {
  margin-bottom: 2rem;
}
.code-block {
  background: #23272e;
  color: #ffffff;
  font-size: 0.95rem;
  padding: 1.2rem;
  border-radius: 8px;
  overflow-x: auto;
  line-height: 1.6;
  font-family: 'Fira Mono', 'Consolas', 'Menlo', 'Monaco', monospace;
}
.el-button {
  margin-top: 0.5rem;
}
</style>
