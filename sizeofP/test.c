










 /*******************************
 client.c
 ********************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <malloc.h>


 #define PORT 8888
 
 typedef struct stXuh {
 
         char a1; 
         char a2;
         char a3;
         char a4;
 
         int aint;
		 char asc[20];
 
 }stXuh;
 
 
 stXuh gAtect[20];
 
 void fun(void *p)
 {
         
         
         p =     malloc(100);
		 free (p);
		 
		 
		 p = gAtect;
 
 
 }
 
 int main()
 {
     stXuh *pa;
         
     fun(pa);
     
     char *pb = malloc(200);
	 
	 
     printf("ptr  pa sizeof %d  \n", sizeof(pa->asc));
	 
	 
	 printf("ptr pb  sizeof %d  \n", sizeof(pb));
  
  
	 printf("ptr pb  sizeof %d  \n", _msize(pb));
  
  
 }