import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import vueDevTools from 'vite-plugin-vue-devtools'

// https://vite.dev/config/
// export default defineConfig({
//   plugins: [vue(), vueDevTools()],
//   resolve: {
//     alias: {
//       '@': fileURLToPath(new URL('./src', import.meta.url)),
//     },
//   },
//   base: '/PersonalWeb/',
//   server: {
//     host: '0.0.0.0',
//     port: 5173, // 可自定义端口
//   },
// })

export default defineConfig(() => {
  const isCloudflare = process.env.CF_PAGES === '1' // ✅ Cloudflare Pages 环境会自动有这个变量

  return {
    plugins: [vue(), vueDevTools()],
    resolve: {
      alias: {
        '@': fileURLToPath(new URL('./src', import.meta.url)),
      },
    },
    base: isCloudflare ? '/' : '/PersonalWeb/', // 默认 GitHub Pages，用 Cloudflare 时改成 /
    server: {
      host: '0.0.0.0',
      port: 5173,
    },
  }
})
