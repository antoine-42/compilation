/**
 * TP 2 / QUESTION 7
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


	const char *
print_func_name(function * fun)
{
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
	return fname1;
}


/******************************/
/****   TD2 - QUESTION 7   ****/
/******************************/

/* Build a filename (as a string) based on function name */
	static char *
cfgviz_generate_filename( function * fun, const char * suffix )
{
	char * target_filename ;

	target_filename = (char *)xmalloc( 2048 * sizeof( char ) ) ;


	snprintf( target_filename, 1024, "%s_%s_%d_%s.dot",
			current_function_name(),
			LOCATION_FILE( fun->function_start_locus ),
			LOCATION_LINE( fun->function_start_locus ),
			suffix ) ;

	return target_filename ;
}

/* Dump the graphviz representation of function 'fun' in file 'out' */
	static void
cfgviz_internal_dump( function * fun, FILE * out )
{
	basic_block bb;

	/* Print the header line and open the main graph */
	fprintf(out, "Digraph G{\n");

	FOR_ALL_BB_FN(bb,cfun)
	{

		/*
		   Print the basic block BB
		*/
		fprintf( out,
				"%d [label=\"BB %d\" shape=ellipse]\n",
				bb->index,
				bb->index
			   ) ;


		/*
		   Process output edges 
		*/
		edge_iterator eit;
		edge e;

		FOR_EACH_EDGE( e, eit, bb->succs )
		{
			const char *label = "";
			if( e->flags == EDGE_TRUE_VALUE )
				label = "true";
			else if( e->flags == EDGE_FALSE_VALUE )
				label = "false";

			fprintf( out, "%d -> %d [color=red label=\"%s\"]\n",
					bb->index, e->dest->index, label ) ;

		}
	}

	/* Close the main graph */
	fprintf(out, "}\n");
}

 int
cfgviz_dump( function * fun, const char * suffix )
{
	char * target_filename ; 
	FILE * out ;

	target_filename = cfgviz_generate_filename( fun, suffix ) ;

	printf( "[GRAPHVIZ] Generating CFG of function %s in file <%s>\n",
			current_function_name(), target_filename ) ;

	out = fopen( target_filename, "w" ) ;
  if ( out == NULL ) 
  {
    fprintf( stderr, "ERROR while opening DOT file <%s>\n", target_filename ) ;
    return 0 ;
  }

	cfgviz_internal_dump( fun, out ) ;

	fclose( out ) ;
	free( target_filename ) ;

  return 1 ;
}

/******************************/
/**   TD2 - FIN QUESTION 7   **/
/******************************/








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
			print_func_name(fun);
			return true;
		}

		/* Execute function */
		unsigned int execute (function *fun)
		{


			printf("plugin: execute...\n");
			const char * fname = print_func_name(fun);	

			/******************************/
			/**** TD2 - QUESTION 5 & 6 ****/
			/******************************/

			basic_block bb;
			gimple_stmt_iterator gsi;
			gimple *stmt;

			FOR_EACH_BB_FN(bb,fun)
			{
				gsi = gsi_start_bb(bb);
				stmt = gsi_stmt(gsi);
				printf(" --- %s --- |||++||| BLOCK INDEX %d : LINE %d\n", fname, bb->index, gimple_lineno(stmt));

			}

			/******************************/
			/** TD2 - FIN QUESTION 5 & 6 **/
			/******************************/


			/******************************/
			/****   TD2 - QUESTION 7   ****/
			/******************************/
			/* Skip system header functions */
			if ( !in_system_header_at( fun->function_start_locus ) )
      {
        if ( cfgviz_dump( fun, "0_ini" ) == 0 )
        {
          return 1 ;
        }
      }
			/******************************/
			/**   TD2 - FIN QUESTION 7   **/
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


