# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

C-React is a framework that enables building React-based web applications using pure C code. It compiles C to WebAssembly via Emscripten and provides bindings to React's JavaScript API.

**Core Architecture:**
- `c2wasm.c` - Bridge layer between C and WebAssembly/JavaScript (MIT License)
- `react.c` - C bindings for React API (Public Domain)
- Applications include these two files and compile to WebAssembly

## Build Commands

### Compile C to WebAssembly
```bash
emcc app.c -o app.js
```

This generates:
- `app.js` - JavaScript loader/glue code
- `app.wasm` - Compiled WebAssembly binary

### Run Local Development Server
```bash
# Python 3
python3 -m http.server 8080

# Node.js (requires http-server package)
npx http-server -p 8080
```

Then visit `http://localhost:8080`

## Code Architecture

### Entry Point Pattern

Every C-React application follows this structure:

```c
#include "c2wasm.c"
#include "react.c"

ReactRoot root;           // Global root - required for re-rendering
void rootRender();        // Forward declaration

// Your component logic here

void rootRender() {
    ReactComponent app = ReactCreateElement(/* ... */);
    ReactRootRender(root, app);
}

int main() {
    ReactStart();         // MUST be called first
    root = ReactDOMCreateRoot(ReactGetElementById("root"));
    rootRender();
    return 0;
}
```

**Critical Rules:**
1. `ReactStart()` must be the first React function called
2. `ReactRoot root` must be global for event handlers to trigger re-renders
3. `rootRender()` rebuilds and renders the entire UI tree
4. Text must be wrapped: `ReactCreateString("text")` not raw strings

### Event Handler Architecture

C-React provides two approaches:

**Simple Helpers (Recommended):**
- `ReactCreateClickHandler(func)` - Takes `void func()`
- `ReactCreateClickHandlerWithArgs(func, ctx)` - Takes `void func(void*)`
- `ReactCreateInputHandler(func)` - Takes `void func(const char*)`
- `ReactCreateInputHandlerWithArgs(func, ctx)` - Takes `void func(const char*, void*)`

**Advanced:**
- `ReactCreateClojure(callback, args...)` - Takes `c2wasm_js_var callback(c2wasm_js_var args)`
  - Access custom args via `c2wasm_get_array_any_by_index(args, index)`
  - Access browser event via `c2wasm_get_array_any_by_index(c2wasm_arguments, 0)`

### Re-rendering Pattern

State changes trigger re-renders by calling `rootRender()`:

```c
static int counter = 0;

void increment() {
    counter++;
    rootRender();  // Rebuild entire UI with new state
}
```

Unlike React's virtual DOM diffing, C-React rebuilds the full component tree on each render. Keep this in mind for performance.

### Component Structure

Elements are created with variadic macros:

```c
ReactCreateElement(tag, props, ...children)
ReactCreateFragment(...children)  // For grouping without wrapper div
ReactCreateProps(key, value, key, value, ...)  // Variadic key-value pairs
```

**Termination:** All variadic functions use sentinels:
- `ReactCreateElement` uses `-1`
- `ReactCreateProps` uses `NULL` (automatically added by macro)

### JavaScript Interop (c2wasm)

Access browser APIs via c2wasm functions:

```c
c2wasm_js_var args = c2wasm_create_array();
c2wasm_append_array_string(args, "Hello!");
c2wasm_call_object_prop(c2wasm_window, "alert", args);
```

Common c2wasm constants:
- `c2wasm_window` - JavaScript window object
- `c2wasm_document` - document object
- `c2wasm_null`, `c2wasm_undefined` - JS null/undefined
- `c2wasm_arguments` - Function arguments in callbacks

## HTML Integration

Applications require an HTML file with:
1. React and ReactDOM scripts from CDN
2. Compiled `app.js` script
3. A `<div id="root"></div>` mount point

```html
<script src="https://unpkg.com/react@18/umd/react.production.min.js"></script>
<script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js"></script>
<script src="app.js"></script>
<div id="root"></div>
```

## Common Patterns

### Conditional Rendering
```c
ReactComponent maybeShowElement() {
    if (condition) {
        return ReactCreateElement("p", ReactNULL, ReactCreateString("Text"));
    }
    return ReactNULL;  // Renders nothing
}
```

### Styling
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "color", ReactCreateString("red"),
        "fontSize", ReactCreateString("16px")
    )
)
```

### Input Handling
```c
char buffer[100] = {0};

void handleInput(const char *value) {
    strncpy(buffer, value, sizeof(buffer) - 1);
    rootRender();
}

// Use with onChange or onBlur
ReactCreateProps("onChange", ReactCreateInputHandler(handleInput))
```

## Key Differences from JavaScript React

- No JSX - function calls instead
- No hooks (useState, useEffect) - use global C variables
- No virtual DOM optimization - full re-renders
- Manual memory management not required (c2wasm handles JS object lifecycle)
- Event handlers are simpler - no synthetic event objects by default

## Debugging

Check browser console (F12) for:
- JavaScript runtime errors
- WebAssembly compilation issues
- React warnings

Use `printf()` for debug logging (appears in browser console).

## Reference Documentation

See [README.md](README.md) for:
- Complete beginner's guide
- Detailed examples (counter, color changer, text input)
- Event handling deep dive
- Full function reference

The README is structured for teaching beginners but contains comprehensive API documentation.
