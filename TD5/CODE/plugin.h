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
#include <bitmap.h>

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
void td5_q1(function * fun)
{
    basic_block bb;
    basic_block runner;
    edge p;
    edge_iterator ie;
    bitmap map;

    FOR_EACH_BB_FN(bb,fun)
    {
        if(EDGE_COUNT(bb->preds) >= 2){
            FOR_EACH_EDGE(p, ie, bb->preds){
                runner = p->src;
                doms_b = get_immediate_dominator(CDI_DOMINATORS, bb);
                while(runner != doms_b){
                    if(1 == bitmap_set_bit(&map[runner->index],)){
                        break;
                    }
                    bitmap_set_bit(&map[runner->index],);

                    runner = get_immediate_dominator(CDI_DOMINATORS, runner);
                }
            }
        }
    }
}
/* TD5 - Q2 */
void td5_q2(function * fun){
    basic_block b;
    edge p;
    edge_iterator ie;
    bitmap map;

    FOR_EACH_BB_FN(b,fun){
        FOR_EACH_EDGE(p, ie, b->preds){
            basic_block runner = p->src;
            basic_block dom = p->dest;
            if(runner == EXIT_BLOCK_PTR_FOR_FN(fun)){
                continue;
            }
            dom = get_immediate_dominator(CDI_DOMINATORS, b)
            while(runner != b){
                if(!bitmap_set_bit(&map[runner->index],dom)){
                    break;
                }
                runner = get_immediate_dominator(CDI_DOMINATORS, runner)
            }
        }
    }
}
/* TD5 - Q3 */
void td5_q3(function * fun){

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
        td5_q1(fun);
        return 0;
    }
};

#endif //CODE_PLUGIN_H
