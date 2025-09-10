<template>
  <div class="about">
    <h1>This is an about page</h1>
    <p>
      Welcome to the personal web application of PengCheng Luo. This site showcases various projects
      and technical skills.
    </p>
    <h2>部署到 Cloudflare Pages 教程</h2>
    <div class="about-section">
      <h3>项目背景</h3>
      <p>
        该项目已经使用 GitHub Pages 托管了，由于在前者过程中必须在 vite.config.ts 的 defineConfig
        内添加代码行：
      </p>
      <pre><code>base: '/PersonalWeb/',</code></pre>
      <p>
        导致远程构建输出除了 index.html 在子文件夹 dist/PersonalWeb/，直接部署到 Cloudflare
        导致页面元素无法访问。
      </p>
    </div>
    <div class="about-section">
      <h3>Cloudflare Pages 导入现有 Git 仓库</h3>
      <p>在 Cloudflare Pages 选择导入现有 Git 存储库。</p>
    </div>
    <div class="about-section">
      <h3>添加 wrangler.toml 文件</h3>
      <p>在项目根目录添加 <code>wrangler.toml</code> 文件。</p>
    </div>
    <div class="about-section">
      <h3>添加 Cloudflare 专用构建命令</h3>
      <p>
        在 <code>package.json</code> 的 scripts 代码块添加一个新的用于 Cloudflare 的 build:cf 命令：
      </p>
      <pre><code>"build:cf": "vite build && mkdir -p dist/PersonalWeb && mv dist/assets dist/PersonalWeb/ && mv dist/index.html dist/PersonalWeb/",</code></pre>
    </div>
    <div class="about-section">
      <h3>Cloudflare Pages 配置参数</h3>
      <p>原始默认：</p>
      <pre><code>
        构建命令：
        npm run build
        构建输出目录：
        /dist</code></pre>
      <p>需要改为：</p>
      <pre><code>
        构建命令：
        npm run build:cf
        构建输出目录：
        /dist
      </code></pre>
    </div>
  </div>
</template>

<style>
@media (min-width: 1024px) {
  .about {
    background: #fff;
    padding: 2rem;
    border-radius: 12px;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
    max-width: 900px;
    margin: 2rem auto;
  }
  .about h2 {
    font-size: 2rem;
    font-weight: bold;
    margin-bottom: 2rem;
    color: #409eff;
    text-align: center;
  }
  .about-section {
    margin-bottom: 2rem;
  }
  .about-section h3 {
    font-size: 1.2rem;
    color: #67c23a;
    margin-bottom: 0.5rem;
  }
  pre {
    background: #f6f8fa;
    padding: 0.8em 1em;
    border-radius: 6px;
    font-size: 1em;
    overflow-x: auto;
  }
  code {
    font-family: 'Fira Mono', 'Consolas', 'Menlo', monospace;
    color: #222;
  }
}
</style>
