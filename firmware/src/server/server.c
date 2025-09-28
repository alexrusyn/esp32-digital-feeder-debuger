#include "server.h"
#include "router.h"
#include "config.h"

static void ipReadyCallback(httpd_handle_t server)
{
    registerApiRoutes(server);
}

void startWebServer(void)
{
    initWifi(&ipReadyCallback);
}
