#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atmi.h>

int main(int argc, char *argv[]) {
  char *sndbuf, *rcvbuf;
  long sndlen, rcvlen;
  int ret;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(1);
  }

  sndlen = strlen(argv[1]);

  sndbuf = (char *)tpalloc("STRING", NULL, sndlen + 1);
  assert(sndbuf != NULL);

  strcpy(sndbuf, argv[1]);

  rcvbuf = (char *)tpalloc("STRING", NULL, sndlen + 1);
  assert(rcvbuf != NULL);

  printf(">>> %s\n", sndbuf);

  ret = tpcall((char *)"TOUPPER", (char *)sndbuf, 0, (char **)&rcvbuf, &rcvlen,
               0);

  if (ret == -1) {
    fprintf(stderr, "TOUPPER call failed %d - %s\n", tperrno,
            tpstrerror(tperrno));
    exit(1);
  }

  printf("<<< %s\n", rcvbuf);

  /* Example of a clean shutdown */
  tpfree(sndbuf);
  tpfree(rcvbuf);
  tpterm();
  return 0;
}
