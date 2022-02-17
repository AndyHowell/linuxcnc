/*
**Notes:
**  1) The rtapi_app_main() creates a minimal component (jogmod)
**     allowing use with:
**     'halcmd loadrt jogmod' (loads module: jogmod.so)
**  2) homing.c provides all functions required by subsequent load
**     of motmod
*/
#include "rtapi.h"
#include "rtapi_app.h"
#include "hal.h"
MODULE_LICENSE("GPL");

#define JOGMOD_DEBUG
#undef  JOGMOD_DEBUG

// provision for testing use of module parameters:
static char *jog_parms;
RTAPI_MP_STRING(jog_parms,"Example jog parms");

static int jogmod_id;
int rtapi_app_main(void)
{
#ifdef JOGMOD_DEBUG
    if (jog_parms) {
        rtapi_print("%s:%s: jog_parms=%s\n",__FILE__,__FUNCTION__,jog_parms);
    }
#endif

    char* emsg;
    jogmod_id = hal_init("jogmod"); // dlopen(".../jogmod.so")
    if (jogmod_id < 0) {emsg="hal_init()"; goto error;}

    hal_ready(jogmod_id);
    return 0;

error:
    rtapi_print_msg(RTAPI_MSG_ERR,"\njogmod FAIL:<%s>\n",emsg);
    hal_exit(jogmod_id);
    return -1;
}

void rtapi_app_exit(void)
{
    hal_exit(jogmod_id);
    return;
}
