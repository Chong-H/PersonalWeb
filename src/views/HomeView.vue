<script setup lang="ts"></script>

<template>
  <div class="profile-home">
    <h1>罗鹏程</h1>
    <h2>软件工程学生，热爱用知识改变生活。</h2>
    <img class="avatar" src="@/assets/headProfile.jpg" alt="头像" />

    <div class="skills">
      <span>Vue</span>
      <span>React</span>
      <span>Node.js</span>
      <!-- 更多技能 -->
    </div>
    <div class="contact">
      <a href="mailto:posedgeclk@qq.com">QQ邮箱</a>
      <a href="https://github.com/Chong-H">GitHub仓库</a>
      <!-- 更多联系方式 -->
    </div>
    <blockquote>“体冲和以通无，应物而无累于物”</blockquote>
  </div>
</template>

<style scoped>
.profile-home {
  background: #fff;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 1200px;
  margin: 2rem auto;
}
.profile-home h1 {
  /* font-size: 4rem;  */
  font-weight: bold;
  margin: 1rem 0;
  font-size: 4rem;
  font-weight: bold;
  margin-bottom: 1.5rem;
  background: linear-gradient(90deg, #409eff 40%, #67c23a 100%);
  color: transparent;
  -webkit-background-clip: text;
  background-clip: text;
  text-shadow: 0 2px 8px rgba(64, 158, 255, 0.12);
  letter-spacing: 2px;
}
.profile-home h2 {
  font-weight: bold;
  margin: 1rem 0;
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
.contact a {
  display: block;
  margin-bottom: 1rem;
}
</style>
