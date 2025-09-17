#include "router.h"

#include "esp_http_server.h"

void registerApiRoutes(httpd_handle_t server)
{
    for (int i = 0; i < sizeof(endpoints) / sizeof(endpoints[0]); i++)
    {
        httpd_register_uri_handler(server, &endpoints[i]);
    }
}