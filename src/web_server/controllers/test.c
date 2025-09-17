#include "test.h"

#include "esp_http_server.h"

esp_err_t testGetHandler(httpd_req_t *req)
{
    const char *resp_str = "Hello from test.c";
    httpd_resp_send(req, resp_str, strlen(resp_str));

    return ESP_OK;
}
