#ifndef __SERVER__H__
#define __SERVER__H__

#include "data_global.h"

int init_network(uint16_t port);
int send_data(struct conver_env_info *data);

#endif
