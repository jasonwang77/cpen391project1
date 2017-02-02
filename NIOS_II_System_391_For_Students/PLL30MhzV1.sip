set_global_assignment -entity "PLL30MhzV1" -library "lib_PLL30MhzV1" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "PLL30MhzV1" -library "lib_PLL30MhzV1" -name IP_TOOL_VERSION "15.0"
set_global_assignment -entity "PLL30MhzV1" -library "lib_PLL30MhzV1" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_PLL30MhzV1" -name SPD_FILE [file join $::quartus(sip_path) "PLL30MhzV1.spd"]

set_global_assignment -library "lib_PLL30MhzV1" -name MISC_FILE [file join $::quartus(sip_path) "PLL30MhzV1_sim/PLL30MhzV1.vho"]
