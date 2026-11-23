
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -lsqlite3

TARGET = neurotraffic

SOURCES = src/main.cpp \
	  src/TrafficLane.cpp \
	  src/TrafficController.cpp \
	  src/TrafficPredictor.cpp \
	  src/RouteOptimizer.cpp \
	  src/Database.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
