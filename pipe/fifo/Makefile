
include Makefile.define

all:    
	make -C ../fifo2
	gcc  write_fifo.c -g  -o write.app    
	gcc read_fifo.c -g -o read.app  
clean:
	-rm -f *.temp    
	-rm -f *.app
    
    
