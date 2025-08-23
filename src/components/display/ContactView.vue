<template>
  <div class="contact-info">
    <h2>联系方式</h2>
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
  </div>
</template>

<style scoped>
.contact-info {
  background: #fff;
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
</style>
