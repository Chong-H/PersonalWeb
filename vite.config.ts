import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import vueDevTools from 'vite-plugin-vue-devtools'

// https://vite.dev/config/
export default defineConfig({
  plugins: [vue(), vueDevTools()],
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
