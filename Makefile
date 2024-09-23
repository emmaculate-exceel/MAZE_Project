# Makefile for the compilation of main_ve.c, screen_ve.c and header_ve.h file

# Compiler
CC = gcc

# Cflags
CFLAGS = -lSDL2 -lSDL2_ttf

# Source files
SRCF = main_ve.c screen_ve.c

# Object files
OBJF = $(SRCF:.c = .o)

# Executable file
TARGET = VE

# Default files
all: $(TARGET)

# Rules for executable
$(TARGET): $(OBJF)
	$(CC) -o $@ $^ $(CFLAGS)

# Rules for object files
%.o: %.c header_ve.h
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up the object files
clean:
	rm -f $(OBJF)
