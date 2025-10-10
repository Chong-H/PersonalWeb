<template>
  <div class="project-info">
    <h2>常用工具与资源推荐</h2>
    <p>
      This page collects some commonly used online tools and resources for easy access during
      learning, development, and daily use.
    </p>

    <h3>在线工具网站</h3>
    <ul>
      <li>
        <a href="https://plantuml.com/zh/" target="_blank" rel="noopener">PlantUML 在线工具</a
        >：支持使用代码进行 UML 图的在线绘制，简化软件工程文档工作。
      </li>
      <li>
        <a href="https://www.runoob.com/" target="_blank" rel="noopener">菜鸟教程</a
        >：涵盖与CS,SE,AI,Web等相关的各种编程语言和技术的入门教程。
      </li>
      <li>
        <a href="https://www.sqlpub.com/" target="_blank" rel="noopener"
          >SQLPUB,免费的云数据库SaaS平台</a
        >：提供免费云数据库服务，Pass（Platform as a Server）。
      </li>
      <li>
        <a href="https://www.cloudflare-cn.com/enterprise/" target="_blank" rel="noopener"
          >Cloudflare</a
        >：提供免费全球webPage托管服务，worker提供全球代理功能，http转发。
      </li>
      <li>
        <a href="https://www.pythonanywhere.com/user/chonghe/" target="_blank" rel="noopener"
          >PythonAnywhere</a
        >：提供免费在线Python编程环境，支持一键部署flask Web应用，内含不可外链的DB。
      </li>
      <li>
        <a href="https://www.iconfont.cn/" target="_blank" rel="noopener">阿里巴巴矢量图标库</a
        >：丰富的免费矢量图标资源，支持自定义下载。
      </li>
      <li>
        <a href="https://element-plus.org/zh-CN/" target="_blank" rel="noopener">Element Plus</a
        >：基于 Vue 3 的组件库，提供丰富的 UI 组件和设计规范。
      </li>
      <li>
        <a href="https://vercel.com/" target="_blank" rel="noopener">Vercel</a
        >：提供NextJs全栈框架的云平台，支持全栈网站和Serverless函数的部署。
      </li>
      <li>
        <a href="https://dash.domain.digitalplat.org/" target="_blank" rel="noopener">digitalplat</a
        >：提供免费域名（可于mainland访问）。
      </li>
      <!-- 可继续补充更多工具网站 -->
    </ul>

    <h3>免责声明</h3>
    <p>
      本页面仅收录部分常用工具与资源，所有内容仅供学习与交流使用。本站不承担任何法律风险或责任，若涉及侵权请及时联系我删除相关链接或内容。
    </p>
  </div>
</template>

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
.project-info ul {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.project-info ul {
  margin-left: 1.2em;
  margin-bottom: 1.2em;
}
.project-info a {
  color: #409eff;
  text-decoration: underline;
}
</style>
