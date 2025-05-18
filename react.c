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
#ifndef c2wasm_fdefine
#include "c2wasm.c"
#endif 

#include <stdarg.h>

typedef c2wasm_js_var ReactComponent;
typedef c2wasm_js_var ReactElement;

c2wasm_js_var ReactFragment;
c2wasm_js_var React;

void ReactStart();



//================================Definitions==================================

void ReactStart(){
    c2wasm_start();
    React = c2wasm_get_object_prop_any(c2wasm_window,"React");
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
    ReactElement element = c2wasm_call_object_prop(React,"createElement",arguments);
   

    return element;
}
ReactElement private_ReactcreateElement(const char *element,...){
    va_list args;
    va_start(args, element);
    ReactElement element = private_ReactcreateElement_raw(c2wasm_create_string(element),args);
    va_end(args);
    return element;
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

void ReactDomRender(c2wasm_js_var element, c2wasm_js_var container){
    c2wasm_js_var arguments = c2wasm_create_array();
    c2wasm_append_array_any(arguments,element);
    c2wasm_append_array_any(arguments,container);
    c2wasm_call_object_prop(React,"render",arguments);
}