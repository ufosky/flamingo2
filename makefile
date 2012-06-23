CC=clang++
CFLAGS=-c -Wall -Iinclude
LDFLAGS=-lsdl `sdl-config --cflags --libs` -framework OpenGL

TARGET   = flamingo

SRCEXT   = cpp
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

SRCS    := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET) : buildrepo $(OBJS)
	@mkdir -p `dirname $@`
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	

$(OBJDIR)/%.o: %.$(SRCEXT)
#	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(CC) $(CFLAGS) $< -o $@

clean:
	@$(RM) -r $(OBJDIR)/*
	@$(RM) $(BINDIR)/$(TARGET)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done;
endef

#define make-depend
#  H=$($(CC) -MM -MF $3 -MP -MT $2 $(CFLAGS) $1 -vl)
#endef

