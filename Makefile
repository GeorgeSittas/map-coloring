
# List module paths
LIST_MODULE    = ./ADT_List/list_module
LIST_INTERFACE = ./ADT_List/include

# Mapcol program paths
MAPCOL_OBJ_DIR = ./src
MAPCOL_INC_DIR = ./include

# Compile options. The -I<dir> option is needed so that
# the compiler can find the .h files

CFLAGS = -Wall -I$(LIST_INTERFACE) -I$(MAPCOL_INC_DIR)
CC = gcc

# .o files and exec. file
OBJS = $(MAPCOL_OBJ_DIR)/mapcol.o $(MAPCOL_OBJ_DIR)/parse.o \
			 $(MAPCOL_OBJ_DIR)/utilities.o $(MAPCOL_OBJ_DIR)/color.o \
			 $(LIST_MODULE)/list.o

EXEC = mapcol

# The @ character is used to silence make's output

$(EXEC): $(OBJS)
	@$(CC) $(OBJS) -o $(EXEC)

genmap: $(MAPCOL_OBJ_DIR)/genmap.o
	@$(CC) $(MAPCOL_OBJ_DIR)/genmap.o -o genmap

.SILENT: $(OBJS) $(MAPCOL_OBJ_DIR)/genmap.o # Silence implicit rule output
.PHONY: clean

all: $(EXEC) genmap

clean:
	@rm -f $(OBJS) $(EXEC) genmap $(MAPCOL_OBJ_DIR)/genmap.o

run: $(EXEC)
	@./$(EXEC)
