CC=clang++
CFLAGS=-Wall -I../../include
LDFLAGS=`sdl-config --cflags --libs` -framework OpenGL -L../../lib -lflamingo

TARGET   = FlamingoTest
SRCEXT   = cpp

SRCS     := $(shell find . -name '*.$(SRCEXT)')

all: $(TARGET)

$(TARGET): clean
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	@$(RM) -rf lib
	@$(RM) -f $(TARGET)

