#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/websocket.h"
#include "hardware/flash.h"
#include <string.h>

// Konfiguracja Wi-Fi
#define WIFI_SSID "your_ssid"
#define WIFI_PASS "your_password"

// MQTT konfiguracja
#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_TOPIC "home/sensor/temp"

void connect_to_wifi() {
    cyw43_arch_init();
    if (cyw43_wifi_connect_timeout(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_MIXED_PSK, 30000) == 0) {
        printf("Połączono z Wi-Fi!\n");
    } else {
        printf("Błąd połączenia!\n");
    }
}

void mqtt_publish() {
    struct mqtt_connect_client_info_t ci = { "RP2040", NULL, NULL, 0, NULL, NULL, 0, 0 };
    struct mqtt_client *client = mqtt_client_new();
    ip_addr_t server;
    IP4_ADDR(&server, 192, 168, 1, 100);
    mqtt_connect(client, &server, MQTT_PORT, NULL, &ci);
    mqtt_publish(client, MQTT_TOPIC, "23.5", strlen("23.5"), 0, 0, NULL, NULL);
}

void websocket_callback(void *arg, struct websocket_pcb *ws, const struct pbuf *p) {
    char msg[64];
    memcpy(msg, p->payload, p->len);
    msg[p->len] = 0;
    if (strcmp(msg, "LED_ON") == 0) gpio_put(25, 1);
    if (strcmp(msg, "LED_OFF") == 0) gpio_put(25, 0);
}

void start_websocket_server() {
    struct websocket_pcb *ws = websocket_new();
    websocket_bind(ws, 81, websocket_callback);
    websocket_listen(ws);
}

int main() {
    stdio_init_all();
    connect_to_wifi();
    mqtt_publish();
    start_websocket_server();
    while (1) sleep_ms(1000);
}
