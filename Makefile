# 編譯器
CC = gcc
CFLAGS = -Wall -g

TOPDIR = ${shell pwd | sed -e 's/ /\\ /g'}
export TOPDIR

# 檔案
TARGET = my_program
OBJS = main.o math_utils.o

# 規則
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c math_utils.h
	$(CC) $(CFLAGS) -c main.c

math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

# 清理
clean:
	rm -f $(TARGET) $(OBJS)
# 	clean: xclean clobber