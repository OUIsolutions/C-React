# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

C-React is a framework that allows developers to build React web applications using C programming language instead of JavaScript. The C code is compiled to WebAssembly using Emscripten, enabling it to run in web browsers at near-native performance.

## Core Architecture

### Three-Layer System

1. **C2Wasm Layer** (`c2wasm.c`): Low-level bridge between C and JavaScript/WebAssembly. Provides primitives for JavaScript object manipulation, DOM access, and function calls from C.

2. **React Wrapper Layer** (`react.c`): C API wrapper around React.js that mirrors React's component model. Translates C function calls into JavaScript React operations.

3. **Application Layer** (`app.c`): User code that uses the React C API to build components and handle events.

### Key Concepts

- **ReactComponent/ReactElement**: Type aliases for `c2wasm_js_var` - these represent JavaScript React objects
- **ReactRoot**: The React DOM root where components are rendered
- **ReactNULL**: Equivalent to `c2wasm_null`, used when no props are needed
- **ReactFragment**: Empty string pointer that identifies React fragments

## Build and Development Commands

### Compile C to WebAssembly
```bash
emcc app.c -o app.js
```
This generates `app.js` (JavaScript loader) and `app.wasm` (compiled WebAssembly module).

### Run Development Server
```bash
# Using Python 3
python3 -m http.server 8080

# Using Node.js http-server
npx http-server -p 8080
```
Then navigate to `http://localhost:8080`

### View in Browser
Open `index.html` via the local server (direct file:// protocol won't work due to CORS).

## Critical Syntax Rules

### Variadic Function Terminators

**CRITICAL**: All variadic React functions require specific terminators:

- `ReactCreateElement()` and `ReactCreateFragment()`: End with `-1`
- `ReactCreateProps()`: End with `NULL`
- `ReactCreateClojure()`: End with `-1`

Missing terminators will cause segmentation faults or undefined behavior.

### Examples
```c
// Element creation - ends with -1
ReactCreateElement("div", ReactNULL,
    ReactCreateString("content"),
    -1  // REQUIRED
);

// Props creation - ends with NULL
ReactCreateProps(
    "className", ReactCreateString("container"),
    "style", ReactCreateProps(
        "padding", ReactCreateString("20px"),
        NULL  // REQUIRED for nested props
    ),
    NULL  // REQUIRED for outer props
);

// Event handler - ends with -1
ReactCreateClojure(handlerFunction,
    ReactCreateString("arg1"),
    -1  // REQUIRED
);
```

## Component Pattern

### Initialization Sequence
```c
int main() {
    ReactStart();  // MUST be called first - initializes React globals
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactComponent app = createAppComponent();
    ReactRootRender(root, app);
    return 0;
}
```

### Event Handler Pattern
```c
c2wasm_js_var handlerName(c2wasm_js_var args) {
    // Event handler logic
    // args contains the event parameters passed from ReactCreateClojure

    // Re-render pattern for state updates
    ReactRootRender(root, createAppComponent());

    return c2wasm_null;
}
```

### State Management
C-React uses global variables for state (no hooks). To update UI:
1. Modify global state variable
2. Call `ReactRootRender()` again with updated component

## HTML Integration

The `index.html` must include:
1. React 18 UMD bundle from CDN
2. ReactDOM 18 UMD bundle from CDN
3. The compiled `app.js`
4. A `<div id="root">` element

See `index.html` for the complete template.

## Common Pitfalls

1. **Forgetting ReactStart()**: All React operations fail without this initialization
2. **Missing terminators**: Causes crashes or memory corruption
3. **Direct string children**: Must wrap text with `ReactCreateString()`
4. **Props on fragments**: `ReactCreateFragment()` doesn't accept props parameter
5. **CORS issues**: Must use a local web server, cannot open HTML files directly

## File Dependencies

### Required for compilation
- `c2wasm.c`: Downloaded from https://github.com/OUIsolutions/C2Wasm/releases
- `react.c`: Downloaded from https://github.com/mateusmoutinho/C-React/releases

### Build artifacts
- `app.js`: JavaScript loader (generated)
- `app.wasm`: WebAssembly binary (generated)

These libraries must be in the same directory as your source files and included via `#include`.

## Emscripten Setup

Emscripten is required to compile C to WebAssembly. Install via:
- Easy installer: https://github.com/mateusmoutinho/emscripten-easy-install
- Official method: https://emscripten.org/docs/getting_started/downloads.html

Verify installation: `emcc --version`
