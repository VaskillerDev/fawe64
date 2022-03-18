#FAWE64

![alt text](promo.png)

##Требования:
* [NodeJs](https://nodejs.org/en/)
* [WASI SDK](https://github.com/WebAssembly/wasi-sdk)
* [Chocolatey](https://chocolatey.org/install)
* [Make (Windows)](https://community.chocolatey.org/packages/make)
* [Wasm4](https://www.npmjs.com/package/wasm4)

##Как запускать:

```shell
git clone https://github.com/VaskillerDev/fawe64.git
cd fawe64
make
npm install -g wasm4
npx w4 watch ./build/cart.wasm
```

##Полезные ссылки:
[Установка WASM4](https://wasm4.org/docs/getting-started/setup)