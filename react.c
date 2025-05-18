/*
 $$$$$$\    $$$$$$$\                                  $$\     
$$  __$$\   $$  __$$\                                 $$ |    
$$ /  \__|  $$ |  $$ | $$$$$$\   $$$$$$\   $$$$$$$\ $$$$$$\   
$$ |$$$$$$\ $$$$$$$  |$$  __$$\  \____$$\ $$  _____|\_$$  _|  
$$ |\______|$$  __$$< $$$$$$$$ | $$$$$$$ |$$ /        $$ |    
$$ |  $$\   $$ |  $$ |$$   ____|$$  __$$ |$$ |        $$ |$$\ 
\$$$$$$  |  $$ |  $$ |\$$$$$$$\ \$$$$$$$ |\$$$$$$$\   \$$$$  |
 \______/   \__|  \__| \_______| \_______| \_______|   \____/ 
                                                              
*/

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

*/
#include <stdarg.h>

#ifndef c2wasm_fdefine
#include "c2wasm.c"
#endif 


typedef c2wasm_js_var ReactComponent;
typedef c2wasm_js_var ReactElement;
typedef c2wasm_js_var ReactRoot;

c2wasm_js_var React;
c2wasm_js_var ReactDOM;
#define ReactNULL  c2wasm_null
// the react fragment object, its the real object while the string its a pointer to indentify it
c2wasm_js_var private_ReactFragment_object;
const char *ReactFragment = "";


#define ReactCreateElement(...) private_ReactcreateElement(__VA_ARGS__,-1)
#define ReactCreateFragment(...) private_ReactcreateFragment(__VA_ARGS__,-1)


#define ReactCreateProps(...)  private_ReactCreateProps(((void*)0),__VA_ARGS__,((void*)0))
#define ReactCreateClojure(...) private_ReacteCreateFunction(__VA_ARGS__,-1)


void ReactStart();


ReactElement private_ReactcreateElement(const char *element,...);

ReactElement private_ReactcreateFragment(c2wasm_js_var sentinel,...);

c2wasm_js_var private_ReactCreateProps(void *sentinel,...);

c2wasm_js_var ReactGetElementById(const char *id);

c2wasm_js_var ReactGetElementByClassName(const char *className);


c2wasm_js_var ReactCreateString(const char *string);

c2wasm_js_var private_ReacteCreateFunction(c2wasm_js_var (*callback)(c2wasm_js_var args),...);

c2wasm_js_var ReactCreateNumber(double number);

ReactRoot ReactDOMCreateRoot(c2wasm_js_var element);

void ReactRootRender(ReactRoot root,c2wasm_js_var element);

//================================Definiprivate_ReactcreatePropstions==================================

void ReactStart(){
    c2wasm_start();
    React = c2wasm_get_object_prop_any(c2wasm_window,"React");
    ReactDOM = c2wasm_get_object_prop_any(c2wasm_window,"ReactDOM");

    private_ReactFragment_object = c2wasm_get_object_prop_any(React,"Fragment");    
}

ReactElement private_ReactcreateElement(const char *element,...){
    va_list args;
    va_start(args,element);
    c2wasm_js_var arguments = c2wasm_create_array();
    if (element == ReactFragment){
        c2wasm_append_array_any(arguments,private_ReactFragment_object);
    }
    else{
        c2wasm_append_array_string(arguments,element);
    }

    while(1){
        c2wasm_js_var arg = va_arg(args, c2wasm_js_var);
        if(arg == -1){
            break;
        }
        c2wasm_append_array_any(arguments,arg);
    }
    ReactElement created_element = c2wasm_call_object_prop(React,"createElement",arguments);
    va_end(args);
    return created_element;
}
ReactElement private_ReactcreateFragment(c2wasm_js_var sentinel,...){
    va_list args;
    va_start(args,sentinel);
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_any(arguments,private_ReactFragment_object);
    c2wasm_append_array_any(arguments,c2wasm_null);
    c2wasm_append_array_any(arguments,sentinel);

    while(1){
        c2wasm_js_var arg = va_arg(args, c2wasm_js_var);
        if(arg == -1){
            break;
        }
        c2wasm_append_array_any(arguments,arg);
    }
    ReactElement created_element = c2wasm_call_object_prop(React,"createElement",arguments);
    va_end(args);
    return created_element;
}

c2wasm_js_var private_ReactCreateProps(void *sentinel,...){

    va_list args;
    va_start(args,sentinel);
    
    c2wasm_js_var created_object = c2wasm_create_object();

    const short GETTING_KEY = 0;
    const short GETTING_VALUE = 1;
    short state = GETTING_KEY;
    const void *NULL_PTR = ((void*)0);
    char *last_key;
    while(true){

        if(state == GETTING_KEY){
            last_key = va_arg(args, char*);
            if(last_key == NULL_PTR){
                break;
            }
            state = GETTING_VALUE;
        }

        if(state == GETTING_VALUE){
            c2wasm_js_var value = va_arg(args, c2wasm_js_var);
            c2wasm_set_object_prop_any(created_object,last_key,value);
            state = GETTING_KEY;
        }
    }

    va_end(args);
    return created_object;
}


c2wasm_js_var ReactGetElementById(const char *id){
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_string(arguments,id);
    return c2wasm_call_object_prop(c2wasm_document,"getElementById",arguments);
}
c2wasm_js_var ReactGetElementByClassName(const char *className){
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_string(arguments,className);
    return c2wasm_call_object_prop(c2wasm_document,"getElementsByClassName",arguments);
}
c2wasm_js_var ReactCreateString(const char *string){
    return c2wasm_create_string(string);
}
c2wasm_js_var private_ReacteCreateFunction(c2wasm_js_var (*callback)(c2wasm_js_var args),...){

    va_list args;
    va_start(args,callback);
    c2wasm_js_var arguments = c2wasm_create_array();
    while(1){
        c2wasm_js_var arg = va_arg(args, c2wasm_js_var);
        if(arg == -1){
            break;
        }
        c2wasm_append_array_any(arguments,arg);
    }
    
    c2wasm_js_var created_function = c2wasm_create_function_with_internal_args(arguments,callback);
    va_end(args);
    return created_function;

}


c2wasm_js_var ReactCreateNumber(double number){
    return c2wasm_create_double(number);
}


ReactRoot ReactDOMCreateRoot(c2wasm_js_var element){
    c2wasm_js_var root_args = c2wasm_create_array();
    c2wasm_append_array_any(root_args,element);
    return c2wasm_call_object_prop(ReactDOM,"createRoot",root_args);
}

void ReactRootRender(ReactRoot root,c2wasm_js_var element){
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_any(arguments,element);
    c2wasm_call_object_prop(root,"render",arguments);
}

/*

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

*/