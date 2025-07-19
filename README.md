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
// Don't worry about understanding every line yet!
// We'll explain the important parts

#include <stdio.h>           // For basic C functions
#include "c2wasm.c"         // Magic file #1
#include "react.c"          // Magic file #2

// This function runs when someone clicks the button
c2wasm_js_var handleClick(c2wasm_js_var args) {
  // Show an alert box (like alert() in JavaScript)
  c2wasm_call_object_prop(c2wasm_window, "alert", args);
  return c2wasm_null;
}

// This function creates our website's content
ReactComponent createAppComponent() {
  return ReactCreateElement(
    "div",                    // Create a <div> container
    ReactCreateProps(         // Set properties for our div
      "className", ReactCreateString("container"),
      "style", ReactCreateProps(    // Make it look nice
        "padding", ReactCreateString("20px"),
        "maxWidth", ReactCreateString("800px"),
        "margin", ReactCreateString("0 auto"),
        NULL                  // End of style properties
      ),
      NULL                    // End of div properties  
    ),
    
    // Create a big heading
    ReactCreateElement("h1", 
      ReactCreateProps(
        "style", ReactCreateProps(
          "color", ReactCreateString("#333"),
          "borderBottom", ReactCreateString("2px solid #eee"),
          "paddingBottom", ReactCreateString("10px"),
          NULL
        ),
        NULL
      ), 
      ReactCreateString("🎉 Welcome to C-React!"), // The heading text
      -1                      // End of heading children
    ),
    
    // Create some paragraphs and a button
    ReactCreateFragment(      // Group multiple elements
      ReactCreateElement("p", ReactNULL, 
        ReactCreateString("🔥 This webpage is made with C code!"),
        -1
      ),
      
      ReactCreateElement("p", ReactNULL, 
        ReactCreateString("✨ Your C code runs super fast in the browser!"),
        -1
      ),
      
      // Create a clickable button
      ReactCreateElement(
        "button",
        ReactCreateProps(
          "onClick", ReactCreateClojure(      // When clicked, run handleClick
            handleClick,
            ReactCreateString("🎊 Hello from C-React! You clicked a button made with C code!"),
            -1
          ),
          "style", ReactCreateProps(          // Make the button pretty
            "padding", ReactCreateString("12px 20px"),
            "backgroundColor", ReactCreateString("#0d6efd"),
            "color", ReactCreateString("white"),
            "border", ReactCreateString("none"),
            "borderRadius", ReactCreateString("5px"),
            "cursor", ReactCreateString("pointer"),
            "fontSize", ReactCreateString("16px"),
            "marginTop", ReactCreateString("20px"),
            NULL
          ),
          NULL
        ),
        ReactCreateString("🚀 Click Me!"),   // Button text
        -1
      ),
      -1                      // End of fragment children
    ),
    -1                        // End of main div children
  );
}

// The main function - where everything starts!
int main() {
  // Step 1: Initialize React
  ReactStart();
  
  // Step 2: Create our website content
  ReactComponent app = createAppComponent();
  
  // Step 3: Put our content on the webpage
  ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
  ReactRootRender(root, app);
  
  return 0;
}
```

**🤓 What does this code do?**
- Creates a webpage with a title, some text, and a button
- When you click the button, it shows an alert message
- All the styling makes it look modern and pretty

### Understanding the Key Parts:

1. **`#include` lines**: Import the special files we downloaded
2. **`handleClick` function**: Runs when button is clicked (like onclick in HTML)
3. **`createAppComponent` function**: Builds our webpage structure
4. **`main` function**: The starting point that puts everything together


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
// Pattern: ReactCreateElement("tag", properties, children..., -1)
ReactCreateElement("div", ReactNULL, 
    ReactCreateString("Hello World!"), 
    -1  // This -1 is VERY important - it marks the end!
);
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
        "fontSize", ReactCreateString("20px"),
        NULL  // NULL marks the end of nested properties
    ),
    NULL  // NULL marks the end of main properties
)
```

### 🎯 Important Rules to Remember:

1. **Always end with terminators:**
   - Use `-1` for `ReactCreateElement()` and `ReactCreateFragment()`
   - Use `NULL` for `ReactCreateProps()`

2. **Always call `ReactStart()` first:**
   ```c
   int main() {
       ReactStart(); // Must be first!
       // ... rest of your code
   }
   ```

3. **Text must be wrapped:**
   ```c
   // ❌ Wrong:
   ReactCreateElement("p", ReactNULL, "Hello", -1);
   
   // ✅ Correct:
   ReactCreateElement("p", ReactNULL, ReactCreateString("Hello"), -1);
   ```

### 🎨 Common HTML Elements You Can Use:

```c
// Headers
ReactCreateElement("h1", ReactNULL, ReactCreateString("Big Title"), -1);
ReactCreateElement("h2", ReactNULL, ReactCreateString("Smaller Title"), -1);

// Paragraphs
ReactCreateElement("p", ReactNULL, ReactCreateString("Some text"), -1);

// Buttons
ReactCreateElement("button", 
    ReactCreateProps("onClick", some_function, NULL),
    ReactCreateString("Click me!"), 
    -1
);

// Containers
ReactCreateElement("div", ReactNULL, /* other elements */, -1);

