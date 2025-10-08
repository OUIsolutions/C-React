# C-React Compact Reference

## Dependencies
Download required files (versions may vary):
- `react.c`: https://github.com/OUIsolutions/C-React/releases/download/0.0.1/react.c
- `c2wasm.c`: https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c

## Build & Run
```bash
emcc app.c -o app.js                    # Generates app.js + app.wasm
python3 -m http.server 8080             # Or: npx http-server -p 8080
```

## Entry Point (Required Structure)
```c
#include "c2wasm.c"  // MIT License - WebAssembly bridge
#include "react.c"   // Public Domain - React bindings

ReactRoot root;      // MUST be global
void rootRender();   // Forward declaration

void rootRender() {
    ReactComponent app = ReactCreateElement(/* ... */);
    ReactRootRender(root, app);
}

int main() {
    ReactStart();    // MUST be first React call
    root = ReactDOMCreateRoot(ReactGetElementById("root"));
    rootRender();
    return 0;
}
```

## Core API

### Element Creation
- `ReactCreateElement(tag, props, ...children)` - Variadic, ends with `-1`
- `ReactCreateFragment(...children)` - No wrapper div, ends with `-1`
- `ReactCreateProps(k, v, k, v, ...)` - Variadic pairs, auto-NULL terminated
- `ReactCreateString("text")` - REQUIRED for text (no raw strings)
- `ReactNULL` - Renders nothing

### Event Handlers (Simple)
- `ReactCreateClickHandler(func)` - `void func()`
- `ReactCreateClickHandlerWithArgs(func, ctx)` - `void func(void*)`
- `ReactCreateInputHandler(func)` - `void func(const char*)`
- `ReactCreateInputHandlerWithArgs(func, ctx)` - `void func(const char*, void*)`

### Event Handlers (Advanced)
- `ReactCreateClojure(callback, ...args)` - `c2wasm_js_var callback(c2wasm_js_var args)`
  - Custom args: `c2wasm_get_array_any_by_index(args, index)`
  - Browser event: `c2wasm_get_array_any_by_index(c2wasm_arguments, 0)`

### Root Management
- `ReactDOMCreateRoot(element)` - Creates root
- `ReactRootRender(root, component)` - Renders component tree
- `ReactGetElementById("id")` - Gets DOM element

## Re-rendering
State changes require calling `rootRender()` - rebuilds entire UI (no virtual DOM diffing)
```c
static int count = 0;
void increment() { count++; rootRender(); }
```

## Patterns

### Conditional Rendering
```c
if (condition) return ReactCreateElement("p", ReactNULL, ReactCreateString("Text"));
return ReactNULL;
```

### Styling
```c
ReactCreateProps("style", ReactCreateProps("color", ReactCreateString("red")))
```

### Input Handling
```c
char buf[100] = {0};
void handleInput(const char *val) { strncpy(buf, val, 99); rootRender(); }
ReactCreateProps("onChange", ReactCreateInputHandler(handleInput))
```

## c2wasm Interop
```c
c2wasm_js_var args = c2wasm_create_array();
c2wasm_append_array_string(args, "Hello!");
c2wasm_call_object_prop(c2wasm_window, "alert", args);
```
**Constants:** `c2wasm_window`, `c2wasm_document`, `c2wasm_null`, `c2wasm_undefined`, `c2wasm_arguments`

## HTML Setup
```html
<script src="https://unpkg.com/react@18/umd/react.production.min.js"></script>
<script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js"></script>
<script src="app.js"></script>
<div id="root"></div>
```

## Key Differences from JS React
- No JSX (function calls) | No hooks (global vars) | No virtual DOM (full re-renders)
- No synthetic events (simple callbacks) | No manual memory mgmt (c2wasm handles lifecycle)

## Debug
- Browser console (F12) for errors/warnings
- `printf()` outputs to console
