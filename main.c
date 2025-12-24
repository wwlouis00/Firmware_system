/**
 * @file      main.c
 * @author    Louis Wang
 * @date      2025-11-21
 * @brief     Interactive command-based test application.
 */

/* -------------------------------------------------------------------------- */
/*                              Include Files                                  */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"
#include "sample.h"
#include "version.h"
#include "define.h"

/* -------------------------------------------------------------------------- */
/*                                Definitions                                  */
/* -------------------------------------------------------------------------- */

#define MAX_CMD_LEN     64
#define MAX_ARGS        4
#define MAX_NAME_LEN    16

/* -------------------------------------------------------------------------- */
/*                              Type Definitions                               */
/* -------------------------------------------------------------------------- */

typedef void (*cmd_handler_t)(int argc, char *argv[]);

typedef struct {
    char          name[MAX_NAME_LEN];
    char          desc[64];
    cmd_handler_t handler;
} command_t;

/* -------------------------------------------------------------------------- */
/*                         Forward Declarations                                */
/* -------------------------------------------------------------------------- */

static void cmd_test(int argc, char *argv[]);
static void cmd_math(int argc, char *argv[]);
static void cmd_info(int argc, char *argv[]);
static void cmd_help(int argc, char *argv[]);
static void cmd_exit(int argc, char *argv[]);
static void linux_test(int argc, char **argv);
void SwitchTest( void );
/* -------------------------------------------------------------------------- */
/*                               Command Table                                 */
/* -------------------------------------------------------------------------- */

static command_t cmd_table[] =
{
    { ".TEST", "Run all test modules",          cmd_test },
    { ".SAMPLE", "SAMPLE TEST",                 sample_test },
    { ".LS", "Linux CMD test",                  linux_test },
    { ".MATH", "Math test: .MATH a b",          cmd_math },
    { ".INFO", "Print build and version info",  cmd_info },
    { ".HELP", "Show help message",             cmd_help },
    { ".EXIT", "Exit program",                  cmd_exit },
};

static const int cmd_count = sizeof(cmd_table) / sizeof(cmd_table[0]);

/* -------------------------------------------------------------------------- */
/*                              Test Functions                                 */
/* -------------------------------------------------------------------------- */

static void test_module_name(void)
{
    const int expected = 5;
    int result = add(2, 3);

    if (result == expected) {
        printf("[PASS] add(2, 3) == %d\n", expected);
    } else {
        printf("[FAIL] add(2, 3) expected %d but got %d\n", expected, result);
    }
}

/* -------------------------------------------------------------------------- */
/*                             Command Handlers                                */
/* -------------------------------------------------------------------------- */

static void cmd_test(int argc, char *argv[])
{
    printf("Executing test_module_name()...\n");
    test_module_name();
}

static void linux_test(int argc, char **argv)
{
   // Default precision for Pi calculation
    char *precision = "2000"; 
    char command[256];

    // If user provides an argument (e.g., .LS 5000), use it as precision
    if (argc > 1) {
        precision = argv[1];
    }

    printf("\n--- Linux Performance & Environment Test ---\n");
    printf("[1/2] 正在執行目錄清單 (ls -l)...\n");
    system("ls -l");

    printf("\n[2/2] 正在執行浮點數運算壓力測試 (計算 Pi 到 %s 位)...\n", precision);
    printf("這可能需要幾秒鐘，請稍候...\n");

    // Construct the bc command string
    // scale: 小數點位數, 4*a(1): 使用反正切函數計算 Pi
    snprintf(command, sizeof(command), "time echo \"scale=%s; 4*a(1)\" | bc -l > /dev/null", precision);

    // Execute the command
    int status = system(command);

    if (status == -1) {
        printf("\n[Error] 指令執行失敗，請檢查是否安裝 'bc' 套件。\n");
    } else {
        printf("\n[Success] 測試完成！回傳狀態碼: %d\n", status);
        printf("提示: 如果計算時間極短，可以嘗試輸入更高位數，例如: .LS 5000\n");
    }
}

static void cmd_math(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: .MATH a b\n");
        return;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("add(%d, %d) = %d\n",      a, b, add(a, b));
    printf("multiply(%d, %d) = %d\n", a, b, multiply(a, b));
}

static void cmd_info(int argc, char *argv[])
{
    printf("\n[BUILD INFO] %s %s\n", __DATE__, __TIME__);
    printf("[VERSION]    %s%03d_V%03d\n", PROJECT, TSTCODE_SUBVER, TSTCODE_VER);
}

static void cmd_help(int argc, char *argv[])
{
    printf("\n[AVAILABLE COMMANDS]\n");

    for (int i = 0; i < cmd_count; i++) {
        printf("  %-8s - %s\n", cmd_table[i].name, cmd_table[i].desc);
    }
}

static int g_exit_flag = 0;

static void cmd_exit(int argc, char *argv[])
{
    printf("Exiting...\n");
    g_exit_flag = 1;
}

/* -------------------------------------------------------------------------- */
/*                           Command Dispatcher                                */
/* -------------------------------------------------------------------------- */

static void process_command(char *input)
{
    char *argv[MAX_ARGS];
    int argc = 0;

    /* Tokenize input command */
    char *tok = strtok(input, " ");
    while (tok && argc < MAX_ARGS) {
        argv[argc++] = tok;
        tok = strtok(NULL, " ");
    }

    if (argc == 0) {
        return;
    }

    /* Check command table */
    for (int i = 0; i < cmd_count; i++) {
        if (strcmp(argv[0], cmd_table[i].name) == 0) {
            cmd_table[i].handler(argc, argv);
            return;
        }
    }

    printf("Unknown command: %s\n", argv[0]);
}

void SwitchTest( void )
{
    int i, runTimes = 0;
    for( i = 0; i < 10000; i++ )
    {
        switch( i % 5 )
        {
            case 0:
                runTimes++;
                break;
            case 1:
                runTimes++;
                break;
            case 2:
                runTimes++;
                break;
            case 3:
                runTimes++;
                break;
            case 4:
                runTimes++;
                break;
            default:
                printf("Error in SwitchTest()\n");
                break;
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                   main()                                    */
/* -------------------------------------------------------------------------- */

int main(void)
{
    printf("\n[BUILD INFO] %s %s\n", __DATE__, __TIME__);
    printf("\n[VERSION]    %s%03d_V%03d\n", PROJECT, TSTCODE_SUBVER, TSTCODE_VER);

    printf("\n=== Command Test System Ready ===\n");
    printf("\nType .HELP for available commands.\n");

#if EMBEDDED_TEST
    char input_buf[MAX_CMD_LEN];
    while (!g_exit_flag) {

        printf("\n> ");
        if (!fgets(input_buf, sizeof(input_buf), stdin)) {
            continue;
        }

        /* Remove trailing newline */
        input_buf[strcspn(input_buf, "\n")] = '\0';

        process_command(input_buf);
    }
#endif

#if EMBEDDED
    SwitchTest();
    while (1) ;
#endif

    return 0;
}
