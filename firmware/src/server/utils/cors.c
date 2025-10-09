#include "cors.h"

#include "esp_http_server.h"

#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "./json.h"

static const char *ALLOWED_ORIGIN_ADDRESS = ALLOWED_ORIGIN;

bool checkAndAddCorsHeaders(httpd_req_t *req)
{
    char originBuffer[128];
    httpd_req_get_hdr_value_str(req, "Origin", originBuffer, sizeof(originBuffer));

    if (strcmp(originBuffer, ALLOWED_ORIGIN_ADDRESS) != 0)
    {
        sendJsonError(req, 403, "Forbidden origin");
        return false;
    }

    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", ALLOWED_ORIGIN_ADDRESS);
    httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "X-Api-Key, Content-Type");
    httpd_resp_set_hdr(req, "Access-Control-Max-Age", "3600");

    return true;
}
