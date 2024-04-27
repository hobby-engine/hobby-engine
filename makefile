CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -fno-exceptions
CXXFLAGS += -Isrc -Ithird -Ithird/glad/include -Ithird/luajit
LDFLAGS = -lm bin/libglfw3.a bin/libluajit.a

RM = rm
RMDIR = rm -rf
MKDIR = mkdir -p
INSTALL_LIBS = sh install_libs.sh

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

SRC = src/main.cc src/log.cc src/shader.cc src/mat4.cc \
			src/engine.cc src/time.cc \
			\
			src/glfw/glfw_window.cc src/glfw/glfw_input.cc \
			\
			src/opengl/gl_renderer.cc src/opengl/gl_shader.cc \
			src/opengl/vertex.cc src/opengl/gl_texture.cc \
			\
			src/lua_wrapper/wrapper.cc src/lua_wrapper/wrap_renderer.cc \
			src/lua_wrapper/wrap_engine.cc src/lua_wrapper/wrap_input.cc \
			src/lua_wrapper/wrap_log.cc src/lua_wrapper/wrap_texture.cc \
			src/lua_wrapper/wrap_window.cc

OBJ = $(SRC:%.cc=$(BUILD)/%_$(PROFILE).o)

DEPENDS = $(OBJ:.o=.d)
EXE = $(BUILD)/hobby_$(PROFILE)
STBI_OBJ = src/stbi_$(PROFILE).o
GLAD_OBJ = src/glad_$(PROFILE).o
LIB_OBJ = $(GLAD_OBJ) $(STBI_OBJ)

.PHONY: clean compile_flags exe libs

exe: libs $(EXE)

$(EXE): $(LIB_OBJ) $(OBJ) 
	@$(MKDIR) $(BUILD)
	@echo "Compiling $(EXE)..."
	@$(CXX) -o $(EXE) $(OBJ) $(LIB_OBJ) $(CXXFLAGS) $(LDFLAGS)

libs:
	$(INSTALL_LIBS)

$(BUILD)/%_$(PROFILE).o: %.cc
	@$(MKDIR) $(@D)
	@echo "Compiling $< -> $@..."
	@$(CXX) -o $@ -c $< $(CXXFLAGS) -MMD -MP

$(GLAD_OBJ):
	@$(MKDIR) $(@D)
	@echo "Compiling glad..."
	@$(CXX) -o $@ -c third/glad/src/glad.c $(CXXFLAGS) -MMD -MP

$(STBI_OBJ):
	@$(MKDIR) $(@D)
	@echo "Compiling stbi..."
	@$(CXX) -o $@ -c third/stb/stb_image.c $(CXXFLAGS) -MMD -MP

clean:
	$(RMDIR) $(BUILD)

compile_flags:
	@echo "clang++" > compile_flags.txt
	@$(foreach flag,$(CXXFLAGS),echo $(flag) >> compile_flags.txt;)

-include $(DEPENDS)
