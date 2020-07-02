CXXFLAGS =	-Wl,--no-as-needed -DDEBUG -g -std=gnu++11 -pthread
#CXXFLAGS =	-O2 -Wl,--no-as-needed -DDEBUG -g -std=c++11 -pthread

#OBJS =		cpuAffinity.o
OBJS =		dataStructure.o

LIBS = 

#TARGET =	MatchEngineData/AppCpp
TARGET =	AppCpp

$(TARGET):	$(OBJS)
	$(CXX) -DDEBUG -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

clean:
	rm -f  *.o $(OBJS) $(TARGET)
