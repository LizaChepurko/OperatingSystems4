OBJS	= General.o
SOURCE	= General.cpp
HEADER	= 
OUT	= graph
FLAGS	= -g -c -Wall
LFLAGS	= 
CC	= g++

all:	graph

graph: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

General.o: General.cpp
	$(CC) $(FLAGS) General.cpp 

clean:
	rm -f $(OBJS) $(OUT)
