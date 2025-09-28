#include "auth.h"
#include "config.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "AUTH";

bool checkApiKey(httpd_req_t *req)
{
    char key[64];
    int len = httpd_req_get_hdr_value_len(req, "x-api-key") + 1;

    if (len > 1 && len < sizeof(key))
    {
        httpd_req_get_hdr_value_str(req, "x-api-key", key, sizeof(key));
        return (strcmp(key, API_KEY) == 0);
    }

    return false;
}

bool checkAccess(httpd_req_t *req)
{
    if (!checkApiKey(req))
    {
        ESP_LOGW(TAG, "Unauthorized request");
        sendForbidden(req);
        return false;
    }

    return true;
}

void addCorsHeader(httpd_req_t *req)
{
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", ORIGIN);
    httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "x-api-key, Content-Type");
}

void sendForbidden(httpd_req_t *req)
{
    httpd_resp_set_status(req, "403 Forbidden");
    httpd_resp_send(req, "Invalid API Key", HTTPD_RESP_USE_STRLEN);
}
