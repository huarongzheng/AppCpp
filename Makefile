CXXFLAGS =	-Wl,--no-as-needed -DDEBUG -g -std=c++11 -pthread
#CXXFLAGS =	-O2 -Wl,--no-as-needed -DDEBUG -g -std=c++11 -pthread

OBJS =		sharedPtr.o

LIBS = 

#TARGET =	MatchEngineData/AppCpp
TARGET =	AppCpp

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -std=c++11 -pthread

all:	$(TARGET)

clean:
	rm -f  *.o $(OBJS) $(TARGET)
