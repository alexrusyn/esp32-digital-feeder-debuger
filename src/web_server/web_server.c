#include "web_server.h"

#include "router.h"

#include "net_config/net_config.h"
#include "web_static/web_static.h"

static void ipReadyCallback(httpd_handle_t server)
{
    registerStaticHandler(server);
    registerApiRoutes(server);
}

void startWebServer(void)
{
    initWifi(&ipReadyCallback);
}
