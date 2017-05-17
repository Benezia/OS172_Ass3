#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"



int main(int argc, char *argv[]){
	char * mtest = malloc (50000); //allocates 13 pages (sums to 16)

	mtest[49000] = 'F'; // accesses the page on file (15th page in lifo)
	mtest[49001] = 'M'; // accesses the page on ram
	malloc(1);
	mtest[49002] = 'L'; // accesses the page on ram
	mtest[49003] = 0; // accesses the page on file (15th page in lifo)
	printf(1, "%s\n",&mtest[49000]);


	//badMalloc = badMalloc;
	exit();
}