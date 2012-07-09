CC=clang++
CFLAGS=-c -Wall -Iinclude -I/Library/Frameworks/SDL.framework/Headers
LDFLAGS=-lIL -lphysfs -framework SDL -framework OpenGL -dynamiclib

TARGET    = libflamingo.dylib
LIBNAME   = flamingo

SRCEXT    = cpp
SRCDIR    = src
TESTDIR   = test
OBJDIR    = build
LIBDIR    = lib
SWIGDIR   = swig
PYDIR	  = python/flamingo

SRCS     := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS  := $(shell find $(SRCDIR) -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
TESTDIRS := $(shell find $(TESTDIR) -name 'makefile' -exec dirname {} \; | uniq)
OBJS     := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

SWIGSRC  := $(shell find $(SWIGDIR) -name '*.i')
SWIGWRAP := $(patsubst %.i,%_wrap.cxx,$(SWIGSRC))

all: clean $(LIBDIR)/$(TARGET) pyswig tests

buildflamingo:
	@echo "Building Flamingo..."

$(LIBDIR)/$(TARGET): buildrepo buildflamingo $(OBJS)
	@echo "\nLinking Flamingo...\n"
	@mkdir -p `dirname $@`
#	ar rs $@ $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -install_name @executable_path/../Frameworks/libflamingo.dylib -o $(LIBDIR)/xcode/$(TARGET)
	$(CC) $(LDFLAGS) $(OBJS) -o $(LIBDIR)/$(TARGET)

$(OBJDIR)/%.o: %.$(SRCEXT)
#	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(CC) $(CFLAGS) $< -o $@

buildswig:
	@echo "\nBuilding Swig Modules...\n"

pyswig: buildswig $(SWIGWRAP)
	ARCHFLAGS="-arch i386 -arch x86_64" python setup.py build_ext --inplace

$(SWIGDIR)/%_wrap.cxx: $(SWIGDIR)/%.i
	swig -python -c++ $<
	@mv $(SWIGDIR)/*.py $(PYDIR)/

tests: $(LIBDIR)/$(TARGET)
	@echo "\nBuilding Tests...\n"
	@for dir in $(TESTDIRS); do $(MAKE) -C $$dir; done;

clean:
	@$(RM) -r $(OBJDIR)/*
	@$(RM) -r $(SWIGDIR)/*.cxx
	@$(RM) -r $(LIBDIR)/*
	@for dir in $(TESTDIRS); do $(MAKE) clean -C $$dir; done;
	@$(MAKE) clean -C $(PYDIR)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done;
	mkdir -p $(LIBDIR)/
	mkdir -p $(LIBDIR)/xcode
endef

#define make-depend
#  $(CC) -MM -MF $3 -MP -MT $2 $(CFLAGS) $1 -vl
#endef

