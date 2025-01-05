
BUILDDIR?=build

CFLAGS+=-Iinclude
CFLAGS+=-Wno-changes-meaning

all: $(BUILDDIR) $(BUILDDIR)/libsrc $(BUILDDIR)/libsrc/glWebKit $(BUILDDIR)/libsrc/example $(BUILDDIR)/libglWebKit.so $(BUILDDIR)/example

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/libsrc:
	mkdir -p $@

$(BUILDDIR)/libsrc/glWebKit:
	mkdir -p $@

$(BUILDDIR)/libsrc/example:
	mkdir -p $@

# glWebKit
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKit.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebkitClient.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebkitRenderer.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebkitThreading.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebkitUtils.o

$(BUILDDIR)/libglWebKit.so: $(glWebKit_OBJECTS)
	gcc $^ -o $@ -shared

$(BUILDDIR)/libsrc/glWebKit/%.o: libsrc/glWebKit/%.cpp
	g++ -c $^ -o $@ -fPIC $(CFLAGS)

example_OBJECTS+=$(BUILDDIR)/libsrc/example/glUtil.cxx
example_OBJECTS+=$(BUILDDIR)/libsrc/example/main.cxx

$(BUILDDIR)/example: $(example_OBJECTS)
	gcc $^ -o $@ -shared -lglWebKit -L$(BUILDDIR) -W,rpath=$(BUILDDIR)

$(BUILDDIR)/libsrc/example/%.o: libsrc/example/%.cxx
	g++ -c $^ -o $@ -fPIC $(CFLAGS)

