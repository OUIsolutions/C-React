# C-React: React in C for Complete Beginners

<div align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language: C">
  <img src="https://img.shields.io/badge/framework-React-61dafb.svg" alt="Framework: React">
  <img src="https://img.shields.io/badge/license-Unlicense-green.svg" alt="License: Unlicense">
</div>

<p align="center">✨ Write websites like Facebook and Netflix using the C programming language! ✨</p>

---

## 🤔 What is C-React?

**Never programmed for the web before? No problem!**

C-React lets you build websites using the **C programming language** instead of JavaScript. If you know how to write `printf("Hello World");` in C, you can learn to make websites!

### Why is this cool?
- 🚀 **Super fast websites** - Your C code runs almost as fast as native programs
- 📦 **Small file sizes** - Your website loads quickly for users
- 💪 **Use C skills for web** - No need to learn JavaScript, HTML, or CSS deeply
- 🎯 **Perfect for beginners** - Start with simple examples and grow

### What you'll build
By the end of this guide, you'll have a working website with buttons, text, and interactivity - all written in C!

## 🎓 For AI Developers & Advanced Users

📋 **Quick Reference**: Check out [`aidoc.md`](./aidoc.md) for a complete API reference optimized for AI assistance and rapid development. It contains all function signatures, common patterns, and troubleshooting tips in a structured format.

## �️ What You Need to Get Started

**Don't worry - we'll walk through everything step by step!**

### What you need on your computer:
1. **A computer** (Windows, Mac, or Linux)
2. **Basic C knowledge** (know what `int main()` means)
3. **A text editor** (VS Code, Notepad++, or even Notepad)
4. **Internet connection** (to download tools)

