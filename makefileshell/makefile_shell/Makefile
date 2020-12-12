	
CFLAG+=  -fsanitize=address -fsanitize-recover=address 

all:
	$(shell test.sh)
	gcc  write_fifo.c -g  -o write.app    $(CFLAG) -lpthread
	gcc read_fifo.c -g -o read.app   $(CFLAG) -lpthread
clean:
	-rm -f *.temp    
	-rm -f *.app
    
    
