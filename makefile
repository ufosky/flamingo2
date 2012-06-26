CC=clang++
CFLAGS=-c -Wall -Iinclude -fPIC
LDFLAGS=`sdl-config --libs` -framework OpenGL -dynamiclib

TARGET    = libflamingo.a
LIBNAME   = flamingo

SRCEXT    = cpp
SRCDIR    = src
TESTDIR   = test
OBJDIR    = build
LIBDIR    = lib

SRCS     := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS  := $(shell find $(SRCDIR) -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
TESTDIRS := $(shell find $(TESTDIR) -name 'makefile' -exec dirname {} \; | uniq)
OBJS     := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

all: $(LIBDIR)/$(TARGET) tests

$(LIBDIR)/$(TARGET): buildrepo $(OBJS)
	@mkdir -p `dirname $@`
	@$(RM) -f $(LIBDIR)/$(TARGET)
	ar rs $@ $(OBJS)

$(OBJDIR)/%.o: %.$(SRCEXT)
#	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(CC) $(CFLAGS) $< -o $@

tests: $(LIBDIR)/$(TARGET)
	@echo ""
	@echo "Building Tests..."
	@for dir in $(TESTDIRS); do $(MAKE) -C $$dir; done;

clean:
	@$(RM) -r $(OBJDIR)/*
	@$(RM) -r $(LIBDIR)/*
	@for dir in $(TESTDIRS); do $(MAKE) clean -C $$dir; done;

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done;
endef

#define make-depend
#  $(CC) -MM -MF $3 -MP -MT $2 $(CFLAGS) $1 -vl
#endef

