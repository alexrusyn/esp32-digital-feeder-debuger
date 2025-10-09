#include "esp_http_server.h"

#include "controllers/default.h"
#include "controllers/test.h"

static const httpd_uri_t endpoints[] = {
    {
        .uri = "/",
        .method = HTTP_GET,
        .handler = defaultGetHandler,
    },
    {
        .uri = "/api/test/status",
        .method = HTTP_GET,
        .handler = testGetHandler,
    },
    {
        .uri = "/api/test/toggle",
        .method = HTTP_POST,
        .handler = testPostHandler,
    },
};

void registerApiRoutes(httpd_handle_t server);