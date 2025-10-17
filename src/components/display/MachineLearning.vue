<template>
  <div class="project-info">
    <h2>机器学习实验</h2>
    <h3>学习与实践经历</h3>
    <p>
      系统学习了机器学习的基础理论与实践方法，完成了多个实验项目，涵盖数据预处理、模型训练与优化等内容。
    </p>

    <h3>实验项目</h3>
    <div class="tech-list">
      <span class="tech-tag">数据预处理</span>
      <span class="tech-tag">线性回归</span>
      <span class="tech-tag">逻辑回归</span>
      <span class="tech-tag">支持向量机</span>
      <span class="tech-tag">神经网络</span>
      <span class="tech-tag">深度学习</span>
      <span class="tech-tag">TensorFlow</span>
      <span class="tech-tag">PyTorch</span>
    </div>

    <h3>实验1 - 数据预处理与可视化</h3>
    <p>
      使用 Python 和 Pandas 对数据集进行清洗、归一化和特征工程处理。通过 Matplotlib 和 Seaborn
      对数据进行可视化分析，发现数据分布和特征之间的关系。
    </p>
    <!-- <img class="image" src="@/assets/pictures/ml/data-visualization.png" alt="数据可视化实验" /> -->

    <h3>实验2 - 线性回归模型</h3>
    <p>
      使用 NumPy
      实现线性回归模型，完成房价预测实验。通过梯度下降优化模型参数，并绘制损失函数的收敛曲线。
    </p>
    <!-- <img class="image" src="@/assets/pictures/ml/linear-regression.png" alt="线性回归实验" /> -->

    <h3>实验3 - 神经网络分类器</h3>
    <p>
      使用 PyTorch
      实现一个简单的神经网络分类器，完成手写数字识别任务。通过调整超参数（如学习率、隐藏层大小）
      提升模型的准确率。
    </p>
    <!-- <img class="image" src="@/assets/pictures/ml/neural-network.png" alt="神经网络实验" /> -->

    <h3>实验4 - 深度学习项目</h3>
    <p>
      使用 TensorFlow
      构建卷积神经网络（CNN），完成图像分类任务。通过数据增强和迁移学习提升模型性能。
    </p>
    <!-- <img class="image" src="@/assets/pictures/ml/deep-learning.png" alt="深度学习实验" /> -->
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
.image {
  max-width: 100%;
  height: auto;
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
}
</style>
