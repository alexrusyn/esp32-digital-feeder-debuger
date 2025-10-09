#include "test.h"

#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"

#include "../utils/cors.h"
#include "../utils/body.h"
#include "../utils/auth.h"
#include "../utils/json.h"

#include "../../led/led.h"

esp_err_t testGetHandler(httpd_req_t *req)
{
    if (!checkAndAddCorsHeaders(req) || !checkAccess(req))
        return ESP_OK;

    cJSON *data = cJSON_CreateObject();
    cJSON_AddBoolToObject(data, "isLedOn", getLedState());

    return sendJsonResponse(req, data);
}

esp_err_t testPostHandler(httpd_req_t *req)
{
    if (!checkAndAddCorsHeaders(req) || !checkAccess(req))
        return ESP_OK;

    cJSON *body = parseRequestBody(req);

    if (!body)
        return sendJsonError(req, 400, "Invalid JSON");

    cJSON *state = cJSON_GetObjectItem(body, "isLedOn");

    if (!cJSON_IsBool(state))
    {
        cJSON_Delete(body);
        return sendJsonError(req, 400, "The 'isLedOn' are missing or invalid");
    }

    setLedState(cJSON_IsTrue(state));
    cJSON_Delete(body);

    return sendJsonMessage(req, "ok", "Led is switched to: " + getLedState());
}
