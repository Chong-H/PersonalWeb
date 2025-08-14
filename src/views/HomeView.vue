<script setup lang="ts"></script>

<template>
  <div class="profile-home">
    <h1>罗鹏程</h1>
    <h2>软件工程学生，热爱用知识改变生活。</h2>
    <img class="avatar" src="@/assets/headProfile.png" alt="头像" />

    <div class="skills">
      <span>Vue</span>
      <span>React</span>
      <span>Node.js</span>
      <!-- 更多技能 -->
    </div>
    <div class="contact">
      <a href="mailto:posedgeclk@qq.com">邮箱</a>
      <a href="https://github.com/Chong-H">GitHub仓库</a>
      <!-- 更多联系方式 -->
    </div>
    <blockquote>“体冲和以通无，应物而无累于物”</blockquote>
  </div>
</template>

<style scoped>
.profile-home h1 {
  font-size: 4rem; /* 或更大，如3rem */
  font-weight: bold;
  margin: 1rem 0;
}
.profile-home h2 {
  font-size: 2.5rem; /* 或更大，如3rem */
  font-weight: bold;
  margin: 1rem 0;
}
</style>
