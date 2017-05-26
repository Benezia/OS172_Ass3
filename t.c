#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"




void lapDance(){
	int i;
	int j;
	int PGSZ = 4096;
	char * mtest = malloc(70000);
	for (i = 0; i<50000; i++)
		mtest[i] = 'A'; //make sure all pages are lineary connected through malloc
	for (i = 0; i<50000; i+=PGSZ){
		for (j = 0; j<i; j+=PGSZ)
			printf(1, "%d ", (int)mtest[j]);
	}
	printf(1,"\n");
}

void lifoTest(){
  int i;
  char * mtest;
  mtest = malloc (50000); //allocates 13 pages (sums to 16), vm.c puts page #15 in file.
  for (i = 0; i < 4100; i++) { 
    mtest[30000+i] = ' '; 
    mtest[34000+i] = ' ';
  }
  printf(1, "filled 8100 pages with spaces...\n");

  for (i = 0; i < 50; i++) { 
    mtest[49100+i] = 'A'; //last six A's stored in page #16, the rest in #15
    mtest[45200+i] = 'B'; //all B's are stored in page #15.
  }
  mtest[49100+i] = 0;
  mtest[45200+i] = 0;
  printf(1, "FORKING...\n");
  
  if (fork() == 0){ //is son
  	printf(1,"SON\n");
    printf(1, "AA PAGE INDEX: %d\n", (int)&mtest[49100]%4096);
    printf(1, "BB PAGE INDEX: %d\n", (int)&mtest[45200]%4096);

    for (i = 40; i < 50; i++) { 
	    mtest[49100+i] = 'C'; //changes last ten A's to C
	    mtest[45200+i] = 'D'; //changes last ten B's to D
  	}
    printf(1, "%s\n",&mtest[49100]); // should print AAAAA..CCC...
    printf(1, "%s\n",&mtest[45200]); // should print BBBBB..DDD...
  	printf(1,"\n");
    free(mtest);
    exit();
  } else { //is parent
    wait();
  	printf(1,"PARENT:\n");
    printf(1, "AA PAGE INDEX: %d\n", (int)&mtest[49100]%4096);
    printf(1, "BB PAGE INDEX: %d\n", (int)&mtest[45200]%4096);
    printf(1, "%s\n",&mtest[49100]); // should print AAAAA...
    printf(1, "%s\n",&mtest[45200]); // should print BBBBB...
    free(mtest);
  }

}


void test1(){
  char * mtest; //allocates 13 pages (sums to 16), vm.c puts page #15 in file.
	char * mtest2;
  mtest = malloc (50000);
  mtest[48000] = 'F'; // accesses page #15 (currently on file in lifo)
                                          // vm.c should bring back page #15 instead of #16
  mtest[48001] = 'M'; // accesses page #15 (now on ram)
  mtest2 = malloc(1);			// allocates 8 new pages (#1 - #14, #24 in ram, #15-#23 on file) 

  mtest[48002] = 'L'; // accesses page #15 (currently on file in lifo)
                                          // vm.c should bring back page #15
  mtest[48003] = 0;  	// accesses page #15 (now on ram) instead of #24
  printf(1, "%s\n",&mtest[48000]);
  free(mtest);
  free(mtest2);
	exit();	//free pages #1 to #15 (#16-#24 are on file)
}


int main(int argc, char *argv[]){
  lapDance();
  exit();
}