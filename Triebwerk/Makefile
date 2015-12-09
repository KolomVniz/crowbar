#MAIN	= chrono_test
MAIN	= permut_test

OBJS	:= $(MAIN).o chrono.o ran64_gsl.o

CC	= clang
#CC	= gcc -std=gnu11
#CC	= clang++
#CC	= g++

OPTFLAGS	= -O3
#OPTFLAGS	= -O1 -march=core-avx2
CFLAGS		= -g -Wall -pedantic

LDFLAGS		= -lm -lgsl -lgslcblas


$(MAIN):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# in OBJS, substitute .o with .d, and include the list
-include $(OBJS:.o=.d)


%.o:	%.c Makefile
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $*.c > $*.d

clean:
	rm -f $(MAIN) *.o

cleanall:
	rm -f $(MAIN) *.o *~ *.d
