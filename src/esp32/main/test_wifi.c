#include "wifi/include/ap.h"
#include "sys/include/init.h"

void test_ap(void) {
    sys_init_custom();
    wifi_init_softap();
}