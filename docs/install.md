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
curl -L -o react.c https://github.com/OUIsolutions/C-React/releases/download/0.2.0/react.c
curl -L -o c2wasm.c https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c
```
### Step 4: Create a `index.html` file
create a file named `index.html` with the following content:
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>🚀 My First C-React Website!</title>
    
    <!-- Load React library (the magic that makes components work) -->
    <script src="https://unpkg.com/react@18/umd/react.production.min.js" crossorigin></script>
    <script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js" crossorigin></script>
    
    <!-- Load your compiled C code (this is what we just created!) -->
    <script src="app.js"></script>
    
    <!-- Make everything look modern and pretty -->
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            background-color: white;
            border-radius: 10px;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            margin: 0 auto;
        }
        
        button:hover {
            background-color: #0b5ed7 !important;
            transform: translateY(-1px);
            transition: all 0.2s ease;
        }
        
        h1 {
            text-align: center;
        }
        
        p {
            font-size: 18px;
            line-height: 1.6;
        }
    </style>
</head>
<body>
    <!-- This is where your C-React component will appear! -->
    <div id="root"></div>
    
    <!-- Loading message (shows while your C code loads) -->
    <script>
        document.getElementById('root').innerHTML = '🔄 Loading your C-React app...';
    </script>
</body>
</html>
```
### Step 5: Create your C-React App
create a file named `app.c` with the following content:
```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

// Simple click handler - no arguments needed!
void handleClick() {
  c2wasm_js_var args = c2wasm_create_array();
  c2wasm_append_array_string(args, "🎊 Hello from C-React! You clicked a button made with C code!");
  c2wasm_call_object_prop(c2wasm_window, "alert", args);
}

void rootRender() {
  ReactComponent main_component = ReactCreateElement(
    "div",
    ReactCreateProps(
      "className", ReactCreateString("container"),
      "style", ReactCreateProps(
        "padding", ReactCreateString("20px"),
        "maxWidth", ReactCreateString("800px"),
        "margin", ReactCreateString("0 auto")
      )
    ),

    ReactCreateElement("h1",
      ReactCreateProps(
        "style", ReactCreateProps(
          "color", ReactCreateString("#333"),
          "borderBottom", ReactCreateString("2px solid #eee"),
          "paddingBottom", ReactCreateString("10px")
        )
      ),
      ReactCreateString("🎉 Welcome to my react in C")
    ),

    ReactCreateFragment(
      ReactCreateElement("p", ReactNULL,
        ReactCreateString("🔥 This webpage is made with C code!")
      ),

      ReactCreateElement("p", ReactNULL,
        ReactCreateString("✨ Your C code runs super fast in the browser!")
      ),

      ReactCreateElement(
        "button",
        ReactCreateProps(
          "onClick", ReactCreateClickHandler(handleClick),
          "style", ReactCreateProps(
            "padding", ReactCreateString("12px 20px"),
            "backgroundColor", ReactCreateString("#0d6efd"),
            "color", ReactCreateString("white"),
            "border", ReactCreateString("none"),
            "borderRadius", ReactCreateString("5px"),
            "cursor", ReactCreateString("pointer"),
            "fontSize", ReactCreateString("16px"),
            "marginTop", ReactCreateString("20px")
          )
        ),
        ReactCreateString("🚀 Click Me!")
      )
    )
  );
  ReactRootRender(root, main_component);
}

int main() {
  ReactStart();
  root = ReactDOMCreateRoot(ReactGetElementById("root"));
  rootRender();
  return 0;
}
```

### Step 6: Compile your C code to WebAssembly
run the following command to compile your `app.c` file to WebAssembly:
```bash
emcc app.c -o app.js

```

### Step 7: Serve your files
you can use any static file server to serve your files. if you have python installed you ca
n use the following command:
```bash
python3 -m http.server 8000
```