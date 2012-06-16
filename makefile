CC=g++
CFLAGS=-c -Wall -Iinclude
LDFLAGS=-lsdl `sdl-config --cflags --libs` -framework OpenGL
SOURCES=flamingo.cpp init.cpp event.cpp render.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BUILDDIR=build
EXECUTABLE=flamingo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS:%=$(BUILDDIR)/%) -o $(BUILDDIR)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@ 

run:
	$(BUILDDIR)/$(EXECUTABLE)

clean:
	rm -r $(BUILDDIR)/*
