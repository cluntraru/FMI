#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int sc_desc = open(argv[1], O_RDONLY);
    if (sc_desc == -1) {
        char *err_msg = "Input file does not exist\n";
        write(STDOUT_FILENO, err_msg, strlen(err_msg));
        return 0;
    }

    int dest_desc = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);
    fchmod(dest_desc, S_IRWXU);

    struct stat st;
    fstat(sc_desc, &st);

    void *buf = malloc(st.st_size);

    int size_left = st.st_size;
    int total_wr = 0;

    while(size_left) {
        int size_rd = read(sc_desc, buf, size_left);
        total_wr += write(dest_desc, buf, size_rd);

        lseek(sc_desc, total_wr, SEEK_SET);
        size_left = st.st_size - total_wr;
    }

    free(buf);
    close(sc_desc);
    close(dest_desc);
    return 0;
}