# Element Handling in C-React

## Overview

Element handling in C-React allows you to create, manipulate, and work with HTML elements using C code. This guide covers how to create elements, set their properties, style them, and work with different types of content.

---

## Table of Contents

1. [Creating Basic Elements](#creating-basic-elements)
2. [Element Properties](#element-properties)
3. [Styling Elements](#styling-elements)
4. [Working with Children](#working-with-children)
5. [Fragments](#fragments)
6. [Special Element Types](#special-element-types)
7. [Finding Elements](#finding-elements)
8. [Best Practices](#best-practices)

---

## Creating Basic Elements

### ReactCreateElement()

The fundamental function for creating HTML elements in C-React.

**Function Signature:**
```c
ReactElement ReactCreateElement(const char *tag, c2wasm_js_var props, ...)
```

**Parameters:**
- `tag`: The HTML tag name (e.g., "div", "button", "h1")
- `props`: Element properties created with `ReactCreateProps()`, or `ReactNULL` for no properties
- `...`: Variable number of child elements (optional)

**Basic Example:**
```c
// Create a simple div with text
ReactComponent my_div = ReactCreateElement(
    "div",
    ReactNULL,  // No properties
    ReactCreateString("Hello, World!")
);
```

**Example with Properties:**
```c
// Create a button with properties
ReactComponent my_button = ReactCreateElement(
    "button",
    ReactCreateProps(
        "className", ReactCreateString("my-button"),
        "id", ReactCreateString("submit-btn")
    ),
    ReactCreateString("Click Me!")
);
```

**Example with Multiple Children:**
```c
// Create a div with multiple children
ReactComponent container = ReactCreateElement(
    "div",
    ReactNULL,
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph text")),
    ReactCreateElement("button", ReactNULL, ReactCreateString("Button"))
);
```

---

## Element Properties

### ReactCreateProps()

Creates a JavaScript object containing element properties (attributes, event handlers, etc.).

**Function Signature:**
```c
c2wasm_js_var ReactCreateProps(const char *key, c2wasm_js_var value, ...)
```

**Parameters:**
- Takes pairs of key-value arguments
- Keys are always strings (`const char*`)
- Values can be various types (strings, numbers, functions, nested props)
- Must be terminated with proper pairs (always even number of arguments after function name)

**Common Properties:**

#### 1. className - CSS Classes
```c
ReactCreateElement("div",
    ReactCreateProps(
        "className", ReactCreateString("container primary-container")
    ),
    ReactCreateString("Content")
)
```

#### 2. id - Element Identifier
```c
ReactCreateElement("div",
    ReactCreateProps(
        "id", ReactCreateString("main-content")
    ),
    ReactCreateString("Content")
)
```

#### 3. href - Links
```c
ReactCreateElement("a",
    ReactCreateProps(
        "href", ReactCreateString("https://github.com"),
        "target", ReactCreateString("_blank")
    ),
    ReactCreateString("Visit GitHub")
)
```

#### 4. src - Images and Media
```c
ReactCreateElement("img",
    ReactCreateProps(
        "src", ReactCreateString("logo.png"),
        "alt", ReactCreateString("Company Logo")
    )
)
```

#### 5. type - Input Types
```c
ReactCreateElement("input",
    ReactCreateProps(
        "type", ReactCreateString("text"),
        "placeholder", ReactCreateString("Enter your name")
    )
)
```

#### 6. disabled - Disable Elements
```c
ReactCreateElement("button",
    ReactCreateProps(
        "disabled", ReactCreateBool(true)
    ),
    ReactCreateString("Submit")
)
```

**Multiple Properties Example:**
```c
ReactCreateElement("input",
    ReactCreateProps(
        "type", ReactCreateString("email"),
        "id", ReactCreateString("user-email"),
        "className", ReactCreateString("form-input"),
        "placeholder", ReactCreateString("Enter email"),
        "required", ReactCreateBool(true)
    )
)
```

---

## Styling Elements

### Inline Styles with the `style` Property

The `style` property accepts a nested `ReactCreateProps()` with CSS properties.

**Basic Styling:**
```c
ReactCreateElement("div",
    ReactCreateProps(
        "style", ReactCreateProps(
            "color", ReactCreateString("blue"),
            "fontSize", ReactCreateString("20px"),
            "padding", ReactCreateString("10px")
        )
    ),
    ReactCreateString("Styled text")
)
```

**Common CSS Properties in C-React:**

#### Colors and Backgrounds
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "color", ReactCreateString("#333"),
        "backgroundColor", ReactCreateString("#f0f0f0"),
        "borderColor", ReactCreateString("red")
    )
)
```

#### Sizing and Spacing
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "width", ReactCreateString("300px"),
        "height", ReactCreateString("200px"),
        "margin", ReactCreateString("10px 20px"),
        "padding", ReactCreateString("15px")
    )
)
```

#### Layout and Positioning
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "display", ReactCreateString("flex"),
        "flexDirection", ReactCreateString("column"),
        "justifyContent", ReactCreateString("center"),
        "alignItems", ReactCreateString("center"),
        "position", ReactCreateString("relative")
    )
)
```

#### Typography
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "fontSize", ReactCreateString("18px"),
        "fontFamily", ReactCreateString("Arial, sans-serif"),
        "fontWeight", ReactCreateString("bold"),
        "textAlign", ReactCreateString("center"),
        "lineHeight", ReactCreateString("1.6")
    )
)
```

#### Borders and Shadows
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "border", ReactCreateString("1px solid #ddd"),
        "borderRadius", ReactCreateString("8px"),
        "boxShadow", ReactCreateString("0 2px 4px rgba(0,0,0,0.1)")
    )
)
```

**Complete Styling Example:**
```c
ReactCreateElement("div",
    ReactCreateProps(
        "className", ReactCreateString("card"),
        "style", ReactCreateProps(
            "backgroundColor", ReactCreateString("white"),
            "padding", ReactCreateString("20px"),
            "borderRadius", ReactCreateString("10px"),
            "boxShadow", ReactCreateString("0 4px 6px rgba(0,0,0,0.1)"),
            "maxWidth", ReactCreateString("500px"),
            "margin", ReactCreateString("20px auto")
        )
    ),
    ReactCreateElement("h2",
        ReactCreateProps(
            "style", ReactCreateProps(
                "color", ReactCreateString("#333"),
                "marginTop", ReactCreateString("0")
            )
        ),
        ReactCreateString("Card Title")
    ),
    ReactCreateElement("p",
        ReactCreateProps(
            "style", ReactCreateProps(
                "color", ReactCreateString("#666"),
                "lineHeight", ReactCreateString("1.6")
            )
        ),
        ReactCreateString("Card content goes here.")
    )
)
```

**Important Notes on CSS Property Names:**
- Use camelCase for multi-word properties (e.g., `backgroundColor` not `background-color`)
- Always use strings for values (e.g., `"20px"`, `"red"`, `"center"`)
- Include units where needed (`px`, `%`, `em`, etc.)

---

## Working with Children

### Adding Child Elements

Elements can contain multiple children of different types:

**Text Children:**
```c
ReactCreateElement("p", ReactNULL,
    ReactCreateString("This is text content.")
)
```

**Element Children:**
```c
ReactCreateElement("div", ReactNULL,
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph"))
)
```

**Mixed Children:**
```c
ReactCreateElement("div", ReactNULL,
    ReactCreateString("Before link "),
    ReactCreateElement("a",
        ReactCreateProps("href", ReactCreateString("#")),
        ReactCreateString("Click here")
    ),
    ReactCreateString(" after link")
)
```

**Nested Structure Example:**
```c
ReactCreateElement("div",
    ReactCreateProps("className", ReactCreateString("page")),
    
    // Header section
    ReactCreateElement("header", ReactNULL,
        ReactCreateElement("h1", ReactNULL, ReactCreateString("My Website")),
        ReactCreateElement("nav", ReactNULL,
            ReactCreateElement("a", ReactCreateProps("href", ReactCreateString("/")),
                ReactCreateString("Home")
            ),
            ReactCreateElement("a", ReactCreateProps("href", ReactCreateString("/about")),
                ReactCreateString("About")
            )
        )
    ),
    
    // Main content
    ReactCreateElement("main", ReactNULL,
        ReactCreateElement("p", ReactNULL, ReactCreateString("Main content here"))
    ),
    
    // Footer
    ReactCreateElement("footer", ReactNULL,
        ReactCreateString("© 2025 My Website")
    )
)
```

---

## Fragments

### ReactCreateFragment()

Creates a React Fragment - a way to group multiple elements without adding extra DOM nodes.

**Function Signature:**
```c
ReactElement ReactCreateFragment(...)
```

**Why Use Fragments?**
- Group elements without adding unnecessary `<div>` wrappers
- Keep DOM structure cleaner
- Better for semantic HTML

**Basic Example:**
```c
ReactCreateFragment(
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph 1")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph 2"))
)
```

**Comparing Fragment vs Div:**

```c
// Without Fragment (adds extra div)
ReactCreateElement("div", ReactNULL,
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Text"))
)
// Result: <div><h1>Title</h1><p>Text</p></div>

