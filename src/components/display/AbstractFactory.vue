<template>
  <div class="factory-visual-container">
    <!-- 标题 -->
    <div class="title">抽象工厂模式可视化</div>
    <div class="subtitle">选择工厂，然后点击产品类型查看创建过程</div>

    <!-- 1. 抽象层：抽象工厂 + 抽象产品 -->
    <div class="abstract-layer">
      <div class="abstract-factory">
        <div>抽象工厂</div>
        <div class="code-text">ShapeFactory</div>
        <div class="abstract-desc">定义创建产品族的接口</div>
      </div>
      <div class="arrow-right">→</div>
      <div class="abstract-products">
        <div class="abstract-product">
          <div>抽象产品A</div>
          <div class="code-text">Cube</div>
        </div>
        <div class="abstract-product">
          <div>抽象产品B</div>
          <div class="code-text">Sphere</div>
        </div>
      </div>
    </div>

    <!-- 2. 工厂选择区 -->
    <div class="factory-selection">
      <div class="section-title">步骤1：选择具体工厂</div>
      <div class="factories">
        <div
          class="concrete-factory factory-wireframe"
          :class="{ active: selectedFactory === 'wireframe' }"
          @click="selectFactory('wireframe')"
        >
          <div class="factory-icon">🔲</div>
          <div>线框工厂</div>
          <div class="code-text">WireframeFactory</div>
        </div>

        <div
          class="concrete-factory factory-solid"
          :class="{ active: selectedFactory === 'solid' }"
          @click="selectFactory('solid')"
        >
          <div class="factory-icon">🟦</div>
          <div>实体工厂</div>
          <div class="code-text">SolidFactory</div>
        </div>

        <div
          class="concrete-factory factory-textured"
          :class="{ active: selectedFactory === 'textured' }"
          @click="selectFactory('textured')"
        >
          <div class="factory-icon">🎨</div>
          <div>表面工厂</div>
          <div class="code-text">TexturedFactory</div>
        </div>
      </div>
    </div>

    <!-- 3. 产品选择区 -->
    <div class="product-selection" v-if="selectedFactory">
      <div class="section-title">步骤2：选择要创建的产品</div>
      <div class="product-buttons">
        <button
          class="product-btn"
          :class="{ disabled: isAnimating }"
          @click="createProduct('cube')"
          :disabled="isAnimating"
        >
          <span class="btn-icon">🔶</span>
          创建正方体
        </button>
        <button
          class="product-btn"
          :class="{ disabled: isAnimating }"
          @click="createProduct('sphere')"
          :disabled="isAnimating"
        >
          <span class="btn-icon">🔵</span>
          创建球体
        </button>
      </div>
    </div>

    <!-- 4. 创建过程可视化 -->
    <div class="creation-area" v-if="selectedFactory">
      <div class="section-title">创建过程</div>

      <!-- 工厂 -> 产品的箭头 -->
      <div class="creation-flow">
        <div class="selected-factory-display" ref="factoryDisplay">
          <div class="factory-name">{{ factoryNames[selectedFactory] }}</div>
          <div class="factory-method" ref="methodDisplay">
            {{ currentMethod }}
          </div>
        </div>

        <div class="flow-arrow" ref="flowArrow">
          <div class="arrow-line"></div>
          <div class="arrow-particle" ref="particle"></div>
        </div>

        <div class="product-display-area">
          <!-- 正方体产品 -->
          <div
            class="created-product product-cube"
            :class="`product-${selectedFactory}`"
            ref="cubeProduct"
            v-show="showCube"
          >
            <div class="product-label">{{ productLabels[selectedFactory].cube }}</div>
          </div>

          <!-- 球体产品 -->
          <div
            class="created-product product-sphere"
            :class="`product-${selectedFactory}`"
            ref="sphereProduct"
            v-show="showSphere"
          >
            <div class="product-label">{{ productLabels[selectedFactory].sphere }}</div>
          </div>
        </div>
      </div>

      <!-- 代码示例 -->
      <div class="code-example" ref="codeExample">
        <pre>{{ codeText }}</pre>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'
import gsap from 'gsap'

// 状态管理
const selectedFactory = ref(null)
const isAnimating = ref(false)
const currentMethod = ref('')
const showCube = ref(false)
const showSphere = ref(false)

// DOM 引用
const factoryDisplay = ref(null)
const methodDisplay = ref(null)
const flowArrow = ref(null)
const particle = ref(null)
const cubeProduct = ref(null)
const sphereProduct = ref(null)
const codeExample = ref(null)

// 配置数据
const factoryNames = {
  wireframe: '线框工厂',
  solid: '实体工厂',
  textured: '表面工厂',
}

const productLabels = {
  wireframe: {
    cube: '线框正方体',
    sphere: '线框球体',
  },
  solid: {
    cube: '实体正方体',
    sphere: '实体球体',
  },
  textured: {
    cube: '表面正方体',
    sphere: '表面球体',
  },
}

