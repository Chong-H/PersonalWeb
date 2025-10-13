<script setup lang="ts"></script>

<template>
  <div class="profile-home">
    <h1 class="typing-animation">罗鹏程</h1>

    <h2 class="typing-animation">软件工程专业，热爱用知识改变生活。</h2>

    <div class="awards">
      <h3 class="typing-animation">荣誉与经历</h3>
      <ul>
        <li>国家励志奖学金获得者</li>
        <li>明诚奖获得者</li>
        <li>一年学生会社团和一年学院实验室管理员经历</li>
        <li>两年学院事务中心助理经历</li>
      </ul>
    </div>

    <div class="education">
      <h3 class="typing-animation">教育背景</h3>
      <ul>
        <li>西南交通大学 本科</li>
        <li>软件工程专业</li>
      </ul>
    </div>

    <div class="certificates">
      <h3 class="typing-animation">证书</h3>
      <ul>
        <li>英语六级证书</li>
        <li>英语四级证书</li>
        <li>蓝桥杯A组C++省二</li>
      </ul>
    </div>

    <div class="courses">
      <h3 class="typing-animation">专业核心课程</h3>
      <ul>
        <li>数据库原理（含实验）</li>
        <li>计算机网络（含实验）</li>
        <li>计算机组成原理（含实验）</li>
        <li>算法分析与设计（含实验）</li>
        <li>操作系统（含实验）</li>
        <li>计算机图形学（含实验）</li>
        <li>软件工程</li>
        <li>单片机原理及应用（含实验）</li>
        <li>区块链技术及应用</li>
        <li>数字电子技术（含实验）</li>
        <li>...</li>
        <!-- 可继续补充更多课程 -->
      </ul>
    </div>

    <div class="skills">
      <!-- <span>Vue</span>
      <span>React</span>
      <span>Node.js</span> -->
      <!-- 更多技能 -->
    </div>
    <div class="contact">
      <a href="mailto:posedgeclk@qq.com">QQ邮箱</a>
      <a href="https://github.com/Chong-H">GitHub仓库</a>
      <!-- 更多联系方式 -->
    </div>
    <!-- <blockquote>“体冲和以通无，应物而无累于物”</blockquote> -->
  </div>
</template>

<style scoped>
/* 标题打字机动画 */
.typing-animation {
  display: block; /* 改为 block，确保每个标题占据一整行 */
  overflow: hidden;
  white-space: nowrap;
  border-right: 2px solid #409eff;
  animation:
    typing 4s steps(20, end),
    blink 0.5s step-end infinite alternate;
}

@keyframes typing {
  from {
    width: 0;
  }
  to {
    width: 100%;
  }
}

@keyframes blink {
  from {
    border-color: transparent;
  }
  to {
    border-color: #409eff;
  }
}
/* --------- */
.profile-home {
  width: 100%;
  background: #fff;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 1200px;
  margin: 0;
}
.profile-home h1 {
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
.profile-home h3 {
  font-size: 1.3rem;
  font-weight: bold;
  margin-top: 2rem;
  margin-bottom: 1rem;
  color: #409eff;
}
.profile-home ul {
  margin-left: 1.2em;
  margin-bottom: 1.2em;
  font-size: 1.08rem;
  line-height: 1.8;
}
.contact a {
  display: block;
  margin-bottom: 1rem;
}
</style>
