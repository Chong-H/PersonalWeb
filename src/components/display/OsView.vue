<template>
  <div class="project-info">
    <h2>操作系统实验项目</h2>

    <h3>软中断通信实验</h3>
    <p>
      由父进程创建两个子进程，通过终端输入 <code>Crtl+\</code> 组合键向父进程发送 SIGQUIT
      软中断信号。父进程收到信号后，分别向两个子进程发送整数值为 16 和 17
      的软中断信号，子进程收到后终止运行。父进程调用
      <code>wait()</code> 等待两个子进程终止，然后自我终止。
    </p>
    <img class="image" src="@/assets/pictures/os/os2.png" alt="软中断通信实验实验场景" />
    <CollapsibleCodeBlock v-if="osCode1" :code="osCode1" :previewLines="8" />

    <h3>线程同步实验</h3>
    <p>
      编写 Linux 线程程序，利用线程信号量及 PV
      操作实现生产者—消费者同步关系。生产者线程生产产品，消费者线程消费产品，信号量保证仓库容量和互斥访问。
    </p>
    <img class="image" src="@/assets/pictures/os/os3.png" alt="线程同步实验场景" />
    <CollapsibleCodeBlock v-if="osCode2" :code="osCode2" :previewLines="8" />

    <h3>进程调度实验</h3>
    <p>
      在 Linux 下编程实现进程调度策略算法的模拟程序，支持
      FCFS（先到先服务）、RR（轮循）、基于优先级的调度算法。通过输入进程参数，模拟不同调度策略下的执行过程。
    </p>
    <img class="image" src="@/assets/pictures/os/os4r.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/pictures/os/os4p.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/pictures/os/os4f.png" alt="进程调度实验场景" />
    <img class="image" src="@/assets/pictures/os/os4e.png" alt="进程调度实验场景" />
    <CollapsibleCodeBlock v-if="osCode3" :code="osCode3" :previewLines="8" />

    <h3>内存管理实验</h3>
    <p>
      在 Linux 下编程实现虚存页面替换算法的模拟程序。根据用户输入参数，随机生成页访问顺序，支持
      OPT、FIFO、LRU 替换算法，并输出页替换流程结果和缺页次数。
    </p>
    <img class="image" src="@/assets/pictures/os/os5f.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/pictures/os/os5o.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/pictures/os/os5l.png" alt="内存管理实验场景" />
    <img class="image" src="@/assets/pictures/os/os5e.png" alt="内存管理实验场景" />
    <CollapsibleCodeBlock v-if="osCode4" :code="osCode4" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
//@ts-ignore
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
// import osCode1 from '@/assets/codes/os/osCode1.cpp?raw'

const osCode1 = ref<string | null>(null)

const osCode2 = ref<string | null>(null)

const osCode3 = ref<string | null>(null)

const osCode4 = ref<string | null>(null)

onMounted(async () => {
  osCode1.value = await import('@/assets/codes/os/osCode1.cpp?raw').then((module) => module.default)
  osCode2.value = await import('@/assets/codes/os/osCode2.cpp?raw').then((module) => module.default)
  osCode3.value = await import('@/assets/codes/os/osCode3.cpp?raw').then((module) => module.default)
  osCode4.value = await import('@/assets/codes/os/osCode4.cpp?raw').then((module) => module.default)
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
  font-size: 2.2rem;
  font-weight: bold;
  margin-bottom: 1.5rem;
  color: #409eff;
  text-align: center;
}
.project-info h3 {
  font-size: 1.3rem;
  font-weight: bold;
  margin-top: 2rem;
  margin-bottom: 1rem;
  color: #67c23a;
}
.project-info p,
.project-info ul,
.project-info ol {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
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
.image {
  max-width: 100%;
  height: auto;
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
}
</style>
