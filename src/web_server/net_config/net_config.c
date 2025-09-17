#include "net_config.h"

#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "esp_netif_ip_addr.h"
#include "esp_http_server.h"

static const char *TAG = "HTTP_SERVER";

static esp_netif_t *sta_netif;
static httpd_handle_t server = NULL;
static ip_ready_cb_t user_ip_cb = NULL;

static void wifiConnectHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));

        httpd_config_t config = HTTPD_DEFAULT_CONFIG();

        if (httpd_start(&server, &config) == ESP_OK && user_ip_cb)
        {
            user_ip_cb(server);
        }
    }
}

void initWifi(ip_ready_cb_t user_cb)
{
    user_ip_cb = user_cb;

    // init NVS memory
    esp_err_t nvsFlashREsult = nvs_flash_init();
    if (nvsFlashREsult == ESP_ERR_NVS_NO_FREE_PAGES || nvsFlashREsult == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvsFlashREsult = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvsFlashREsult);

    // init TCP/IP
    esp_netif_init();
    esp_event_loop_create_default();
    sta_netif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

    // Disable DHCP
    esp_netif_dhcpc_stop(sta_netif);

    // Apply static address
    esp_netif_ip_info_t ip_info = {
        .ip = {.addr = esp_ip4addr_aton(IP_ADDR)},
        .gw = {.addr = esp_ip4addr_aton(GW_ADDR)},
        .netmask = {.addr = esp_ip4addr_aton(NETMASK)},
    };

    ESP_ERROR_CHECK(esp_netif_set_ip_info(sta_netif, &ip_info));

    // Start WiFi
    esp_wifi_start();
    esp_wifi_connect();

    ESP_LOGI(TAG, "Connecting to WiFi: %s", WIFI_SSID);

    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifiConnectHandler, NULL, NULL);
}
