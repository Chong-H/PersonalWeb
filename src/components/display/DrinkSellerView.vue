<template>
  <div class="project-info">
    <h2>课设项目：饮料贩卖机</h2>
    <h3>项目简介</h3>
    <p>
      本课设实现了一个简易饮料贩卖机，支持投币、购买、找零与状态清零功能。<br />
      使用 Verilog 进行硬件逻辑设计，并通过 ModelSim 仿真验证系统功能。
    </p>

    <h3>我的主要工作</h3>
    <ul>
      <li>负责 ModelSim 仿真代码编写与测试，验证核心功能：</li>
      <li>投币逻辑（1 元、5 角）</li>
      <li>购买操作</li>
      <li>找零功能</li>
      <li>编写 Testbench，对不同投币情况进行激励输入，并观测输出波形</li>
      <li>通过仿真，验证了设计逻辑与硬件电路一致</li>
    </ul>

    <h3>系统总体设计方案</h3>
    <p>
      <strong>功能描述：</strong><br />
      1. 售卖一种饮料，每盒售价 1.5 元，按下 Key1 购买。<br />
      2. 投币器接受 1 元和 5 角硬币，Key2 表示投五角，Key3 表示投一元。<br />
      3. 具有找零功能，只找零 5 角。购买后数码管显示找零数，LED0 灯亮。<br />
      4. LED1 表示饮料成功售出，LED0 表示找零成功。<br />
      5. 数码管用二进制显示投币总额和找零值。<br />
      6. Key5 可清零状态。
    </p>
    <p>
      <strong>开发与调试：</strong><br />
      共用三天时间，两天实验室完成代码编写和开发板功能实现，第三天完成报告和系统介绍。
    </p>

    <h3>核心 Verilog 代码（部分/由组员田同学完成）</h3>
    <CollapsibleCodeBlock :code="verilogCode" :previewLines="8" />

    <h3>ModelSim 仿真示例（由我负责写代码）</h3>
    <p>
      <strong>测试 1：</strong>投 4 个 5 角（2 元）购买<br />
      投币显示总额：2 元，购买成功，输出饮料 + 找零 0.5 元<br />
      ModelSim 波形显示：total_coin_display = 0100，change_display = 0001
    </p>
    <CollapsibleCodeBlock :code="testbench1" :previewLines="8" />
    <img class="image" src="@/assets/wave1.png" alt="波形图1" />
    <p>
      <strong>分析波形和其在测试视频代表的意思：</strong><br />
      1. 输入信号 <code>coin_1</code> 产生 4 个脉冲，代表投 5 角硬币四次。<br />
      2. 然后 <code>buy_button</code> 产生一个脉冲信号，代表点击购买键。<br />
      3. 在 <code>coin_1</code> 产生投币信号脉冲时，<code>total_coin_display</code>
      根据投币的信号改变，代表投币总额，并在开发板显示出来：开发板数码管前 4
      位灯的亮灭情况是“灭亮灭灭”，对应 <code>0100</code>，即总投币 2 元。<br />
      4. 在 <code>buy_button</code> 产生购买信号脉冲时，输出信号 <code>drink_dispensed</code> 和
      <code>change_dispensed</code> 由 0 到 1，提示顾客取走零钱和饮料。<br />
      5. 在 <code>buy_button</code> 产生购买信号脉冲时，<code>change_display</code>
      值改变，根据投币总额（4*5角=2元）和饮料单价 1.5 元，找零 5 角，开发板数码管后 4
      位灯的亮灭情况是“灭灭灭亮”，对应 <code>0001</code>，即十进制 1，即找零一个 5 角。
    </p>
    <p>
      <strong>测试 2：</strong>投 3 个 1 元（3 元）购买<br />
      投币显示总额：3 元，购买成功，输出饮料 + 找零 1.5 元<br />
      ModelSim 波形显示：total_coin_display = 0110，change_display = 0011
    </p>
    <CollapsibleCodeBlock :code="testbench2" :previewLines="8" />
    <img class="image" src="@/assets/wave2.png" alt="波形图2" />
    <p>
      <strong>分析波形和其在测试视频代表的意思：</strong><br />
      1. 输入信号 <code>coin_2</code> 产生 3 个脉冲，代表投一元硬币 3 次。<br />
      2. 然后 <code>buy_button</code> 产生一个脉冲信号，代表点击购买键。<br />
      3. 在 <code>coin_2</code> 产生投币信号脉冲时，<code>total_coin_display</code>
      根据投币的信号改变，代表投币总额，并在开发板显示出来：开发板数码管前 4
      位灯的亮灭情况是“灭亮亮灭”，对应 <code>0110</code>，即总投币 3 元。<br />
      4. 在 <code>buy_button</code> 产生购买信号脉冲时，输出信号 <code>drink_dispensed</code> 和
      <code>change_dispensed</code> 由 0 到 1，提示顾客取走零钱和饮料。<br />
      5. 在 <code>buy_button</code> 产生购买信号脉冲时，<code>change_display</code>
      值改变，根据投币总额（3*1元=3元）和饮料单价 1.5 元，找 1.5 元，即三个 5 角，开发板数码管后 4
      位灯的亮灭情况是“灭灭亮亮”，对应 <code>0011</code>，即十进制 3，即找零 3 个 5 角硬币。
    </p>

    <h3>技术收获</h3>
    <ul>
      <li>学习了如何用 Testbench 激励信号驱动仿真</li>
      <li>熟悉了有限状态机 (FSM) 在硬件系统中的验证流程</li>
      <li>掌握了 Verilog 与仿真工具 ModelSim 的结合使用</li>
    </ul>

    <h3>系统特点与说明</h3>
    <ul>
      <li>系统功能齐全，满足饮料自动贩卖的全部操作过程，实验结果符合预期</li>
      <li>支持状态清零，方便下一个用户继续购买</li>
      <li>LED 灯和数码管直观显示系统状态</li>
      <li>存在问题：数码管界面无法用十进制显示投币总额和找零值</li>
    </ul>

    <h3>部分电路图与引脚分配表</h3>
    <CollapsibleCodeBlock :code="pinTable" :previewLines="8" />

    <h3>调试与测试流程</h3>
    <ol>
      <li>分析代码逻辑，检查错误</li>
      <li>编译通过后运行仿真</li>
      <li>发现问题并修正代码</li>
      <li>重新运行和仿真，得到正确波形</li>
    </ol>
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
import verilogCode from '@/assets/codes/drinkSeller/verilogCode.v?raw'

import testbench1 from '@/assets/codes/drinkSeller/testbench1.v?raw'
import testbench2 from '@/assets/codes/drinkSeller/testbench2.v?raw'

const pinTable = `
信号名         主板器件    PIN
clk            CLK0        PIN_88
reset          Key4        PIN_32
coin_1         Key2        PIN_30
coin_2         Key3        PIN_33
buy_button     Key1        PIN_31
drink_dispensed LED0       PIN_46
change_dispensed LED1      PIN_50
change_display[3] SEG3     PIN_125
change_display[2] SEG2     PIN_115
change_display[1] SEG1     PIN_126
change_display[0] SEG0     PIN_119
total_coin_display[3] SEG7 PIN_120
total_coin_display[2] SEG6 PIN_113
total_coin_display[1] SEG5 PIN_121
total_coin_display[0] SEG4 PIN_114
`
</script>

<style scoped>
.image {
  max-width: 100%;
  height: auto;
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
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
</style>
