#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <esp_log.h>
#include <esp_mac.h>
#include <esp_wifi.h>
#include <esp_check.h>
#include <esp_err.h>
#include <ping/ping_sock.h>

static const char *TAG = "csi_recv_router";

/* function prototype */

static void wifi_csi_rx_cb(void *ctx, wifi_csi_info_t *info);
esp_err_t wifi_ping_router_start(void);

/* end of function prototype */


esp_err_t wifi_csi_init(void) {
    esp_err_t ret = ESP_OK;
    wifi_csi_config_t csi_config = {
        .lltf_en           = true,
        .htltf_en          = false,
        .stbc_htltf2_en    = false,
        .ltf_merge_en      = true,
        .channel_filter_en = true,
        .manu_scale        = true,
        .shift             = true,
    };

    static wifi_ap_record_t s_ap_info = {0};
    ret = esp_wifi_sta_get_ap_info(&s_ap_info);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to get AP info");

    ret = esp_wifi_set_csi_config(&csi_config);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to set CSI config");

    ret = esp_wifi_set_csi_rx_cb(wifi_csi_rx_cb, s_ap_info.bssid);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to set CSI RX callback");

    ret = esp_wifi_set_csi(true);
    if (ret != ESP_OK) {
        ESP_RETURN_ON_ERROR(ret, TAG, "Failed to enable CSI: %d", ret);
    }


    ret = wifi_ping_router_start();
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to start ping");

    return ret;
}

esp_err_t wifi_ping_router_start(void) {
    esp_ping_handle_t ping_handle = NULL;

    esp_ping_config_t ping_config = ESP_PING_DEFAULT_CONFIG();
    ping_config.count = 0;
    ping_config.interval_ms = 1000;
    ping_config.task_stack_size = 3072;
    ping_config.data_size = 1;

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(
        esp_netif_get_handle_from_ifkey("WIFI_AP_DEF"),
        &ip_info
    );

    ESP_LOGI(
        TAG, 
        "got ip:" IPSTR ", gw: " IPSTR,
        IP2STR(&ip_info.ip),
        IP2STR(&ip_info.gw)
    );

    ping_config.target_addr.u_addr.ip4.addr = ip4_addr_get_u32(&ip_info.gw);
    ping_config.target_addr.type = ESP_IPADDR_TYPE_V4;

    esp_ping_callbacks_t cbs = {0};
    esp_ping_new_session(&ping_config, &cbs, &ping_handle);
    esp_ping_start(ping_handle);

    return ESP_OK;
}

static void wifi_csi_rx_cb(void *ctx, wifi_csi_info_t *info) {
    if (!info || !info->buf) {
        ESP_LOGW(TAG, "<%s> wifi_csi_cb", esp_err_to_name(ESP_ERR_INVALID_ARG));
        return;
    }

    if (memcmp(info->mac, ctx, 6)) {
        return;
    }

    static int s_count = 0;
    const wifi_pkt_rx_ctrl_t *rx_ctrl = &info->rx_ctrl;

    if (!s_count) {
        ESP_LOGI(TAG, "================ CSI RECV ================");
    }

    info->len = 128;

    printf("CSI_DATA,%d," MACSTR ",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            s_count++, MAC2STR(info->mac), rx_ctrl->rssi, rx_ctrl->rate, rx_ctrl->sig_mode,
            rx_ctrl->mcs, rx_ctrl->cwb, rx_ctrl->smoothing, rx_ctrl->not_sounding,
            rx_ctrl->aggregation, rx_ctrl->stbc, rx_ctrl->fec_coding, rx_ctrl->sgi,
            rx_ctrl->noise_floor, rx_ctrl->ampdu_cnt, rx_ctrl->channel, rx_ctrl->secondary_channel,
            rx_ctrl->timestamp, rx_ctrl->ant, rx_ctrl->sig_len, rx_ctrl->rx_state);

    printf(",%d,%d,\"[%d", info->len, info->first_word_invalid, info->buf[0]);

    for (int i = 1; i < info->len; i++) {
        printf(",%d", info->buf[i]);
    }

    printf("]\"\n");
}