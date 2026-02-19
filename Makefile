# ------------------------------------------------------------
#  Project Build System - Multi-Platform Version
#  Supports: Ubuntu (x86_64) & Raspberry Pi 4B (AArch64)
# ------------------------------------------------------------

OPDIR = $(shell pwd)
export TOPDIR

# 基礎檔名
TARGET_BASE ?= ModuleTest
# 編譯模式: debug, release, asan
BUILD       ?= debug
# 目標平台: ubuntu, rpi
PLATFORM    ?= ubuntu

# ------------------------------------------------------------
# 平台選擇與編譯器設定
# ------------------------------------------------------------
ifeq ($(PLATFORM), rpi)
    # 樹莓派 4B (64位元) 交叉編譯器
    # 請先執行 sudo apt install gcc-aarch64-linux-gnu 安裝
	CC     := aarch64-linux-gnu-gcc
	TARGET := $(TARGET_BASE)_rpi
else
    # 預設 Ubuntu 本地編譯器
	CC     := gcc
	TARGET := $(TARGET_BASE)_ubuntu
endif

# ------------------------------------------------------------
# 編譯旗標設定
# ------------------------------------------------------------
CFLAGS := -Wall

ifeq ($(BUILD), release)
	CFLAGS += -O2
else ifeq ($(BUILD), asan)
	CFLAGS += -fsanitize=address -g
else
	CFLAGS += -g
endif

# ------------------------------------------------------------
# 自動掃描目錄與檔案 (Auto-discovery)
# ------------------------------------------------------------
# 取得 test 目錄下的所有子目錄名稱
TEST_SUB_DIRS := $(patsubst %/,%,$(shell ls -d test/*/ 2>/dev/null))

# 原始碼與標頭檔目錄
SRC_DIRS := . test $(TEST_SUB_DIRS)
INC_DIRS := . test include $(TEST_SUB_DIRS)

# 自動抓取所有 .c 檔並轉換成 .o 檔名
SRCS     := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS     := $(patsubst %.c,%.o,$(SRCS))

# 加入 -I 旗標以搜尋標頭檔
CPPFLAGS := $(addprefix -I,$(INC_DIRS))

# ------------------------------------------------------------
# 編譯規則
# ------------------------------------------------------------
.PHONY: all clean help

# 預設目標
all: $(TARGET)

# 連結 (Linking)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "------------------------------------------------"
	@echo "  Build Success: $(TARGET)"
	@echo "  Platform:      $(PLATFORM)"
	@echo "  Compiler:      $(CC)"
	@echo "------------------------------------------------"

# 編譯 (Compiling .c to .o)
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# ------------------------------------------------------------
# 清除暫存檔 (只清除目前平台產出的檔案)
# ------------------------------------------------------------
clean:
	@echo "Cleaning up $(PLATFORM) objects and binaries..."
	$(RM) $(OBJS)

# ------------------------------------------------------------
# 使用說明
# ------------------------------------------------------------
help:
	@echo "Professional Makefile Usage:"
	@echo "  make PLATFORM=ubuntu   - 編譯 Ubuntu 執行檔 (ModuleTest_ubuntu)"
	@echo "  make PLATFORM=rpi      - 編譯樹莓派 執行檔 (ModuleTest_rpi)"
	@echo "  make BUILD=release     - 開啟 O2 優化"
	@echo "  make clean             - 清除所有產出物"