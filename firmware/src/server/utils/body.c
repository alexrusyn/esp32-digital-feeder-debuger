#include "esp_http_server.h"

#include "cJSON.h"

static char buffer[512];

cJSON *parseRequestBody(httpd_req_t *req)
{
    int bufferLength = httpd_req_recv(req, buffer, sizeof(buffer) - 1);

    if (bufferLength <= 0)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid body");
        return NULL;
    }

    buffer[bufferLength] = '\0';

    cJSON *json = cJSON_Parse(buffer);

    if (!json)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return NULL;
    }

    return json;
}
