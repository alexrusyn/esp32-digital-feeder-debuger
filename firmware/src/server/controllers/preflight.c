#include "preflight.h"

#include "../utils/cors.h"

esp_err_t preflightHandler(httpd_req_t *req)
{
    if (!checkAndAddCorsHeaders(req))
        return ESP_OK;

    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}
