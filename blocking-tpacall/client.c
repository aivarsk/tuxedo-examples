#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atmi.h>

int main(int argc, char *argv[]) {
  char *sndbuf;
  long sndlen;
  int ret;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(1);
  }

  sndlen = strlen(argv[1]);

  sndbuf = (char *)tpalloc("STRING", NULL, sndlen + 1);
  assert(sndbuf != NULL);

  strcpy(sndbuf, argv[1]);

  printf(">>> %s\n", sndbuf);

  printf("tpacall(..., TPNOFLAGS) for implicit tpinit()\n");
  ret = tpacall((char *)"SLEEPER", (char *)sndbuf, 0, TPNOFLAGS);
  if (ret == -1) {
    fprintf(stderr, "SLEEPER call failed %d - %s\n", tperrno,
            tpstrerror(tperrno));
    exit(1);
  }

  printf("tpacall(..., TPNOTIME)\n");
  ret = tpacall((char *)"SLEEPER", (char *)sndbuf, 0, TPNOTIME);
  if (ret == -1) {
    fprintf(stderr, "SLEEPER call failed %d - %s\n", tperrno,
            tpstrerror(tperrno));
    exit(1);
  }

  printf("tpacall(..., TPNOBLOCK)\n");
  int pending_calls = 0;
  while (1) {
    ret = tpacall((char *)"SLEEPER", (char *)sndbuf, 0, TPNOBLOCK);
    if (ret == -1 && tperrno == TPEBLOCK) {
      fprintf(stdout, "Blocked after %d calls\n", pending_calls);
      break;
    }
    pending_calls++;
  }

  printf("tpacall(..., TPNOFLAGS)\n");
  ret = tpacall((char *)"SLEEPER", (char *)sndbuf, 0, TPNOFLAGS);
  if (ret == -1) {
    fprintf(stderr, "SLEEPER call failed %d - %s\n", tperrno,
            tpstrerror(tperrno));
    exit(1);
  }

  /* Example of a clean shutdown */
  tpfree(sndbuf);
  tpterm();
  return 0;
}
