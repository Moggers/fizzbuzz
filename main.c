#include <stdio.h>
#include <stdlib.h>
#include <argtable2.h>
#include "fizzbuzz.h"

int main( int argc, char * argv[] )
{
	struct arg_int *from = arg_int0( NULL, "from", "<n>", "start number" );
	struct arg_int *to = arg_int0( NULL, "to", "<n>", "end number" );
	struct arg_int *threads = arg_int0( NULL, "threads", "<n>", "thread count" );
	struct arg_lit *help =  arg_lit0( "h", "help", "print this text" );
	struct arg_end *end = arg_end( 3 );
	void * argtable[] = { from, to, threads, help, end };

	if( arg_nullcheck( argtable ) != 0 )
	{
		printf( "Failure to initialize argument list\n" );
		return;
	}

	from->ival[0] = 0;
	to->ival[0] = 30;
	threads->ival[0] = 2;

	int nerrors = arg_parse( argc, argv, argtable );

	if( help->count > 0 )
	{
		printf( "Usage: %s\n", argv[0] );
		arg_print_syntax( stdout, argtable, "\n" );
		printf( "Solve the common fizzbuzz problem, using various silly little optimizations that -O3 would probably do for us anyway :)\n\n" );
		arg_print_glossary( stdout, argtable, "  %-20s %s\n" );
		arg_freetable( argtable, sizeof(argtable)/sizeof(argtable[0] ) );
		return;
	}
	if( nerrors == 0 )
	{
		fizzbuzz_start( from->ival[0], to->ival[0], threads->ival[0] );
	}
	if( nerrors > 0 )
	{
		arg_print_errors( stdout, end, argv[0] );
		arg_print_syntax( stdout, argtable, "\n" );
	}

	arg_freetable( argtable, sizeof(argtable)/sizeof(argtable[0] ) );
}
