OBJS = main.o gene.o population.o
SRCS = $(OBJS:.o=.c)
TARGET = maxcut
CC = g++

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -g -o $@ $^
.cpp.o:
	$(CC) -g -c $<

clean :
	rm -f $(TARGET) $(OBJS)

main.o : env.h gene.h population.h main.cpp
gene.o : env.h gene.h gene.cpp
population.o : env.h gene.h population.h population.cpp
