# C-React Installation Guide

## Step 1: Install Emscripten
C-React requires [Emscripten](https://emscripten.org/) version `4.0.7` or higher.

If you are on Linux, you can use the [easy_installer](https://github.com/mateusmoutinho/emscripten-easy-install) tutorial:
```bash
curl -L https://github.com/mateusmoutinho/emscripten-easy-install/releases/download/0.1.0/emcc_install.sh | bash -s 4.0.7
```

If you are on macOS, run:
```bash
brew install emscripten
```

## Step 2: Download Dependencies

You need to download the following files:
- [`react.c`](https://github.com/OUIsolutions/C-React/releases/download/0.0.1/react.c): C React bindings
- [`c2wasm.c`](https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c): C to WebAssembly bindings

You can download them using `curl`:
```bash
curl -L -o react.c https://github.com/OUIsolutions/C-React/releases/download/0.2.0/react.c
curl -L -o c2wasm.c https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c
```

## Step 3: Create an `index.html` File

Create a file named `index.html` with the following content:
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My First C-React Website</title>
    
    <!-- Load React library -->
    <script src="https://unpkg.com/react@18/umd/react.production.min.js" crossorigin></script>
    <script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js" crossorigin></script>
    
    <!-- Load compiled C code -->
    <script src="app.js"></script>
    
    <!-- Basic styling -->
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
    <!-- Root element for C-React component -->
    <div id="root"></div>
    
    <!-- Loading message -->
    <script>
        document.getElementById('root').innerHTML = 'Loading C-React application...';
    </script>
</body>
</html>
```

## Step 4: Create Your C-React Application

Create a file named `app.c` with the following content:
```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

// Click handler function
void handleClick() {
  c2wasm_js_var args = c2wasm_create_array();
  c2wasm_append_array_string(args, "Hello from C-React! You clicked a button made with C code.");
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
      ReactCreateString("Welcome to C-React")
    ),

    ReactCreateFragment(
      ReactCreateElement("p", ReactNULL,
        ReactCreateString("This webpage is built with C code compiled to WebAssembly.")
      ),

      ReactCreateElement("p", ReactNULL,
        ReactCreateString("Your C code runs efficiently in the browser.")
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
        ReactCreateString("Click Me")
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

## Step 5: Compile Your C Code to WebAssembly

Run the following command to compile your `app.c` file to WebAssembly:
```bash
emcc app.c -o app.js
```

## Step 6: Serve Your Files

You can use any static file server to serve your files. If you have Python installed, you can use the following command:
```bash
python3 -m http.server 8000
```