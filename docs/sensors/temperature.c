#include <si_toolchain.h>
#include <C8051F040.h>
#include <timer.h>

#define TEMP_CMD_SKIP_ROM 0xCC
#define TEMP_CMD_CONVERT 0x44
#define TEMP_CMD_READ_PAD 0xBE

sbit wire = P2 ^ 7;

void __drive_wire(void) {
    XBR2 = 0x40;
    wire = 0;
}

void __release_wire(void) {
    wire = 1;
    XBR2 = 0x00;
}

bool reset_communication(void) {
    bool result = false;

    __drive_wire();
    delay_us(480);

    __release_wire();
    delay_us(80);

    result = !wire;
    delay_us(450);

    return result;
}

void __write_bit(uint8_t context) {
    init_timer0(5);
    __drive_wire();
    delay_timer0();

    wire = context & 0x01;
    delay_us(100);
    __release_wire();
}

void __write_byte(uint8_t context) {
    uint8_t i = 8;

    while (i--) {
        delay_us(100);
        __write_bit(context);
        context >>= 1;
        XBR2  = 0x40;
    }
}

uint8_t __read_bit(void) {
    uint8_t result = 0;
    __drive_wire();
    
    init_timer0(12);
    __release_wire();
    delay_timer0();

    return wire;
}

uint8_t __read_byte(void) {
    uint8_t result = 0, i = 8;
    while (i--) {
        delay_us(100);
        result >>= 1;
        if (__read_bit()) result |= 0x80;
        XBR2 = 0x40;
    }

    return result;
}

uint32_t read_temperature(void) {
    uint32_t temperature = 0;

    reset_communication();
    __write_byte(TEMP_CMD_SKIP_ROM);
    __write_byte(TEMP_CMD_CONVERT);
    while(__read_byte() != 0xFF);

    reset_communication();
    __write_byte(TEMP_CMD_SKIP_ROM);
    __write_byte(TEMP_CMD_READ_PAD);
    temperature = __read_byte();
    temperature |= __read_byte() << 8;

    return temperature;
}