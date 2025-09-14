#pragma once

#include "esp_wifi.h"
#include "esp_http_server.h"

void initWiFi(void);
void startServer(void);

esp_err_t rootGetHandler(httpd_req_t *req);