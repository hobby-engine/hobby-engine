CC = gcc
LDFLAGS = -lglfw -lm
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
DEPENDS = $(OBJ:.o=.d)
BUILD = bin
EXE = $(BUILD)/hobby_$(PROFILE)

.PHONY: clean libs compile_flags

$(EXE): libs src/glad.o $(OBJ)
	@mkdir -p $(BUILD)
	@echo "Compiling $(EXE)..."
	@$(CC) -o $(EXE) $(OBJ) src/glad.o $(CFLAGS) $(LDFLAGS)

src/glad.o:
	@echo "Compiling GLAD..."
	@$(CC) -o src/glad.o -c third/glad/src/glad.c $(CFLAGS)

%_$(PROFILE).o: %.c
	@echo "Compiling $< -> $@..."
	@$(CC) -o $@ -c $< $(CFLAGS) -MMD -MP

clean:
	$(RM) $(wildcard src/*.o)
	$(RM) $(wildcard src/*.d)
	$(RMDIR) $(BUILD)

compile_flags:
	@echo "" > compile_flags.txt
	@$(foreach flag,$(CFLAGS),echo $(flag) >> compile_flags.txt;)

-include $(DEPENDS)
