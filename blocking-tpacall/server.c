#include <ctype.h>
#include <userlog.h>
#include <atmi.h>
#include <stdlib.h>

int tpsvrinit(int argc, char *argv[]) {
  userlog("Server %s started", argv[0]);
  return 0;
}

void tpsvrdone() { userlog("Server stopped"); }

#ifdef __cplusplus
extern "C" void SLEEPER(TPSVCINFO *svcinfo);
#endif

void SLEEPER(TPSVCINFO *svcinfo) {
  userlog("Received string '%s'", svcinfo->data);
  sleep(60);
  userlog("Returning string '%s'", svcinfo->data);
  tpreturn(TPSUCCESS, 0, svcinfo->data, 0, 0);
}
