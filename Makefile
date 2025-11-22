# ------------------------------------------------------------
#  Project Build System - Professional Version
#  Auto-discovery of sources, include paths, and build directory
# ------------------------------------------------------------

OPDIR = $(shell pwd)
export TOPDIR

TARGET ?= ModuleTest
export TARGET

# ------------------------------------------------------------
# Build type (default = debug)
# Usage:
#   make              ← debug
#   make BUILD=release
#   make BUILD=asan
# ------------------------------------------------------------

# ------------------------------------------------------------
# Compiler and Flags
# ------------------------------------------------------------
CC       := gcc
CFLAGS   := -Wall -g


# 專案目錄
SRC_DIRS := . test       # 自動掃描這些目錄裡的 .c 檔
INC_DIRS := . test include       # 標頭檔搜尋路徑

# 自動抓取來源檔與物件檔
SRCS     := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS     := $(patsubst %.c,%.o,$(SRCS))


# 編譯參數（加上 -I 旗標）
CPPFLAGS := $(addprefix -I,$(INC_DIRS))

.PHONY: all

# 最終目標
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 一般規則：.c → .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Clean
# ------------------------------------------------------------
clean:
	@echo "Cleaning build directory..."
	$(RM) $(TARGET) $(OBJS)
