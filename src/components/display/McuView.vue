<template>
  <div class="project-info">
    <h2>单片机实验</h2>
    <h3>学习与实践经历</h3>
    <p>旁听电气工程学院潘育山老师的单片机课程及实验课，系统学习了51单片机的基础原理与应用开发。</p>
    <h3>硬件组装</h3>
    <p>
      使用潘育山老师发放的原件，独立焊接并组装了51单片机开发板，掌握了硬件电路的基础搭建与调试方法。
    </p>
    <h3>实验项目</h3>
    <div class="tech-list">
      <span class="tech-tag">跑马灯实验</span>
      <span class="tech-tag">LCD显示屏学号实验</span>

      <span class="tech-tag">数码显像管实验</span>
      <span class="tech-tag">51单片机开发</span>
      <span class="tech-tag">硬件焊接</span>
      <span class="tech-tag">C语言</span>
    </div>
    <h3>实验1-跑马灯实验（汇编语言）</h3>
    <img class="image" src="@/assets/runningled.png" alt="51单片机实验场景" />
    <img class="image" src="@/assets/runningled-lab.jpg" alt="51单片机实验场景" />
    <h3>实验8-LCD显示屏显示学号实验（C语言实现）</h3>
    <img class="image" src="@/assets/51MCUScreen1.png" alt="51单片机实验场景" />

    <h3>数码显像管实验出现鬼影（C语言）</h3>
    <p>
      具体原因是因为段选和位选信号发生变化总有先后顺序，先发生变化的会导致鬼影出现，可以通过如下方式解决：
    </p>
    <p>
      1. 先关闭所有位选信号，再改变段选信号，最后打开位选信号。 2.
      先关闭所有段选信号，再改变位选信号，最后打开段选信号。（在下一个位选信号发出前，段选信号发送FF，使得这一时刻显像管不显示”）
    </p>
    <img class="image" src="@/assets/ghost.jpg" alt="51单片机实验场景" />

    <h2>复刻硬件项目</h2>
    <h3>嘉立创 USB 电流计</h3>
    <p>参考开源设计，使用嘉立创 PCB 制作平台复刻了 USB电流计硬件项目。通过焊接元器件、调试电路，</p>
    <p>实现了 USB设备的电流实时检测与显示，提升了对硬件测量与 PCB 制作流程的理解。</p>
    <p>
      我在该项目复刻中主要做了物料采购，pcb打板，焊接元件，修改显示函数，适配0.91寸OLED屏幕，代码烧录,电流电压放大倍速参数调试等工作。
    </p>
    <img class="image" src="@/assets/usbdetecter.png" alt="嘉立创USB电流计实物图" />
    <img class="image" src="@/assets/usbdetecter2.png" alt="嘉立创USB电流计实物图" />
    <h3>ESP32 AI 女友项目</h3>
    <p>
      基于 ESP32 单片机，复刻了 AI 女友语音交互硬件项目。项目包含语音识别、语音合成模块，通过 ESP32
      实现与用户的语音互动。
    </p>
    <p>我在该项目复刻中主要做了物料采购，pcb打板，焊接元件，网络环境搭建，代码烧录等工作。</p>
    <img class="image" src="@/assets/AIGF.jpg" alt="ESP32 AI女友项目实物图" />
  </div>
</template>

<script setup lang="ts">
// 无需特殊脚本
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
.code-block {
  background: #23272e;
  color: #e6e6e6;
  font-size: 0.95rem;
  padding: 1.2rem;
  border-radius: 8px;
  overflow-x: auto;
  margin: 1.5rem 0;
  line-height: 1.6;
  font-family: 'Fira Mono', 'Consolas', 'Menlo', 'Monaco', monospace;
}
.image {
  max-width: 100%;
  height: auto;
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
}
</style>
