# Simple Makefile for 8085 Emulator with Qt5

CXX = g++
CXXFLAGS = -std=c++17 -Wall $(shell pkg-config --cflags Qt5Widgets)
LDFLAGS = $(shell pkg-config --libs Qt5Widgets)
MOC = moc-qt5

TARGET = 8085_emulator
SOURCES = gui.cpp cpu8085.cpp
OBJECTS = gui.o cpu8085.o
HEADERS = cpu8085.h

all: $(TARGET)

gui.moc.cpp: gui.cpp
	$(MOC) gui.cpp -o gui.moc.cpp

gui.o: gui.cpp $(HEADERS) gui.moc.cpp
	$(CXX) $(CXXFLAGS) -c gui.cpp -o gui.o

cpu8085.o: cpu8085.cpp cpu8085.h
	$(CXX) $(CXXFLAGS) -c cpu8085.cpp -o cpu8085.o

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) gui.moc.cpp $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
