/* fse.c */
#include "fse.h"

int8 *securerand(int16 size) {
    int8 *p;

    assert(size > 0);
    p = (int8 *)malloc(size);
    assert(p);

    arc4random_buf(p, (size_t)size);
    return p;
}

int8 *readkey(char *prompt) {
    char buf[256];
    int8 *p;
    int8 size, idx;

    printf("%s", prompt);
    fflush(stdout);

    memset(buf, 0, 256);
    read(0, buf, 255);
    size = (int8)strlen(buf);

    // abcd\n = 5
    // 01234
    idx = size - 1;
    p = (int8 *)buf + idx;
    *p = 0;

    p = (int8 *)malloc(size);
    assert(p);
    strncpy((char *)p, buf, idx);

    return p;
}

int main(int argc, char *argv[]) {
    char *infile, *outfile;
    int infd, outfd;
    int8 *key;
    int16 padsize;
    int16 *padsize16;
    int8 *padsize8;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", *argv);
        return -1;
    }

    infile = argv[1];
    outfile = argv[2];

    infd = open(infile, O_RDONLY);
    if (infd < 1) {
        perror("open");
        return -1;
    }

    outfd = open(outfile, O_WRONLY|O_CREAT, 00600);
    if (outfd < 1) {
        close(infd);
        perror("open");
        return -1;
    }

    key = readkey("Key:");
    assert(key);

    padsize8 = securerand(2);
    padsize16 = (int16 *)padsize8;
    padsize = *padsize16;
    printf("padsize: %d\n", (int)padsize);

    close(infd);
    close(outfd);
    free(padsize8);

    return 0;
}
