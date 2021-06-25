

#include <stdio.h>
#include <stdlib.h>
static int * g_count = NULL;
__attribute__((constructor)) void load_file()
{
	    printf("Constructor is called.\n");
	        g_count = (int *)malloc(sizeof(int));
		    if (g_count == NULL)
			        {
					    fprintf(stderr, "Failed to malloc memory.\n");
					        }
}
__attribute__((destructor)) void unload_file()
{
	    printf("destructor is called.\n");
	        if (g_count)
			    free(g_count);
}
int main()
{
    
     printf("main is called.\n");
	    return 0;
}
