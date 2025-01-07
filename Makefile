
BUILDDIR?=build

CFLAGS+=-Iinclude
CFLAGS+=-Wno-changes-meaning

all: $(BUILDDIR) $(BUILDDIR)/src $(BUILDDIR)/src/glWebKit $(BUILDDIR)/src/example $(BUILDDIR)/libglWebKit.so $(BUILDDIR)/example

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/src:
	mkdir -p $@

$(BUILDDIR)/src/glWebKit:
	mkdir -p $@

$(BUILDDIR)/src/example:
	mkdir -p $@

# glWebKit
glWebKit_OBJECTS+=$(BUILDDIR)/src/glWebKit/glWebKit.o
glWebKit_OBJECTS+=$(BUILDDIR)/src/glWebKit/glWebkitClient.o
glWebKit_OBJECTS+=$(BUILDDIR)/src/glWebKit/glWebkitRenderer.o
glWebKit_OBJECTS+=$(BUILDDIR)/src/glWebKit/glWebkitThreading.o
glWebKit_OBJECTS+=$(BUILDDIR)/src/glWebKit/glWebkitUtils.o

$(BUILDDIR)/libglWebKit.so: $(glWebKit_OBJECTS)
	gcc $^ -o $@ -shared

$(BUILDDIR)/src/glWebKit/%.o: src/glWebKit/%.cpp
	g++ -c $^ -o $@ -fPIC $(CFLAGS)

example_OBJECTS+=$(BUILDDIR)/src/example/glUtil.o
example_OBJECTS+=$(BUILDDIR)/src/example/main.o

$(BUILDDIR)/example: $(example_OBJECTS)
	gcc $^ -o $@  -lglWebKit -L$(BUILDDIR) -Wl,-rpath,$(BUILDDIR) -lSDL2 -lm -lstdc++ -lGLEW -lGL -Lbin64 -lEAWebKitd -Wl,-rpath,bin64 -lX11

$(BUILDDIR)/src/example/%.o: src/example/%.cxx
	g++ -c $^ -o $@ $(CFLAGS)

