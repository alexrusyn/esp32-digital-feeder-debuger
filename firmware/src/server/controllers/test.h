#pragma once

#include "esp_http_server.h"

esp_err_t testGetHandler(httpd_req_t *req);

esp_err_t testPostHandler(httpd_req_t *req);