### What we'll install:
- **Emscripten**: A magical tool that turns your C code into website code
- **Two special files**: `c2wasm.c` and `react.c` (we'll download these)

---

## 📚 Step 1: Install Emscripten (The Magic Converter)

**What is Emscripten?** It's a program that takes your C code and converts it into code that web browsers can understand.

### Easy Installation (Recommended for Beginners):

1. **Download the easy installer:**
   - Go to: https://github.com/mateusmoutinho/emscripten-easy-install
   - Follow the simple instructions there

### Manual Installation (If you're adventurous):

1. **Visit the official guide:**
   - Go to: https://emscripten.org/docs/getting_started/downloads.html
   - Follow their step-by-step instructions

### How to know it worked:
Open your terminal/command prompt and type:
```bash
emcc --version
```
If you see version numbers, you're ready! 🎉

---

## 📥 Step 2: Download the Special Files

You need two magic files that make C-React work:

### File 1: c2wasm.c
1. **Right-click this link and save:** [Download c2wasm.c](https://github.com/OUIsolutions/C2Wasm/releases/download/0.4.0/c2wasm.c)
2. **Save it to your project folder** (create a new folder called `my-first-website`)

### File 2: react.c  
1. **Right-click this link and save:** [Download react.c](https://github.com/mateusmoutinho/C-React/releases/download/0.0.1/react.c)
2. **Save it to the same folder** as c2wasm.c

**Your folder should now have:**
```
my-first-website/
├── c2wasm.c
└── react.c
```

---

## 🚀 Step 3: Your First Website in C!

**Let's create a simple website with a button that shows an alert!**

### Create your first file: `app.c`

Create a new file called `app.c` in your folder and copy this code:

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

**🤓 What does this code do?**
- Creates a webpage with a title, some text, and a button
- When you click the button, it shows an alert message
- All the styling makes it look modern and pretty

### Understanding the Key Parts:

1. **`#include` lines**: Import the special files we downloaded
2. **`ReactRoot root`**: Global variable to store the React root (needed for re-rendering)
3. **`void handleClick()`**: Simple function that runs when button is clicked - no complex arguments!
4. **`ReactCreateClickHandler(handleClick)`**: Converts your C function into a button click handler
5. **`rootRender` function**: Builds and renders our webpage structure
6. **`main` function**: The starting point that initializes React and creates the root

### 🎯 Notice the Simple Pattern:

Instead of complex event handling, we use **`ReactCreateClickHandler()`** which:
- Takes a simple `void functionName()` with no parameters
- Automatically handles all the browser event plumbing
- Makes your code clean and easy to read!


---

## ⚡ Step 4: Convert C Code to Website Code

**Now we'll use Emscripten to convert your C code into something browsers understand!**

### Open your terminal/command prompt:
- **Windows**: Press `Windows key + R`, type `cmd`, press Enter
- **Mac**: Press `Cmd + Space`, type `terminal`, press Enter  
- **Linux**: Press `Ctrl + Alt + T`

### Navigate to your project folder:
```bash
cd path/to/your/my-first-website
```
*(Replace "path/to/your/" with the actual path where you saved your files)*

### Convert your C code:
```bash
emcc app.c -o app.js
```

**What just happened?**
- `emcc` is the Emscripten compiler
- `app.c` is your C code file
- `-o app.js` means "output a file called app.js"

**If it worked**, you should see new files in your folder:
```
my-first-website/
├── app.c          (your C code)
├── app.js          (generated - JavaScript version)
├── app.wasm        (generated - the fast WebAssembly code)
├── c2wasm.c        (magic file #1)
└── react.c         (magic file #2)
```

---

## 🌐 Step 5: Create the Webpage Container

**Your C code needs an HTML page to live in!**

Create a file called `index.html` in the same folder and copy this:

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

**🤓 What does this HTML do?**
1. **Loads React**: Downloads the React library from the internet
2. **Loads your C code**: Includes the `app.js` file we just created
3. **Creates a container**: The `<div id="root">` is where your C code will put the website content
4. **Makes it pretty**: CSS styling to make everything look modern

---

## 🎉 Step 6: See Your Website!

**Almost there! Let's see your C code running in a web browser!**

### Why you need a local server:
Web browsers are picky about security. They won't run WebAssembly files directly from your hard drive - you need a "local server" (don't worry, it's easier than it sounds!).

### Option 1: Using Python (Easiest if you have Python)

**Check if you have Python:**
```bash
python --version
```
or
```bash
python3 --version
```

**If you have Python, run:**
```bash
python -m http.server 8080
```
or
```bash
python3 -m http.server 8080
```

### Option 2: Using Node.js

**If you have Node.js installed:**
```bash
# Install a simple server tool
npm install -g http-server

# Run the server
http-server -p 8080
```

### Option 3: Using any other local server
Any local web server will work! Just make sure it serves from your project folder.

### Open your website:
1. **Start your server** using one of the methods above
2. **Open your web browser**
3. **Go to**: `http://localhost:8080`
4. **🎉 You should see your website!**

### What you should see:
- A nice-looking webpage with a title
- Some text explaining what you built
- A blue button that says "🚀 Click Me!"
- When you click the button, an alert pops up!

---

## 🐛 Troubleshooting (When Things Go Wrong)

**Don't panic! Here are solutions to common problems:**

### "emcc: command not found"
**Problem**: Emscripten isn't installed properly
**Solution**: Go back to Step 1 and reinstall Emscripten

### "No such file or directory: c2wasm.c or react.c"  
**Problem**: The magic files aren't in the right place
**Solution**: Make sure `c2wasm.c` and `react.c` are in the same folder as your `app.c`

### "Failed to load app.js"
**Problem**: You need to run a local server
**Solution**: Make sure you're using `http://localhost:8080` and not opening the HTML file directly

### Website shows but clicking does nothing
**Problem**: JavaScript console might have errors
**Solution**: 
1. Press `F12` in your browser
2. Look at the "Console" tab for error messages
3. Check that all files are in the correct locations

### Need more help?
**Check [`aidoc.md`](./aidoc.md)** for technical details and common error solutions!

---

## 📖 Learning More: Key C-React Concepts

**Now that you have a working website, let's understand how it works!**

### 🧱 Basic Building Blocks

**1. ReactStart()** - Always call this first!
```c
ReactStart(); // This must be the first React function you call
```

**2. ReactCreateElement()** - Creates webpage elements
```c
// Pattern: ReactCreateElement("tag", properties, children...)
ReactCreateElement("div", ReactNULL,
    ReactCreateString("Hello World!")
)
```

**3. ReactCreateString()** - Creates text
```c
ReactCreateString("This text will appear on the webpage")
```

**4. ReactCreateProps()** - Sets element properties
```c
ReactCreateProps(
    "style", ReactCreateProps(
        "color", ReactCreateString("red"),
        "fontSize", ReactCreateString("20px")
    )
)
```

### 🎯 Important Rules to Remember:

1. **Use the rootRender pattern:**
   - Store `ReactRoot root` as a global variable
   - Create a `void rootRender()` function that builds and renders your UI
   - Call `rootRender()` from event handlers to update the UI

2. **Always call `ReactStart()` first:**
   ```c
   int main() {
       ReactStart(); // Must be first!
       root = ReactDOMCreateRoot(ReactGetElementById("root"));
       rootRender();
   }
   ```

3. **Text must be wrapped:**
   ```c
   // ❌ Wrong:
   ReactCreateElement("p", ReactNULL, "Hello");

   // ✅ Correct:
   ReactCreateElement("p", ReactNULL, ReactCreateString("Hello"));
   ```

### 🎨 Common HTML Elements You Can Use:

```c
// Headers
ReactCreateElement("h1", ReactNULL, ReactCreateString("Big Title"));
ReactCreateElement("h2", ReactNULL, ReactCreateString("Smaller Title"));

// Paragraphs
ReactCreateElement("p", ReactNULL, ReactCreateString("Some text"));

// Buttons
ReactCreateElement("button",
    ReactCreateProps("onClick", some_function),
    ReactCreateString("Click me!")
);

// Containers
ReactCreateElement("div", ReactNULL, /* other elements */);

// Links
ReactCreateElement("a",
    ReactCreateProps("href", ReactCreateString("https://google.com")),
    ReactCreateString("Visit Google")
);
```

---

## 🔥 Cool Examples to Try

### Example 1: Simple Counter

**What it does**: A button that counts how many times you click it

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

// Global variable to store the count
static int counter = 0;

// Simple function that runs when button is clicked - no complex arguments!
void incrementCounter() {
    counter++;  // Add 1 to counter
    rootRender();  // Re-render with new counter value
}

// Create and render the counter webpage
void rootRender() {
    ReactComponent main_component = ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "textAlign", ReactCreateString("center"),
                "padding", ReactCreateString("50px"),
                "fontFamily", ReactCreateString("Arial, sans-serif")
            )
        ),

        ReactCreateElement("h1", ReactNULL,
            ReactCreateString("🔢 Simple Counter")
        ),

        ReactCreateElement("p",
            ReactCreateProps(
                "style", ReactCreateProps(
                    "fontSize", ReactCreateString("24px"),
                    "margin", ReactCreateString("20px")
                )
            ),
            ReactCreateString("Count: "),
            ReactCreateNumber(counter)  // Show the current count
        ),

        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClickHandler(incrementCounter),
                "style", ReactCreateProps(
                    "padding", ReactCreateString("15px 30px"),
                    "fontSize", ReactCreateString("18px"),
                    "backgroundColor", ReactCreateString("#28a745"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer")
                )
            ),
            ReactCreateString("➕ Click to Count!")
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

### Example 2: Color Changer

**What it does**: Buttons that change the background color

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;

// Current background color
static char current_color[20] = "#ffffff";  // Start with white

// Simple functions to change colors - no complex arguments!
void changeToRed() {
    sprintf(current_color, "#ff6b6b");  // Red color
    rootRender();  // Re-render with new color
}

void changeToBlue() {
    sprintf(current_color, "#74c0fc");  // Blue color
    rootRender();  // Re-render with new color
}

void changeToGreen() {
    sprintf(current_color, "#51cf66");  // Green color
    rootRender();  // Re-render with new color
}

void rootRender() {
    ReactComponent main_component = ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "backgroundColor", ReactCreateString(current_color),
                "minHeight", ReactCreateString("100vh"),
                "padding", ReactCreateString("50px"),
                "textAlign", ReactCreateString("center"),
                "transition", ReactCreateString("background-color 0.3s ease")
            )
        ),

        ReactCreateElement("h1", ReactNULL,
            ReactCreateString("🎨 Color Changer")
        ),

        ReactCreateElement("p", ReactNULL,
            ReactCreateString("Click the buttons to change the background color!")
        ),

        // Red button
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClickHandler(changeToRed),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#ff6b6b"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer")
                )
            ),
            ReactCreateString("🔴 Red")
        ),

        // Blue button
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClickHandler(changeToBlue),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#74c0fc"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer")
                )
            ),
            ReactCreateString("🔵 Blue")
        ),

        // Green button
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClickHandler(changeToGreen),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#51cf66"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer")
                )
            ),
            ReactCreateString("🟢 Green")
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

