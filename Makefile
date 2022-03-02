
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out

# Generate source and object lists, also just string variables
C_SRC := driver.c src/ppm/ppm_functions.c
HRDS := src/ppm/ppm_info.h
OBJS := driver.o src/ppm/ppm_functions.o


C_SRCS := \
		 $(wildcard *.c) \
		 $(wildcard src/*.c) \
		 $(wildcard src/**/*.c)

HDRS := \
		 $(wildcard *.h) \
		 $(wildcard src/*.h) \
		 $(wildcard src/**/*.h)

OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

# default target
all: build
				@echo "All done"

# Link all built objects
build: $(OBJS)
							 $(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

# special build rule
%.o: %.c $(HDRS)
								$(CC) $(CFLAGS) -c $< -o $@
%.o: %.cpp $(HDRS)
								$(CC) $(CFLAGS) -c $< -o $@
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"

# Catch root directory src files
bin/%.o: %.c $(HDRS)
								@mkdir -p $(dir $@)
								$(CC) $(CFLAGS) -c $< -o $@

# Catch all nested directory files
bin/%.o: src/%.c $(HDRS)
								@mkdir -p $(dir $@)
								$(CC) $(CFLAGS) -c $< -o $@


# Catch root directory src files
bin/%.o: %.c $(HDRS)
								@mkdir -p $(dir $@)
								$(CC) $(CFLAGS) -c $< -o $@

clean:
				rm -f $(TARGET)
				rm -rf bin

run:build
	./$(TARGET) ClemsonPaw.ppm Disney.ppm