// 代码示例
const codeText = computed(() => {
  if (!selectedFactory.value) return ''

  const factoryClass =
    selectedFactory.value.charAt(0).toUpperCase() + selectedFactory.value.slice(1) + 'Factory'
  const lastProduct = showSphere.value ? 'Sphere' : 'Cube'
  const methodName = lastProduct === 'Sphere' ? 'createSphere()' : 'createCube()'

  return `// 使用${factoryNames[selectedFactory.value]}创建产品
ShapeFactory factory = new ${factoryClass}();
Shape product = factory.${methodName};`
})

// 选择工厂
const selectFactory = (factoryType) => {
  if (isAnimating.value) return

  selectedFactory.value = factoryType
  currentMethod.value = ''
  showCube.value = false
  showSphere.value = false

  // 工厂选择动画
  gsap.fromTo(
    factoryDisplay.value,
    { scale: 0.8, opacity: 0 },
    { scale: 1, opacity: 1, duration: 0.5, ease: 'back.out(1.7)' },
  )
}

// 创建产品动画
const createProduct = async (productType) => {
  if (isAnimating.value) return

  isAnimating.value = true

  // 确定产品引用
  const productRef = productType === 'cube' ? cubeProduct.value : sphereProduct.value
  const showFlag = productType === 'cube' ? showCube : showSphere

  // 隐藏另一个产品
  if (productType === 'cube') {
    showSphere.value = false
  } else {
    showCube.value = false
  }

  // 显示当前产品
  showFlag.value = true

  // 更新方法名
  currentMethod.value = productType === 'cube' ? 'createCube()' : 'createSphere()'

  // 创建动画时间轴
  const tl = gsap.timeline({
    onComplete: () => {
      isAnimating.value = false
    },
  })

  // 1. 方法名闪烁
  tl.fromTo(methodDisplay.value, { opacity: 0, y: 10 }, { opacity: 1, y: 0, duration: 0.3 })

  // 2. 粒子流动
  tl.to(
    particle.value,
    {
      x: 300,
      opacity: [0, 1, 1, 0],
      duration: 1,
      ease: 'power1.inOut',
    },
    '-=0.1',
  )

  // 3. 产品生成
  tl.fromTo(
    productRef,
    { scale: 0, rotation: -180, opacity: 0 },
    {
      scale: 1,
      rotation: 0,
      opacity: 1,
      duration: 0.8,
      ease: 'back.out(1.7)',
    },
    '-=0.5',
  )

  // 4. 产品弹跳
  tl.to(productRef, {
    y: -20,
    duration: 0.3,
    ease: 'power2.out',
  }).to(productRef, {
    y: 0,
    duration: 0.3,
    ease: 'bounce.out',
  })

  // 5. 代码示例淡入
  tl.fromTo(codeExample.value, { opacity: 0, y: 20 }, { opacity: 1, y: 0, duration: 0.4 }, '-=0.5')
}
</script>

<style scoped>
.factory-visual-container {
  font-family: 'Microsoft YaHei', 'Arial', sans-serif;
  padding: 40px 20px;
  background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
  min-height: 100vh;
}

.title {
  font-size: 32px;
  font-weight: bold;
  color: #2c3e50;
  text-align: center;
  margin-bottom: 10px;
}

.subtitle {
  font-size: 16px;
  color: #7f8c8d;
  text-align: center;
  margin-bottom: 40px;
}

.section-title {
  font-size: 20px;
  font-weight: bold;
  color: #34495e;
  margin-bottom: 20px;
  text-align: center;
}

.code-text {
  font-family: 'Courier New', monospace;
  font-size: 12px;
  color: #e74c3c;
  margin-top: 5px;
}

