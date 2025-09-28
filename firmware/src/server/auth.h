#pragma once

#include "esp_http_server.h"

#include <stdbool.h>

bool checkApiKey(httpd_req_t *req);

bool checkAccess(httpd_req_t *req);

void addCorsHeaders(httpd_req_t *req);

void sendForbidden(httpd_req_t *req);
