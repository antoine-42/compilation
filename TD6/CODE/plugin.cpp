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
/* td6 q3 */
static void handle_pragma_instrument_function_3(cpp_reader *ARG_UNUSED(dummy)){
    enum cpp_ttype token;
    tree x;

    token = pragma_lex (&x);

    while (token != CPP_EOF){
        if (token == CPP_NAME){
            const char *op = IDENTIFIER_POINTER(x);
            printf("%s\n", op);
        }

        token = pragma_lex (&x);
    }
}


int
plugin_init(struct plugin_name_args *plugin_info,
            struct plugin_gcc_version *version) {
    printf("plugin init\n");
    c_register_pragma("instrument", "function1", handle_pragma_instrument_function_1);
    c_register_pragma("instrument", "function2", handle_pragma_instrument_function_2);
    c_register_pragma("instrument", "function", handle_pragma_instrument_function_3);
    return 0;
}
