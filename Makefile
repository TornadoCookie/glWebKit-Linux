
BUILDDIR?=build

CFLAGS+=-Iinclude
CFLAGS+=-Wno-changes-meaning

all: $(BUILDDIR) $(BUILDDIR)/src $(BUILDDIR)/src/rlWebKit $(BUILDDIR)/src/example $(BUILDDIR)/librlWebKit.so $(BUILDDIR)/example

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/src:
	mkdir -p $@

$(BUILDDIR)/src/rlWebKit:
	mkdir -p $@

$(BUILDDIR)/src/example:
	mkdir -p $@

# rlWebKit
rlWebKit_OBJECTS+=$(BUILDDIR)/src/rlWebKit/rlWebKit.o
rlWebKit_OBJECTS+=$(BUILDDIR)/src/rlWebKit/rlWebkitClient.o
rlWebKit_OBJECTS+=$(BUILDDIR)/src/rlWebKit/rlWebkitRenderer.o
rlWebKit_OBJECTS+=$(BUILDDIR)/src/rlWebKit/rlWebkitThreading.o
rlWebKit_OBJECTS+=$(BUILDDIR)/src/rlWebKit/rlWebkitUtils.o

$(BUILDDIR)/librlWebKit.so: $(rlWebKit_OBJECTS)
	gcc $^ -o $@ -shared

$(BUILDDIR)/src/rlWebKit/%.o: src/rlWebKit/%.cpp
	g++ -c $^ -o $@ -fPIC $(CFLAGS)

example_OBJECTS+=$(BUILDDIR)/src/example/glUtil.o
example_OBJECTS+=$(BUILDDIR)/src/example/main.o

$(BUILDDIR)/example: $(example_OBJECTS)
	gcc $^ -o $@  -lrlWebKit -L$(BUILDDIR) -Wl,-rpath,$(BUILDDIR) -lSDL2 -lm -lstdc++ -lGLEW -lGL -Lbin64 -lEAWebKitd -Wl,-rpath,bin64 -lX11

$(BUILDDIR)/src/example/%.o: src/example/%.cxx
	g++ -c $^ -o $@ $(CFLAGS)

