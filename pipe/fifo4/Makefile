	
CFLAG+=  -fsanitize=address -fsanitize-recover=address 
ARCH := 1111111111111111111111

all: 
	@$(MAKE) xuh ARCH=222222
	
	
	@echo  $(ARCH) 
#	gcc  write_fifo.c -g  -o write.app    $(CFLAG) -lpthread
#	gcc read_fifo.c -g -o read.app   $(CFLAG) -lpthread
    
    
clean:
	-rm -f *.temp    
	-rm -f *.app
 
xuh:
	@echo ================== $(ARCH) 

    
premake:
	echo $(ARCH)=====1
ifeq ($(ARCH),x86_64)
	echo "premake"
	$(MAKE) ARCH=arm64 xuhong0
	echo "premake===end $(ARCH)"
else 
	echo "fkyou "
endif
	echo $(ARCH)===premake=finish=2

xuhong0 xuhonga xuhongb b:
	@echo "==================$(ARCH) ============================fkyou 0"
	echo $@
    
xuhong4:
	@echo "==================$(ARCH) ============================fkyou 4"
    
xuhong1:
	@echo "fkyou 1"

xuhong2:
	@echo "fkyou 2"
    
xuhong3:
	@echo "fkyou 3"

precompiling: premake
	echo "precompiling"

Compiling: precompiling
	echo "Compiling"

release: Compiling
	echo "release"
    
xuhong: xuhong0
	echo $(ARCH)
    #下面所有的目标都是并行走的
	$(MAKE)  xuhong1  xuhong2 xuhong3  premake xuhong4
