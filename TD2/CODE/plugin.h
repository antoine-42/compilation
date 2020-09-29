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
/* TD3 - Q1 */
void print_mpi_function(gimple * stmt){
    tree current_fn_decl = gimple_call_fndecl(stmt);
    const char* name = get_name(current_fn_decl);
    if (4 >= strlen(name) && ( strncmp("mpi_",name,4) == 0 || strncmp("MPI_",name,4) == 0 )) {
        printf("%s\n", name);
    }
    return;
}
void td3_q1(function * fun)
{
    basic_block bb;
    gimple_stmt_iterator gsi;
    gimple *stmt;

    FOR_EACH_BB_FN(bb,fun)
    {
        for (gsi=gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
            stmt = gsi_stmt(gsi);
            if (is_gimple_call(stmt)){
                print_mpi_function(stmt);
            }
        }
    }
}
/* TD3 - Q2 */
void print_file_mpi_function(gimple * stmt){
    tree current_fn_decl = gimple_call_fndecl(stmt);
    const char* name = get_name(current_fn_decl);
    for ( int mpi_function = 0; mpi_function < LAST_AND_UNUSED_MPI_COLLECTIVE_CODE; ++mpi_function)
    {
        if (strcmp(name,mpi_collective_name[mpi_function]) == 0) {
            printf("%s\n", name);
        }
    }
}
void td3_q2(function * fun)
    {
        basic_block bb;
        gimple_stmt_iterator gsi;
        gimple *stmt;

        FOR_EACH_BB_FN(bb,fun)
        {
            for (gsi=gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
            {
                stmt = gsi_stmt(gsi);
                if (is_gimple_call(stmt)){
                    print_file_mpi_function(stmt);
                }
            }
        }
    }
     /* TD3 - Q3 */
int get_mpi_function(gimple * stmt){
    tree current_fn_decl = gimple_call_fndecl(stmt);
    const char* name = get_name(current_fn_decl);
    for ( int mpi_function = 0; mpi_function < LAST_AND_UNUSED_MPI_COLLECTIVE_CODE; ++mpi_function)
    {
        if (strcmp(name,mpi_collective_name[mpi_function]) == 0) {
            return mpi_function;
        }
    }
    return -1;
}
void td3_q3(function * fun)
{
    basic_block bb;
    gimple_stmt_iterator gsi;
    gimple *stmt;

    FOR_EACH_BB_FN(bb,fun)
    {
        for (gsi=gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
            stmt = gsi_stmt(gsi);
            if (is_gimple_call(stmt)){
                printf("%i\n", get_mpi_function(stmt));
            }
        }
    }
}
/* TD3 - Q4 */
// aux
///* Basic block information indexed by block number.  */
//struct GTY((chain_next ("%h.next_bb"), chain_prev ("%h.prev_bb"))) basic_block_def {
//    /* The edges into and out of the block.  */
//    vec<edge, va_gc> *preds;
//    vec<edge, va_gc> *succs;
//
//    /* Auxiliary info specific to a pass.  */
//>>> PTR GTY ((skip (""))) aux; <<<<<<<
//
//    /* Innermost loop containing the block.  */
//    struct loop *loop_father;

/* TD3 - Q5 */
void td3_q5(function * fun)
{
    basic_block bb;
    gimple_stmt_iterator gsi;
    gimple *stmt;

    FOR_EACH_BB_FN(bb,fun)
    {
        for (gsi=gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
            stmt = gsi_stmt(gsi);
            if (is_gimple_call(stmt)){
                bb->aux = (void*) get_mpi_function(stmt);
            }
        }
    }

    FOR_EACH_BB_FN(bb,fun)
    {
        for (gsi=gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
        {
            stmt = gsi_stmt(gsi);
            if (is_gimple_call(stmt)){
                bb->aux = (void*) 0;
            }
        }
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
        td3_q5(fun);
//        printf("Executing my_pass execute with function %s function_name\n",
//               fndecl_name(fun->decl) );
//        printf("Executing my_pass execute with function %s function_name\n",
//               function_name(fun) );
//        printf("Executing my_pass execute with function %s current_function_name\n",
//               current_function_name() );
//        basic_block bb;
//        FOR_EACH_BB_FN(bb, cfun)
//        {
//            printf("basic block index: %i\n", bb->index);
//            printf("start line no: %i", gimple_lineno(gsi_stmt(gsi_start_bb(bb))));
//        }
        return 0;
    }
};

#endif //CODE_PLUGIN_H
