
BUILDDIR?=build

CFLAGS+=-Iinclude

all: $(BUILDDIR)/libglWebKit.so $(BUILDDIR)/example

# glWebKit
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKit.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKitClient.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKitRenderer.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKitThreading.o
glWebKit_OBJECTS+=$(BUILDDIR)/libsrc/glWebKit/glWebKitUtils.o

$(BUILDDIR)/libglWebKit.so: $(glWebKit_OBJECTS)
	gcc $^ -o $@ -shared

$(BUILDDIR)/libsrc/glWebKit/%.o: libsrc/glWebKit/%.cpp
	g++ $^ -o $@ -fPIC $(CFLAGS)

example_OBJECTS+=$(BUILDDIR)/libsrc/example/glUtil.cxx
example_OBJECTS+=$(BUILDDIR)/libsrc/example/main.cxx

$(BUILDDIR)/example: $(example_OBJECTS)
	gcc $^ -o $@ -shared -lglWebKit -L$(BUILDDIR) -W,rpath=$(BUILDDIR)

$(BUILDDIR)/libsrc/example/%.o: libsrc/example/%.cxx
	g++ $^ -o $@ -fPIC $(CFLAGS)