// Links
ReactCreateElement("a", 
    ReactCreateProps("href", ReactCreateString("https://google.com"), NULL),
    ReactCreateString("Visit Google"), 
    -1
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

// Global variable to store the count
static int counter = 0;

// Function that runs when button is clicked
c2wasm_js_var incrementCounter(c2wasm_js_var args) {
    counter++;  // Add 1 to counter
    
    // Update the webpage with new counter value
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createCounterApp());
    
    return c2wasm_null;
}

// Create the counter webpage
ReactComponent createCounterApp() {
    return ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "textAlign", ReactCreateString("center"),
                "padding", ReactCreateString("50px"),
                "fontFamily", ReactCreateString("Arial, sans-serif"),
                NULL
            ),
            NULL
        ),
        
        ReactCreateElement("h1", ReactNULL, 
            ReactCreateString("🔢 Simple Counter"), -1),
        
        ReactCreateElement("p", 
            ReactCreateProps(
                "style", ReactCreateProps(
                    "fontSize", ReactCreateString("24px"),
                    "margin", ReactCreateString("20px"),
                    NULL
                ),
                NULL
            ),
            ReactCreateString("Count: "), 
            ReactCreateNumber(counter),  // Show the current count
            -1
        ),
        
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClojure(incrementCounter, -1),
                "style", ReactCreateProps(
                    "padding", ReactCreateString("15px 30px"),
                    "fontSize", ReactCreateString("18px"),
                    "backgroundColor", ReactCreateString("#28a745"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer"),
                    NULL
                ),
                NULL
            ),
            ReactCreateString("➕ Click to Count!"),
            -1
        ),
        -1
    );
}

int main() {
    ReactStart();
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createCounterApp());
    return 0;
}
```

### Example 2: Color Changer

**What it does**: Buttons that change the background color

```c
#include <stdio.h>
#include "c2wasm.c"
#include "react.c"

// Current background color
static char current_color[20] = "#ffffff";  // Start with white

// Function to change color to red
c2wasm_js_var changeToRed(c2wasm_js_var args) {
    sprintf(current_color, "#ff6b6b");  // Red color
    
    // Update the page
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createColorApp());
    return c2wasm_null;
}

// Function to change color to blue  
c2wasm_js_var changeToBlue(c2wasm_js_var args) {
    sprintf(current_color, "#74c0fc");  // Blue color
    
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createColorApp());
    return c2wasm_null;
}

// Function to change color to green
c2wasm_js_var changeToGreen(c2wasm_js_var args) {
    sprintf(current_color, "#51cf66");  // Green color
    
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createColorApp());
    return c2wasm_null;
}

ReactComponent createColorApp() {
    return ReactCreateElement("div",
        ReactCreateProps(
            "style", ReactCreateProps(
                "backgroundColor", ReactCreateString(current_color),
                "minHeight", ReactCreateString("100vh"),
                "padding", ReactCreateString("50px"),
                "textAlign", ReactCreateString("center"),
                "transition", ReactCreateString("background-color 0.3s ease"),
                NULL
            ),
            NULL
        ),
        
        ReactCreateElement("h1", ReactNULL, 
            ReactCreateString("🎨 Color Changer"), -1),
            
        ReactCreateElement("p", ReactNULL,
            ReactCreateString("Click the buttons to change the background color!"), -1),
        
        // Red button
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClojure(changeToRed, -1),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#ff6b6b"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer"),
                    NULL
                ),
                NULL
            ),
            ReactCreateString("🔴 Red"),
            -1
        ),
        
        // Blue button  
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClojure(changeToBlue, -1),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#74c0fc"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer"),
                    NULL
                ),
                NULL
            ),
            ReactCreateString("🔵 Blue"),
            -1
        ),
        
        // Green button
        ReactCreateElement("button",
            ReactCreateProps(
                "onClick", ReactCreateClojure(changeToGreen, -1),
                "style", ReactCreateProps(
                    "margin", ReactCreateString("10px"),
                    "padding", ReactCreateString("10px 20px"),
                    "backgroundColor", ReactCreateString("#51cf66"),
                    "color", ReactCreateString("white"),
                    "border", ReactCreateString("none"),
                    "borderRadius", ReactCreateString("5px"),
                    "cursor", ReactCreateString("pointer"),
                    NULL
                ),
                NULL
            ),
            ReactCreateString("🟢 Green"),
            -1
        ),
        -1
    );
}

int main() {
    ReactStart();
    ReactRoot root = ReactDOMCreateRoot(ReactGetElementById("root"));
    ReactRootRender(root, createColorApp());
    return 0;
}
```

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
ReactElement ReactCreateElement(const char *tag, ..., -1)  // Create HTML elements  
ReactElement ReactCreateFragment(..., -1)                 // Group elements
c2wasm_js_var ReactCreateString(const char *text)        // Create text
c2wasm_js_var ReactCreateNumber(double number)           // Create numbers
```

### Properties & Styling:
```c
c2wasm_js_var ReactCreateProps(const char *key, value, ..., NULL)  // Set properties
```

### Event Handling:
```c  
c2wasm_js_var ReactCreateClojure(callback_function, ..., -1)  // Handle clicks, etc.
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
