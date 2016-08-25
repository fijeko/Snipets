#include <stdio.h>
#include <stdlib.h>
#include <time.h>   /* clock_t, clock, CLOCKS_PER_SEC */
   
FILE * save_file;

void show(int argc, char **argv, int *block, int turn )
{
	fprintf( save_file, " %5d :  ", turn );
	int i, v;
	for( i = 0; i < argc; i++ ){
		v = block[i];
		fprintf( save_file, "%s ", argv[v] );
	}
	fprintf( save_file, "\n" );
}

void perm_without_repetition( int argc, char **argv )
{
	// single combination - array of integer that is position in argv 
	int *single_cmb = malloc( argc * sizeof(int) );

	// lock allready used positions
	int *lock   = malloc( (argc + 1) * sizeof(int) );

	int cmb_iter;    // iterator through single_cmp
	int lock_iter;   // iterator through lock
	int cmb_nr;      // combination number (for show)
	int tmp_val;     // current value of current position

	// fill in arrays
	
	cmb_iter = 0;
	for( ; cmb_iter < argc; cmb_iter++ )
		{
			single_cmb[cmb_iter] = argc;
			lock[cmb_iter] = 0;
		}

	// start form first position 
	cmb_iter = 0;
	cmb_nr = 0;
	
	// when combination is argc means restart
	// when lock is 0 that position is free to use, when 1 allready used
	while( 1 )
		{
			tmp_val = single_cmb[cmb_iter];

			if( tmp_val == argc )
				lock_iter = 0;
			else
				{
					lock[tmp_val] = 0;
					lock_iter = tmp_val + 1;
				}
				
			while( ( lock[lock_iter] != 0 ) && lock_iter < argc ) lock_iter++;

			
			single_cmb[cmb_iter] = lock_iter;

			if( lock_iter == argc )
				cmb_iter--;
			else
				{
					lock[lock_iter] = 1;
					cmb_iter++;
				}
				
			if( cmb_iter == argc )
				{
					show( argc, argv, single_cmb, cmb_nr );
					cmb_nr++;
					cmb_iter--;
				}
				
			if( cmb_iter < 0 ) break;
		}

}


void perm_with_repetition( int argc, char **argv )
{
	// single combination - array of integer that is position in argv 
	int *single_cmb = malloc( argc * sizeof(int) );

	int cmb_iter;    // iterator through single_cmp
	int cmb_nr;      // combination number (for show)
	int tmp_val;     // current value of current position

	// fill in array
	cmb_iter = 0;
	for( ; cmb_iter < argc; cmb_iter++ )
		{
			single_cmb[cmb_iter] = argc;
		}

	// start form first position 
	cmb_iter = 0;
	cmb_nr = 0;
	
	// when combination is argc means restart
	while( 1 )
		{
			tmp_val = single_cmb[cmb_iter];

			if( tmp_val == argc )
				tmp_val = 0;
			else
				tmp_val++;

			single_cmb[cmb_iter] = tmp_val;
			
			if( tmp_val == argc )
				cmb_iter--;
			else
				cmb_iter++;
				
			if( cmb_iter == argc )
				{
					show( argc, argv, single_cmb, cmb_nr );
					cmb_nr++;
					cmb_iter--;
				}
				
			if( cmb_iter < 0 ) break;
		}

}


int main( int argc, char **argv )
{
	// working safeguard
	if(argc < 3){
		printf(	
			"Usage: ./permutation arg1 arg2 [arg3 [arg4 [...]]]\n" 
			"\t argn - any string that will be use as element of permutation\n"
		);
		return 1;
	}

	time_t start_time_1, start_time_2, end_time_1, end_time_2;
	save_file = stdout;
	//~ save_file = fopen( "combinations", "w" );
	//~ if( save_file == NULL )
	//~ {
		//~ fprintf( stderr, "Can't open file for output!\n" );
		//~ exit( 1 );
	//~ }

	// remove program name and adjust size of args
	argv++;
	argc--;

	printf(	"Permutation without repetition\n" );
	start_time_1 = time(0);
	perm_without_repetition( argc, argv );
	end_time_1 = time(0);

	printf(	"Permutation with repetition\n" );
	start_time_2 = time(0);
	perm_with_repetition( argc, argv );
	end_time_2 = time(0);

	printf(	"time(without repetition): %d-%d; time(with repetition): %d-%d \n",
		(int)start_time_1, (int)end_time_1, (int)start_time_2, (int)end_time_2 );

	printf( "CLOCKS_PER_SEC: %f %f \n",
		(double)(end_time_1 - start_time_1), // / CLOCKS_PER_SEC,
		(double)(end_time_2 - start_time_2) ); // / CLOCKS_PER_SEC );
		
	//~ if( !(fclose( save_file )) )
		//~ return 0;
	//~ else
		//~ {
			//~ printf( "Error closing file!\n");
			//~ return 1;
		//~ }

	return 0;
}
