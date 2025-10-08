# C-React Callback Handling Guide

## Overview

C-React provides specialized callback handlers to connect C functions with React event handlers. This guide covers all available callback types and their usage patterns.

## Available Callback Types

C-React provides three main categories of callbacks:

1. **Click Handlers** - Handle button clicks and clickable elements
2. **Input Handlers** - Handle text input changes
3. **Option Handlers** - Handle select/dropdown changes
4. **Custom Closures** - Create advanced custom callbacks

Each category has two variants:
- **Simple version** - No additional context needed
- **WithArgs version** - Pass additional context/state to the handler

## Click Handlers

### ReactCreateClickHandler

Creates a simple click handler for buttons and clickable elements.

**Function Signature:**
```c
c2wasm_js_var ReactCreateClickHandler(void (*click_handler)(void))
```

**Example:**
```c
void handleClick() {
    printf("Button clicked!\n");
    // Update state and re-render
    rootRender();
}

ReactComponent button = ReactCreateElement(
    "button",
    ReactCreateProps(
        "onClick", ReactCreateClickHandler(handleClick)
    ),
    ReactCreateString("Click Me")
);
```

### ReactCreateClickHandlerWithArgs

Creates a click handler that receives custom context data.

**Function Signature:**
```c
c2wasm_js_var ReactCreateClickHandlerWithArgs(
    void (*click_handler)(void *ctx),
    void *ctx
)
```

**Example:**
```c
typedef struct {
    int *counter;
    int increment;
} ButtonContext;

void handleClickWithContext(void *ctx) {
    ButtonContext *data = (ButtonContext *)ctx;
    *(data->counter) += data->increment;
    rootRender();
}

int counter = 0;
ButtonContext ctx = { &counter, 5 };

ReactComponent button = ReactCreateElement(
    "button",
    ReactCreateProps(
        "onClick", ReactCreateClickHandlerWithArgs(handleClickWithContext, &ctx)
    ),
    ReactCreateString("Increment by 5")
);
```

## Input Handlers

### ReactCreateInputHandler

Creates a handler for text input changes. The handler receives the current input value as a string.

**Function Signature:**
```c
c2wasm_js_var ReactCreateInputHandler(
    void (*input_handler)(const char *input_value)
)
```

**Example:**
```c
char username[50] = {0};

void handleInput(const char *input_value) {
    strncpy(username, input_value, sizeof(username) - 1);
    printf("Current input: %s\n", username);
    rootRender();
}

ReactComponent input = ReactCreateElement(
    "input",
    ReactCreateProps(
        "type", ReactCreateString("text"),
        "onChange", ReactCreateInputHandler(handleInput),
        "placeholder", ReactCreateString("Enter username")
    )
);
```

### ReactCreateInputHandlerWithArgs

Creates an input handler that receives both the input value and custom context.

**Function Signature:**
```c
c2wasm_js_var ReactCreateInputHandlerWithArgs(
    void (*input_handler)(const char *input_value, void *ctx),
    void *ctx
)
```

**Example:**
```c
typedef struct {
    char *buffer;
    size_t max_length;
} InputContext;

void handleInputWithContext(const char *input_value, void *ctx) {
    InputContext *data = (InputContext *)ctx;
    strncpy(data->buffer, input_value, data->max_length - 1);
    rootRender();
}

char name_buffer[100] = {0};
InputContext ctx = { name_buffer, sizeof(name_buffer) };

ReactComponent input = ReactCreateElement(
    "input",
    ReactCreateProps(
        "onChange", ReactCreateInputHandlerWithArgs(handleInputWithContext, &ctx)
    )
);
```

## Option Handlers

### ReactCreateOptionHandler

Creates a handler for select/dropdown changes. The handler receives the selected value.

**Function Signature:**
```c
c2wasm_js_var ReactCreateOptionHandler(
    void (*option_handler)(const char *selected_value)
)
```

**Example:**
```c
char selected_color[20] = "red";

void handleColorChange(const char *selected_value) {
    strncpy(selected_color, selected_value, sizeof(selected_color) - 1);
    printf("Selected: %s\n", selected_color);
    rootRender();
}

ReactComponent select = ReactCreateElement(
    "select",
    ReactCreateProps(
        "onChange", ReactCreateOptionHandler(handleColorChange)
    ),
    ReactCreateElement("option",
        ReactCreateProps("value", ReactCreateString("red")),
        ReactCreateString("Red")
    ),
    ReactCreateElement("option",
        ReactCreateProps("value", ReactCreateString("blue")),
        ReactCreateString("Blue")
    ),
    ReactCreateElement("option",
        ReactCreateProps("value", ReactCreateString("green")),
        ReactCreateString("Green")
    )
);
```

