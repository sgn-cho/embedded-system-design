#ifndef SYS_MSGD_H_
#define SYS_MSGD_H_

typedef struct {
    uint8_t route; // right 4 bits for destination, left 4 bits for source
    uint32_t data;
} sensor_message_t;

void msgd_init(void);

#endif