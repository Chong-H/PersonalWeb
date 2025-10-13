<template>
  <div id="falling-container">
    <!-- 悬浮按钮 -->
    <button
      class="sidebar-toggle"
      @click="showAside = !showAside"
      @mousedown="startDrag"
      ref="dragButton"
    >
      <span>☰</span>
    </button>

    <div class="common-layout">
      <el-container>
        <!-- 左侧：侧边栏 -->
        <el-aside v-show="showAside" width="200px">
          <div class="aside-header">
            <span class="aside-title">个人网站</span>
          </div>
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
                    <span>项目经历</span>
                  </template>

                  <el-sub-menu index="PersonalPro">
                    <template #title>Personal Projects</template>
                    <el-menu-item index="pms">pms</el-menu-item>
                    <el-menu-item index="MCU">MCU</el-menu-item>
                    <el-menu-item index="sokoban">sokoban</el-menu-item>
                  </el-sub-menu>
                  <el-sub-menu index="GroupPro">
                    <template #title>group Project</template>
                    <el-menu-item index="DCS">DCS-Chain </el-menu-item>
                  </el-sub-menu>
                  <el-sub-menu index="CoursePro">
                    <template #title>Course Projects</template>
                    <el-menu-item index="drinkSeller">Drink Seller</el-menu-item>
                    <el-menu-item index="os">Operating System</el-menu-item>
                  </el-sub-menu>
                </el-sub-menu>

                <!-- <el-menu-item index="3" disabled>
                  <el-icon><document /></el-icon>
                  <span>Navigator Three</span>
                </el-menu-item>

                <el-menu-item index="4">
                  <el-icon><setting /></el-icon>
                  <span>Navigator Four</span>
                </el-menu-item> -->
                <el-sub-menu index="tutorial">
                  <!-- <RouterLink to="/about">About</RouterLink> -->

                  <template #title>
                    <!-- <el-icon><setting /></el-icon> -->
                    <el-icon><Document /></el-icon>
                    <span>tutorial</span>
                  </template>
                  <el-menu-item index="other">Other</el-menu-item>
                  <el-sub-menu index="SiblingPages">
                    <template #title>SiblingPages</template>
                    <!-- <el-menu-item index="pms">pms</el-menu-item>
                    <el-menu-item index="MCU">MCU</el-menu-item>
                    <el-menu-item index="sokoban">sokoban</el-menu-item> -->
                  </el-sub-menu>
                </el-sub-menu>
                <el-menu-item index="Contact">
                  <el-icon><icon-menu /></el-icon>
                  <span>Contact me</span>
                </el-menu-item>
                <el-menu-item index="about">
                  <el-icon><MoreFilled /></el-icon>

                  <span>About</span>
                </el-menu-item>
                <!-- <RouterLink to="/">Home</RouterLink> -->
              </el-menu>
            </el-col>
          </el-row>
        </el-aside>

        <!-- <el-main
            :style="
              showAside
                ? 'margin-left:200px;width:calc(100% - 200px);'
                : 'margin-left:0;width:100%;'
            "
          >
            <el-header>
              <el-text class="main-title" size="large" type="primary">
                PengCheng Luo's Personal Web
              </el-text>
            </el-header>
            <RouterView />
          </el-main> -->

        <!-- 右侧：主内容区 -->

        <div class="main-vertical" :style="showAside ? 'margin-left:200px;' : 'margin-left:0px;'">
          <!-- 上方栏目 -->
          <el-header class="main-header" :style="showAside ? 'left:200px;' : 'left:0px;'">
            <div class="header-left">
              <el-button type="text" @click="showAside = !showAside">
                <el-icon size="20">
                  <Expand v-if="showAside" />
                  <Fold v-else />
                </el-icon>
              </el-button>

              <!-- 快捷返回主页面按钮 -->
              <el-button
                v-if="$route.path !== '/'"
                type="primary"
                @click="handleMenuSelect('home')"
                class="dashboard-btn"
                size="small"
              >
                <el-icon><House /></el-icon>
                <span v-show="!showAside">工作台</span>
              </el-button>

              <el-breadcrumb separator="/">
                <el-breadcrumb-item>
                  <el-button text class="breadcrumb-home"> 主页面 </el-button>
                </el-breadcrumb-item>
                <el-breadcrumb-item>{{ currentMenuTitle }}</el-breadcrumb-item>
              </el-breadcrumb>
            </div>

            <!-- <el-text class="main-title" size="large" type="primary">
              {{ currentMenuTitle }}
            </el-text> -->
          </el-header>

          <!-- 下方内容 -->

          <transition name="fade" mode="out-in">
            <el-main :key="$route.fullPath">
              <!-- <template v-if="externalUrl">
              <iframe :src="externalUrl" style="width: 100%; height: 80vh; border: none"></iframe>
            </template> -->
              <RouterView />
            </el-main>
          </transition>
        </div>
      </el-container>
    </div>
  </div>