// With Fragment (no extra wrapper)
ReactCreateFragment(
    ReactCreateElement("h1", ReactNULL, ReactCreateString("Title")),
    ReactCreateElement("p", ReactNULL, ReactCreateString("Text"))
)
// Result: <h1>Title</h1><p>Text</p>
```

**Practical Use Case:**
```c
void rootRender() {
    ReactComponent app = ReactCreateElement("div",
        ReactCreateProps("className", ReactCreateString("container")),
        
        // Use Fragment to group related elements
        ReactCreateFragment(
            ReactCreateElement("h2", ReactNULL, ReactCreateString("Section Title")),
            ReactCreateElement("p", ReactNULL, ReactCreateString("Description")),
            ReactCreateElement("button", ReactNULL, ReactCreateString("Action"))
        ),
        
        // Another group
        ReactCreateFragment(
            ReactCreateElement("h2", ReactNULL, ReactCreateString("Another Section")),
            ReactCreateElement("p", ReactNULL, ReactCreateString("More content"))
        )
    );
    
    ReactRootRender(root, app);
}
```

---

## Special Element Types

### Creating Different Content Types

#### ReactCreateString()
Creates text content for elements.

```c
c2wasm_js_var ReactCreateString(const char *text)
```

**Example:**
```c
ReactCreateElement("p", ReactNULL,
    ReactCreateString("This is a paragraph.")
)
```

#### ReactCreateNumber()
Creates numeric content (though usually converted to string).

```c
c2wasm_js_var ReactCreateNumber(double number)
```

**Example:**
```c
char score_text[50];
sprintf(score_text, "Score: %d", score);

