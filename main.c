/**
 * @file      main.c
 * @author    Louis Wang
 * @date      2025-11-21
 * @brief     Entry point for math utility test application.
 */

/*-----------------------------------------------------------------------------*/
/* Include Header Files                                                        */
/*-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "math_utils.h"
#include "version.h"

/* -------------------------------------------------------------------------- */
/*                               Type Definitions                              */
/* -------------------------------------------------------------------------- */

typedef enum _TEST_ITEMS{
    TEST_MODULE_NAME = 0,
    TEST_PRINT,
    
    TEST_ITEMS_MAX,
} test_item_t;

/* -------------------------------------------------------------------------- */
/*                             Function Prototypes                             */
/* -------------------------------------------------------------------------- */

static void test_module_name(void);
static void cmd_test(int argc, char **argv);
static void cmd_print(int argc, char **argv);
static void cmd_help(void);
static void trim_newline(char *s);
static int parse_args(char *input, char *argv[]);
static void to_upper(char *s);


#define MAX_COMBINE_NUM     3
#define MAX_NAME_LEN        16
#define MAX_INPUT_LEN       128
#define MAX_ARGC            8


typedef struct {
    char       test_name[MAX_NAME_LEN];
    test_item_t items[MAX_COMBINE_NUM];
} module_command_t;


/* 示例測試命令表，可根據專案需要擴充 */
static module_command_t module_test_cmd[] =
{
    { ".TEST", { TEST_MODULE_NAME, TEST_PRINT, -1 } }
};

/* -------------------------------------------------------------------------- */
/*                                 CLI TABLE                                   */
/* -------------------------------------------------------------------------- */

typedef void (*command_func_t)(int argc, char **argv);

typedef struct {
    const char       *name;
    command_func_t    handler;
    const char       *desc;
} command_entry_t;

static void cmd_exit(int argc, char **argv)
{
    printf("Exiting...\n");
    exit(0);
}

static const command_entry_t cmd_table[] =
{
    { "TEST",  cmd_test,  "Run test routines" },
    { "PRINT", cmd_print, "Print example data" },
    { "HELP",  NULL,      "Show command list" },
    { "EXIT",  cmd_exit,  "Exit program" }
};

/* -------------------------------------------------------------------------- */
/*                               Test Functions                                */
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
/*                               CLI Functions                                 */
/* -------------------------------------------------------------------------- */

static void cmd_test(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: TEST <MODULE>\n");
        printf("Example: TEST MODULE\n");
        return;
    }

    to_upper(argv[1]);

    if (strcmp(argv[1], "MODULE") == 0) {
        test_module_name();
        return;
    }

    printf("Unknown test: %s\n", argv[1]);
}

static void cmd_print(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: PRINT <DATA>\n");
        printf("Example: PRINT A\n");
        return;
    }

    to_upper(argv[1]);

    if (strcmp(argv[1], "A") == 0) {
        printf("A = 12\n");
    } else if (strcmp(argv[1], "B") == 0) {
        printf("B = 18\n");
    } else {
        printf("Unknown print item: %s\n", argv[1]);
    }
}

static void cmd_help(void)
{
    printf("\nAvailable Commands:\n");
    for (size_t i = 0; i < sizeof(cmd_table)/sizeof(cmd_table[0]); i++) {
        printf("  %-6s - %s\n",
               cmd_table[i].name,
               cmd_table[i].desc);
    }
    printf("\n");
}

/* -------------------------------------------------------------------------- */
/*                           CLI Helper Functions                              */
/* -------------------------------------------------------------------------- */

static void trim_newline(char *s)
{
    s[strcspn(s, "\r\n")] = 0;
}

static int parse_args(char *input, char *argv[])
{
    int argc = 0;
    char *token = strtok(input, " ");

    while (token != NULL && argc < MAX_ARGC) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    return argc;
}

static void to_upper(char *s)
{
    while (*s) {
        *s = toupper((unsigned char)*s);
        s++;
    }
}

/* -------------------------------------------------------------------------- */
/*                              Command Dispatcher                             */
/* -------------------------------------------------------------------------- */

static void process_command(int argc, char **argv)
{
    if (argc == 0) return;

    to_upper(argv[0]);

    for (size_t i = 0; i < sizeof(cmd_table)/sizeof(cmd_table[0]); i++) {
        if (strcmp(argv[0], cmd_table[i].name) == 0) {

            if (strcmp(argv[0], "HELP") == 0) {
                cmd_help();
                return;
            }

            cmd_table[i].handler(argc, argv);
            return;
        }
    }

    printf("Unknown command: %s\n", argv[0]);
}

/* -------------------------------------------------------------------------- */
/*                                   main()                                    */
/* -------------------------------------------------------------------------- */

int main(void)
{
    char input[MAX_INPUT_LEN];
    char *argv[MAX_ARGC];
    int argc;

    int a = 12, b = 18;
    printf("a + b = %d\n", add(a, b));
    printf("a * b = %d\n", multiply(a, b));

    printf("\n[REGISTERED TEST COMMANDS]\n");
    printf("  %s\n", module_test_cmd[0].test_name);

    printf("\n[BUILD INFO] %s %s\n", __DATE__, __TIME__);
    printf("[VERSION] MP Ver: %s%03d_V%03d\n",
           PROJECT, TSTCODE_SUBVER, TSTCODE_VER);

    printf("\n===== ENTER COMMAND MODE =====\n");
    printf("Type HELP to view commands.\n\n");

    while (1)
    {
        printf("> ");

        if (!fgets(input, sizeof(input), stdin))
            continue;

        trim_newline(input);
        argc = parse_args(input, argv);

        if (argc > 0)
            process_command(argc, argv);
    }

    return 0;
}