### Example 3: Text Input Handler

**What it does**: Takes user input from a text field and displays a personalized greeting

```c
#include <stdio.h>
#include <string.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

// Global variable to store user's name
char user_input[100] = {0};

// Simple function that handles input changes - C-React does the hard work!
void set_input_value(const char *input_value) {
    // Copy the user's input to our global variable
    strncpy(user_input, input_value, sizeof(user_input) - 1);
    user_input[sizeof(user_input) - 1] = '\0';  // Ensure null termination

    printf("User typed: %s\n", user_input);  // Debug output
    rootRender();  // Re-render to show the greeting
}

// Function to create greeting message (only if user typed something)
ReactComponent user_message(){
    if(user_input[0] == 0){
        return ReactNULL;  // Don't show anything if input is empty
    }
    
    // Create personalized greeting
    char user_hello[200] = {0};
    strcat(user_hello, "Hello, ");
    strcat(user_hello, user_input);
    strcat(user_hello, "! 👋");
    
    return ReactCreateElement("h1",
        ReactCreateProps(
            "style", ReactCreateProps(
                "color", ReactCreateString("#28a745"),
                "marginTop", ReactCreateString("20px")
            )
        ),
        ReactCreateString(user_hello)
    );    
}

// Create and render the input webpage
void rootRender() {
    ReactComponent main_component = ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "textAlign", ReactCreateString("center"),
                "padding", ReactCreateString("50px"),
                "fontFamily", ReactCreateString("Arial, sans-serif")
            )
        ),

        ReactCreateElement("h1", ReactNULL,
            ReactCreateString("📝 Type Your Name")
        ),

        ReactCreateElement("p", ReactNULL,
            ReactCreateString("Enter your name and press Tab or click outside:")
        ),

        // Input field that triggers set_input_value on blur (when user leaves the field)
        ReactCreateElement("input",
            ReactCreateProps(
                "onBlur", ReactCreateInputHandler(set_input_value),
                "placeholder", ReactCreateString("Type your name here..."),
                "style", ReactCreateProps(
                    "padding", ReactCreateString("10px"),
                    "fontSize", ReactCreateString("16px"),
                    "border", ReactCreateString("2px solid #ccc"),
                    "borderRadius", ReactCreateString("5px"),
                    "width", ReactCreateString("300px")
                )
            )
        ),

        // Display greeting (only shows if user typed something)
        user_message()
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

**🤓 How this works:**
1. **`user_input[100]`**: Global array to store what the user types
2. **`void set_input_value(const char *input_value)`**: Simple function that receives the text directly!
3. **`ReactCreateInputHandler(set_input_value)`**: Converts your C function into an input handler
4. **`onBlur` event**: Triggers when user clicks outside the input field or presses Tab
5. **`strncpy()`**: Safely copies the text to our global variable
6. **`user_message()`**: Helper function that returns a greeting element or nothing

**✨ The Magic:** `ReactCreateInputHandler()` automatically:
- Extracts the text from the input field
- Converts it from JavaScript to a C string
- Passes it to your simple function
- No complex event handling needed!

### Example 4: Real-Time Input (onChange)

**What it does**: Updates the greeting as you type (real-time feedback)

```c
#include <stdio.h>
#include <string.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

