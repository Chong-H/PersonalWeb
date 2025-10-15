<template>
  <div class="collapsible-code-block">
    <div class="code-preview" v-if="!expanded">
      <pre
        class="code-block"
      ><code ref="previewCode" class="language-cpp">{{ preview }}</code></pre>
      <el-button type="primary" size="small" @click="expanded = true">展开全部代码</el-button>
    </div>
    <div v-else>
      <pre class="code-block"><code ref="fullCode" class="language-cpp">{{ code }}</code></pre>
      <el-button type="default" size="small" @click="expanded = false">收起</el-button>
    </div>
  </div>
</template>

<script setup>
import hljs from 'highlight.js' // 引入highlight.js
import 'highlight.js/styles/atom-one-dark.css' // 引入一个深色主题（可选其他主题）
import { ref, computed, onMounted, watch, nextTick } from 'vue' // 添加所有需要的导入

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
// 定义两个 ref 指向代码块 DOM 元素
const previewCode = ref(null)
const fullCode = ref(null)

const preview = computed(() => {
  const lines = props.code.split('\n')
  if (lines.length <= props.previewLines) return props.code
  return lines.slice(0, props.previewLines).join('\n') + '\n...'
})

// 组件挂载后初始化高亮
onMounted(() => {
  if (previewCode.value) {
    hljs.highlightElement(previewCode.value) // 高亮预览代码
  }
})

// 监听展开/收起状态变化,更新高亮
watch(expanded, (newVal) => {
  nextTick(() => {
    // 用 nextTick 确保 DOM 已更新
    if (newVal) {
      // 展开时,高亮完整代码
      if (fullCode.value) hljs.highlightElement(fullCode.value)
    } else {
      // 收起时,重新高亮预览代码(防止折叠后样式丢失)
      if (previewCode.value) hljs.highlightElement(previewCode.value)
    }
  })
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
