# C-React AI-Optimized API Documentation

## CRITICAL_SETUP_REQUIREMENTS
```
MANDATORY_FILES:
- c2wasm.c (DOWNLOAD: https://github.com/OUIsolutions/C2Wasm/releases/download/0.4.0/c2wasm.c)
- react.c (DOWNLOAD: https://github.com/mateusmoutinho/C-React/releases/download/0.0.1/react.c)
COMPILER: emcc (Emscripten)
COMPILATION: emcc app.c -o app.js
```

## INITIALIZATION_SEQUENCE
```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"

int main() {
    ReactStart(); // MANDATORY_FIRST_CALL
    ReactComponent app = /* component_creation */;
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, app);
    return 0;
}
```

## CORE_TYPES
```
ReactComponent = c2wasm_js_var
ReactElement = c2wasm_js_var
ReactRoot = c2wasm_js_var
ReactNULL = c2wasm_null
ReactFragment = "" (const char*, use as tag in ReactCreateElement)
```

## ELEMENT_CREATION_PATTERNS

### BASIC_ELEMENT
```c
ReactCreateElement("tag", props, ...children, -1)
// TERMINATOR: -1 MANDATORY
// props: ReactNULL or ReactCreateProps(...)
// children: ReactCreateString(), ReactCreateNumber(), ReactCreateElement(), etc.
```

### FRAGMENT_CREATION
```c
ReactCreateFragment(...children, -1)
// NO_PROPS_ALLOWED
// TERMINATOR: -1 MANDATORY
```

### PROPS_CREATION
```c
ReactCreateProps(
    "key1", value1,
    "key2", value2,
    ...,
    NULL
)
// TERMINATOR: NULL MANDATORY
// values: ReactCreateString(), ReactCreateNumber(), ReactCreateProps() for nested objects
```

## EVENT_HANDLER_PATTERN
```c
c2wasm_js_var handler_name(c2wasm_js_var args) {
    // handler_logic
    return c2wasm_null;
}

// USAGE:
ReactCreateProps(
    "onClick", ReactCreateClojure(handler_name, ...args, -1)
)
// TERMINATOR: -1 MANDATORY
```

## VALUE_CREATORS
```c
ReactCreateString("text") // for text nodes and string props
ReactCreateNumber(123.45) // for numeric values
ReactCreateClojure(callback, ...args, -1) // for event handlers
```

## DOM_QUERIES
```c
ReactGetElementById("id") // returns c2wasm_js_var
ReactGetElementByClassName("className") // returns c2wasm_js_var
```

## RENDERING_SEQUENCE
```c
ReactRoot root = ReactDOMCreateRoot(dom_element);
ReactRootRender(root, react_component);
```

## STYLE_PROP_PATTERN
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "padding", ReactCreateString("20px"),
        "color", ReactCreateString("#333"),
        "fontSize", ReactCreateString("16px"),
        NULL
    ),
    NULL
)
```

## NESTED_ELEMENTS_PATTERN
```c
ReactCreateElement("div", ReactNULL,
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph")),
    ReactCreateElement("button", 
        ReactCreateProps("onClick", ReactCreateClojure(handler, -1), NULL),
        ReactCreateString("Click")
    ),
    -1
)
```

## CONDITIONAL_RENDERING_PATTERN
```c
ReactComponent conditional_component(int condition) {
    if (condition) {
        return ReactCreateElement("div", ReactNULL, ReactCreateString("True"), -1);
    }
    return ReactCreateElement("div", ReactNULL, ReactCreateString("False"), -1);
}
```

## STATE_UPDATE_PATTERN
```c
c2wasm_js_var state_value = c2wasm_create_long(0);

c2wasm_js_var update_handler(c2wasm_js_var args) {
    // update_state
    state_value = c2wasm_create_long(new_value);
    // re-render
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, create_component_with_new_state());
    return c2wasm_null;
}
```

## HTML_TEMPLATE
```html
<!DOCTYPE html>
<html>
<head>
    <script src="https://unpkg.com/react@18/umd/react.production.min.js"></script>
    <script src="https://unpkg.com/react-dom@18/umd/react-dom.production.min.js"></script>
    <script src="app.js"></script>
</head>
<body>
    <div id="root"></div>
</body>
</html>
```

## COMMON_ERRORS_TO_AVOID
```
ERROR: Missing -1 terminator in ReactCreateElement/ReactCreateFragment/ReactCreateClojure
ERROR: Missing NULL terminator in ReactCreateProps
ERROR: Using props with ReactCreateFragment
ERROR: Not calling ReactStart() before any React operations
ERROR: Using regular strings instead of ReactCreateString() for React text nodes
```

## FUNCTION_SIGNATURES_REFERENCE
```c
void ReactStart()
ReactElement ReactCreateElement(const char *element, ...)
ReactElement ReactCreateFragment(...)
c2wasm_js_var ReactCreateProps(...)
c2wasm_js_var ReactGetElementById(const char *id)
c2wasm_js_var ReactGetElementByClassName(const char *className)
c2wasm_js_var ReactCreateString(const char *string)
c2wasm_js_var ReactCreateClojure(c2wasm_js_var (*callback)(c2wasm_js_var args), ...)
c2wasm_js_var ReactCreateNumber(double number)
ReactRoot ReactDOMCreateRoot(c2wasm_js_var element)