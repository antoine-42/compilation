//
// Created by antoine on 22/09/20.
//

#ifndef CODE_PLUGIN_H
#define CODE_PLUGIN_H

#include <gcc-plugin.h>
//#include <plugin-version.h>
#include <tree.h>
#include <tree-pass.h>
#include <context.h>
#include <function.h>
#include <basic-block.h>
#include <gimple.h>
#include <gimple-iterator.h>

int plugin_is_GPL_compatible;


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

    bool gate (function *fun) {
        return true;
    }

    unsigned int execute (function *fun) {
        printf("Executing my_pass execute with function %s function_name\n",
               fndecl_name(fun->decl) );
        printf("Executing my_pass execute with function %s function_name\n",
               function_name(fun) );
        printf("Executing my_pass execute with function %s current_function_name\n",
               current_function_name() );
        basic_block bb;
        FOR_EACH_BB_FN(bb, cfun)
        {
            printf("basic block index: %i\n", bb->index);
            printf("start line no: %i", gimple_lineno(gsi_stmt(gsi_start_bb(bb))));
        }
        return 0;
    }
};

#endif //CODE_PLUGIN_H
