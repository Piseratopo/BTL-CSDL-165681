CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2

# Application and test targets
APP_TARGET = sensor_app
TEST_TARGET = sensor_test

COMMON_SRCS = models.c sort.c tree.c
APP_SRCS    = main.c $(COMMON_SRCS)
TEST_SRCS   = test.c $(COMMON_SRCS)

APP_OBJS  = $(APP_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

.PHONY: all clean run run-test

all: $(APP_TARGET) $(TEST_TARGET)

$(APP_TARGET): $(APP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(APP_OBJS) $(TEST_OBJS) $(APP_TARGET) $(TEST_TARGET)

run: $(APP_TARGET)
	./$(APP_TARGET)

run-test: $(TEST_TARGET)
	./$(TEST_TARGET)