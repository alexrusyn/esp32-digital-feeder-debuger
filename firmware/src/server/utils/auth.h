#pragma once

#include "esp_http_server.h"

#include <stdbool.h>

bool checkAccess(httpd_req_t *req);
