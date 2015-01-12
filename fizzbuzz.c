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
	pthread_t ** threads = calloc( thread_count, sizeof( pthread_t* ) ); // Create a list of pointers to pthreads
	int li_createthread, li_jointhread; // Loop iterators for the thread creation and joining
	struct fizzbuzz_args args = { from, ceil((double)(to - from) / thread_count) + from }; // Arguments to be passed to the threads, from starts at from, to starts at the final number, divided by the number of workers and ceiled
	printf( "Operating fizzbuzz, starting at %d, ending at %d, and split into %d threads with each checking %d entries. \nThe last worker thread will have its jobs shortened where the job count is not divisable by the worker count.\n", from, to, thread_count, (int)ceil((double)(to-from) / thread_count) );

	for(li_createthread = 0; li_createthread < thread_count; li_createthread++ )
	{
		threads[li_createthread] = malloc( sizeof( pthread_t ) ); // Allocate thread in memory
		pthread_create( threads[li_createthread], NULL, &fizzbuzz_routine, &(struct fizzbuzz_args){args.from, args.to} ); // Begin thread, reading in the arguments as a pointer to a compound literal containing the previously defined arguments, this is to keep them unique.
		printf( "Created thread %d\n", li_createthread );

		args.from = args.to + 1; // Move args.from for the next worker to the position one after the current
		args.to = args.to + ceil((double)(to - from) / thread_count); // Move to, to the next batch which is the jobs divided by the number of worker threads (i.e. 0-30, 2 threads, first job is 0-15, second job is then 16-30)
		if( args.to > to ) { args.to = to; } // In the event that we have a job number not divisible by the number of workers, we truncate the final worker
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

