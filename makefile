TARGET = libesys
OUTDIR = lib
LIBS = -lesys
CC = g++
INCLUDES = include

EXAMPLE_TARGET = esys-demo
EXAMPLE_OUTDIR = bin

INCPARAMS=$(foreach d, $(INCLUDES), -I$d)

#OPTFLAGS = -s -O3
CFLAGS = -g -Wall -std=c++11 $(INCPARAMS) $(OPTFLAGS)
LFLAGS = -Wall -L$(OUTDIR)/
RUNARGS = 

SRCS = src/app/SimpleApp.cpp src/app/AppContext.cpp src/sys/AbstractThread.cpp 
SRCS +=src/sys/StopWatch.cpp

EXAMPLE_SRCS = example/main.cpp 

OBJS = $(subst .cpp,.o,$(SRCS))

.PHONY: default all $(EXAMPLE_TARGET) clean

default: $(TARGET)
all: default $(EXAMPLE_TARGET)

.PRECIOUS: $(TARGET) $(OBJS)

DEPS := $(OBJS:.o=.d)

-include $(DEPS)

%.o: %.cpp
	@$(CC) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET): $(OBJS)
	@mkdir -p $(OUTDIR)
	@ar rvs $(OUTDIR)/$@.a $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(OUTDIR)/$(TARGET).a
	rm -f $(EXAMPLE_OUTDIR)/$(EXAMPLE_TARGET)
	
# Example code
$(EXAMPLE_TARGET): main.o $(OBJS)
	@mkdir -p $(EXAMPLE_OUTDIR)
	$(CC) $< $(LFLAGS) $(LIBS) -o $(EXAMPLE_OUTDIR)/$@ -pthread $(OPTFLAGS)


main.o: example/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
