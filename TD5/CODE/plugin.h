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



/* TD3 */
/* Enum to represent the collective operations */
enum mpi_collective_code {
#define DEFMPICOLLECTIVES( CODE, NAME ) CODE,
#include "MPI_collectives.def"
    LAST_AND_UNUSED_MPI_COLLECTIVE_CODE
#undef DEFMPICOLLECTIVES
} ;

/* Name of each MPI collective operations */
#define DEFMPICOLLECTIVES( CODE, NAME ) NAME,
const char *const mpi_collective_name[] = {
#include "MPI_collectives.def"
} ;
#undef DEFMPICOLLECTIVES

/* TD5 - Q1 */
void td4_q5(function * fun)
{
    basic_block bb;

    FOR_EACH_BB_FN(bb,fun)
    {
        //todo
    }
}


class my_pass : public gimple_opt_pass {
public:
    my_pass(gcc::context *ctxt)
            : gimple_opt_pass(my_pass_data, ctxt) {}

    my_pass *clone() { return new my_pass(g); }

    bool gate (function *fun) {
        return true;
    }

    unsigned int execute (function *fun) {
        td4_q5(fun);
        return 0;
    }
};

#endif //CODE_PLUGIN_H
