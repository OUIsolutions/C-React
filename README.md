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