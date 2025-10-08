<div align="center">

# C-React
![C Logo](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
[![GitHub Release](https://img.shields.io/github/release/OUIsolutions/C-React.svg?style=for-the-badge)](https://github.com/OUIsolutions/C-React/releases)
[![License](https://img.shields.io/badge/License-Public%20Domain-green.svg?style=for-the-badge)](https://github.com/OUIsolutions/C-React/blob/main/LICENSE)
![Status](https://img.shields.io/badge/Status-Stable-brightgreen?style=for-the-badge)
![Platforms](https://img.shields.io/badge/Platforms-WebAssembly-lightgrey?style=for-the-badge)

</div>

---

### Overview

C-React is a framework that enables building React-based web applications using pure C code. It compiles to WebAssembly via Emscripten and provides intuitive bindings to React's JavaScript API:

1. **Write C code with React-like components**
2. **Compile to WebAssembly with Emscripten**
3. **Run React applications in the browser**

This framework is designed for developers who need to:
- Build web UIs with C code compiled to WebAssembly
- Leverage React's component model from native C
- Create high-performance browser applications
- Integrate existing C codebases with modern web frontends

### Key Features

- **React Integration** - Full C bindings for React 18 API
- **WebAssembly Compilation** - Compile C directly to browser-compatible WASM
- **Event Handling** - Simple callbacks for clicks, inputs, and custom events
- **Component System** - Create reusable UI components in pure C
- **Zero JavaScript Required** - Write entire applications in C
- **Browser APIs Access** - Direct access to DOM and window objects via c2wasm


### Getting Started

Want to build your first C-React application? Follow the [Installation Guide](docs/install.md) for step-by-step instructions, including creating an HTML template and compiling your first component.

---

## Releases

|  **File**                                                                                                           | **What is**                                |
|---------------------------------------------------------------------------------------------------------------------|-----------------------------------------------|
|[react.c](https://github.com/OUIsolutions/C-React/releases/download/0.2.0/react.c) | C-React framework bindings  |

**Dependencies:**
- [c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.10.0/c2wasm.c) - C to WebAssembly bridge library (required)

## Documentation

### Installation and Setup
| **Document**                                                    | **Description**                                         |
|-----------------------------------------------------------------|---------------------------------------------------------|
| [Installation Guide](docs/install.md)              | Complete setup instructions for all platforms                       |

### API Reference
| **Document**                                                    | **Description**                                         |
|-----------------------------------------------------------------|---------------------------------------------------------|
| [Element Handling](docs/element_handle.md)              | Creating and manipulating HTML elements                       |
| [Callback Handling](docs/callback_handle.md)                           | Event handlers, clicks, inputs, and custom callbacks                               |

### Additional Resources
| **Document**                                                    | **Description**                                         |
|-----------------------------------------------------------------|---------------------------------------------------------|
| [CLAUDE.md](CLAUDE.md)      | Project architecture and development guide for AI assistants                          |

## Quick Example

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"

ReactRoot root;
void rootRender();

static int counter = 0;

void handleClick() {
    counter++;
    rootRender();
}

void rootRender() {
    char buffer[50];
    sprintf(buffer, "Count: %d", counter);

    ReactComponent app = ReactCreateElement(
        "div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "padding", ReactCreateString("20px")
            )
        ),
        ReactCreateElement("h1", ReactNULL,
            ReactCreateString("C-React Counter")
        ),
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClickHandler(handleClick)
            ),
            ReactCreateString("Increment")
        ),
        ReactCreateElement("p", ReactNULL,
            ReactCreateString(buffer)
        )
    );

    ReactRootRender(root, app);
}

int main() {
    ReactStart();
    root = ReactDOMCreateRoot(ReactGetElementById("root"));
    rootRender();
    return 0;
}
```

Compile with:
```bash
emcc app.c -o app.js
```

##  License

This project is licensed under the Public Domain - see the [LICENSE](LICENSE) file for details.

The c2wasm dependency is licensed under the MIT License.

---
