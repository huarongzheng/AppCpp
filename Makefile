CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Polymorphism.o

LIBS =

#TARGET =	MatchEngineData/AppCpp
TARGET =	AppCpp

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f  *.o $(OBJS) $(TARGET)
