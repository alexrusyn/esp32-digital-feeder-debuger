#include "esp_http_server.h"
#include "cJSON.h"

esp_err_t sendJsonResponse(httpd_req_t *req, cJSON *data);

esp_err_t sendJsonMessage(httpd_req_t *req, const char *status, const char *message);

esp_err_t sendJsonError(httpd_req_t *req, int code, const char *error);
