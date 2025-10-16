<template>
  <div class="project-info">
    <h2>ProjectName：PMS密码管理系统</h2>
    <h3>Role项目角色</h3>
    <p>项目经理，软件开发者</p>
    <h3>技术栈</h3>
    <div class="tech-list">
      <span class="tech-tag">SpringBoot</span>
      <span class="tech-tag">SpringDataJPA</span>
      <span class="tech-tag">.NET</span>
      <span class="tech-tag">Winform</span>
      <span class="tech-tag">RestfulAPI</span>
      <span class="tech-tag">VUE3</span>
      <span class="tech-tag">AES加密算法</span>
      <span class="tech-tag">ECDH密钥协商算法</span>
      <span class="tech-tag">Java</span>
      <span class="tech-tag">Ts</span>
      <span class="tech-tag">C#</span>
      <span class="tech-tag">nginx</span>
      <span class="tech-tag">OTP(TOTP)验证码生成算法</span>
      <span class="tech-tag">2fa验证</span>
    </div>
    <h3>项目内容</h3>
    <p>
      负责密码管理系统的开发和实现，采用CS和BS双架构。<br />
      CS架构程序部分主要使用C#语言和.NET
      Winform框架，实现对密码的增删改查功能。加密算法采用AES（128bit）算法，对数据库敏感词条（如账号和密码）进行加密存储和解密展示。<br />
      BS架构程序部分采用前后端分离的模式，展示各个账号信息。前后端交流时，通过ECDH算法协商生成信息交流的密钥，并使用AES加密进行数据传输。后端与数据库交互也通过AES加密进行。<br />
      本项目也实现了2fa验证码（基于OTP算法），可以代替Google Authenticator,SafeAuth,Microsoft
      Authenticator进行身份验证。<br />
      项目部署在RK3399单板机（Ubuntu）和Intel
      laptop（Win11）上，并使用花生壳进行内网穿透，开放端口到域名，实现外网访问。
    </p>
    <h3>CS客户端页面示例-2fa验证码生成</h3>
    <img class="image" src="@/assets/PMSPageCS.png" alt="密码管理系统界面截图" />
    <h3>BS客户端页面示例-信道密钥生成与协商</h3>
    <img class="image" src="@/assets/PMSPageBS.png" alt="密码管理系统界面截图" />
    <h3>BS客户端页面示例-加密数据交流演示</h3>
    <img class="image" src="@/assets/PMSPageBSCommunicate.png" alt="密码管理系统加密信道截图" />
    <h3>CS客户端页面示例-AES加密解密代码C#实现（部分）</h3>
    <CollapsibleCodeBlock v-if="code1" :code="code1" :previewLines="8" />

    <h3>CS客户端页面示例-TOTP算法基于C#实现（部分）</h3>
    <CollapsibleCodeBlock v-if="code2" :code="code2" :previewLines="8" />

    <h3>BS客户端页面示例-AES算法基于Java实现（部分）</h3>
    <CollapsibleCodeBlock v-if="code3" :code="code3" :previewLines="8" />

    <h3>BS客户端页面示例-TOTP算法基于Java实现（部分）</h3>
    <CollapsibleCodeBlock v-if="code4" :code="code4" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
import { ref, onMounted } from 'vue'
const code1 = ref<string | null>(null)
const code2 = ref<string | null>(null)
const code3 = ref<string | null>(null)
const code4 = ref<string | null>(null)

onMounted(async () => {
  code1.value = await import('@/assets/codes/pmsCode1.cs?raw').then((module) => module.default)
  code2.value = await import('@/assets/codes/pmsCode2.cs?raw').then((module) => module.default)
  code3.value = await import('@/assets/codes/pmsCode3.class?raw').then((module) => module.default)
  code4.value = await import('@/assets/codes/pmsCode4.class?raw').then((module) => module.default)
})
</script>

<style scoped>
.image {
  display: block;
  max-width: 100%;
  height: auto;
  margin: 2rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
}
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
