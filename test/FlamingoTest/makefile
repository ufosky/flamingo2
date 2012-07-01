CC=clang++
CFLAGS=-Wall -I../../include -I/Library/Frameworks/SDL.framework/Headers
LDFLAGS=-framework SDL -framework OpenGL -framework Cocoa -L../../lib -lflamingo -lIL -lphysfs

TARGET   = FlamingoTest
SRCEXT   = cpp

SRCS     := $(shell find . -name '*.$(SRCEXT)')

all: $(TARGET)

$(TARGET): clean
	$(CC) $(SRCS) SDLMain.m $(CFLAGS) $(LDFLAGS) -o $@

clean:
	@$(RM) -f $(TARGET)

