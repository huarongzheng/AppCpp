CXXFLAGS =	-g -Wall -fmessage-length=0

OBJS =		RollDice.o

LIBS =

#TARGET =	MatchEngineData/AppCpp
TARGET =	AppCpp

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f  *.o $(OBJS) $(TARGET)
