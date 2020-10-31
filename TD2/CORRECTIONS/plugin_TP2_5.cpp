/**
 * TP 2 / QUESTION 5
 */
#include <gcc-plugin.h>
#include <plugin-version.h>
#include <tree.h>
#include <basic-block.h>
#include <gimple.h>
#include <tree-pass.h>
#include <context.h>
#include <function.h>
#include <gimple-iterator.h>


/* Global variable required for plugin to execute */
int plugin_is_GPL_compatible;


/* Global object (const) to represent my pass */
const pass_data my_pass_data =
{
	GIMPLE_PASS, /* type */
	"NEW_PASS", /* name */
	OPTGROUP_NONE, /* optinfo_flags */
	TV_OPTIMIZE, /* tv_id */
	0, /* properties_required */
	0, /* properties_provided */
	0, /* properties_destroyed */
	0, /* todo_flags_start */
	0, /* todo_flags_finish */
};

/* My new pass inheriting from regular gimple pass */
class my_pass : public gimple_opt_pass
{
	public:
		my_pass (gcc::context *ctxt)
			: gimple_opt_pass (my_pass_data, ctxt)
		{}

		/* opt_pass methods: */

		my_pass *clone ()
		{
			return new my_pass(g);
		}

		/* Gate function (shall we apply this pass?) */
		bool gate (function *fun)
		{
			printf("plugin: gate... \n");
			/******************************/
			/**** TD2 - QUESTION 3 & 4 ****/
			/******************************/

			const char * fname1 = fndecl_name(fun->decl);
			const char * fname2 = function_name(fun);
			const char * fname3 = current_function_name();
			printf("\t ... in function %s %s %s\n", fname1, fname2, fname3);

			/******************************/
			/** TD2 - FIN QUESTION 3 & 4 **/
			/******************************/
			return true;
		}

		/* Execute function */
		unsigned int execute (function *fun)
		{

			printf("plugin: execute...\n");
			/******************************/
			/**** TD2 - QUESTION 3 & 4 ****/
			/******************************/

			const char * fname1 = fndecl_name(fun->decl);
			const char * fname2 = function_name(fun);
			const char * fname3 = current_function_name();
			printf("\t ... in function %s %s %s\n", fname1, fname2, fname3);

			/******************************/
			/****   TD2 - QUESTION 5   ****/
			/******************************/

			basic_block bb;

			FOR_ALL_BB_FN(bb,fun)
			{
				printf(" --- %s --- |||++||| BLOCK INDEX %d \n", fname1, bb->index);

			}

			/******************************/
			/**   TD2 - FIN QUESTION 5   **/
			/******************************/

			/******************************/
			/** TD2 - FIN QUESTION 3 & 4 **/
			/******************************/
			return 0;
		}

};



/* Main entry point for plugin */
	int
plugin_init(struct plugin_name_args * plugin_info,
		struct plugin_gcc_version * version)
{
	struct register_pass_info my_pass_info;

	printf( "plugin_init: Entering...\n" ) ;

	/* First check that the current version of GCC is the right one */

	if(!plugin_default_version_check(version, &gcc_version))
		return 1;

	printf( "plugin_init: Check ok...\n" ) ;

	/* Declare and build my new pass */
	my_pass p(g);

	/* Fill info on my pass 
	   (insertion after the pass building the CFG) */
	my_pass_info.pass = &p;
	my_pass_info.reference_pass_name = "cfg";
	my_pass_info.ref_pass_instance_number = 0;
	my_pass_info.pos_op = PASS_POS_INSERT_AFTER;

	/* Add my pass to the pass manager */
	register_callback(plugin_info->base_name,
			PLUGIN_PASS_MANAGER_SETUP,
			NULL,
			&my_pass_info);

	printf( "plugin_init: Pass added...\n" ) ;

	return 0;
}


