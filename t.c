#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"



int main(int argc, char *argv[]){
	char * mtest = malloc (50000); //allocates 13 pages (sums to 16), vm.c puts page #15 in file.

	mtest[48000] = 'F'; // accesses page #15 (currently on file in lifo)
						// vm.c should bring back page #15 instead of #16
	mtest[48001] = 'M'; // accesses page #15 (now on ram)
	char * mtest2 = malloc(1);			// allocates 8 new pages (#1 - #14, #24 in ram, #15-#23 on file) 
	mtest[48002] = 'L'; // accesses page #15 (currently on file in lifo)
						// vm.c should bring back page #15
	mtest[48003] = 0;  	// accesses page #15 (now on ram) instead of #24
	printf(1, "%s\n",&mtest[48000]);
	free(mtest);
	free(mtest2);
	exit();	//free pages #1 to #15 (#16-#24 are on file)
}