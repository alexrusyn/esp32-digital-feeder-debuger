#include "router.h"

#include "esp_http_server.h"

#include "controllers/preflight.h"

void registerApiRoutes(httpd_handle_t server)
{
    for (int i = 0; i < sizeof(endpoints) / sizeof(endpoints[0]); i++)
    {
        // Add preflight if needed
        if (endpoints[i].method == HTTP_GET || endpoints[i].method == HTTP_POST)
        {
            httpd_uri_t optionsUri = {
                .uri = endpoints[i].uri,
                .method = HTTP_OPTIONS,
                .handler = preflightHandler,
            };

            httpd_register_uri_handler(server, &optionsUri);
        }

        httpd_register_uri_handler(server, &endpoints[i]);
    }
}