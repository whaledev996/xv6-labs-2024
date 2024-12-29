#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: xargs [file] [args]...");
    exit(1);
  }
  int cc;
  int i = 0;
  int j = 1;
  char c;
  char *arglist[MAXARG];
  char buf[100];
  for(;;){
    cc = read(0, &c, 1);
    if (cc < 1) {
      break;
    }
    if (c == '\n' || c == '\r'){
      buf[i] = '\0';
      for(; argv[j]; j++) {
        arglist[j-1] = argv[j];
      }
      arglist[j-1] = buf;
      if(fork() == 0) {
        exec(arglist[0], arglist);
      }
      wait(0);
      memset(buf, 0, 100);
      i = 0;
      j = 1;
    } else {
      buf[i++] = c;
    }
  }
  return 0;
}
