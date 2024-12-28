#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int pid;
  int p1[2];
  int p2[2];
  pipe(p1); // from parent (write) -> child (read)
  pipe(p2); // from child (write) -> parent (read)
  pid = fork();
  if (pid == -1) {
    exit(1);
  }

  if (pid == 0) {
    // child
    // close p1 for writing and p2 for reading
    close(p1[1]);
    close(p2[0]);

    char buf[1];
    read(p1[0], buf, 1);
    printf("%d: received ping\n", getpid());

    write(p2[1], buf, 1);

    close(p1[0]);
    close(p2[1]);
  } else {
    // parent
    // close p1 for reading and p2 for writing
    close(p1[0]);
    close(p2[1]);

    write(p1[1], "h", 1);

    char buf[1];
    read(p2[0], buf, 1);

    printf("%d: received pong\n", getpid());

    close(p1[1]);
    close(p2[0]);
  }

  exit(0);
}
