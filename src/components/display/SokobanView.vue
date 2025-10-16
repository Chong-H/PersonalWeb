<template>
  <div class="project-info">
    <h2>ProjectName：Sokoban推箱子游戏</h2>
    <h3>项目简介</h3>
    <p>
      Sokoban（推箱子）是一款经典的益智游戏，本项目实现了自动求解最优路径的功能。除分支限界算法外，核心还深度依赖A*算法（启发式搜索），并辅助使用DFS（深度优先搜索）进行可行性校验。
    </p>
    <h3>核心算法定位：分支限界 + A*算法</h3>
    <p>
      推箱子的最优路径搜索采用分支限界算法结合A*启发式搜索。<br />
      <strong>分支限界：</strong
      >通过优先队列管理待探索状态，利用“限界”剪去不可能找到最优解的分支，避免无效搜索。<br />
      <strong>A*算法：</strong>核心是f(n) = g(n) +
      h(n)，其中g(n)为已走步数，h(n)为箱子到目标的曼哈顿距离。优先队列按总代价估值排序，确保每次优先探索最有希望的状态。
    </p>
    <h3>辅助算法：DFS可行性校验</h3>
    <p>
      DFS用于校验机器人能否到达推箱子所需的位置（发力点），只有可达时才允许推动箱子。有效剪枝，提升搜索效率。
    </p>
    <h3>算法流程简述</h3>
    <ol>
      <li>初始化地图，确定箱子、机器人、目标位置。</li>
      <li>计算初始状态估值，加入优先队列。</li>
      <li>循环：每次取出估值最小状态，若箱子到达目标则返回步数。</li>
      <li>遍历四个方向，尝试推动箱子，DFS校验机器人可达性。</li>
      <li>有效新状态加入队列，已访问位置剪枝。</li>
      <li>队列空则无解。</li>
    </ol>
    <h3>关键函数与算法对应关系</h3>
    <table class="algo-table" role="table">
      <thead>
        <tr>
          <th>函数名</th>
          <th>核心作用</th>
          <th>依赖算法</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>fzxj</td>
          <td>最优路径搜索（主函数）</td>
          <td>分支限界 + A*</td>
        </tr>
        <tr>
          <td>lowerbound</td>
          <td>计算启发式估值（曼哈顿距离）</td>
          <td>A* 启发函数</td>
        </tr>
        <tr>
          <td>dfs</td>
          <td>机器人移动可行性校验</td>
          <td>DFS（深度优先）</td>
        </tr>
        <tr>
          <td>Compare</td>
          <td>优先队列排序规则</td>
          <td>A* 估值排序</td>
        </tr>
        <tr>
          <td>visited</td>
          <td>箱子位置去重</td>
          <td>分支限界剪枝</td>
        </tr>
      </tbody>
    </table>

    <h3>结论</h3>
    <p>
      本项目通过分支限界算法与A*启发式搜索结合，配合DFS可行性校验，实现了高效且准确的推箱子最优解搜索。分支限界负责状态管理与剪枝，A*引导搜索方向，DFS辅助校验，有效提升了算法性能和游戏体验。
    </p>
    <h3>预测路径（程序运行截图，其中B是box,S是人，T是目标位置）</h3>
    <img class="image" src="@/assets/sokoban.png" alt="推箱子游戏界面截图" />
    <h3>部分核心代码展示（C++）</h3>
    <CollapsibleCodeBlock v-if="codeSokoban" :code="codeSokoban" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'

import { ref, onMounted } from 'vue'

const codeSokoban = ref<string | null>(null)

onMounted(async () => {
  codeSokoban.value = await import('@/assets/codes/sokoban.cpp?raw').then(
    (module) => module.default,
  )
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
.project-info ol {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.algo-table {
  width: 100%;
  border-collapse: collapse;
  margin: 1.2rem 0;
  font-size: 1rem;
}
.algo-table th,
.algo-table td {
  border: 1px solid #e0e0e0;
  padding: 0.5em 1em;
  text-align: left;
}
.algo-table th {
  background: #f5f7fa;
  color: #409eff;
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
