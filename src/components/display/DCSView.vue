<template>
  <div class="project-info">
    <h2>项目名称：基于区块链的数字藏品系统</h2>
    <h3>项目角色</h3>
    <p>ScrumMaster、编码人员</p>
    <h3>技术亮点</h3>
    <div class="tech-list">
      <span class="tech-tag">SpringBoot</span>
      <span class="tech-tag">Vue3</span>
      <span class="tech-tag">TypeScript</span>
      <span class="tech-tag">SpringDataJPA</span>
      <span class="tech-tag">CRUDRepository</span>
      <span class="tech-tag">区块链</span>
      <span class="tech-tag">智能合约</span>
      <span class="tech-tag">FiscoBcos</span>
      <span class="tech-tag">Solidity</span>
    </div>
    <h3>项目介绍</h3>
    <p>
      <a
        href="https://www.bilibili.com/video/BV1wc7az9EpU/?share_source=copy_web&vd_source=eaa8ba3bb0c8263f4cfc5e659af52b97"
        target="_blank"
        style="color: #409eff; font-weight: bold"
      >
        项目演示视频（Bilibili）
      </a>
    </p>
    <h3>我的主要工作</h3>
    <p>
      负责交易记录模块前端和后端的实现，交易功能的前端实现，区块链相关所有部分的实现（智能合约编写，对后端的移植，前后端的改造），交易部分前端的实现，商城模块的前端实现，以及交易/赠送/销毁的前端实现。
    </p>
    <!-- 可添加项目截图
    <h3>系统界面示例</h3>
    <img class="image" src="@/assets/DCSPage.png" alt="数字藏品系统界面截图" />
    -->
    <h3>智能合约-交易记录上链（Solidity 实现）</h3>
    <CollapsibleCodeBlock v-if="code1" :code="code1" :previewLines="8" />

    <h3>服务器启动区块链（linux终端）</h3>
    <pre class="code-block">
    <code>
    #!/bin/bash
    luo@ubuntu:~/fisco$ bash nodes/127.0.0.1/start_all.sh
    </code>
    </pre>
    <h3>控制区块链</h3>
    <pre class="code-block">
    <code>
    #!/bin/bash
    luo@ubuntu:~$ cd ~/fisco/console && bash start.sh
    </code>
    </pre>
    <h3>后端上链服务类（JAVA）</h3>
    <CollapsibleCodeBlock v-if="code2" :code="code2" :previewLines="8" />

    <h3>后端依赖项</h3>
    <pre class="code-block">
    <code>
    implementation ("org.fisco-bcos.java-sdk:fisco-bcos-java-sdk:2.9.1")
    </code>
    </pre>
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
import { ref, onMounted } from 'vue'
const code1 = ref<string | null>(null)

const code2 = ref<string | null>(null)

onMounted(async () => {
  code1.value = await import('@/assets/codes/DCS/code1.sol?raw').then((module) => module.default)
  code2.value = await import('@/assets/codes/DCS/TransactionChainService.java.txt?raw').then(
    (module) => module.default,
  )
})
</script>

<style scoped>
.project-info {
  background: #fff;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 1200px;
  margin: 2rem auto;
}
.project-info h2 {
  font-size: 2.6rem;
  font-weight: bold;
  margin-bottom: 1.5rem;
  background: linear-gradient(90deg, #409eff 40%, #67c23a 100%);
  color: transparent;
  -webkit-background-clip: text;
  background-clip: text;
  text-shadow: 0 2px 8px rgba(64, 158, 255, 0.12);
  letter-spacing: 2px;
}
.project-info h3 {
  font-size: 1.5rem;
  font-weight: bold;
  margin-top: 2rem;
  margin-bottom: 1rem;
  color: #409eff;
  text-shadow: 0 1px 4px rgba(64, 158, 255, 0.08);
  border-left: 5px solid #67c23a;
  padding-left: 0.6em;
  background: linear-gradient(90deg, #e0f7fa 0%, #fff 100%);
  border-radius: 6px;
}
.project-info p {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.tech-list {
  margin: 1rem 0 2rem 0;
  display: flex;
  flex-wrap: wrap;
  gap: 0.8rem;
}
.tech-tag {
  display: inline-block;
  font-size: 1.1rem;
  font-weight: bold;
  color: #fff;
  background: linear-gradient(90deg, #409eff 60%, #67c23a 100%);
  padding: 0.4em 1em;
  border-radius: 20px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
  letter-spacing: 1px;
  transition: transform 0.2s;
}
.tech-tag:hover {
  transform: scale(1.08);
  background: linear-gradient(90deg, #67c23a 60%, #409eff 100%);
}
.image {
  display: block;
  max-width: 100%;
  height: auto;
  margin: 2rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
}
.code-block {
  background: #23272e;
  color: #dcdcdc;
  font-size: 0.95rem;
  padding: 1.2rem;
  border-radius: 8px;
  overflow-x: auto;
  margin: 1.5rem 0;
  line-height: 1.6;
  font-family: 'Fira Mono', 'Consolas', 'Menlo', 'Monaco', monospace;
}
</style>
