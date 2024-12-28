#include "kernel/types.h"
#include "user/user.h"

// read from left neighbor (fd), send finish signal to root process (fd2)
void process(int fd, int fd2)
{
  int p[2];
  pipe(p);
  int num;
  int ret = read(fd, &num, sizeof(int));
  if (ret == 0) {
    write(fd2, 0, 1);
    close(fd2);
    return;
  }
  printf("prime %d\n", num);
  int pid = fork();
  if (pid == 0) {
    close(p[1]);
    close(fd);
    process(p[0], fd2);
  } else {
    close(p[0]);
    for(;;) {
      int num2;
      int res = read(fd, &num2, sizeof(int));
      if (res == 0) {
        break;
      }
      if (num2 % num != 0) {
        write(p[1], &num2, sizeof(int));
      }
    }
    close(p[1]);
    close(fd);
    close(fd2);
  }
}

int main(int argc, char *argv[])
{
  int p[2];
  int s[2];
  pipe(p);
  pipe(s);
  int pid = fork();
  if (pid == 0) {
    close(s[0]);
    close(p[1]);
    process(p[0], s[1]);
    close(s[1]);
  } else {
    close(p[0]);
    close(s[1]);
    for(int i = 2; i <= 280; i++) {
      write(p[1], &i, sizeof(int));
    }
    close(p[1]);
    char buf;
    read(s[0], &buf, 1);
    close(s[0]);
  }
  return 0;
}
