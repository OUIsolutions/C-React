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

typedef c2wasm_js_var ReactComponent;

c2wasm_js_var ReactFragment;
c2wasm_js_var React;
void cwasm_start();

void cwasm_start(){
    React = c2wasm_get_object_prop_any(c2wasm_window,"React");
    ReactFragment = c2wasm_get_object_prop_any(React,"Fragment");    
}
