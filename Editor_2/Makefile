# compiler
CC = gcc

# compilers flag(s)
CFLAGS = -lncurses

# compiled files 
SRCF = main_v2.c view_v2.c

# object files
OBJF = $(SRCF:.c = .o)

# Executable file 
TARGET = V2

# Defaults files 
all : $(TARGET)

# Rules for executable files 
$(TARGET) : $(OBJF)
	$(CC) -o $@ $^ $(CFLAGS)

# Rules for object files
%.o : %.c header_v2.h
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up the object files
clean:
	rm -f $(OBJF)