ReactCreateElement("p", ReactNULL,
    ReactCreateString(score_text)
)
```

#### ReactCreateBool()
Creates boolean values (for properties like `disabled`, `checked`).

```c
c2wasm_js_var ReactCreateBool(bool value)
```

**Example:**
```c
ReactCreateElement("input",
    ReactCreateProps(
        "type", ReactCreateString("checkbox"),
        "checked", ReactCreateBool(is_checked),
        "disabled", ReactCreateBool(is_disabled)
    )
)
```

### Common HTML Elements

#### Headings
```c
ReactCreateElement("h1", ReactNULL, ReactCreateString("Main Title"))
ReactCreateElement("h2", ReactNULL, ReactCreateString("Subtitle"))
ReactCreateElement("h3", ReactNULL, ReactCreateString("Section Title"))
// h4, h5, h6 also available
```

#### Text Elements
```c
ReactCreateElement("p", ReactNULL, ReactCreateString("Paragraph"))
ReactCreateElement("span", ReactNULL, ReactCreateString("Inline text"))
ReactCreateElement("strong", ReactNULL, ReactCreateString("Bold"))
ReactCreateElement("em", ReactNULL, ReactCreateString("Italic"))
```

#### Containers
```c
ReactCreateElement("div", ReactNULL, /* children */)
ReactCreateElement("section", ReactNULL, /* children */)
ReactCreateElement("article", ReactNULL, /* children */)
ReactCreateElement("header", ReactNULL, /* children */)
ReactCreateElement("footer", ReactNULL, /* children */)
ReactCreateElement("main", ReactNULL, /* children */)
```

#### Lists
```c
ReactCreateElement("ul", ReactNULL,
    ReactCreateElement("li", ReactNULL, ReactCreateString("Item 1")),
    ReactCreateElement("li", ReactNULL, ReactCreateString("Item 2")),
    ReactCreateElement("li", ReactNULL, ReactCreateString("Item 3"))
)

