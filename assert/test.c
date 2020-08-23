/*******************************
client.c
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <assert.h>
int main()
{    
	printf("asssert 1  statrt \n");
	assert(1);
	printf("asssert 1  statrt \n");

	printf("asssert 0  statrt \n");
	assert(0);
	printf("asssert 0  end \n");
	printf("asssert 1  statrt \n");
	assert(1);
	printf("asssert 1  statrt \n");
}


