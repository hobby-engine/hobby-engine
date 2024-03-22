CC = gcc
LDFLAGS = -lm third/glfw/src/libglfw3.a
CFLAGS = -std=c11 -Wall -Wextra
CFLAGS += -Ithird -Ithird/glad/include

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

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=_$(PROFILE).o)
LIB_OBJ = src/glad.o src/stb_image.o
DEPENDS = $(OBJ:.o=.d)
BUILD = bin
EXE = $(BUILD)/hobby_$(PROFILE)

.PHONY: clean compile_flags

$(EXE): third/glfw/src/libglfw3.a $(LIB_OBJ) $(OBJ) 
	@mkdir -p $(BUILD)
	@echo "Compiling $(EXE)..."
	@$(CC) -o $(EXE) $(OBJ) $(LIB_OBJ) $(CFLAGS) $(LDFLAGS)

src/stb_image.o:
	@echo "Compiling stb_image..."
	@$(CC) -o src/stb_image.o -c third/stb/stb_image.c $(CFLAGS)

src/glad.o:
	@echo "Compiling GLAD..."
	@$(CC) -o src/glad.o -c third/glad/src/glad.c $(CFLAGS)

third/glfw/src/libglfw3.a:
	@echo "Compiling GLFW..."
	@cd third/glfw && cmake . && make

%_$(PROFILE).o: %.c
	@echo "Compiling $< -> $@..."
	@$(CC) -o $@ -c $< $(CFLAGS) -MMD -MP

clean:
	$(RM) $(wildcard src/*.o)
	$(RM) $(wildcard src/*.d)
	$(RMDIR) $(BUILD)
	@cd third/glfw && cmake . && make clean

compile_flags:
	@echo "" > compile_flags.txt
	@$(foreach flag,$(CFLAGS),echo $(flag) >> compile_flags.txt;)

-include $(DEPENDS)
