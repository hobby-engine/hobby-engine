CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
CFLAGS += -Isrc -Ithird -Ithird/glad/include -Ithird/glfw/include -Ithird/luajit/src
LDFLAGS = -lm third/glfw/src/libglfw3.a third/luajit/src/libluajit.a

RM = rm
RMDIR = rm -r

ifndef PROFILE
	PROFILE = debug
endif

ifeq ($(PROFILE), debug)
	CFLAGS += -O0 -g -fsanitize=address
endif

ifeq ($(PROFILE), release)
	CFLAGS += -O3
endif

SRC = src/engine.c src/log.c src/main.c src/renderer.c src/shader.c \
			src/texture.c src/time.c src/vertex_array.c src/vertex_buffer.c \
			src/window.c \
			src/lua_wrap/lua_wrapper.c src/lua_wrap/lua_wrap_renderer.c \
			src/lua_wrap/lua_wrap_time.c src/lua_wrap/lua_wrap_texture.c
OBJ = $(SRC:.c=_$(PROFILE).o)
LIB_OBJ = src/glad_$(PROFILE).o src/stb_image_$(PROFILE).o
DEPENDS = $(OBJ:.o=.d)
BUILD = bin
EXE = $(BUILD)/hobby_$(PROFILE)

.PHONY: all clean compile_flags libs lua

all: libs $(EXE)

$(EXE): lua $(OBJ) 
	@mkdir -p $(BUILD)
	@echo "Compiling $(EXE)..."
	@$(CC) -o $(EXE) $(OBJ) $(LIB_OBJ) $(CFLAGS) $(LDFLAGS)

libs:
	@echo "Compiling GLFW..."
	@cd third/glfw && cmake . && $(MAKE) --no-print-directory
	@echo "Compiling LuaJIT..."
	@cd third/luajit && $(MAKE) --no-print-directory
	@echo "Compiling GLAD..."
	@$(CC) -o src/glad_$(PROFILE).o -c third/glad/src/glad.c $(CFLAGS)
	@echo "Compiling stb_image..."
	@$(CC) -o src/stb_image_$(PROFILE).o -c third/stb/stb_image.c $(CFLAGS)

%_$(PROFILE).o: %.c
	@echo "Compiling $< -> $@..."
	@$(CC) -o $@ -c $< $(CFLAGS) -MMD -MP

clean:
	$(RM) $(wildcard src/*.o)
	$(RM) $(wildcard src/*.d)
	$(RMDIR) $(BUILD)
	@cd third/glfw && cmake . && make clean
	@cd third/luajit && make clean

compile_flags:
	@echo "" > compile_flags.txt
	@$(foreach flag,$(CFLAGS),echo $(flag) >> compile_flags.txt;)

-include $(DEPENDS)
