#include <stdio.h>
#include <stdbool.h>

int main() {
    char text[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaLorem ipsum dolor sit amet, consecteturaaa adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char word[50];
    char best[50];
    int maxCount = 0;
    int count = 0;
    int i = 0;
    int w = 0;

    while (true) {
        char ch = text[i];
        if (ch == ' ' || ch == '\0') {
            if (w > 0) {
                word[w] = '\0';
                if (count > maxCount) {
                    maxCount = count;
                    int k = 0;
                    while (word[k]) {
                        best[k] = word[k];
                        k++;
                    }
                    best[k] = '\0';
                }
                w = 0;
                count = 0;
            }
            if (ch == '\0') break;
        } else {
            if (w < 100) word[w++] = ch;
            if (ch == 'a' || ch == 'A') count++;
        }
        i++;
    }

    if (maxCount == 0) {
        printf("Net slov\n");
    } else {
        printf("%s\n%d\n", best, maxCount);
    }
}
