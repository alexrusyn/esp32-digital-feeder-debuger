#include "esp_http_server.h"

#include "controllers/test.h"

static const httpd_uri_t endpoints[] = {
    {
        .uri = "/api/test",
        .method = HTTP_GET,
        .handler = testGetHandler,
    },
};

void registerApiRoutes(httpd_handle_t server);