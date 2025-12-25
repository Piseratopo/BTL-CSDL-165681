CC      = gcc
CFLAGS  = -Wall -Wextra -O2

# Application and test targets
APP_TARGET  = sensor_app
TEST_TARGET = sensor_test

COMMON_SRCS = models.c sort.c tree.c menu.c
APP_SRCS    = main.c
TEST_SRCS   = test.c

COMMON_OBJS = $(COMMON_SRCS:.c=.o)
APP_OBJS    = $(APP_SRCS:.c=.o)
TEST_OBJS   = $(TEST_SRCS:.c=.o)

.PHONY: all app test clean run run-test

all: $(APP_TARGET) $(TEST_TARGET)

app: $(APP_TARGET)

test: $(TEST_TARGET)

$(APP_TARGET): $(COMMON_OBJS) $(APP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(COMMON_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_OBJS) $(APP_OBJS) $(TEST_OBJS) $(APP_TARGET) $(TEST_TARGET)

run: app
	./$(APP_TARGET)

run-test: test
	./$(TEST_TARGET)