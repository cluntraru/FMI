#include <unistd.h>
#include <stdio.h>

int main() {
    char *buff = "Hello world!\n";
    write(STDOUT_FILENO, buff, 13);
    return 0;
}
