#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

struct fizzbuzz_args
{
	int from;
	int to;
};

void * fizzbuzz_routine( void * arg )
{
	struct fizzbuzz_args * arg_list = (struct fizzbuzz_args*)arg;
	char * buf = calloc( arg_list->to - arg_list->from, sizeof(char) * 8 );

	int li_fizzbuzzcount = arg_list->from - (arg_list->from % 15);
	int l;

	printf( "Worker begin fizzbuzz at %d, real work order is %d to %d, job description is at memory position %d\n", li_fizzbuzzcount, arg_list->from, arg_list->to, arg );
	switch( arg_list->from % 15 )
	{
		for( ; li_fizzbuzzcount < arg_list->to; li_fizzbuzzcount+=15 )
		{
			case 0:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount );
			}
			case 1:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 1 );
			}
			case 2:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 2 );
			}
			case 3:
			{
				l += sprintf( buf + l, "%s\n", "fizz" );
			}
			case 4:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 4 );
			}
			case 5:
			{
				l += sprintf( buf + l, "%s\n", "buzz" );
			}
			case 6:
			{
				l += sprintf( buf + l, "%s\n", "fizz" );
			}
			case 7:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 7 );
			}
			case 8:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 8 );
			}
			case 9:
			{
				l += sprintf( buf + l, "%s\n", "fizz" );
			}
			case 10:
			{
				l += sprintf( buf + l, "%s\n", "buzz" );
			}
			case 11:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 11 );
			}
			case 12:
			{
				l += sprintf( buf + l, "%s\n", "fizz" );
			}
			case 13:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 13 );
			}
			case 14:
			{
				l += sprintf( buf + l, "%d\n", li_fizzbuzzcount + 14 );
			}
			case 15:
			{
				l += sprintf( buf + l, "%s\n", "fizzbuzz" );
			}
		}
	}
}

void fizzbuzz_start( int from, int to, int thread_count )
{
	pthread_t ** threads = calloc( thread_count, sizeof( pthread_t* ) );
	int li_createthread, li_jointhread;
	struct fizzbuzz_args args = { from, ceil((double)(to - from) / thread_count) + from };
	printf( "Operating fizzbuzz, starting at %d, ending at %d, and split into %d threads with each checking %d entries. \nThe last worker thread will have its jobs shortened where the job count is not divisable by the worker count.\n", from, to, thread_count, (int)ceil((double)(to-from) / thread_count) );

	for(li_createthread = 0; li_createthread < thread_count; li_createthread++ )
	{
		threads[li_createthread] = malloc( sizeof( pthread_t ) );
		pthread_create( threads[li_createthread], NULL, &fizzbuzz_routine, &(struct fizzbuzz_args){args.from, args.to} );
		printf( "Created thread %d\n", li_createthread );

		args.from = args.to + 1;
		args.to = args.to + ceil((double)(to - from) / thread_count);
		if( args.to > to ) { args.to = to; }
	}

	printf( "Working..\n" );
	for( li_jointhread = 0; li_jointhread < thread_count; li_jointhread++ )
	{
		printf( "Waiting for thread %d\n", li_jointhread );
		pthread_join( *threads[li_jointhread], NULL );
		printf( "Thread %d finished\n", li_jointhread );
	}
	printf( "Done!\n" );
}