### ReactCreateOptionHandlerWithArgs

Creates an option handler that receives both the selected value and custom context.

**Function Signature:**
```c
c2wasm_js_var ReactCreateOptionHandlerWithArgs(
    void (*option_handler)(const char *selected_value, void *ctx),
    void *ctx
)
```

**Example:**
```c
typedef struct {
    char *selection;
    int *selection_count;
} SelectContext;

void handleOptionWithContext(const char *selected_value, void *ctx) {
    SelectContext *data = (SelectContext *)ctx;
    strcpy(data->selection, selected_value);
    (*(data->selection_count))++;
    rootRender();
}

char selection[50] = {0};
int count = 0;
SelectContext ctx = { selection, &count };

ReactComponent select = ReactCreateElement(
    "select",
    ReactCreateProps(
        "onChange", ReactCreateOptionHandlerWithArgs(handleOptionWithContext, &ctx)
    ),
    // ... options
);
```

## Custom Closures (Advanced)

### ReactCreateClojure

For advanced use cases, you can create custom callbacks with full control over arguments and return values.

**Function Signature:**
```c
c2wasm_js_var ReactCreateClojure(
    c2wasm_js_var (*callback)(c2wasm_js_var args),
    ...  // Variable arguments to pass to callback
)
```

**Example:**
```c
c2wasm_js_var customHandler(c2wasm_js_var args) {
    // Access custom arguments
    long user_data = c2wasm_get_array_long_by_index(args, 0);

    // Access browser event
    c2wasm_js_var event = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);

    // Get event properties
    c2wasm_js_var target = c2wasm_get_object_prop_any(event, "target");

    printf("Custom handler called with data: %ld\n", user_data);

    return c2wasm_undefined;
}

ReactComponent element = ReactCreateElement(
    "button",
    ReactCreateProps(
        "onClick", ReactCreateClojure(
            customHandler,
            c2wasm_create_long(42),
            c2wasm_create_string("extra_data")
        )
    ),
    ReactCreateString("Custom Handler")
);
```

## Memory Management

### Important Notes

1. **String Arguments**: Input and option handlers receive strings that are **temporarily allocated**. If you need to store the value beyond the handler's scope, copy it to your own buffer:

```c
// WRONG - pointer will become invalid
const char *stored_value;
void badHandler(const char *input_value) {
    stored_value = input_value;  // Dangling pointer!
}

// CORRECT - copy to your own buffer
char stored_value[100];
void goodHandler(const char *input_value) {
    strncpy(stored_value, input_value, sizeof(stored_value) - 1);
}
```

2. **Context Pointers**: When using `WithArgs` variants, ensure your context remains valid. Use static or global variables, not stack-allocated temporaries:

```c
// WRONG - context on stack will be invalid
void createButton() {
    int local_counter = 0;
    ReactCreateClickHandlerWithArgs(handler, &local_counter);  // BAD!
}

// CORRECT - static or global context
static int global_counter = 0;
void createButton() {
    ReactCreateClickHandlerWithArgs(handler, &global_counter);  // GOOD
}
```

## Common Event Properties

### All Events Have

React events provide these common properties (accessible via custom closures):

- `target` - The DOM element that triggered the event
- `currentTarget` - The element the handler is attached to
- `type` - Event type string (e.g., "click", "change")
- `preventDefault()` - Prevent default browser action
- `stopPropagation()` - Stop event bubbling

### Input/Select Events

- `target.value` - Current value of input/select
- `target.checked` - Checkbox state (boolean)

## Best Practices

### 1. Always Re-render After State Changes

```c
void handleClick() {
    counter++;
    rootRender();  // Update the UI
}
```

### 2. Use Simple Handlers When Possible

Prefer `ReactCreateClickHandler` over `ReactCreateClojure` unless you need custom behavior:

```c
// Good - simple and clear
ReactCreateClickHandler(handleClick)

// Overkill for simple clicks
ReactCreateClojure(complexClickWrapper, ...)
```

### 3. Validate Input

Always validate user input in handlers:

```c
void handleAgeInput(const char *input_value) {
    int age = atoi(input_value);
    if (age >= 0 && age <= 120) {
        user_age = age;
        rootRender();
    }
}
```

### 4. Use Context for Multiple Similar Handlers

Instead of creating separate functions:

