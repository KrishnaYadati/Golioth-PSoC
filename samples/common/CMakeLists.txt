zephyr_library_sources_ifdef(CONFIG_GOLIOTH_SAMPLES_COMMON net_connect.c)
zephyr_library_sources_ifdef(CONFIG_GOLIOTH_SAMPLE_NRF91_LTE_MONITOR nrf91_lte_monitor.c)
zephyr_library_sources_ifdef(CONFIG_GOLIOTH_SAMPLE_SETTINGS_AUTOLOAD settings_autoload.c)
zephyr_library_sources_ifdef(CONFIG_GOLIOTH_SAMPLE_SETTINGS_SHELL settings_shell.c)
zephyr_library_sources_ifdef(CONFIG_GOLIOTH_SAMPLE_WIFI wifi.c)

zephyr_include_directories(include)
