CC=clang++
CFLAGS=-Wall -I../../include -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/Python.framework/Headers
LDFLAGS=-framework SDL -framework OpenGL -framework Cocoa -framework Python -lIL -lphysfs -L../../lib -lflamingo

TARGET   = FlamingoTest
SRCEXT   = cpp

SRCS     := $(shell find . -name '*.$(SRCEXT)')

all: $(TARGET)

$(TARGET): clean
	@ln -s ../../lib lib
	$(CC) $(SRCS) SDLMain.m $(CFLAGS) $(LDFLAGS) -o $@

clean:
	@$(RM) -rf lib
	@$(RM) -f $(TARGET)

