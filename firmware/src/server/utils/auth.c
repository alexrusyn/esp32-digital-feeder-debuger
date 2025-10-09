#include "auth.h"

#include "esp_log.h"

#include <string.h>

#include "./json.h"

// TODO: Need redo auth with PIN and TOKEN

static bool checkApiKey(httpd_req_t *req)
{
    char key[64];
    int len = httpd_req_get_hdr_value_len(req, "X-Api-Key") + 1;

    if (len > 1 && len < sizeof(key))
    {
        httpd_req_get_hdr_value_str(req, "X-Api-Key", key, sizeof(key));
        return (strcmp(key, API_KEY) == 0);
    }

    return false;
}

bool checkAccess(httpd_req_t *req)
{
    if (!checkApiKey(req))
    {
        sendJsonError(req, 403, "Access denied");

        return false;
    }

    return true;
}
