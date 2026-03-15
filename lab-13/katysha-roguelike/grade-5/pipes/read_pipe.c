#include "pipes.h"
void read_pipe(int p,char *b,int size){while(size){int r=read(p,b,size);if(r<=0)exit(0);b+=r;size-=r;}}
