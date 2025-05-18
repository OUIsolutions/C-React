# C-React

<div align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language: C">
  <img src="https://img.shields.io/badge/framework-React-61dafb.svg" alt="Framework: React">
  <img src="https://img.shields.io/badge/license-Unlicense-green.svg" alt="License: Unlicense">
</div>

<p align="center">A lightweight, high-performance bridge enabling React development in C using WebAssembly</p>

---

## 📖 Overview

C-React provides a complete binding layer that allows you to write React applications using pure C. It leverages the power of WebAssembly through C2Wasm and Emscripten to compile your C code into high-performance web applications.

Key benefits include:

- **Familiar C syntax** for frontend development
- **Near-native performance** through WebAssembly compilation
- **Small bundle sizes** compared to typical JavaScript frameworks
- **Direct access to React APIs** with C-style function calls

## 🔧 Installation

### Prerequisites

- **Emscripten SDK**: Required to compile C code to WebAssembly.

### Step 1: Install Emscripten

Follow the [official Emscripten installation guide](https://emscripten.org/docs/getting_started/downloads.html).

For a simplified installation experience, you can use our [emscripten-easy-install](https://github.com/mateusmoutinho/emscripten-easy-install) helper tool.

### Step 2: Add Required Dependencies

1. Download [c2wasm.c (v0.4.0)](https://github.com/OUIsolutions/C2Wasm/releases/download/0.4.0/c2wasm.c) to your project directory
2. Download [react.c (v0.0.1)](https://github.com/mateusmoutinho/C-React/releases/download/0.0.1/react.c) to your project directory

## 🏁 Getting Started

### Step 1: Create Your First Component

Create a file named `app.c` with the following content:

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"

// Handler for button clicks
c2wasm_js_var handleClick(c2wasm_js_var args) {
  c2wasm_call_object_prop(c2wasm_window, "alert", args);
  return c2wasm_null;
}

// Create a simple component
ReactComponent createAppComponent() {
  return ReactCreateElement(
    "div", 
    ReactCreateProps(
      "className", ReactCreateString("container"),
      "style", ReactCreateProps(
        "padding", ReactCreateString("20px"),
        "maxWidth", ReactCreateString("800px"),
        "margin", ReactCreateString("0 auto")
      )
    ),
    // Header
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
    
    // Content
    ReactCreateFragment(
      ReactCreateElement("p", ReactNULL, 
        ReactCreateString("This page is rendered using React components written in C!")
      ),
      
      ReactCreateElement("p", ReactNULL, 
        ReactCreateString("WebAssembly enables C code to run directly in the browser with near-native performance.")
      ),
      
      ReactCreateElement(
        "button",
        ReactCreateProps(
          "onClick", ReactCreateClojure(
            handleClick,
            ReactCreateString("Hello from C-React!")
          ),
          "className", ReactCreateString("btn btn-primary"),
          "style", ReactCreateProps(
            "padding", ReactCreateString("10px 15px"),
            "backgroundColor", ReactCreateString("#0d6efd"),
            "color", ReactCreateString("white"),
            "border", ReactCreateString("none"),
            "borderRadius", ReactCreateString("4px"),
            "cursor", ReactCreateString("pointer"),
            "fontSize", ReactCreateString("16px"),
            "marginTop", ReactCreateString("15px")
          )
        ),
        ReactCreateString("Click Me")
      )
    )
  );
}

int main() {
  // Initialize React
  ReactStart();
  
  // Create our component
  ReactComponent app = createAppComponent();
  
  // Mount to DOM
  ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
  ReactRootRender(root, app);
  
  return 0;
}
```

### Step 2: Compile Your Code

Compile the C code to WebAssembly using Emscripten:

```bash
emcc app.c -o app.js
```

For optimized production builds, add optimization flags:

```bash
emcc app.c -O3 -o app.js
```

### Step 3: Create an HTML File

Create an `index.html` file to load your application:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>C-React Application</title>
    
    <!-- Load React -->
    <script src="https://unpkg.com/react@18/umd/react.production.min.js" crossorigin></script>
    <script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js" crossorigin></script>
    
    <!-- Load your compiled application -->
    <script src="app.js"></script>
    
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            line-height: 1.6;
        }
        
        .container {
            color: #333;
            background-color: #f9f9f9;
            border-radius: 8px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
        
        .btn-primary:hover {
            background-color: #0b5ed7 !important;
        }
    </style>
</head>
<body>
    <div id="root"></div>
</body>
</html>
```

### Step 4: Run Your Application

WebAssembly requires a server to function correctly. Here are two methods:

#### Using Python

```bash
python3 -m http.server 8080
```

Then navigate to [http://localhost:8080](http://localhost:8080)

#### Using Node.js with http-server

Install the package:

```bash
npm install -g http-server
```

Run the server:

```bash
http-server -p 8080
```

#### Using Yahr (Zero-config alternative)

```bash
yahr
```

## 📚 API Reference

C-React provides a comprehensive set of bindings to React's most essential functions:

### Core Functions

- `ReactStart()`: Initialize the React library
- `ReactCreateElement(tag, props, ...children)`: Create a React element
- `ReactCreateFragment(...children)`: Create a React fragment
- `ReactCreateProps(key, value, ...)`: Create element properties
- `ReactCreateString(text)`: Create a React string node
- `ReactCreateNumber(value)`: Create a numeric node

### DOM Operations

- `ReactGetElementById(id)`: Get a DOM element by ID
- `ReactGetElementByClassName(className)`: Get DOM elements by class name
- `ReactDOMCreateRoot(element)`: Create a React root
- `ReactRootRender(root, element)`: Render a React element to the DOM

### Event Handling

- `ReactCreateClojure(callback, ...args)`: Create an event handler

## 🔍 Advanced Usage

### Managing State

Here's how to create a simple counter component with state:

```c
c2wasm_js_var counter = 0;

c2wasm_js_var incrementCounter(c2wasm_js_var args) {
  counter = c2wasm_create_long(c2wasm_get_object_prop_long(counter, "value") + 1);
  
  ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
  ReactRootRender(root, createCounterComponent());
  
  return c2wasm_null;
}

ReactComponent createCounterComponent() {
  return ReactCreateElement(
    "div",
    ReactNULL,
    ReactCreateElement("h2", ReactNULL, 
      ReactCreateString("Counter: ")
    ),
    ReactCreateElement("p", ReactNULL, 
      ReactCreateNumber(c2wasm_get_object_prop_long(counter, "value"))
    ),
    ReactCreateElement(
      "button",
      ReactCreateProps(
        "onClick", ReactCreateClojure(incrementCounter, ReactNULL)
      ),
      ReactCreateString("Increment")
    )
  );
}
```

### Conditional Rendering

```c
ReactComponent renderContent(int isLoggedIn) {
  if (isLoggedIn) {
    return ReactCreateElement(
      "div",
      ReactNULL,
      ReactCreateElement("h2", ReactNULL, ReactCreateString("Welcome back!")),
      ReactCreateElement("p", ReactNULL, ReactCreateString("You are logged in."))
    );
  } else {
    return ReactCreateElement(
      "div",
      ReactNULL,
      ReactCreateElement("h2", ReactNULL, ReactCreateString("Please log in")),
      ReactCreateElement(
        "button",
        ReactCreateProps("onClick", ReactCreateClojure(handleLogin, ReactNULL)),
        ReactCreateString("Login")
      )
    );
  }
}
```

## 📝 License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
