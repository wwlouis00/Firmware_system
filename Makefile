# 編譯器與參數
CC       := gcc
CFLAGS   := -Wall -g

# 專案目錄
SRC_DIRS := . test       # 自動掃描這些目錄裡的 .c 檔
INC_DIRS := . test       # 標頭檔搜尋路徑

# 自動抓取來源檔與物件檔
SRCS     := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS     := $(patsubst %.c,%.o,$(SRCS))

# 輸出目標
TARGET   := my_program

# 編譯參數（加上 -I 旗標）
CPPFLAGS := $(addprefix -I,$(INC_DIRS))

.PHONY: all clean

# 最終目標
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 一般規則：.c → .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# 清理
clean:
	$(RM) $(TARGET) $(OBJS)
