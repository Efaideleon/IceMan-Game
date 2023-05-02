CC = /usr/bin/g++    # On lnxsrv07 or 09, replace this with /usr/local/cs/bin/g++
LIBS = -framework OpenGL -lglut -L/opt/homebrew/Cellar/freeglut/3.4.0/lib
RPATH = 

# On lnxsrv07 or 09, uncommment the following line
#RPATH = -Wl,--rpath=/usr/local/cs/lib64

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean


all: IceMan

%.o: %.cpp $(HEADERS)
	$(CC) -c -std=c++11 $< -o $@ -Wno-deprecated-declarations

IceMan: $(OBJECTS) 
	$(CC) $(RPATH) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f IceMan 
