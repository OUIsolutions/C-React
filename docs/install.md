### C-React Installation Guide

### Step 1: Install Emscripten
C-React requires [Emscripten](https://emscripten.org/) on version `4.0.7` or higher.
if you are on linux you can use the [easy_installer](https://github.com/mateusmoutinho/emscripten-easy-install) tutorial:
```bash
curl -L https://github.com/mateusmoutinho/emscripten-easy-install/releases/download/0.1.0/emcc_install.sh | bash -s 4.0.7
```
if you are on mac os just run:
```bash
brew install emscripten
```

### Step 2: Download Dependencies
you need to download the following files:
- [`react.c`](https://github.com/OUIsolutions/C-React/releases/download/0.0.1/react.c): c react bindings
- [`c2wasm.c`](https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c): c to wasm bindings
you can download them using `curl`:
```bash
curl -L -o react.c https://github.com/OUIsolutions/C-React/releases/download/0.0.1/react.c
curl -L -o c2wasm.c https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c
```