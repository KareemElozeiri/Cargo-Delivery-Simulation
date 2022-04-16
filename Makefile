# Program Exec Name
EXEC_NAME := main.run

SRCDIR := .

SRCS_CPP := $(shell find $(SRCDIR) -name "*.cpp")
SRCS_H := $(shell find $(SRCDIR) -name "*.h")

CC := g++
CFLAGS := -c -Wall

$(EXEC_NAME): $(SRCS_CPP)
	@echo "--------BUILD--------"
	$(CC) $(SRCS_CPP) -o $(EXEC_NAME)
	
clean:
	@echo "--------CLEAN--------"
	rm -rf *.run
	rm -rf *.o

run: clean $(EXEC_NAME)
	@echo "--------RUN--------"
	@./$(EXEC_NAME)