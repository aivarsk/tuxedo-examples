#include <ctype.h>
#include <userlog.h>
#include <atmi.h>

int tpsvrinit(int argc, char *argv[]) {
  userlog("Server %s started", argv[0]);
  return 0;
}

void tpsvrdone() { userlog("Server stopped"); }

#ifdef __cplusplus
extern "C" void TOUPPER(TPSVCINFO *svcinfo);
#endif

void TOUPPER(TPSVCINFO *svcinfo) {
  userlog("Received string '%s'", svcinfo->data);
  for (int i = 0; i < svcinfo->len - 1; i++) {
    svcinfo->data[i] = toupper(svcinfo->data[i]);
  }
  userlog("Returning string '%s'", svcinfo->data);
  tpreturn(TPSUCCESS, 0, svcinfo->data, 0, 0);
}
