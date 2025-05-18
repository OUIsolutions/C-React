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

c2wasm_js_var ReactFragment;
c2wasm_js_var React;
c2wasm_js_var ReactDOM;

#define ReactCreateElement(...) private_ReactcreateElement(__VA_ARGS__,-1)

//================================Definitions==================================

void ReactStart(){
    c2wasm_start();
    React = c2wasm_get_object_prop_any(c2wasm_window,"React");
    ReactDOM = c2wasm_get_object_prop_any(c2wasm_window,"ReactDOM");

    ReactFragment = c2wasm_get_object_prop_any(React,"Fragment");    
}

ReactElement private_ReactcreateElement_raw(c2wasm_js_var element,va_list args){
    
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_any(arguments,element);

    while(1){
        c2wasm_js_var arg = va_arg(args, c2wasm_js_var);
        if(arg == -1){
            break;
        }
        c2wasm_append_array_any(arguments,arg);
    }
    ReactElement created_element = c2wasm_call_object_prop(React,"createElement",arguments);
   

    return created_element;
}
ReactElement private_ReactcreateElement(const char *element,...){
    va_list args;
    va_start(args, element);
    ReactElement created_element = private_ReactcreateElement_raw(c2wasm_create_string(element),args);
    va_end(args);
    return created_element;
}

ReactElement private_ReactCreateFragment(c2wasm_js_var sentinel,...){
    va_list args;
    va_start(args, sentinel);
    ReactElement element = private_ReactcreateElement_raw(ReactFragment,args);
    va_end(args);
    return element;
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