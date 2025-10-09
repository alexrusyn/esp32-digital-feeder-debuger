#include "cJSON.h"

#include "esp_http_server.h"
#include "esp_log.h"

#include "./errorStatus.h"

static esp_err_t clearResponse(char *response, cJSON *json)
{
    free(response);
    cJSON_Delete(json);
    return ESP_OK;
}

esp_err_t sendJsonResponse(httpd_req_t *req, cJSON *data)
{
    cJSON *json = cJSON_CreateObject();

    cJSON_AddItemToObject(json, "data", data);
    cJSON_AddStringToObject(json, "status", "ok");

    char *response = cJSON_PrintUnformatted(json);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_status(req, getHttpStatusText(200));
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    return clearResponse(response, json);
}

esp_err_t sendJsonMessage(httpd_req_t *req, const char *status, const char *message)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "status", status);
    cJSON_AddStringToObject(json, "message", message);

    char *response = cJSON_PrintUnformatted(json);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_status(req, getHttpStatusText(200));
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    return clearResponse(response, json);
}

esp_err_t sendJsonError(httpd_req_t *req, int code, const char *error)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "status", "error");
    cJSON_AddNumberToObject(json, "code", code);
    cJSON_AddStringToObject(json, "message", error);

    char *response = cJSON_PrintUnformatted(json);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_status(req, getHttpStatusText(code));
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    return clearResponse(response, json);
}