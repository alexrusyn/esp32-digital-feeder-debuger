#include "fs_manager.h"

#include "esp_spiffs.h"
#include "esp_log.h"

static const char *TAG = "FS";
static const char *PARTITION_LABEL = "storage";

void filesystemMount()
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = PARTITION_LABEL,
        .max_files = 10,
        .format_if_mount_failed = true,
    };

    esp_err_t registerReturn = esp_vfs_spiffs_register(&conf);

    if (registerReturn == ESP_OK)
    {
        ESP_LOGI(TAG, "SPIFFS mounted successfully");
    }
    else
    {
        if (registerReturn == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        }
        else if (registerReturn == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, "Failed to find %s partition", PARTITION_LABEL);
        }
        else
        {
            ESP_LOGE(TAG, "Failed to init %s partition: %s", PARTITION_LABEL, esp_err_to_name(registerReturn));
        }
    }

    size_t total = 0, used = 0;
    esp_err_t infoRet = esp_spiffs_info(PARTITION_LABEL, &total, &used);
    if (infoRet != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get %s partition info (%s)", PARTITION_LABEL, esp_err_to_name(infoRet));
        filesystemUnmount();
    }

    ESP_LOGI(TAG, "Partition size: total=%d, used=%d", total, used);
}

void filesystemUnmount()
{
    esp_vfs_spiffs_unregister(PARTITION_LABEL);
    ESP_LOGI(TAG, "SPIFFS unmounted");
}
