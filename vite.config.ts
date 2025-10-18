import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import vueDevTools from 'vite-plugin-vue-devtools'
import { ViteImageOptimizer } from 'vite-plugin-image-optimizer'; // 注意成员名称是 ViteImageOptimizer

// https://vite.dev/config/
export default defineConfig({
  plugins: [vue(),
  vueDevTools(),
  ViteImageOptimizer({
    // ↓ 这里是图片压缩参数
    png: {
      quality: 70, // 压缩质量（0~100）
    },
    jpeg: {
      quality: 75,
    },
    jpg: {
      quality: 75,
    },
    webp: {
      quality: 80,
    },
    avif: {
      quality: 50,
    },
    // 可选：启用缓存，避免重复压缩相同图片
    cache: true,
  }),
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url)),
    },
  },
  base: '/PersonalWeb/',
  server: {
    host: '0.0.0.0',
    port: 5173, // 可自定义端口
  },
  optimizeDeps: {
    include: ['vue', 'vue-router', 'animejs'], // 提前预构建依赖
  },
})
