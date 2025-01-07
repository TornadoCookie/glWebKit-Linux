# Generated using Helium v2.1.0 (https://github.com/tornadocookie/he)

PLATFORM?=linux64-debug
DISTDIR?=build

.PHONY: all

RAYLIB_NAME=raylib5.5-$(PLATFORM)

ifeq ($(PLATFORM), linux64)
EXEC_EXTENSION=
LIB_EXTENSION=.so
LIB_EXTENSION_STATIC=.a
CC=gcc
CXX=g++
RAYLIB_DLL=-lraylib
CFLAGS+=-O2
CFLAGS+=-D RELEASE
CFLAGS+=-D EXEC_EXTENSION=\"\"
CFLAGS+=-D LIB_EXTENSION=\".so\"
endif

ifeq ($(PLATFORM), linux64-debug)
EXEC_EXTENSION=-debug
LIB_EXTENSION=.so
LIB_EXTENSION_STATIC=.a
CC=gcc
CXX=g++
RAYLIB_DLL=-lraylib
CFLAGS+=-g
CFLAGS+=-D DEBUG
CFLAGS+=-D EXEC_EXTENSION=\"-debug\"
CFLAGS+=-D LIB_EXTENSION=\".so\"
endif

ifeq ($(PLATFORM), win64)
EXEC_EXTENSION=.exe
LIB_EXTENSION=.dll
LIB_EXTENSION_STATIC=.a
CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
RAYLIB_DLL=-lraylibdll
CFLAGS+=-O2
CFLAGS+=-D RELEASE
CFLAGS+=-D EXEC_EXTENSION=\".exe\"
CFLAGS+=-D LIB_EXTENSION=\".dll\"
endif

ifeq ($(PLATFORM), web)
EXEC_EXTENSION=.html
LIB_EXTENSION=.a
LIB_EXTENSION_STATIC=.a
CC=emcc
CXX=em++
RAYLIB_DLL=-lraylib
CFLAGS+=-O2
CFLAGS+=-D RELEASE
CFLAGS+=-D EXEC_EXTENSION=\".html\"
CFLAGS+=-D LIB_EXTENSION=\".a\"
endif

PROGRAMS=example
LIBRARIES=librlWebKit 

EAWebKitd_NAME=libEAWebKitd-$(PLATFORM)
CFLAGS+=-Ilib/$(EAWebKitd_NAME)/include
LDFLAGS+=-Llib/$(EAWebKitd_NAME)/lib
LDFLAGS+=-lEAWebKitd
LDFLAGS+=-Wl,-rpath,lib/$(EAWebKitd_NAME)/lib


rlWebKit_NAME=librlWebKit-$(PLATFORM)
CFLAGS+=-Ilib/$(rlWebKit_NAME)/include
LDFLAGS+=-Llib/$(rlWebKit_NAME)/lib
LDFLAGS+=-lrlWebKit
LDFLAGS+=-Wl,-rpath,lib/$(rlWebKit_NAME)/lib


all: $(DISTDIR) $(DISTDIR)/src/rlWebKit $(DISTDIR)/src/example $(foreach prog, $(PROGRAMS), $(DISTDIR)/$(prog)$(EXEC_EXTENSION)) $(foreach lib, $(LIBRARIES), $(DISTDIR)/$(lib)$(LIB_EXTENSION) $(DISTDIR)/$(lib)$(LIB_EXTENSION_STATIC)) deps

ifneq ($(DISTDIR), .)
deps:
	mkdir -p $(DISTDIR)/lib
	if [ -d lib/$(EAWebKitd_NAME) ] && [ ! -d $(DISTDIR)/lib/$(EAWebKitd_NAME) ]; then cp -r lib/$(EAWebKitd_NAME) $(DISTDIR)/lib; fi
	if [ -d lib/$(rlWebKit_NAME) ] && [ ! -d $(DISTDIR)/lib/$(rlWebKit_NAME) ]; then cp -r lib/$(rlWebKit_NAME) $(DISTDIR)/lib; fi
	if [ -d lib/$(RAYLIB_NAME) ] && [ ! -d $(DISTDIR)/lib/$(RAYLIB_NAME) ]; then cp -r lib/$(RAYLIB_NAME) $(DISTDIR)/lib; fi
