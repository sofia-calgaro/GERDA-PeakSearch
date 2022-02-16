CXX = c++

INC = $(shell gerda-ada-config --cflags) \
      $(shell gelatio-config --cflags) \
      $(shell root-config --cflags) \
      $(shell mgdo-config --cflags) \
      $(shell clhep-config --include)

LIBS = $(shell gerda-ada-config --libs) \
       $(shell gelatio-config --libs) \
       $(shell root-config --libs) -lTreePlayer \
       $(shell mgdo-config --cflags) \
       $(shell clhep-config --libs)

EXEC = 95-114-BEGe-loader

all : $(EXEC)

% : %.cxx
	$(CXX) $(INC) $(LIBS) $^ -o $@

clean : 
	-rm $(EXEC)



