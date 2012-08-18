CC=clang++
CFLAGS=-c -Wall -Iinclude -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/Python.framework/Headers -DSWIG_TYPE_TABLE=flamingo
LDFLAGS=-lIL -lphysfs -framework SDL -framework OpenGL -lsqlite3 -framework Python -dynamiclib

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
SWIGINC  := $(patsubst %.i,include/FL/swig/%.h,$(SWIGSRC))

all: clean swigheaders $(LIBDIR)/$(TARGET) pyswig tests

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

swigheaders:
	swig -python -external-runtime include/FL/swigpyrun.h

buildswig:
	@echo "\nBuilding Swig Modules...\n"

pyswig: buildswig $(SWIGWRAP)
	ARCHFLAGS="-arch x86_64" CC="clang" python setup.py build_ext --inplace --quiet

$(SWIGDIR)/%_wrap.cxx: $(SWIGDIR)/%.i
	swig -python -c++ -outdir $(PYDIR)/$(shell dirname $(patsubst $(SWIGDIR)/%.i,%.i,$<)) $<

tests: $(LIBDIR)/$(TARGET)
	@echo "\nBuilding Tests...\n"
	@for dir in $(TESTDIRS); do $(MAKE) -C $$dir; done;

clean:
	@$(RM) -r $(OBJDIR)/*
	@$(RM) -r $(SWIGDIR)/*.cxx
	@$(RM) -r $(SWIGDIR)/components/*.cxx
	@$(RM) -r $(SWIGDIR)/events/*.cxx
	@$(RM) -r $(LIBDIR)/*
	@for dir in $(TESTDIRS); do $(MAKE) clean -C $$dir; done;
	@for f in $(shell find $(PYDIR)/* ! \( -name '__init__.py' \) ! \( -name 'script.py' \) ! \( -name 'inputmanager.py' \) -type f); do $(RM) $$f; done;

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