else
deps:
endif

$(DISTDIR)/src/rlWebKit:
	mkdir -p $@

$(DISTDIR)/src/example:
	mkdir -p $@

$(DISTDIR):
	mkdir -p $@

CFLAGS+=-Isrc
CFLAGS+=-Iinclude
CFLAGS+=-D PLATFORM=\"$(PLATFORM)\"
CFLAGS+=-Wno-changes-meaning
CFLAGS+=-fPIC

LDFLAGS+=-lSDL2
LDFLAGS+=-lGLEW
LDFLAGS+=-lGL

CFLAGS+=-Ilib/$(RAYLIB_NAME)/include

LDFLAGS+=-lm
LDFLAGS+=-Llib/$(RAYLIB_NAME)/lib
LDFLAGS+=$(RAYLIB_DLL)
LDFLAGS+=-Wl,-rpath,lib/$(RAYLIB_NAME)/lib

LDFLAGS+=-lstdc++
librlWebKit_CXX_SOURCES+=$(DISTDIR)/src/rlWebKit/rlWebKit.o
librlWebKit_CXX_SOURCES+=$(DISTDIR)/src/rlWebKit/rlWebkitClient.o
librlWebKit_CXX_SOURCES+=$(DISTDIR)/src/rlWebKit/rlWebkitRenderer.o
librlWebKit_CXX_SOURCES+=$(DISTDIR)/src/rlWebKit/rlWebkitThreading.o
librlWebKit_CXX_SOURCES+=$(DISTDIR)/src/rlWebKit/rlWebkitUtils.o

$(DISTDIR)/librlWebKit$(LIB_EXTENSION): $(librlWebKit_SOURCES) $(librlWebKit_CXX_SOURCES)
	$(CC) -o $@ $^ -fPIC -shared $(LDFLAGS)


$(DISTDIR)/librlWebKit$(LIB_EXTENSION_STATIC): $(librlWebKit_SOURCES) $(librlWebKit_CXX_SOURCES)
	$(AR) rcs $@ $^

example_CXX_SOURCES+=$(DISTDIR)/src/example/glUtil.o
example_CXX_SOURCES+=$(DISTDIR)/src/example/main.o

$(DISTDIR)/example$(EXEC_EXTENSION): $(example_SOURCES) $(example_CXX_SOURCES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DISTDIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@

$(DISTDIR)/%.o: %.cpp
	$(CXX) -c $^ $(CFLAGS) -o $@

clean:
	rm -f $(DISTDIR)/src/rlWebKit/rlWebKit.o
	rm -f $(DISTDIR)/src/rlWebKit/rlWebkitClient.o
	rm -f $(DISTDIR)/src/rlWebKit/rlWebkitRenderer.o
	rm -f $(DISTDIR)/src/rlWebKit/rlWebkitThreading.o
	rm -f $(DISTDIR)/src/rlWebKit/rlWebkitUtils.o
	rm -f $(DISTDIR)/librlWebKit$(EXEC_EXTENSION)
	rm -f $(DISTDIR)/src/example/glUtil.o
	rm -f $(DISTDIR)/src/example/main.o
	rm -f $(DISTDIR)/example$(EXEC_EXTENSION)

all_dist:
	DISTDIR=$(DISTDIR)/dist/linux64 PLATFORM=linux64 $(MAKE)
	DISTDIR=$(DISTDIR)/dist/linux64-debug PLATFORM=linux64-debug $(MAKE)
	DISTDIR=$(DISTDIR)/dist/win64 PLATFORM=win64 $(MAKE)
	DISTDIR=$(DISTDIR)/dist/web PLATFORM=web $(MAKE)
