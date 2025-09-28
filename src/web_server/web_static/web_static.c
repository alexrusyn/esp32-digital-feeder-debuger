#include "web_static.h"

#include "esp_log.h"
#include "esp_http_server.h"

#define FILE_PATH_MAX 256
#define CHECK_FILE_EXTENSION(filename, ext) (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

static const char *TAG = "STATIC_WEB_SERVER";

static esp_err_t setContentTypeFromFile(httpd_req_t *req, const char *filepath)
{
    const char *type = "text/plain";
    if (CHECK_FILE_EXTENSION(filepath, ".html"))
    {
        type = "text/html";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".js"))
    {
        type = "application/javascript";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".css"))
    {
        type = "text/css";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".png"))
    {
        type = "image/png";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".ico"))
    {
        type = "image/x-icon";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".svg"))
    {
        type = "text/xml";
    }
    return httpd_resp_set_type(req, type);
}

static esp_err_t defaultFileHandler(httpd_req_t *req, const char *filepath)
{
    FILE *f = fopen(filepath, "r");

    if (!f)
    {
        ESP_LOGW(TAG, "File not found: %s", filepath);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "File not found");
        return ESP_FAIL;
    }

    setContentTypeFromFile(req, filepath);

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

esp_err_t staticFileHandler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Requested URI: %s", req->uri);
    return defaultFileHandler(req, "/spiffs/index.html");
}

esp_err_t staticStyleFileHandler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Requested URI: %s", req->uri);
    return defaultFileHandler(req, "/spiffs/static/css/main.4efb37a3.css");
}

void registerStaticHandler(httpd_handle_t server)
{
    httpd_uri_t indexURI = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = staticFileHandler,
    };

    httpd_register_uri_handler(server, &indexURI);

    httpd_uri_t styleURI = {
        .uri = "/static/css/main.4efb37a3.css",
        .method = HTTP_GET,
        .handler = staticStyleFileHandler,
    };

    httpd_register_uri_handler(server, &styleURI);
}