```c
typedef struct {
    int *value;
    int delta;
} CounterContext;

void adjustCounter(void *ctx) {
    CounterContext *data = (CounterContext *)ctx;
    *(data->value) += data->delta;
    rootRender();
}

static CounterContext inc_ctx = { &counter, 1 };
static CounterContext dec_ctx = { &counter, -1 };

ReactCreateClickHandlerWithArgs(adjustCounter, &inc_ctx);  // +1
ReactCreateClickHandlerWithArgs(adjustCounter, &dec_ctx);  // -1
```

## Complete Example

Here's a complete example demonstrating all callback types:

```c
#include <stdio.h>
#include <string.h>
#include "c2wasm.c"
#include "react.c"

ReactRoot root;
void rootRender();

// State
static int click_count = 0;
static char user_input[100] = {0};
static char selected_option[50] = "option1";

// Click handler
void handleClick() {
    click_count++;
    rootRender();
}

// Input handler
void handleInput(const char *input_value) {
    strncpy(user_input, input_value, sizeof(user_input) - 1);
    rootRender();
}

// Option handler
void handleSelect(const char *selected_value) {
    strncpy(selected_option, selected_value, sizeof(selected_option) - 1);
    rootRender();
}

void rootRender() {
    char buffer[200];

    ReactComponent app = ReactCreateElement(
        "div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "padding", ReactCreateString("20px")
            )
        ),

        // Click counter
        ReactCreateElement("h2", ReactNULL,
            ReactCreateString("Click Counter")
        ),
        ReactCreateElement("button",
            ReactCreateProps("onClick", ReactCreateClickHandler(handleClick)),
            ReactCreateString("Click Me")
        ),
        sprintf(buffer, "Clicks: %d", click_count),
        ReactCreateElement("p", ReactNULL,
            ReactCreateString(buffer)
        ),

        // Text input
        ReactCreateElement("h2", ReactNULL,
            ReactCreateString("Text Input")
        ),
        ReactCreateElement("input",
            ReactCreateProps(
                "type", ReactCreateString("text"),
                "onChange", ReactCreateInputHandler(handleInput),
                "placeholder", ReactCreateString("Type something...")
            )
        ),
        sprintf(buffer, "You typed: %s", user_input),
        ReactCreateElement("p", ReactNULL,
            ReactCreateString(buffer)
        ),

        // Select dropdown
        ReactCreateElement("h2", ReactNULL,
            ReactCreateString("Select Option")
        ),
        ReactCreateElement("select",
            ReactCreateProps(
                "onChange", ReactCreateOptionHandler(handleSelect),
                "value", ReactCreateString(selected_option)
            ),
            ReactCreateElement("option",
                ReactCreateProps("value", ReactCreateString("option1")),
                ReactCreateString("Option 1")
            ),
            ReactCreateElement("option",
                ReactCreateProps("value", ReactCreateString("option2")),
                ReactCreateString("Option 2")
            ),
            ReactCreateElement("option",
                ReactCreateProps("value", ReactCreateString("option3")),
                ReactCreateString("Option 3")
            )
        ),
        sprintf(buffer, "Selected: %s", selected_option),
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

## Troubleshooting

### Handler Not Firing

**Problem:** Click/input handler doesn't execute.

**Solution:**
- Verify `ReactStart()` is called before creating the root
- Ensure the handler is passed to the correct prop (`onClick`, `onChange`, etc.)
- Check browser console for JavaScript errors

### Segmentation Fault

**Problem:** Crash when handler executes.

**Solution:**
- Check that context pointers are valid (not stack-allocated in a different scope)
- Ensure string buffers are large enough
- Verify `rootRender()` is not called during initialization before root is created

### Input Value Not Updating

**Problem:** Typed text doesn't appear or disappears.

**Solution:**
- Make sure you're copying the input value to your own buffer
- Call `rootRender()` after updating state
- For controlled inputs, set the `value` prop to reflect current state

## Summary

C-React provides six main callback creator functions:

| Function | Use Case | Handler Signature |
|----------|----------|-------------------|
| `ReactCreateClickHandler` | Simple button clicks | `void func()` |
| `ReactCreateClickHandlerWithArgs` | Clicks with context | `void func(void *ctx)` |
| `ReactCreateInputHandler` | Text input changes | `void func(const char *value)` |
| `ReactCreateInputHandlerWithArgs` | Input with context | `void func(const char *value, void *ctx)` |
| `ReactCreateOptionHandler` | Select changes | `void func(const char *value)` |
| `ReactCreateOptionHandlerWithArgs` | Select with context | `void func(const char *value, void *ctx)` |
| `ReactCreateClojure` | Custom callbacks | `c2wasm_js_var func(c2wasm_js_var args)` |

Choose the simplest handler that meets your needs, and always remember to call `rootRender()` to update the UI after state changes.
