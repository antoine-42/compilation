//
// Created by antoine on 22/09/20.
//

#include "plugin.h"


/* td6 q1 */
static void handle_pragma_instrument_function_1(cpp_reader *ARG_UNUSED(dummy)){
    printf("k\n");
}
/* td6 q2 */
static void handle_pragma_instrument_function_2(cpp_reader *ARG_UNUSED(dummy)){
    enum cpp_ttype token;
    tree x;
    printf("k\n");

    token = pragma_lex (&x);

    if (token == CPP_NAME){
        printf("%s", IDENTIFIER_POINTER(x));
    }
}


int
plugin_init(struct plugin_name_args *plugin_info,
            struct plugin_gcc_version *version) {
    printf("plugin init\n");
    c_register_pragma("instrument", "function1", handle_pragma_instrument_function_1);
    c_register_pragma("instrument", "function", handle_pragma_instrument_function_2);
    return 0;
}

