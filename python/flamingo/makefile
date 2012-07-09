
SWIGGEN   := $(shell find . -name '*.so')
SWIGGENPY := $(patsubst ./_%.so,./%.py,$(SWIGGEN))

clean:
	for g in $(SWIGGEN) $(SWIGGENPY); do $(RM) $$g; done;

