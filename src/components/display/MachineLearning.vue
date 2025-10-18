<template>
  <div class="project-info">
    <h2>机器学习实验</h2>
    <h3>学习与实践经历</h3>
    <p>
      系统学习了机器学习的基础理论与实践方法，完成了多个实验项目，涵盖数据预处理、模型训练与优化等内容。
    </p>

    <h3>实验项目</h3>
    <div class="tech-list">
      <span class="tech-tag">Python 基础</span>
      <span class="tech-tag">数据预处理</span>
      <span class="tech-tag">线性回归</span>
      <span class="tech-tag">逻辑回归</span>
      <span class="tech-tag">支持向量机</span>
      <span class="tech-tag">神经网络</span>
      <span class="tech-tag">深度学习</span>
      <span class="tech-tag">TensorFlow</span>
      <span class="tech-tag">PyTorch</span>
    </div>

    <h3>实验0 - Python 基础语法与 NumPy 使用</h3>
    <p>学习了 Python 的基础语法和 NumPy 的基本操作，为后续的机器学习实验打下了坚实的基础。</p>
    <ul>
      <li>
        <strong>Python 基础语法：</strong>
        <ul>
          <li>print 输出、注释、基本变量赋值、格式化字符串（百分号、str.format、f-string）。</li>
        </ul>
      </li>
      <li>
        <strong>数据类型与容器：</strong>
        <ul>
          <li>标量与集合类型：int、float、tuple、list、set、dict。</li>
          <li>切片与索引：例如 <code>xtuple[0:-2]</code>、<code>xlist[0:1]</code>。</li>
          <li>列表排序：<code>list.sort()</code>。</li>
        </ul>
      </li>
      <li>
        <strong>函数与错误处理基础：</strong>
        <ul>
          <li>
            自定义函数：例如 <code>dot_product(x, y)</code>，包含参数长度检查和返回
            <code>None</code> 的简单错误处理。
          </li>
        </ul>
      </li>
      <li>
        <strong>面向对象（OOP）基础：</strong>
        <ul>
          <li>
            类定义与方法：<code>__init__</code>、实例方法（<code>greet</code>、<code>introduce</code>、<code>study</code>）。
          </li>
          <li>
            继承与 <code>super()</code> 的使用（<code>people</code> 继承自
            <code>object</code>、<code>student</code> 继承自 <code>people</code>）。
          </li>
          <li>
            注意：代码中把类命名为 <code>object</code> 会覆盖 Python 内建
            <code>object</code>，这是一个常见的坑，应避免使用内建名并按规范使用大写类名（例如
            <code>Person</code>、<code>Student</code>）。
          </li>
        </ul>
      </li>
      <li>
        <strong>文件读写（示例被注释）：</strong>
        <ul>
          <li>
            展示了逐行读取与写入文件的基本模式（<code>open</code>、<code>readline</code>、<code>write</code>、<code>close</code>）。
          </li>
        </ul>
      </li>
      <li>
        <strong>NumPy 矩阵与向量运算：</strong>
        <ul>
          <li>创建数组：一维、二维、列向量、行向量。</li>
          <li>形状与维度：<code>shape</code>、<code>np.shape</code>。</li>
          <li>线性代数运算：<code>np.dot</code>、<code>np.matmul</code>、转置 <code>.T</code>。</li>
          <li>广播机制：矩阵与向量相加（<code>A + a</code>、<code>B + b</code>）。</li>
          <li>元素级运算：加、减、乘、除（逐元素）。</li>
          <li>
            聚合函数：<code>np.max</code>、<code>np.argmax</code>、<code>np.sum</code>、<code>np.prod</code>、<code>np.mean</code>、<code>np.std</code>、<code>np.average</code>。
          </li>
          <li>
            数组拷贝与引用问题：<code>b1 = b</code>（引用） vs <code>b.copy()</code>（深拷贝）。
          </li>
        </ul>
      </li>
    </ul>

    <h3>实验1 - 模型评估</h3>
    <p>
      该实验围绕模型评估展开，分别完成了回归问题和二分类问题的模型评估指标计算与结果分析，并提供了对应实验代码。
    </p>

    <h4>一、实验基本信息</h4>
    <ul>
      <li><strong>实验名称：</strong>模型评估</li>

      <li>
        <strong>实验目的：</strong
        >掌握回归与分类问题的模型评估方法，能运用平方和误差（SSE）、均方误差（MSE）等指标评估回归模型，用错误率、精度等指标评价分类模型。
      </li>
    </ul>

    <h4>二、实验内容</h4>
    <p>实验分为两大模块，分别针对回归问题和二分类问题开展评估工作。</p>
    <ul>
      <li>
        <strong>回归问题评估：</strong>
        给定回归问题的真实标签与多个算法的预测结果，通过编程计算
        SSE、MSE、均方根误差（RMSE）、最大绝对误差（MAE）四种评测指标。
      </li>
      <li>
        <strong>二分类问题评估：</strong>
        给定二分类问题的真实标签与多个算法的预测结果，编程实现混淆矩阵，并计算查全率、查准率、F1
        指标。
      </li>
    </ul>

    <h4>三、实验结果与分析</h4>
    <h5>（一）回归问题（问题 1）结果分析</h5>
    <p>通过计算三个模型的四项指标，结果如下（保留两位小数）：</p>
    <table class="algo-table">
      <thead>
        <tr>
          <th>模型</th>
          <th>SSE</th>
          <th>MSE</th>
          <th>RMSE</th>
          <th>MAE</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>模型 1</td>
          <td>1328.65</td>
          <td>1.33</td>
          <td>1.15</td>
          <td>0.97</td>
        </tr>
        <tr>
          <td>模型 2</td>
          <td>507.79</td>
          <td>0.51</td>
          <td>0.71</td>
          <td>0.59</td>
        </tr>
        <tr>
          <td>模型 3</td>
          <td>642.84</td>
          <td>0.64</td>
          <td>0.80</td>
          <td>0.65</td>
        </tr>
      </tbody>
    </table>
    <p>
      从数据可知，模型 2 在 SSE、MSE、RMSE、MAE 四项指标上均为最小，回归预测效果最优；模型 1
      各项指标最大，预测效果最差。
    </p>

    <h5>（二）二分类问题（问题 2）结果分析</h5>
    <p>混淆矩阵：</p>
    <ul>
      <li>
        模型 1：真实正例中预测正例 88 个、预测反例 89 个；真实反例中预测正例 8 个、预测反例 815 个。
      </li>
      <li>
        模型 2：真实正例中预测正例 78 个、预测反例 168 个；真实反例中预测正例 18 个、预测反例 736
        个。
      </li>
      <li>
        模型 3：真实正例中预测正例 71 个、预测反例 244 个；真实反例中预测正例 25 个、预测反例 660
        个。
      </li>
    </ul>
    <p>核心评估指标（保留两位小数）：</p>
    <table class="algo-table">
      <thead>
        <tr>
          <th>模型</th>
          <th>查准率（P）</th>
          <th>查全率（R）</th>
          <th>F1</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>模型 1</td>
          <td>0.50</td>
          <td>0.92</td>
          <td>0.64</td>
        </tr>
        <tr>
          <td>模型 2</td>
          <td>0.32</td>
          <td>0.81</td>
          <td>0.46</td>
        </tr>
        <tr>
          <td>模型 3</td>
          <td>0.23</td>
          <td>0.74</td>
          <td>0.35</td>
        </tr>
      </tbody>
    </table>
    <p>综合来看，模型 1 在查准率、查全率和 F1 指标上均优于模型 2 和模型 3，二分类性能最佳。</p>

    <h4>四、实验代码</h4>
    <p>（一）回归问题（问题 1）代码</p>
    <ul>
      <li>导入 numpy 库，加载数据集 <code>experiment_01_dataset_01.csv</code>。</li>
      <li>定义四个函数分别计算 SSE、MSE、RMSE、MAE。</li>
      <li>
        循环遍历三个模型，提取真实标签与预测结果，调用函数计算并输出各模型的四项指标，且结果保留两位小数。
      </li>
    </ul>

    <p>（二）二分类问题（问题 2）代码</p>
    <ul>
      <li>导入 numpy 库，加载数据集 <code>experiment_01_dataset_02.csv</code>。</li>
      <li>定义函数分别计算查准率、查全率、F1 值和混淆矩阵。</li>
      <li>
        循环遍历三个模型，提取真实标签与预测结果，调用函数计算并输出各模型的查准率、查全率、F1
        值及混淆矩阵，结果保留两位小数。
      </li>
    </ul>
    <CollapsibleCodeBlock v-if="code1" :code="code1" :previewLines="8" />
    <h3>实验2 - 线性回归</h3>
    <p>本实验旨在理解线性回归模型原理，掌握其建模与预测方法，并学会拟合问题的模型评估方式。</p>

    <h4>一、实验基本信息</h4>
    <ul>
      <li><strong>实验名称：</strong>线性回归</li>
      <li>
        <strong>实验目的：</strong
        >理解线性回归模型原理，掌握其建模与预测方法，学会拟合问题的模型评估方式。
      </li>
    </ul>

    <h4>二、实验内容</h4>
    <p>
      实验分为两个任务，分别基于不同线性模型对数据进行处理，核心流程均为“数据加载→模型训练→参数求解→误差计算→结果绘图”。
    </p>
    <ul>
      <li>
        <strong>一元线性模型任务：</strong>
        假设模型为 <code>y = w1 * x + w2</code>，使用给定数据集训练模型，得到参数 <code>w1</code> 和
        <code>w2</code>，计算测试集均方误差（MSE），并绘制训练数据、测试数据与模型的可视化图表。
      </li>
      <li>
        <strong>二次多项式模型任务：</strong>
        假设模型为 <code>y = w1 * x^2 + w2 * x + w3</code>，重复上述流程，求解参数
        <code>w1</code>、<code>w2</code>、<code>w3</code>，计算测试集 MSE 并完成可视化。
      </li>
    </ul>

    <h4>三、实验结果与分析</h4>
    <h5>（一）一元线性模型（问题 1）</h5>
    <ul>
      <li>
        <strong>模型参数（保留两位小数）：</strong> <code>w1 = -9.72</code>，<code
          >w2 = 208.60</code
        >
      </li>
      <li><strong>测试集均方误差（保留两位小数）：</strong> 12.37</li>
      <li>
        <strong>可视化结果：</strong>
        图表标题为 “Linear
        Regression”，蓝色点代表训练数据，绿色点代表测试数据，红色直线代表训练得到的线性模型；从图中可观察到模型对数据的拟合程度一般，与部分数据点偏差较明显。
      </li>
    </ul>
    <img class="image" src="@/assets/pictures/ml/2-1.png" alt=" " />
    <h5>（二）二次多项式模型（问题 2）</h5>
    <ul>
      <li>
        <strong>模型参数（保留两位小数）：</strong> <code>w1 = -50.05</code>，<code>w2 = 40.12</code
        >，<code>w3 = 200.45</code>
      </li>
      <li><strong>测试集均方误差（保留两位小数）：</strong> 0.10</li>
      <li>
        <strong>可视化结果：</strong>
        图表标题为 “Polynomial Regression (Degree
        2)”，数据点颜色含义与一元模型一致，红色曲线代表二次多项式模型；曲线能更紧密地贴合训练与测试数据，拟合效果显著优于一元线性模型。
      </li>
    </ul>
    <img class="image" src="@/assets/pictures/ml/2-2.png" alt=" " />
    <h5>（三）结果对比</h5>
    <p>
      二次多项式模型的测试集
      MSE（0.10）远小于一元线性模型（12.37），说明该数据集的分布更符合二次函数规律，复杂程度更高的多项式模型能更好地捕捉数据间的关系，拟合精度更高。
    </p>

    <h4>四、实验代码</h4>
    <p>（一）一元线性模型（问题 1）代码</p>
    <ul>
      <li>
        导入 numpy 和 matplotlib 库，加载训练集 <code>experiment_02_training_set.csv</code> 与测试集
        <code>experiment_02_testing_set.csv</code>。
      </li>
      <li>
        分割数据为特征（<code>x</code>）和标签（<code>y</code>），并对训练集与测试集的
        <code>x</code> 进行扩展（增加全 1 列，用于拟合截距 <code>w2</code>）。
      </li>
      <li>
        通过矩阵求逆（<code>w = (X.T * X)^-1 * X.T * y</code>）求解模型参数，保留两位小数并输出。
      </li>
      <li>定义 MSE 计算函数，用训练好的模型预测测试集结果，计算并输出测试集 MSE。</li>
      <li>绘制散点图（训练数据、测试数据）与线性模型图，添加标签、标题与图例后展示。</li>
    </ul>

    <p>（二）二次多项式模型（问题 2）代码</p>
    <ul>
      <li>数据加载与分割步骤与一元模型一致，额外对训练集与测试集的 <code>x</code> 计算平方项。</li>
      <li>
        扩展 <code>x</code> 特征（包含平方项、原 <code>x</code> 项与全 1
        项），通过同样的矩阵求逆方法求解三个模型参数，保留两位小数并输出。
      </li>
      <li>复用 MSE 函数，计算测试集预测结果的 MSE 并输出。</li>
      <li>
        生成连续的 <code>x</code> 值（用于绘制平滑曲线），计算对应
        <code>y</code> 值，绘制散点图（训练 / 测试数据）与多项式曲线，添加标注后展示。
      </li>
    </ul>
    <CollapsibleCodeBlock v-if="code2" :code="code2" :previewLines="8" />
    <h3>实验3 - 神经网络分类器</h3>
    <p>
      使用 PyTorch
      实现一个简单的神经网络分类器，完成手写数字识别任务。通过调整超参数（如学习率、隐藏层大小）
      提升模型的准确率。
    </p>

    <h3>实验4 - 深度学习项目</h3>
    <p>
      使用 TensorFlow
      构建卷积神经网络（CNN），完成图像分类任务。通过数据增强和迁移学习提升模型性能。
    </p>
  </div>
</template>

<script setup lang="ts">
// 无需特殊脚本
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
import { ref, onMounted } from 'vue'
const code1 = ref<string | null>(null)
const code2 = ref<string | null>(null)
// const code2 = ref<string | null>(null)

onMounted(async () => {
  code1.value = await import('@/assets/codes/ml/ml-1.py.txt?raw').then((module) => module.default)
  //   code2.value = await import('@/assets/codes/DCS/TransactionChainService.java.txt?raw').then(
  //     (module) => module.default,
  //   )
  code2.value = await import('@/assets/codes/ml/ml-2.py.txt?raw').then((module) => module.default)
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
/* table */
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
</style>
