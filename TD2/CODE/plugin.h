//
// Created by antoine on 22/09/20.
//

#ifndef CODE_PLUGIN_H
#define CODE_PLUGIN_H

#include <gcc-plugin.h>
#include <tree.h>
#include <tree-pass.h>
#include <context.h>


const pass_data my_pass_data = {
        GIMPLE_PASS, /* type */
        "my pass", /* name */
        OPTGROUP_NONE, /* optinfo_flags */
        TV_OPTIMIZE, /* tv_id */
        PROP_gimple_any, /* properties_required */
        0, /* properties_provided */
        0, /* properties_destroyed */
        0, /* todo_flags_start */
        0, /* todo_flags_finish */
};


class my_pass : public gimple_opt_pass {
public:
    my_pass(gcc::context *ctxt)
            : gimple_opt_pass(my_pass_data, ctxt) {}

    my_pass *clone() { return new my_pass(g); }

    bool gate (function *fun) { return true; }

    unsigned int execute (function *fun) {
        printf("Executing my_pass with function %s\n",
               function_name(fun) );
        return 0;
    }
};

#endif //CODE_PLUGIN_H
