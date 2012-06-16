CC=g++
CFLAGS=-c -Wall -Iinclude
LDFLAGES=
SOURCES=flamingo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=flamingo
BUILDDIR=build

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(BUILDDIR)/$(OBJECTS) -o $(BUILDDIR)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)/$@ 

run:
	$(BUILDDIR)/$(EXECUTABLE)

clean:
	rm -r $(BUILDDIR)/*