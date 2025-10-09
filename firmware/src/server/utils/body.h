#pragma once

#include "esp_http_server.h"
#include "cJSON.h"

cJSON *parseRequestBody(httpd_req_t *req);