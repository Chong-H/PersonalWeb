<template>
  <div class="contact-flex">
    <div class="contact-info">
      <div class="contact-title-row">
        <h2>联系方式</h2>
        <!-- <img class="avatar" src="@/assets/headProfile.jpg" alt="头像" /> -->
      </div>
      <div class="contact-item">
        <span class="contact-label">电话：</span>
        <span class="contact-value">(+86)19102846720</span>
      </div>
      <div class="contact-item">
        <span class="contact-label">微信号：</span>
        <span class="contact-value">posedgeclk</span>
      </div>
      <div class="contact-item">
        <span class="contact-label">邮箱：</span>
        <a class="contact-value" href="mailto:posedgeclk@qq.com">posedgeclk@qq.com</a>
      </div>
      <div class="contact-item">
        <span class="contact-label">QQ：</span>
        <a class="contact-value" href="javascript:void(0);" @click="copyQQ">2846438764</a>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
const copyQQ = () => {
  const qq = '2846438764'
  if (navigator.clipboard) {
    navigator.clipboard.writeText(qq).then(
      () => {
        alert('QQ号已复制到剪切板！')
      },
      () => {
        alert('复制失败，请手动复制。')
      },
    )
  } else {
    const input = document.createElement('input')
    input.value = qq
    document.body.appendChild(input)
    input.select()
    try {
      document.execCommand('copy')
      alert('QQ号已复制到剪切板！')
    } catch {
      alert('复制失败，请手动复制。')
    }
    document.body.removeChild(input)
  }
}
</script>
<style scoped>
.contact-info {
  /* background: #fff; */

  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 500px;
  margin: 2rem auto;
}
.contact-info h2 {
  font-size: 2rem;
  font-weight: bold;
  margin-bottom: 2rem;
  color: #409eff;
  text-align: center;
}
.contact-item {
  display: flex;
  align-items: center;
  margin-bottom: 1.5rem;
  font-size: 1.2rem;
  flex-wrap: wrap;
}
.contact-label {
  font-weight: bold;
  color: #67c23a;
  min-width: 80px;
}
.contact-value {
  color: #222;
  margin-left: 1rem;
  word-break: break-all;
  text-decoration: none;
}
.contact-value:hover {
  color: #409eff;
  text-decoration: underline;
}
.contact-flex {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 32px;
}
.contact-view {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100%;
}
.avatar {
  width: 110px;
  height: 110px;
  /* border-radius: 80%; */
  object-fit: cover;
  margin-bottom: 0;
}
.contact-title-row {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 24px;
  margin-bottom: 2rem;
}
</style>
