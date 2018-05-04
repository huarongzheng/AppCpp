CXXFLAGS =	-O2 -Wl,--no-as-needed -std=c++11 -pthread

OBJS =		thread.o

LIBS = 

#TARGET =	MatchEngineData/AppCpp
TARGET =	AppCpp

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -std=c++11 -pthread

all:	$(TARGET)

clean:
	rm -f  *.o $(OBJS) $(TARGET)
