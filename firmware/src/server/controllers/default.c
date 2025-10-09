#include "test.h"

#include "esp_http_server.h"

#include "../utils/cors.h"

esp_err_t defaultGetHandler(httpd_req_t *req)
{
    if (!checkAndAddCorsHeaders(req))
        return ESP_OK;

    const char *resp_str = "The server is up and running.";
    httpd_resp_send(req, resp_str, strlen(resp_str));

    return ESP_OK;
}