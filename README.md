# C-React
React Port to C Language using c2wasm and ecmescripten


## 🔧 Installation

### Prerequisites

- **Emscripten SDK**: C2Wasm requires the Emscripten SDK to compile C code to WebAssembly.

### Step 1: Install Emscripten

Install [Emscripten](https://github.com/emscripten-core/emsdk) by following the official documentation.

Alternatively, you can use our [quick install setup](https://github.com/mateusmoutinho/emscripten-easy-install) for a simplified installation process.

### Step 2: Add [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.4.0/c2wasm.c) to Your Project

Download the  [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.4.0/c2wasm.c) from [c2wasm Repo](https://github.com/OUIsolutions/C2Wasm) on version **0.4.0** to your project, and save it in your project directory.

### Step 3: Add [react.c](https://github.com/mateusmoutinho/C-React/releases/download/0.0.1/react.c) to your project 
Download the [react.c](https://github.com/mateusmoutinho/C-React/releases/download/0.0.1/react.c) from this repository to your project, and save it in your project directory.



## 🏁 Getting Started

### Step 1: Create Your C File

Create a `test.c` file in the same directory where you saved `c2wasm.c`:

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"


c2wasm_js_var my_allert(c2wasm_js_var args){
  c2wasm_call_object_prop(c2wasm_window,"alert",args);
  return c2wasm_null;
}
ReactComponent create_my_component(){
  return ReactCreateElement(
    "div",
    ReactCreateProps(
      "className",ReactCreateString("container")
    ),
    ReactCreateElement("h1",ReactNULL, ReactCreateString("First Menssage")),
    ReactCreateFragment(
      ReactCreateElement("p",ReactNULL,ReactCreateString("Second Menssage")),
      ReactCreateElement(
        "button",
        ReactCreateProps(
          "onClick",ReactCreateClojure(
            my_allert,
            ReactCreateString("hello from C")
          ),
          "className",ReactCreateString("btn btn-primary")
        ),
        ReactCreateString("Click me")
      )
    )
  );
}
int main() {
  // Initialize React Lib
  ReactStart();
 
  ReactComponent my_div = create_my_component();
  ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
  ReactRootRender(root,my_div);
  return 0;
}
```

### Step 2: Compile Your C Code

Compile the C code to JavaScript using Emscripten:

```bash
emcc test.c -o test.js
```

### Step 3: Create an HTML File

Create an HTML file to test your code:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <script src="https://unpkg.com/react@18/umd/react.development.js" crossorigin></script>
    <script src="https://unpkg.com/react-dom@18/umd/react-dom.development.js" crossorigin></script>
    
    <script src="test.js"></script>
    <style>
        .container{
            color:red;
        }
        .btn-primary{
            background-color:blue;
            color:white;
        }

    </style>
</head>
<body>
    <div id="root"></div>
    
</body>
</html>
```

### Step 4: Set Up a Local Server

WebAssembly requires a server to work. You can use one of these methods:

#### Using Python

```bash
python3 -m http.server 8080
```

Then navigate to [http://localhost:8080/test.html](http://localhost:8080/test.html)

#### Using Yahr (Alternative)

If you don't have Python, you can use [Yahr](https://github.com/OUIsolutions/yahr):

```bash
yahr
```
