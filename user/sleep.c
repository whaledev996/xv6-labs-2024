#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: sleep [ticks]...\n");
    exit(1);
  }
  int res = sleep(atoi(argv[1]));
  if (res == -1) {
    fprintf(2, "Process killed");
    exit(1);
  }
  exit(0);
}

