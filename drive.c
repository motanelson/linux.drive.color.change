#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// troca vermelho <-> azul (30-37, 40-47, 90-97, 100-107)
int swap_ansi_color(int code) {
    // cores normais FG
    if (code >= 30 && code <= 37) {
        int c = code - 30;
        int r = (c >> 0) & 1;
        int g = (c >> 1) & 1;
        int b = (c >> 2) & 1;
        int swapped = (b << 0) | (g << 1) | (r << 2);
        return 30 + swapped;
    }

    // cores normais BG
    if (code >= 40 && code <= 47) {
        int c = code - 40;
        int r = (c >> 0) & 1;
        int g = (c >> 1) & 1;
        int b = (c >> 2) & 1;
        int swapped = (b << 0) | (g << 1) | (r << 2);
        return 40 + swapped;
    }

    // bright FG
    if (code >= 90 && code <= 97) {
        int c = code - 90;
        int r = (c >> 0) & 1;
        int g = (c >> 1) & 1;
        int b = (c >> 2) & 1;
        int swapped = (b << 0) | (g << 1) | (r << 2);
        return 90 + swapped;
    }

    // bright BG
    if (code >= 100 && code <= 107) {
        int c = code - 100;
        int r = (c >> 0) & 1;
        int g = (c >> 1) & 1;
        int b = (c >> 2) & 1;
        int swapped = (b << 0) | (g << 1) | (r << 2);
        return 100 + swapped;
    }

    return code; // outros códigos não alterados
}

void process_ansi(const char *str) {
    while (*str) {
        if (*str == 27 && *(str+1) == '[') {
            str += 2;

            printf("\x1b[");

            while (*str && *str != 'm') {
                int code = 0;

                // parse número manual
                while (*str >= '0' && *str <= '9') {
                    code = code * 10 + (*str - '0');
                    str++;
                }

                code = swap_ansi_color(code);

                printf("%d", code);

                if (*str == ';') {
                    printf(";");
                    str++;
                }
            }

            if (*str == 'm') {
                printf("m");
                str++;
            }
        } else {
            putchar(*str);
            str++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        return 1;
    }

    // construir comando
    char cmd[4096] = "";
    for (int i = 1; i < argc; i++) {
        strcat(cmd, argv[i]);
        if (i < argc - 1) strcat(cmd, " ");
    }

    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), fp)) {
        process_ansi(buffer);
    }

    pclose(fp);
    return 0;
}
