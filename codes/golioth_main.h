

#ifndef GOLIOTH_MAIN_H_
#define GOLIOTH_MAIN_H_

/*******************************************************************************
* Macros
********************************************************************************/
/* Wi-Fi Credentials: Modify WIFI_SSID, WIFI_PASSWORD and WIFI_SECURITY_TYPE
 * to match your Wi-Fi network credentials.
 * Note: Maximum length of the Wi-Fi SSID and password is set to
 * CY_WCM_MAX_SSID_LEN and CY_WCM_MAX_PASSPHRASE_LEN as defined in cy_wcm.h file.
 */

#define WIFI_SSID "SRKS"
#define WIFI_PASSWORD "sankara1"

/*
 * Fill in with your Golioth credentials
 *
 * These can be found at console.golioth.io -> Devices -> (yourdevice) -> Credentials
 */
#define GOLIOTH_PSK_ID "20230315062555-lime-tremendous-gazelle@esp32-84225f"
#define GOLIOTH_PSK "dab1e82b89ec849c7e2c27663c9c49c6"

/* Security type of the Wi-Fi access point. See 'cy_wcm_security_t' structure
 * in "cy_wcm.h" for more details.
 */
#define WIFI_SECURITY_TYPE                 CY_WCM_SECURITY_WPA2_AES_PSK

/* Maximum number of connection retries to the Wi-Fi network. */
#define MAX_WIFI_CONN_RETRIES             (10u)

/* Wi-Fi re-connection time interval in milliseconds */
#define WIFI_CONN_RETRY_INTERVAL_MSEC     (1000)

/*******************************************************************************
* Function Prototype
********************************************************************************/
void golioth_main_task(void *arg);

#endif /* GOLIOTH_MAIN_H_ */

/* [] END OF FILE */

