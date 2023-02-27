# Node.js C++ addon

> [官方文档](https://nodejs.org/api/addons.html#:~:text=Addons%20are%20dynamically-linked%20shared%20objects%20written%20in%20C%2B%2B.,provide%20an%20interface%20between%20JavaScript%20and%20C%2FC%2B%2B%20libraries.)
>
> [官方示例](https://github.com/nodejs/node-addon-examples)

## 基本概念

- C++ addon 允许开发者调用 v8、libuv、Node.js 内部库、Node.js 外部依赖（如 OpenSSL）开发能够使用 require 动态加载的模块。
- nan：屏蔽了 v8 的版本差异。
- Node-API：提供了 ABI 的能力，即屏蔽了 Node.js 版本差异，满足指定 ABI 接口标准的二进制能够用于多种不同的 Node.js 版本。
- node-addon-api：进一步封装 C++ 类，简化开发。

## 代码示例

- 比较 JS 与 C++ addon 冒泡排序的性能。
- JS 实现及比较逻辑参见 [test.js](./test.js)
- C++ addon 实现参见 [sort.cc](./sort.cc)
  - 参考了 [这篇文章](https://medium.com/@denismalykhin/n-api-add-on-and-js-code-performance-comparison-9a69c6282fa6)，但可能存在的问题是：在 `Napi::Array` 与 `unsigned int*` 之间做了两次数据拷贝以实现对 `Napi::Array` 的元素移动，这样是否会导致 **性能下降**？
- 比较结果：确有提升，但不明显，最多为 20%。

| 元素个数 | JS 耗时 | C++ addon 耗时 |
| :------: | :-----: | :------------: |
|   1000   |    3    |       1        |
|  10000   |   100   |       80       |
|  100000  |  12000  |     10000      |
|  500000  | 310000  |     270000     |

## 如何运行

首先，参考官方文档搭建 node-addon-api 环境。

```bash
npm install -g node-gyp
npm install
node-gyp configure build
```

将 `build/Release/sort.node` 拷贝至根目录。

```bash
node test.js
```