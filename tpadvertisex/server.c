#include <userlog.h>
#include <atmi.h>
#include <string.h>

static char name[128];
void SERVICE(TPSVCINFO *svcinfo) {
  userlog("%s called for %s called", svcinfo->name, name);
  tpreturn(strcmp(svcinfo->name, name) == 0 ? TPSUCCESS : TPFAIL, 0, svcinfo->data, 0, 0);
}

static char namex[128];
void SERVICEX(TPSVCINFO *svcinfo) {
  userlog("%s called for %s", svcinfo->name, namex);
  tpreturn(strcmp(svcinfo->name, namex) == 0 ? TPSUCCESS : TPFAIL, 0, svcinfo->data, 0, 0);
}

int tpsvrinit(int argc, char *argv[]) {
  const char *g = NULL;
  const char *i = NULL;

  for (int n = 0; n < argc; n++) {
    if (strcmp(argv[n], "-g") == 0) {
      g = argv[++n];
    } else if (strcmp(argv[n], "-i") == 0) {
      i = argv[++n];
    }
  }

  snprintf(name, sizeof(name), "SERVICE_%s_%s", g, i);
  tpadvertise(name, SERVICE);
  snprintf(namex, sizeof(namex), "SERVICEX_%s_%s", g, i);
  tpadvertisex(namex, SERVICEX, 0);
  return 0;
}