/* 抽象层 */
.abstract-layer {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 40px;
  margin-bottom: 60px;
  padding: 30px;
  background: white;
  border-radius: 12px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.abstract-factory {
  padding: 30px;
  border: 3px solid #3498db;
  border-radius: 12px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  color: white;
  text-align: center;
  min-width: 200px;
}

.abstract-factory .code-text {
  color: #ffeaa7;
}

.abstract-desc {
  font-size: 12px;
  margin-top: 10px;
  opacity: 0.9;
}

.arrow-right {
  font-size: 48px;
  color: #3498db;
}

.abstract-products {
  display: flex;
  gap: 20px;
}

.abstract-product {
  padding: 20px;
  border: 2px solid #95a5a6;
  border-radius: 12px;
  background: white;
  text-align: center;
  min-width: 120px;
}

/* 工厂选择区 */
.factory-selection {
  margin-bottom: 40px;
  padding: 30px;
  background: white;
  border-radius: 12px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.factories {
  display: flex;
  justify-content: center;
  gap: 30px;
  flex-wrap: wrap;
}

.concrete-factory {
  width: 180px;
  padding: 25px;
  border: 3px solid;
  border-radius: 12px;
  text-align: center;
  cursor: pointer;
  transition: all 0.3s;
  background: white;
}

.concrete-factory:hover {
  transform: translateY(-5px);
  box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
}

.concrete-factory.active {
  transform: scale(1.1);
  box-shadow: 0 12px 24px rgba(0, 0, 0, 0.3);
}

.factory-wireframe {
  border-color: #3498db;
  color: #3498db;
}

.factory-wireframe.active {
  background: linear-gradient(135deg, #e6f7ff 0%, #bae7ff 100%);
}

.factory-solid {
  border-color: #e67e22;
  color: #e67e22;
}

.factory-solid.active {
  background: linear-gradient(135deg, #fff7e6 0%, #ffd591 100%);
}

.factory-textured {
  border-color: #27ae60;
  color: #27ae60;
}

.factory-textured.active {
  background: linear-gradient(135deg, #f6ffed 0%, #b7eb8f 100%);
}

.factory-icon {
  font-size: 48px;
  margin-bottom: 10px;
}

/* 产品选择区 */
.product-selection {
  margin-bottom: 40px;
  padding: 30px;
  background: white;
  border-radius: 12px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.product-buttons {
  display: flex;
  justify-content: center;
  gap: 30px;
  flex-wrap: wrap;
}

.product-btn {
  padding: 20px 40px;
  font-size: 18px;
  font-weight: bold;
  border: none;
  border-radius: 12px;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  color: white;
  cursor: pointer;
  transition: all 0.3s;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
  display: flex;
  align-items: center;
  gap: 10px;
}

.product-btn:hover:not(.disabled) {
  transform: translateY(-3px);
  box-shadow: 0 8px 16px rgba(0, 0, 0, 0.2);
}

.product-btn:active:not(.disabled) {
  transform: translateY(-1px);
}

.product-btn.disabled {
  opacity: 0.5;
  cursor: not-allowed;
}

.btn-icon {
  font-size: 24px;
}

/* 创建过程区 */
.creation-area {
  padding: 30px;
  background: white;
  border-radius: 12px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.creation-flow {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 40px;
  margin-bottom: 30px;
  padding: 40px;
  background: #f8f9fa;
  border-radius: 12px;
  min-height: 200px;
}

.selected-factory-display {
  padding: 30px;
  border: 3px solid #3498db;
  border-radius: 12px;
  background: white;
  text-align: center;
  min-width: 180px;
}

.factory-name {
  font-size: 20px;
  font-weight: bold;
  color: #2c3e50;
  margin-bottom: 10px;
}

.factory-method {
  font-family: 'Courier New', monospace;
  font-size: 14px;
  color: #e74c3c;
  font-weight: bold;
  min-height: 20px;
}

.flow-arrow {
  position: relative;
  width: 300px;
  height: 4px;
}

.arrow-line {
  width: 100%;
  height: 4px;
  background: linear-gradient(to right, #3498db, #9b59b6);
  border-radius: 2px;
  position: relative;
}

.arrow-line::after {
  content: '';
  position: absolute;
  right: -10px;
  top: -8px;
  border-width: 10px 0 10px 12px;
  border-style: solid;
  border-color: transparent transparent transparent #9b59b6;
}

.arrow-particle {
  position: absolute;
  left: 0;
  top: -6px;
  width: 16px;
  height: 16px;
  background: #e74c3c;
  border-radius: 50%;
  box-shadow: 0 0 20px #e74c3c;
  opacity: 0;
}

.product-display-area {
  position: relative;
  min-width: 150px;
  min-height: 150px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.created-product {
  width: 120px;
  height: 120px;
  border: 3px solid;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  position: absolute;
  font-weight: bold;
}

.product-cube {
  border-radius: 8px;
}

.product-sphere {
  border-radius: 50%;
}

.product-wireframe {
  border-color: #3498db;
  background: linear-gradient(135deg, #e6f7ff 0%, #bae7ff 100%);
  color: #3498db;
}

.product-solid {
  border-color: #e67e22;
  background: linear-gradient(135deg, #fff7e6 0%, #ffd591 100%);
  color: #e67e22;
}

.product-textured {
  border-color: #27ae60;
  background: linear-gradient(135deg, #f6ffed 0%, #b7eb8f 100%);
  color: #27ae60;
}

.product-label {
  font-size: 14px;
  text-align: center;
  padding: 5px;
}

/* 代码示例 */
.code-example {
  background: #282c34;
  border-radius: 8px;
  padding: 20px;
  overflow-x: auto;
}

.code-example pre {
  color: #abb2bf;
  font-family: 'Courier New', monospace;
  font-size: 14px;
  margin: 0;
  white-space: pre-wrap;
}
</style>
