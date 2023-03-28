
#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"
#include "watchdog.h"
#include <FreeRTOS.h>
#include "golioth_main.h"
#include <task.h>
#include <inttypes.h>

#ifdef CY_BOOT_USE_EXTERNAL_FLASH
#include "flash_qspi.h"
#endif

#define QSPI_SLAVE_SELECT_LINE              (1UL)

#define LED_TOGGLE_INTERVAL_MS              (1000u)

#define BLINK_TASK_STACK_SIZE               (3 * 1024)
#define BLINK_TASK_PRIORITY                 (1)

#define GOLIOTH_MAIN_TASK_STACK_SIZE        (5 * 1024)
#define GOLIOTH_MAIN_TASK_PRIORITY          (1)

static void blink_task(void* arg) {
    for (;;)
    {
        vTaskDelay(LED_TOGGLE_INTERVAL_MS / portTICK_PERIOD_MS);
        cyhal_gpio_toggle(CYBSP_USER_LED);
    }
}


int main(void)
{
    cy_rslt_t result;

    /* Update watchdog timer to mark successful start up of application */
    cy_wdg_kick();
    cy_wdg_free();

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    /* Free the hardware instance object iff initialized by other core
     * before initializing the same hardware instance object in this core. */
    cyhal_hwmgr_free(&CYBSP_UART_obj);
    cyhal_hwmgr_free(&CYBSP_DEBUG_UART_RX_obj);
    cyhal_hwmgr_free(&CYBSP_DEBUG_UART_TX_obj);

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

#ifdef CY_BOOT_USE_EXTERNAL_FLASH
    cy_en_smif_status_t qspi_status = qspi_init_sfdp(QSPI_SLAVE_SELECT_LINE);
    if (CY_SMIF_SUCCESS == qspi_status) {
        printf("External Memory initialized w/ SFDP.");
    } else {
        printf("External Memory initialization w/ SFDP FAILED: 0x%08"PRIx32, (uint32_t)qspi_status);
    }
#endif

    /* Initialize the User LED */
    result = cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT,
              CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    (void) result; /* To avoid compiler warning in release build */

    printf("\n=========================================================\n");
    printf("[GoliothApp] Version: %d.%d.%d, CPU: CM4\n",
           APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_BUILD);
    printf("\n=========================================================\n");

    printf("[GoliothApp] Watchdog timer started by the bootloader is now turned off to mark the successful start of Golioth app.\r\n");

    printf("[GoliothApp] User LED toggles at %d msec interval\r\n\n", LED_TOGGLE_INTERVAL_MS);

    /* Create the tasks. */
    xTaskCreate(blink_task, "Blink task", BLINK_TASK_STACK_SIZE, NULL,
                BLINK_TASK_PRIORITY, NULL);
    xTaskCreate(golioth_main_task, "Golioth main task", GOLIOTH_MAIN_TASK_STACK_SIZE, NULL,
                GOLIOTH_MAIN_TASK_PRIORITY, NULL);

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never get here. */
    CY_ASSERT(0);

    for (;;)
    {
        /* Toggle the user LED periodically */
        cyhal_system_delay_ms(LED_TOGGLE_INTERVAL_MS);
        cyhal_gpio_toggle(CYBSP_USER_LED);
    }

    return 0;
}




