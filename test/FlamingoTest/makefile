CC=clang++
CFLAGS=-Wall -I../../include -I/Library/Frameworks/SDL.framework/Headers
LDFLAGS=-framework SDL -framework OpenGL -framework Cocoa -L../../lib -lflamingo -lIL -lphysfs

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

