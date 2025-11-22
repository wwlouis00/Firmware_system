# ------------------------------------------------------------
#  Project Build System - Professional Version
#  Auto-discovery of sources, include paths, and build directory
# ------------------------------------------------------------

OPDIR = $(shell pwd)
export TOPDIR

target ?= ModuleTest
export target

# ------------------------------------------------------------
# Build type (default = debug)
# Usage:
#   make              ← debug
#   make BUILD=release
#   make BUILD=asan
# ------------------------------------------------------------

BUILD ?= debug
BUILD_DIR := build/$(BUILD)

# ------------------------------------------------------------
# Compiler and Flags
# ------------------------------------------------------------
CC       := gcc
CFLAGS   := -Wall -g


# Debug build (default)
ifeq ($(BUILD),debug)
    CFLAGS := $(CFLAGS_COMMON) -g -O0 -DDEBUG
endif

# Release build
ifeq ($(BUILD),release)
    CFLAGS := $(CFLAGS_COMMON) -O2 -DNDEBUG
endif

# ASan build (Memory sanitizer)
ifeq ($(BUILD),asan)
    CFLAGS := $(CFLAGS_COMMON) -g -O1 -fsanitize=address -fno-omit-frame-pointer -DDEBUG
    LDFLAGS := -fsanitize=address
endif

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
all: $(target)

$(target): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 一般規則：.c → .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Clean
# ------------------------------------------------------------
clean:
	@echo "Cleaning build directory..."
	$(RM) -r build $(TARGET)
