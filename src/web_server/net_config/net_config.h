#pragma once

#include "esp_http_server.h"

typedef void (*ip_ready_cb_t)(httpd_handle_t server);

void initWifi(ip_ready_cb_t user_cb);
