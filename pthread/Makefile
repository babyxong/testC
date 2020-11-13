

SRC=$(wildcard *.c)

APP = $(patsubst %.c,%,$(wildcard *.c)).app

all: $(APP)
	

$(APP): $(SRC)
	gcc $< -o $@ -lpthread
    
clean:
	-rm -f *.app



