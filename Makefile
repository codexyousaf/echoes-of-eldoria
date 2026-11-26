.RECIPEPREFIX := >
.SECONDARY:

CXX := g++
RAYLIB := libs/raylib
RAYGUI := libs/raygui
TARGET := build/eldoria.exe
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,build/obj/%.o,$(SRCS))
HDRS := $(wildcard src/*/*.h)
WARN := -Wall -Wextra
GUIFLAGS := -std=c++17 $(WARN) -g -Isrc -isystem $(RAYLIB)/include -isystem $(RAYGUI)
CXXFLAGS := $(GUIFLAGS) -MMD -MP
LDFLAGS := -L$(RAYLIB)/lib
LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm

.PHONY: all run clean gui-check test-game

all: $(TARGET)

$(TARGET): $(OBJS)
> @mkdir -p $(dir $@)
> $(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

build/obj/%.o: src/%.cpp
> @mkdir -p $(dir $@)
> $(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
> ./$(TARGET)

clean:
> rm -rf build

# Setup check window: make gui-check
gui-check: tests/gui-check.cpp
> @mkdir -p build
> $(CXX) $(GUIFLAGS) $< -o build/gui-check.exe $(LDFLAGS) $(LDLIBS)
> ./build/gui-check.exe

# One slice demo window: make demo-player, demo-story, demo-battle,
# demo-codex, demo-quest, demo-menus (uses demos/demo-NAME.cpp)
build/demos/%.exe: demos/%.cpp $(HDRS)
> @mkdir -p $(dir $@)
> $(CXX) $(GUIFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

demo-%: build/demos/demo-%.exe
> ./$<

# Whole game in the console, no GUI: make test-game
test-game: tests/test-game-console.cpp $(HDRS)
> @mkdir -p build
> $(CXX) -std=c++17 $(WARN) -g -Isrc $< -o build/test-game.exe
> ./build/test-game.exe

# One structure test, no GUI: make test-inventory, test-quest-list, ...
build/tests/%.exe: tests/%.cpp $(HDRS)
> @mkdir -p $(dir $@)
> $(CXX) -std=c++17 $(WARN) -g -Isrc $< -o $@

test-%: build/tests/test-%.exe
> ./$<

-include $(OBJS:.o=.d)