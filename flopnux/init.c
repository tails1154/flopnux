#define _GNU_SOURCE
#include <stdio.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}
// Very small TAR extractor
static void untar(int fd, const char *dest) {
    char header[512];

    while (1) {
        if (read(fd, header, 512) != 512) break;

        if (header[0] == '\0') break;  // end of archive

        // Name and size
        char name[101];
        memcpy(name, header, 100);
        name[100] = '\0';

        // File type
        char type = header[156];

        // File size in octal ascii
        char sizebuf[12];
        memcpy(sizebuf, header+124, 12);
        long size = strtol(sizebuf, NULL, 8);

        // Build destination path
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dest, name);

        if (type == '5') { // directory
            mkdir(path, 0755);
        } else if (type == '0' || type == '\0') { // regular file
            int out = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0755);
            if (out < 0) die("untar create");

            char buf[512];
            long remaining = size;

            while (remaining > 0) {
                int n = read(fd, buf, 512);
                if (n <= 0) break;
                write(out, buf, (remaining < 512 ? remaining : 512));
                remaining -= 512;
            }

            close(out);
        } else {
            // unsupported type — skip it
        }

        // Skip padding to next 512 boundary
        long skip = ((size + 511) & ~511) - size;
        if (skip > 0) lseek(fd, skip, SEEK_CUR);
    }
}

int main() {
    // (1) Mount special filesystems
    mkdir("/proc", 0755);
//    mkdir("/sys", 0755);
    mkdir("/dev", 0755);
    mkdir("/mnt", 0755);
    mkdir("/mnt/floppy", 0755);
    mkdir("/tmp", 0755);
    mkdir("/newroot", 0755);

    if (mount("proc", "/proc", "proc", 0, "") < 0) die("mount /proc");
 //   if (mount("sysfs", "/sys", "sysfs", 0, "") < 0) die("mount /sys");

    // (2) Prepare /dev
    mknod("/dev/console", S_IFCHR | 0600, makedev(5,1));
    mknod("/dev/null",    S_IFCHR | 0666, makedev(1,3));

    // Rootfs concatenation file
    int out = open("/tmp/rootfs.gz", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (out < 0) die("open /tmp/rootfs.gz");

    // Function to read one part
    char path[64];
    for (int part = 1; part <= 2; part++) {
        printf("Insert floppy with part %d and press ENTER\n", part);
        getchar();

        if (mount("/dev/fd0", "/mnt/floppy", "vfat", 0, "") < 0) {
            die("mount /dev/fd0");
        }

        snprintf(path, sizeof(path), "/mnt/floppy/part%d.gz", part);
        int in = open(path, O_RDONLY);
        if (in < 0) die(path);

        char buf[4096];
        ssize_t r;
        while ((r = read(in, buf, sizeof(buf))) > 0)
            write(out, buf, r);
        close(in);

        umount("/mnt/floppy");
    }

    close(out);

    printf("Extracting rootfs...\n");

    // (3) Mount tmpfs for newroot
    if (mount("tmpfs", "/newroot", "tmpfs", 0, "") < 0)
        die("mount tmpfs /newroot");

    // (4) Extract using tar -xzf
    int tarfd = open("/tmp/rootfs.tar", O_RDONLY);if (tarfd < 0) die("open rootfs.tar");untar(tarfd, "/newroot");close(tarfd);
    die("exec tar");

    return 0;
}