char live_input[100] = {0};

// Simple function that handles every keystroke - no complex code!
void handle_change(const char *input_value) {
    // Copy the user's input to our global variable
    strncpy(live_input, input_value, sizeof(live_input) - 1);
    live_input[sizeof(live_input) - 1] = '\0';  // Ensure null termination

    rootRender();  // Re-render after each keystroke
}

void rootRender() {
    // Count the characters
    int char_count = strlen(live_input);
    char count_text[50];
    sprintf(count_text, "Characters: %d", char_count);

    ReactComponent main_component = ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "textAlign", ReactCreateString("center"),
                "padding", ReactCreateString("50px"),
                "fontFamily", ReactCreateString("Arial, sans-serif")
            )
        ),

        ReactCreateElement("h1", ReactNULL,
            ReactCreateString("⚡ Real-Time Input")
        ),

        // Input field with onChange (triggers on every keystroke)
        ReactCreateElement("input",
            ReactCreateProps(
                "onChange", ReactCreateInputHandler(handle_change),
                "placeholder", ReactCreateString("Start typing..."),
                "style", ReactCreateProps(
                    "padding", ReactCreateString("10px"),
                    "fontSize", ReactCreateString("18px"),
                    "border", ReactCreateString("2px solid #0d6efd"),
                    "borderRadius", ReactCreateString("5px"),
                    "width", ReactCreateString("400px")
                )
            )
        ),

        // Show what user is typing
        ReactCreateElement("p",
            ReactCreateProps(
                "style", ReactCreateProps(
                    "fontSize", ReactCreateString("20px"),
                    "marginTop", ReactCreateString("20px"),
                    "color", ReactCreateString("#666")
                )
            ),
            ReactCreateString("You typed: "),
            ReactCreateString(live_input[0] ? live_input : "(nothing yet)")
        ),

        // Show character count
        ReactCreateElement("p",
            ReactCreateProps(
                "style", ReactCreateProps(
                    "fontSize", ReactCreateString("16px"),
                    "color", ReactCreateString("#999")
                )
            ),
            ReactCreateString(count_text)
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

**🎯 Key Differences: onChange vs onBlur**

| Event | When it triggers | Use case |
|-------|------------------|----------|
| `onChange` | Every keystroke | Real-time validation, character counters, live search |
| `onBlur` | User leaves field | Form validation, save data when user finishes typing |

**💡 Pro Tips for Input Handling:**
- Use `onChange` for real-time feedback (like search suggestions)
- Use `onBlur` for better performance (less re-rendering)
- `ReactCreateInputHandler()` makes input handling super simple!
- Just write a function that takes `const char *` - C-React does the rest!

---

## 🎓 Event Handler Deep Dive

**C-React provides TWO ways to handle events: Simple helpers (recommended for beginners) and advanced `ReactCreateClojure()`**

### ✨ Simple Event Handlers (Recommended)

C-React provides easy-to-use helper functions that handle all the complex event plumbing for you:

#### 1. **ReactCreateClickHandler()** - For button clicks

```c
// Your simple function - no complex arguments!
void myClickFunction() {
    printf("Button was clicked!\n");
    // Do something...
}

// Use it in a button
ReactCreateElement("button",
    ReactCreateProps(
        "onClick", ReactCreateClickHandler(myClickFunction)
    ),
    ReactCreateString("Click me!")
)
```

**What it does:** Converts a simple `void function()` into a React event handler.

#### 2. **ReactCreateClickHandlerWithArgs()** - Click with custom data

```c
typedef struct {
    int id;
    char name[50];
} ButtonData;

// Your function receives custom data
void myClickWithData(void *ctx) {
    ButtonData *data = (ButtonData*)ctx;
    printf("Clicked button: %s (ID: %d)\n", data->name, data->id);
}

ButtonData my_button = {.id = 42, .name = "Submit"};

// Pass your data along
ReactCreateElement("button",
    ReactCreateProps(
        "onClick", ReactCreateClickHandlerWithArgs(myClickWithData, &my_button)
    ),
    ReactCreateString("Click me!")
)
```

**What it does:** Lets you pass custom data (any pointer) to your click handler.

#### 3. **ReactCreateInputHandler()** - For text input

```c
// Your simple function receives the text directly!
void handleUserInput(const char *text) {
    printf("User typed: %s\n", text);
    // Do something with the text...
}

// Use it with input fields
ReactCreateElement("input",
    ReactCreateProps(
        "onChange", ReactCreateInputHandler(handleUserInput)
    )
)
```

**What it does:** Automatically extracts text from input fields and passes it as a C string.

#### 4. **ReactCreateInputHandlerWithArgs()** - Input with custom data

```c
typedef struct {
    char buffer[100];
    int max_length;
} InputContext;

// Function receives both the text AND your custom data
void handleInputWithContext(const char *text, void *ctx) {
    InputContext *input_ctx = (InputContext*)ctx;
    if (strlen(text) <= input_ctx->max_length) {
        strcpy(input_ctx->buffer, text);
    }
}

InputContext my_input = {.max_length = 50};

ReactCreateElement("input",
    ReactCreateProps(
        "onChange", ReactCreateInputHandlerWithArgs(handleInputWithContext, &my_input)
    )
)
```

**What it does:** Passes both the input text AND custom context data to your handler.

---

### 🔥 Advanced: ReactCreateClojure()

**When should you use `ReactCreateClojure()`?**
- You need direct access to JavaScript event objects
- You want to handle events not covered by the simple helpers
- You need maximum control and flexibility
- You're doing something complex or unusual

**How it works:**

```c
// Your handler receives c2wasm_js_var arguments
c2wasm_js_var myAdvancedHandler(c2wasm_js_var args) {
    // args contains any values you passed to ReactCreateClojure()
    // c2wasm_arguments contains the actual browser event

    // Example: Get the first argument you passed
    c2wasm_js_var my_data = c2wasm_get_array_any_by_index(args, 0);

    // Example: Access the browser event
    c2wasm_js_var event = c2wasm_get_array_any_by_index(c2wasm_arguments, 0);

    // Do complex JavaScript interop...

    return c2wasm_null;  // or c2wasm_undefined
}

// Use it with custom arguments
ReactCreateElement("button",
    ReactCreateProps(
        "onClick", ReactCreateClojure(
            myAdvancedHandler,
            ReactCreateString("custom arg 1"),
            ReactCreateNumber(42)
        )
    ),
    ReactCreateString("Advanced button")
)
```

**Example: Custom Alert with ReactCreateClojure()**

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"
ReactRoot root;
void rootRender();

// Advanced handler that shows a custom alert
c2wasm_js_var showCustomAlert(c2wasm_js_var args) {
    // Get the message we passed (first argument)
    c2wasm_js_var message = c2wasm_get_array_any_by_index(args, 0);

    // Create arguments for window.alert()
    c2wasm_js_var alert_args = c2wasm_create_array();
    c2wasm_append_array_any(alert_args, message);

    // Call JavaScript: window.alert(message)
    c2wasm_call_object_prop(c2wasm_window, "alert", alert_args);

    return c2wasm_null;
}

void rootRender() {
    ReactComponent app = ReactCreateElement("div", ReactNULL,
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClojure(
                    showCustomAlert,
                    ReactCreateString("🎉 This is a custom alert!")
                )
            ),
            ReactCreateString("Show Alert")
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

**Key Rules for ReactCreateClojure():**
1. Your function must return `c2wasm_js_var`
2. Your function receives a single `c2wasm_js_var args` parameter
3. Access your custom arguments via `c2wasm_get_array_any_by_index(args, index)`
4. Access browser events via `c2wasm_get_array_any_by_index(c2wasm_arguments, 0)`

---

### 📊 Quick Comparison Table

| Feature | Simple Helpers | ReactCreateClojure() |
|---------|---------------|---------------------|
| **Difficulty** | ⭐ Beginner-friendly | ⭐⭐⭐ Advanced |
| **Code Clarity** | Very clean | More complex |
| **Flexibility** | Limited to common patterns | Unlimited |
| **Use Cases** | Buttons, inputs, common events | Custom events, JS interop |
| **Recommendation** | **Use this first!** | Only when necessary |

**🎯 Best Practice:** Always start with the simple helpers (`ReactCreateClickHandler`, `ReactCreateInputHandler`, etc.). Only use `ReactCreateClojure()` when you need advanced functionality not covered by the helpers.

---

## 🤖 For AI Developers & Quick Reference

**Working with AI tools or need rapid development?** 

📋 **Check [`aidoc.md`](./aidoc.md)** - This file contains:
- Complete API reference with exact function signatures
- Common patterns and code templates  
- Error troubleshooting guide
- Structured format perfect for AI assistance
- All terminators and syntax rules clearly marked

The `aidoc.md` is optimized for AI tools like ChatGPT, GitHub Copilot, and other coding assistants to understand C-React quickly and generate correct code.

---

## 🚀 Next Steps: What to Build

**Ready to build more cool stuff? Here are ideas:**

### Beginner Projects:
1. **Todo List**: Add and remove items from a list
2. **Calculator**: Make a simple calculator with buttons  
3. **Quiz App**: Ask questions and show scores
4. **Photo Gallery**: Display and navigate through images

### Intermediate Projects:
1. **Weather App**: Fetch weather data from an API
2. **Chat Interface**: Create a messaging interface
3. **Game**: Simple games like Tic-Tac-Toe or Snake
4. **Dashboard**: Show data with charts and graphs

### Where to Learn More:
- **React concepts**: Since C-React mirrors React, learning React concepts helps
- **C programming**: Strengthen your C skills for better web development
- **WebAssembly**: Learn more about how your C code runs in browsers

---

## 🎯 Complete Function Reference

**Quick lookup for all C-React functions:**

### Setup Functions:
```c
void ReactStart()                    // Always call first!
```

### Element Creation:
```c
ReactElement ReactCreateElement(const char *tag, ...)  // Create HTML elements
ReactElement ReactCreateFragment(...)                  // Group elements
c2wasm_js_var ReactCreateString(const char *text)     // Create text
c2wasm_js_var ReactCreateNumber(double number)        // Create numbers
```

### Properties & Styling:
```c
c2wasm_js_var ReactCreateProps(const char *key, value, ...)  // Set properties
```

### Event Handling (Simple - Recommended):
```c
c2wasm_js_var ReactCreateClickHandler(void (*func)())                    // Simple click handler
c2wasm_js_var ReactCreateClickHandlerWithArgs(void (*func)(void*), ctx)  // Click with custom data
c2wasm_js_var ReactCreateInputHandler(void (*func)(const char*))         // Simple input handler
c2wasm_js_var ReactCreateInputHandlerWithArgs(                           // Input with custom data
    void (*func)(const char*, void*), void *ctx
)
```

### Event Handling (Advanced):
```c
c2wasm_js_var ReactCreateClojure(callback_function, ...)  // Advanced event handling
```

### DOM Operations:
```c
c2wasm_js_var ReactGetElementById(const char *id)           // Find element by ID
c2wasm_js_var ReactGetElementByClassName(const char *cls)   // Find by class
ReactRoot ReactDOMCreateRoot(c2wasm_js_var element)        // Create root
void ReactRootRender(ReactRoot root, ReactElement element) // Show on webpage  
```

### Special Values:
```c
ReactNULL = c2wasm_null              // When you don't need properties
```

**🔍 Need more details?** Check [`aidoc.md`](./aidoc.md) for comprehensive documentation and examples!

---

## ❤️ License & Contributing

This project is **completely free** and released into the public domain. 

**What this means:**
- ✅ Use it for personal projects
- ✅ Use it for commercial projects  
- ✅ Modify it however you want
- ✅ No need to credit us (but we'd appreciate it!)
- ✅ No restrictions whatsoever

**Want to help improve C-React?**
- Report bugs or issues
- Suggest new features
- Share your cool projects
- Help other beginners learn

---

## 🏆 You Did It!

**Congratulations! 🎉 You just:**
- ✅ Built your first website using C programming
- ✅ Learned how to compile C code for the web
- ✅ Created interactive buttons and dynamic content  
- ✅ Used modern web technologies (React + WebAssembly)

**You're now a C web developer!** 🚀

Share your creation with friends and keep building amazing things with C-React!
