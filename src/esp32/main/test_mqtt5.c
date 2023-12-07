#include <sys/include/init.h>
#include <mqtt5/include/control.h>
#include <wifi/include/init.h>
#include "sys/include/msgd.h"
#include "sys/include/sensord.h"

void test_mqtt5(void) {
    sys_init_custom();
    init_wifi();
    init_mqtt5();
    msgd_init();
    sensord_init();
}