#include "web_static.h"

#include "esp_log.h"
#include "esp_http_server.h"

static const char *TAG = "STATIC_WEB_SERVER";

esp_err_t staticFileHandler(httpd_req_t *req)
{
    char filepath[128];

    if (strcmp(req->uri, "/") == 0)
    {
        strcpy(filepath, "spiffs/index.html");
    }
    else
    {
        strcat(filepath, req->uri);
    }

    FILE *f = fopen(filepath, "r");

    if (!f)
    {
        ESP_LOGW(TAG, "File not found: %s", filepath);
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    if (strstr(filepath, ".html"))
        httpd_resp_set_type(req, "text/html");
    else if (strstr(filepath, ".css"))
        httpd_resp_set_type(req, "text/css");
    else if (strstr(filepath, ".js"))
        httpd_resp_set_type(req, "application/javascript");
    else if (strstr(filepath, ".png"))
        httpd_resp_set_type(req, "image/png");
    else if (strstr(filepath, ".jpg"))
        httpd_resp_set_type(req, "image/jpg");

    char chunk[256];
    size_t readBytes;

    while ((readBytes = fread(chunk, 1, sizeof(chunk), f)) > 0)
    {
        httpd_resp_send_chunk(req, chunk, readBytes);
    }
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

void registerStaticHandler(httpd_handle_t server)
{
    httpd_uri_t static_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = staticFileHandler,
    };

    httpd_register_uri_handler(server, &static_uri);
}
