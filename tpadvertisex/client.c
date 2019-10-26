#include <stdio.h>
#include <tpadm.h>

int main(int argc, char *argv[]) {
  FBFR32 *fml = (FBFR32 *)tpalloc("FML32", NULL, 1024);

  Fchg32(fml, TA_CLASS, 0, "T_SVCGRP", 0);
  Fchg32(fml, TA_OPERATION, 0, "GET", 0);

  long olen;
  tpcall(".TMIB", (char *)fml, 0, (char **)&fml, &olen, 0);

  Fprint32(fml);

  char *req = tpalloc("FML32", NULL, 1024);
  FLDOCC32 occ = Foccur32(fml, TA_SERVICENAME);
  for (FLDOCC32 i = 0; i < occ; i++) {
    char *service = Ffind32(fml, TA_SERVICENAME, i, NULL);
    tpcall(service, req, 0, &req, &olen, 0);
    printf("%s - %s\n", service, tperrno == TPESVCFAIL ? "mismatch" : "match");
  }
  return 0;
}
