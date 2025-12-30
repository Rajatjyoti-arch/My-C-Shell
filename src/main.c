#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h> // For Windows process management

#define MAX_LINE 80
#define MAX_ARGS 10
#define MAX_HISTORY 10

// History storage
char history[MAX_HISTORY][MAX_LINE];
int history_count = 0;

void add_to_history(char *cmd) {
    if (history_count < MAX_HISTORY) {
        strcpy(history[history_count], cmd);
        history_count++;
    } else {
        // Shift history up to make room
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            strcpy(history[i], history[i + 1]);
        }
        strcpy(history[MAX_HISTORY - 1], cmd);
    }
}

void show_history() {
    printf("\n--- Command History ---\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
    printf("-----------------------\n");
}

int main(void) {
    char *args[MAX_ARGS];
    char input[MAX_LINE];
    int should_run = 1;

    while (should_run) {
        printf("my_shell> ");
        fflush(stdout);

        // 1. Get user input
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        // 2. Clean the input (remove newline)
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        // 3. Save to history
        add_to_history(input);

        // 4. Handle Built-in Shell Commands
        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            continue;
        }
        if (strcmp(input, "history") == 0) {
            show_history();
            continue;
        }

        /* 5. SMART CHECK: Internal Windows Commands 
           Commands like 'dir', 'cls', and 'copy' are part of cmd.exe.
           We use system() for these because it knows how to find them.
        */
        if (strcmp(input, "dir") == 0 || strcmp(input, "cls") == 0 || 
            strncmp(input, "echo ", 5) == 0 || strcmp(input, "date") == 0) {
            system(input);
            continue;
        }

        // 6. Tokenize for External Programs (like gcc, notepad, python)
        char temp_input[MAX_LINE];
        strcpy(temp_input, input);
        
        int i = 0;
        char *token = strtok(temp_input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL; // Must end with NULL

        // 7. Execute External Program with the correct pointer cast
        intptr_t result = _spawnvp(_P_WAIT, args[0], (const char * const *)args);

        if (result == -1) {
            printf("Error: '%s' is not a recognized command or program.\n", args[0]);
        }
    }

    return 0;
}
