<template>
  <div id="falling-container">
    <div class="common-layout">
      <el-container>
        <el-header>
          <el-text class="mx-1" size="large" type="primary"> PengCheng Luo </el-text>
        </el-header>

        <el-container>
          <el-aside width="200px">
            <el-row class="tac">
              <el-col :span="23">
                <h5 class="mb-2 custom-title">please select</h5>
                <el-menu
                  active-text-color="#ffd04b"
                  background-color="#545c64"
                  class="el-menu-vertical-demo"
                  default-active="2"
                  text-color="#fff"
                  style="height: 100%; width: 100%"
                  @open="handleOpen"
                  @close="handleClose"
                  @select="handleMenuSelect"
                >
                  <el-menu-item index="home">
                    <el-icon><setting /></el-icon>
                    <span>Home</span>
                    <!-- <RouterLink to="/">Home</RouterLink> -->
                  </el-menu-item>

                  <el-sub-menu index="1">
                    <template #title>
                      <el-icon><location /></el-icon>
                      <span>My Projects</span>
                    </template>
                    <el-menu-item-group title="Group One">
                      <el-menu-item index="1-1">item one</el-menu-item>
                      <el-menu-item index="1-2">item two</el-menu-item>
                    </el-menu-item-group>
                    <el-menu-item-group title="Group Two">
                      <el-menu-item index="1-3">item three</el-menu-item>
                    </el-menu-item-group>
                    <el-sub-menu index="1-4">
                      <template #title>item four</template>
                      <el-menu-item index="1-4-1">item one</el-menu-item>
                    </el-sub-menu>
                  </el-sub-menu>

                  <el-menu-item index="2">
                    <el-icon><icon-menu /></el-icon>
                    <span>Navigator Two</span>
                  </el-menu-item>

                  <el-menu-item index="3" disabled>
                    <el-icon><document /></el-icon>
                    <span>Navigator Three</span>
                  </el-menu-item>

                  <el-menu-item index="4">
                    <el-icon><setting /></el-icon>
                    <span>Navigator Four</span>
                  </el-menu-item>

                  <el-menu-item index="about">
                    <el-icon><setting /></el-icon>
                    <!-- <RouterLink to="/about">About</RouterLink> -->
                    <span>About</span>
                  </el-menu-item>
                  <!-- <RouterLink to="/">Home</RouterLink> -->
                </el-menu>
              </el-col>
            </el-row>
          </el-aside>

          <el-main>
            <RouterView />
          </el-main>
        </el-container>
      </el-container>
    </div>
  </div>
</template>

<script setup lang="ts">
import { RouterLink, RouterView } from 'vue-router'
import HelloWorld from './components/HelloWorld.vue'
import { useRouter } from 'vue-router'
const router = useRouter()
import { Document, Menu as IconMenu, Location, Setting } from '@element-plus/icons-vue'

const handleOpen = (key: string, keyPath: string[]) => {
  console.log(key, keyPath)
}
const handleClose = (key: string, keyPath: string[]) => {
  console.log(key, keyPath)
}

const handleMenuSelect = (index: string) => {
  if (index === 'home') {
    router.push('/')
  } else if (index === 'about') {
    router.push('/about')
  }
  // 其他菜单项...
}

//效果
function createFallingChar(x: number, y: number) {
  const chars = [
    '★',
    '♥',
    '✿',
    '☺',
    '♬',
    '♛',
    '♞',
    '♠',
    '♣',
    '♦',
    '♪',
    '☀',
    '☁',
    '☂',
    '☃',
    '☄',
    '☾',
    '☽',
    '☼',
    '☽',
    '☾',
    '☀',
    '☁',
    '☂',
    '☃',
    '☄',
    '☾',
    '☽',
    '☼',
  ]
  const char = chars[Math.floor(Math.random() * chars.length)]
  const el = document.createElement('span')
  el.textContent = char
  el.style.position = 'fixed'
  el.style.left = x + 'px'
  el.style.top = y + 'px'
  el.style.fontSize = Math.random() * 24 + 16 + 'px'
  el.style.color = `hsl(${Math.random() * 360},80%,60%)`
  el.style.pointerEvents = 'none'
  el.style.transition = 'transform 1.2s linear, opacity 1.2s linear'
  el.style.transform = 'translateY(0)'
  el.style.opacity = '1'
  document.body.appendChild(el)

  setTimeout(() => {
    el.style.transform = 'translateY(120px)'
    el.style.opacity = '0'
  }, 10)

  setTimeout(() => {
    el.remove()
  }, 1300)
}

window.addEventListener('mousemove', (e) => {
  createFallingChar(e.clientX, e.clientY)
})
</script>

<style scoped>
header {
  line-height: 1.5;
  max-height: 100vh;
}
.el-aside {
  position: fixed;
  left: 0;
  top: 64px; /* 如果 header 高度是 64px */
  height: calc(100vh - 64px);
  width: 200px; /* 或你自己的宽度 */
  z-index: 999;
  background: #545c64; /* 你想要的灰色 */
  /* box-shadow: 1px 0 8px rgba(0, 0, 0, 0.05);  */
  /* border-right: 1px solid #dcdcdc; */
}
.el-header {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 64px;
  z-index: 1000;

  display: flex;
  justify-content: center;
  align-items: center;
  /* box-shadow: 0 2px 8px rgb(255, 158, 158); */

  background-color: #545c64;
  color: #333;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
}
.el-main {
  margin-left: 200px; /* 与 aside 宽度一致 */
  padding-top: 64px; /* 与 header 高度一致 */
  min-height: calc(100vh - 64px);
  width: calc(100% - 200px);
  background: #ffffff; /* 你想要的灰色 */
  box-sizing: border-box;
}

.custom-title {
  color: #fffdf8; /* 你想要的颜色 */
}
/* 让主内容下移，避免被 header 遮挡 */
.common-layout {
  padding-top: 0px;
  /* position: fixed; */
  top: 0;
  left: 0;
  width: 100%;
  /* background: #feffbc; */
  display: flex;
  align-items: center;
}

.logo {
  display: block;
  margin: 0 auto 2rem;
}

nav {
  width: 100%;
  font-size: 12px;
  text-align: center;
  margin-top: 2rem;
}

nav a.router-link-exact-active {
  color: var(--color-text);
}

nav a.router-link-exact-active:hover {
  background-color: transparent;
}

nav a {
  display: inline-block;
  padding: 0 1rem;
  border-left: 1px solid var(--color-border);
}

nav a:first-of-type {
  border: 0;
}

@media (min-width: 1024px) {
  header {
    display: flex;
    place-items: center;
    padding-right: calc(var(--section-gap) / 2);
  }

  .logo {
    margin: 0 2rem 0 0;
  }

  header .wrapper {
    display: flex;
    place-items: flex-start;
    flex-wrap: wrap;
  }

  nav {
    text-align: left;
    margin-left: -1rem;
    font-size: 1rem;

    padding: 1rem 0;
    margin-top: 1rem;
  }
}
</style>
