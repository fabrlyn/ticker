EMPTY = 

PROJECT_NAME = ticker

SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests
TEST_BIN_DIR = $(TEST_DIR)/bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS_TEST = $(wildcard $(TEST_DIR)/*.c)

OBJS = $(subst $(SRC_DIR)/, $(EMPTY), $(SRCS:.c=.o)) 
OBJS_BIN = $(subst $(SRC_DIR)/, $(BIN_DIR)/, $(SRCS:.c=.o))
OBJS_TEST = $(subst $(TEST_DIR)/, $(EMPTY), $(SRCS_TEST:.c=.o)) 
OBJS_BIN_TEST = $(subst $(TEST_DIR)/, $(TEST_BIN_DIR)/, $(SRCS_TEST:.c=.o))

EXEC_TEST = tests_run

CC = clang
STD = --std=c11
FLAGS = #-Wall -Wpedantic
OPTIMAZATION = -O2

LIB_NAME = $(PROJECT_NAME).a
LINKS = -I$(PWD)/deps/minunit -I$(PWD)/$(SRC_DIR) -L$(PWD) $(LIB_NAME)


all: build

build: clean
	mkdir $(BIN_DIR)
	$(CC) $(STD) $(FLAGS) $(OPTIMAZATION) -c $(SRCS)
	mv $(OBJS) $(BIN_DIR)

test: static
	$(info $(OBJS_TEST))
	$(info $(OBJS_BIN_TEST))
	mkdir $(TEST_BIN_DIR)
	$(CC) $(STD) $(FLAGS) $(OPTIMAZATION)  $(SRCS_TEST) -o $(TEST_DIR)/$(EXEC_TEST) $(LINKS)
	$(TEST_DIR)/$(EXEC_TEST)


static: build
	ar rc $(PROJECT_NAME).a $(OBJS_BIN)

clean:
	rm -f $(LIB_NAME)
	rm -rf $(BIN_DIR)
	rm -rf $(TEST_BIN_DIR)
	rm -f $(TEST_DIR)/$(EXEC_TEST)
