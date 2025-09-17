#pragma once

#include "esp_http_server.h"

esp_err_t staticFileHandler(httpd_req_t *req);
void registerStaticHandler(httpd_handle_t server);