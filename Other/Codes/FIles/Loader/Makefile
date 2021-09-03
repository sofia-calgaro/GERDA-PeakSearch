CXX = c++

INC = $(shell gerda-ada-config --cflags) \
      $(shell gelatio-config --cflags) \
      $(shell root-config --cflags) \
      $(shell mgdo-config --cflags)

LIBS = $(shell gerda-ada-config --libs) \
       $(shell gelatio-config --libs) \
       $(shell root-config --libs) -lTreePlayer \
       $(shell mgdo-config --cflags)

EXEC = IC-loader

all : $(EXEC)

% : %.cxx
	$(CXX) $(INC) $(LIBS) $^ -o $@

clean : 
	-rm $(EXEC)
