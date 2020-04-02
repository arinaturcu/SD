#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Deque.h"

int main() {
    int n;
    char digits[20];
    struct Deque *dq = malloc(sizeof(struct Deque));

    if (dq == NULL) {
        perror("Not enough memory to create the deque!");
        return -1;
    }

    printf("Introdu numarul: ");
    scanf("%d", &n);

    init_deque(dq);

    sprintf(digits, "%d", n);

    for (int i = 0; i < (int)strlen(digits); ++i) {
        push_back(dq, &digits[i]);
    }

    while (*(char*)back(dq) == *(char*)front(dq) && get_size_deque(dq) > 1) {
        pop_back(dq);
        pop_front(dq);
    }

    if (get_size_deque(dq) > 1) {
        printf("Nu este palindrom.\n");
    } else {
        printf("Este palindrom\n");
    }

    return 0;
}
