#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/Stack.h"

void check (char *brackets) {
    struct Stack *st = malloc(sizeof(struct Stack));

    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        return;
    }

    init_stack(st);

    push_stack(st, &brackets[0]);

    for (int i = 1; i < (int)strlen(brackets); ++i) {
        if (strchr("([{", brackets[i])) {
            push_stack(st, &brackets[i]);
            continue;
        }
        if (brackets[i] == ')') {
            if(*(char*)peek_stack(st) == '(') {
                pop_stack(st);
                continue;
            } else {
                push_stack(st, &brackets[i]);
                break;
            }
        }
        if (brackets[i] == ']') {
            if(*(char*)peek_stack(st) == '[') {
                pop_stack(st);
                continue;
            } else {
                push_stack(st, &brackets[i]);
                break;
            }
        }
        if (brackets[i] == '}') {
            if(*(char*)peek_stack(st) == '{') {
                pop_stack(st);
                continue;
            } else {
                push_stack(st, &brackets[i]);
                break;
            }
        }
    }

    if (is_empty_stack(st)) {
        printf("Sirul %s este corect parantezat\n", brackets);
    } else {
        printf("Sirul %s nu este corect parantezat\n", brackets);
    }

    purge_stack(st);
    free(st);

}

int main() {
    char brackets[] = "{{[(())()][]}}";
    char brackets2[] = "{{[(()()][]}})";

    check (brackets);
    check (brackets2);

    return 0;
}