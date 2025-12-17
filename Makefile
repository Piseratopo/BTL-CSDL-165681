CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2

# Target executable
TARGET = alarm_app

# Source files
SRCS = main.c models.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c models.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	 ./$(TARGET)