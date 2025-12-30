#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h> 

#define MAX_LINE 80
#define MAX_HISTORY 10
char history[MAX_HISTORY][MAX_LINE];
int count = 0;
void save_to_history(char *text) {
    if (count < MAX_HISTORY) {
        strcpy(history[count], text);
        count++;
    }
    else {
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            strcpy(history[i], history[i + 1]);
        }
        strcpy(history[MAX_HISTORY - 1], text);
    }
}

int main() {
    char input[MAX_LINE];
    char *args[10];
    printf("--- My Simple Windows Shell ---\n");
    while (1) {
        printf("> "); 
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0; 
        if (strlen(input) == 0) continue; 
        save_to_history(input);
        if (strcmp(input, "exit") == 0) break;
        if (strcmp(input, "history") == 0) {
            for (int i = 0; i < count; i++) {
                printf("%d: %s\n", i + 1, history[i]);
            }
            continue;
        }
        if (strcmp(input, "dir") == 0 || strcmp(input, "cls") == 0) {
            system(input);
            continue;
        }
        int i = 0;
        char *word = strtok(input, " ");
        while (word != NULL) {
            args[i++] = word;
            word = strtok(NULL, " ");
        }
        args[i] = NULL; 
        _spawnvp(_P_WAIT, args[0], (const char * const *)args);
    }

    return 0;
}
