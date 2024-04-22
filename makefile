CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
CXXFLAGS += -Isrc -Ithird -Ithird/glad/include -Ithird/glfw/include -Ithird/luajit/src
LDFLAGS = -lm third/glfw/src/libglfw3.a third/luajit/src/libluajit.a

RM = rm
RMDIR = rm -r

ifndef PROFILE
	PROFILE = debug
endif

ifeq ($(PROFILE), debug)
	CXXFLAGS += -O3 -g -fsanitize=address
endif

ifeq ($(PROFILE), release)
	CXXFLAGS += -O3
endif

BUILD = bin

SRC = src/main.cc src/window.cc src/log.cc src/shader.cc src/mat4.cc \
			src/engine.cc src/time.cc \
			src/opengl/gl_window.cc src/opengl/gl_renderer.cc src/opengl/gl_shader.cc \
			src/opengl/vertex.cc \
			src/lua_wrapper/wrapper.cc src/lua_wrapper/wrap_renderer.cc \
			src/lua_wrapper/wrap_engine.cc

OBJ = $(SRC:%.cc=$(BUILD)/%_$(PROFILE).o)

DEPENDS = $(OBJ:.o=.d)
EXE = $(BUILD)/hobby_$(PROFILE)
GLAD_OBJ = src/glad_$(PROFILE).o
LIB_OBJ = $(GLAD_OBJ)

.PHONY: all clean compile_flags libs lua glfw luajit exe

all: libs $(EXE)

exe: $(EXE)

$(EXE): $(OBJ) 
	@mkdir -p $(BUILD)
	@echo "Compiling $(EXE)..."
	@$(CXX) -o $(EXE) $(OBJ) $(LIB_OBJ) $(CXXFLAGS) $(LDFLAGS)

libs: glfw luajit $(LIB_OBJ)

glfw:
	@echo "Compiling GLFW..."
	@cd third/glfw && cmake . && $(MAKE) --no-print-directory

luajit:
	@echo "Compiling LuaJIT..."
	@cd third/luajit && $(MAKE) --no-print-directory

$(BUILD)/%_$(PROFILE).o: %.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CXX) -o $@ -c $< $(CXXFLAGS) -MMD -MP

$(GLAD_OBJ):
	@mkdir -p $(@D)
	@echo "Compiling glad..."
	@$(CXX) -o $@ -c third/glad/src/glad.c $(CXXFLAGS) -MMD -MP

clean:
	$(RMDIR) $(BUILD)
	@cd third/glfw && cmake . && make clean
	@cd third/luajit && make clean

compile_flags:
	@echo "clang++" > compile_flags.txt
	@$(foreach flag,$(CXXFLAGS),echo $(flag) >> compile_flags.txt;)

-include $(DEPENDS)