ReactCreateElement("ol", ReactNULL,
    ReactCreateElement("li", ReactNULL, ReactCreateString("First")),
    ReactCreateElement("li", ReactNULL, ReactCreateString("Second")),
    ReactCreateElement("li", ReactNULL, ReactCreateString("Third"))
)
```

#### Forms
```c
ReactCreateElement("form", ReactNULL,
    ReactCreateElement("input",
        ReactCreateProps(
            "type", ReactCreateString("text"),
            "placeholder", ReactCreateString("Name")
        )
    ),
    ReactCreateElement("textarea",
        ReactCreateProps("placeholder", ReactCreateString("Message"))
    ),
    ReactCreateElement("button",
        ReactCreateProps("type", ReactCreateString("submit")),
        ReactCreateString("Submit")
    )
)
```

#### Media
```c
// Image
ReactCreateElement("img",
    ReactCreateProps(
        "src", ReactCreateString("photo.jpg"),
        "alt", ReactCreateString("Description")
    )
)

// Video
ReactCreateElement("video",
    ReactCreateProps(
        "src", ReactCreateString("video.mp4"),
        "controls", ReactCreateBool(true)
    )
)
```

---

## Finding Elements

### ReactGetElementById()

Finds a DOM element by its ID attribute.

**Function Signature:**
```c
c2wasm_js_var ReactGetElementById(const char *id)
```

**Example:**
```c
// Find the root element
c2wasm_js_var root_element = ReactGetElementById("root");

// Create a React root from it
ReactRoot root = ReactDOMCreateRoot(root_element);
```

**HTML Setup:**
```html
<div id="root"></div>
<div id="sidebar"></div>
```

**C Code:**
```c
c2wasm_js_var root_el = ReactGetElementById("root");
c2wasm_js_var sidebar_el = ReactGetElementById("sidebar");
```

### ReactGetElementByClassName()

Finds DOM elements by their class name.

**Function Signature:**
```c
c2wasm_js_var ReactGetElementByClassName(const char *className)
```

**Example:**
```c
// Get element with class "container"
c2wasm_js_var container = ReactGetElementByClassName("container");
```

**Note:** Returns the first element matching the class name, or a collection depending on implementation.

---

## Best Practices

### 1. Use Semantic HTML

Choose appropriate HTML elements for their purpose:

```c
// Good - semantic structure
ReactCreateElement("article", ReactNULL,
    ReactCreateElement("header", ReactNULL,
        ReactCreateElement("h1", ReactNULL, ReactCreateString("Article Title"))
    ),
    ReactCreateElement("main", ReactNULL,
        ReactCreateElement("p", ReactNULL, ReactCreateString("Content"))
    )
)