</template>

<script setup lang="ts">
import { RouterLink, RouterView } from 'vue-router'
import HelloWorld from './components/HelloWorld.vue'
import { Expand, Fold, House } from '@element-plus/icons-vue'
import { useRouter } from 'vue-router'
const router = useRouter()
import { Document, Menu as IconMenu, Location, Setting } from '@element-plus/icons-vue'
import { ref } from 'vue'
const showAside = ref(true)
const currentMenuTitle = ref("PengCheng Luo's Personal Web")

const externalUrl = ref('')
const handleOpen = (key: string, keyPath: string[]) => {
  console.log(key, keyPath)
}
const handleClose = (key: string, keyPath: string[]) => {
  console.log(key, keyPath)
}

function toggleSidebar() {
  showAside.value = !showAside.value
  // 这里可以加你的侧边栏显示/隐藏逻辑
}
const handleMenuSelect = (index: string) => {
  if (index === 'home') {
    router.push('/')
  } else if (index === 'about') {
    router.push('/about')
  } else if (index === 'pms') {
    router.push('/pms')
  } else if (index === 'DCS') {
    router.push('/dcs-chain')
  } else if (index === 'Contact') {
    router.push('/contact')
  } else if (index === '4') {
    // window.location.href = 'https://www.baidu.com'
    // externalUrl.value = 'https://www.baidu.com'
  } else if (index === 'MCU') {
    router.push('/MCU')
  } else if (index === 'sokoban') {
    router.push('/sokoban')
  } else if (index === 'drinkSeller') {
    router.push('/drinkSeller')
  } else if (index === 'os') {
    router.push('/os')
  } else if (index === 'other') {
    router.push('/other')
  }
  currentMenuTitle.value = menuMap[index] || '...'
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

const menuMap: Record<string, string> = {
  home: '首页',
  about: '关于',
  pms: 'PMS 密码管理系统',
  MCU: 'MCU 单片机项目',
  sokoban: 'Sokoban 推箱子',
  DCS: 'DCS-Chain 数字藏品',
  drinkSeller: '饮料贩卖机课设',
  os: '操作系统实验',
  Contact: '联系方式',
}
// 侧边栏拖拽功能
const dragButton = ref<HTMLElement | null>(null)
const position = ref({ x: 24, y: 32 }) // 初始位置

const startDrag = (event: MouseEvent) => {
  const button = dragButton.value
  if (!button) return

  const startX = event.clientX - position.value.x
  const startY = event.clientY - position.value.y

  const onMouseMove = (e: MouseEvent) => {
    position.value.x = e.clientX - startX
    position.value.y = e.clientY - startY
    updateButtonPosition()
  }

  const onMouseUp = () => {
    document.removeEventListener('mousemove', onMouseMove)
    document.removeEventListener('mouseup', onMouseUp)
  }

  document.addEventListener('mousemove', onMouseMove)
  document.addEventListener('mouseup', onMouseUp)
}

const updateButtonPosition = () => {
  const button = dragButton.value
  if (button) {
    button.style.left = `${position.value.x}px`
    button.style.top = `${position.value.y}px`
  }
}
</script>

<style scoped>
header {
  line-height: 1.5;
  max-height: 100vh;
}
.header-left {
  display: flex;
  align-items: center;
  gap: 16px;
}
.el-aside {
  position: fixed;
  left: 0;
  top: 0px; /* 如果 header 高度是 64px */
  height: calc(100vh - 0px);
  width: 200px; /* 或你自己的宽度 */
  z-index: 999;
  background: #545c64; /* 你想要的灰色 */
  /* box-shadow: 1px 0 8px rgba(0, 0, 0, 0.05);  */
  /* border-right: 1px solid #dcdcdc; */
}
.el-header {
  position: fixed;
  /* position: sticky; */
  top: 0;
  /* left: 0; */
  width: 100%;
  height: 64px;
  /* z-index: 1000; */

  display: flex;
  /* justify-content: center; */
  /* align-items: center; */
  /* box-shadow: 0 2px 8px rgb(255, 158, 158); */

  z-index: 100;
  background-color: #fff;
  color: #333;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
}
.main-title {
  font-size: 2rem !important;
  font-weight: 700;
  color: #222;
  letter-spacing: 1px;
  padding-bottom: 0.4em;
  /* border-bottom: 2px solid #409eff; */
  background: none;
  text-shadow: none;
  border-radius: 0;
}
.el-main {
  /* margin-left: 200px;  */
  /* 与 aside 宽度一致 */
  padding: 64px 0 0 0; /* 顶部留出header高度，左右无间隙 */
  margin-left: -7%;
  margin-right: -7%;
  left: 0;
  flex: 1;
  min-width: 0;
  background: #ffffff;
  box-sizing: border-box;
}
.main-vertical {
  flex: 1;
  width: 100%;
  left: 0;

  min-width: 0;
  display: flex;
  flex-direction: column;
  height: 100vh;
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
  height: 100vh;
  /* background: #feffbc; */
  display: flex;
  /* align-items: center; */
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
/* 悬浮按钮样式 */
.sidebar-toggle {
  position: fixed;
  bottom: 32px;
  left: 24px;
  z-index: 2000;
  width: 48px;
  height: 48px;
  border-radius: 50%;
  background: #409eff;
  color: #fff;
  font-size: 2rem;
  border: none;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.12);
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: background 0.2s;
  left: 44px; /* 初始位置 */
  top: 48px; /* 初始位置 */
  animation: heartbeat 1s infinite ease-in-out; /* 添加心跳动画 */
}

/* 心跳动画 */
@keyframes heartbeat {
  0%,
  100% {
    transform: translateY(0); /* 初始位置 */
  }
  50% {
    transform: translateY(-5px); /* 向上移动 10px */
  }
}
.sidebar-toggle:hover {
  background: #67c23a;
}
.aside-header {
  height: 64px;
  background: #6d7680; /* 比侧边栏浅一点 */
  display: flex;
  align-items: center;
  justify-content: center;
  border-bottom: 1px solid #e0e0e0;
}
.aside-title {
  font-size: 1.3rem;
  font-weight: 600;
  color: #fff;
  letter-spacing: 1px;
}
.el-breadcrumb {
  display: flex;
  align-items: center;
}
.breadcrumb-home {
  height: 24px;
  line-height: 24px;
  padding: 0;
  font-size: 1em;
  vertical-align: middle;
}
.el-breadcrumb__item {
  display: flex;
  align-items: center;
}
</style>
<style>
/* 进入动画起始状态 + 离开动画结束状态 */
.fade-enter-from {
  opacity: 0;
  transform: translateX(-30px); /* 关键：水平向左偏移，模拟“从左进入”的起点 */
}

/* 离开动画结束状态（向左侧外部离开：透明度0 + 向左偏移30px） */
.fade-leave-to {
  opacity: 0;
  transform: translateX(30px); /* 离开时也向左侧偏移，保持动画一致性 */
}

/* 进入/离开动画的活跃状态（过渡时间和曲线不变，确保流畅） */
.fade-enter-active,
.fade-leave-active {
  transition: all 0.5s ease-out; /* 控制动画速度，0.5s 可根据需求调整（如0.6s更慢） */
}

/* 进入动画结束状态（最终位置：透明度1 + 无偏移） */
.fade-enter-to {
  opacity: 1;
  transform: translateX(0); /* 水平复位，完成“从左到右”的加载 */
}

/* 离开动画起始状态（初始位置：透明度1 + 无偏移） */
.fade-leave-from {
  opacity: 1;
  transform: translateX(0); /* 离开前保持在正常位置 */
}
</style>