// Bad - everything is divs
ReactCreateElement("div", ReactNULL,
    ReactCreateElement("div", ReactNULL,
        ReactCreateElement("div", ReactNULL, ReactCreateString("Article Title"))
    ),
    ReactCreateElement("div", ReactNULL,
        ReactCreateElement("div", ReactNULL, ReactCreateString("Content"))
    )
)
```

### 2. Keep Element Creation Organized

Break complex UI into helper functions:

```c
ReactComponent create_header() {
    return ReactCreateElement("header",
        ReactCreateProps("className", ReactCreateString("app-header")),
        ReactCreateElement("h1", ReactNULL, ReactCreateString("My App"))
    );
}

ReactComponent create_content() {
    return ReactCreateElement("main",
        ReactCreateProps("className", ReactCreateString("content")),
        ReactCreateElement("p", ReactNULL, ReactCreateString("Main content"))
    );
}

void rootRender() {
    ReactComponent app = ReactCreateElement("div", ReactNULL,
        create_header(),
        create_content()
    );
    ReactRootRender(root, app);
}
```

### 3. Use Constants for Repeated Values

```c
#define PRIMARY_COLOR "#0d6efd"
#define BUTTON_PADDING "12px 20px"
#define BORDER_RADIUS "8px"

ReactComponent styled_button(const char *text) {
    return ReactCreateElement("button",
        ReactCreateProps(
            "style", ReactCreateProps(
                "backgroundColor", ReactCreateString(PRIMARY_COLOR),
                "padding", ReactCreateString(BUTTON_PADDING),
                "borderRadius", ReactCreateString(BORDER_RADIUS),
                "border", ReactCreateString("none"),
                "color", ReactCreateString("white")
            )
        ),
        ReactCreateString(text)
    );
}
```

### 4. Combine CSS Classes and Inline Styles

```c
// Use className for shared styles, style for specific overrides
ReactCreateElement("div",
    ReactCreateProps(
        "className", ReactCreateString("card"),  // Shared CSS
        "style", ReactCreateProps(
            "marginTop", ReactCreateString("20px")  // Specific override
        )
    ),
    ReactCreateString("Content")
)
```

### 5. Use Fragments to Avoid Unnecessary Wrappers

```c
// Good - no extra div
ReactComponent render_items() {
    return ReactCreateFragment(
        ReactCreateElement("li", ReactNULL, ReactCreateString("Item 1")),
        ReactCreateElement("li", ReactNULL, ReactCreateString("Item 2"))
    );
}

// Bad - unnecessary div wrapper
ReactComponent render_items_bad() {
    return ReactCreateElement("div", ReactNULL,
        ReactCreateElement("li", ReactNULL, ReactCreateString("Item 1")),
        ReactCreateElement("li", ReactNULL, ReactCreateString("Item 2"))
    );
}
```

### 6. Always Use ReactNULL for No Properties

```c
// Correct
ReactCreateElement("div", ReactNULL, ReactCreateString("Text"))

// Wrong - passing NULL directly may cause issues
ReactCreateElement("div", NULL, ReactCreateString("Text"))
```

### 7. Group Related Properties

```c
// Create a helper for common property sets
c2wasm_js_var create_card_props() {
    return ReactCreateProps(
        "className", ReactCreateString("card"),
        "style", ReactCreateProps(
            "padding", ReactCreateString("20px"),
            "borderRadius", ReactCreateString("10px"),
            "boxShadow", ReactCreateString("0 2px 4px rgba(0,0,0,0.1)")
        )
    );
}

// Use it
ReactCreateElement("div", create_card_props(),
    ReactCreateString("Card content")
)
```

---

## Summary

Element handling in C-React provides a powerful way to build web UIs using C:

- **`ReactCreateElement()`** creates HTML elements
- **`ReactCreateProps()`** sets element properties and styles
- **`ReactCreateFragment()`** groups elements without extra DOM nodes
- **Element finding functions** help locate existing DOM elements
- **Semantic HTML** improves code readability and accessibility
- **Helper functions** keep code organized and maintainable

For event handling (clicks, inputs, etc.), see the event handling documentation.

For complete examples and advanced patterns, check the main [README.md](../README.md).
