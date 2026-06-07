# 2026-06-06T12:16:07.398882644
import vitis

client = vitis.create_client()
client.set_workspace(path="software")

comp = client.get_component(name="eth_test0")
comp.build()

platform = client.get_component(name="platform")
domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.set_config(option = "lib", param = "XILTIMER_tick_timer", value = "ps7_scutimer_0", lib_name="xiltimer")

status = domain.set_config(option = "lib", param = "XILTIMER_en_interval_timer", value = "false", lib_name="xiltimer")

status = platform.build()

status = domain.set_config(option = "lib", param = "lwip220_dhcp", value = "true", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "lwip220_lwip_dhcp_does_acd_check", value = "true", lib_name="lwip220")

status = platform.build()

status = domain.set_config(option = "lib", param = "lwip220_temac_phy_link_speed", value = "CONFIG_LINKSPEED1000", lib_name="lwip220")

status = platform.build()

comp.build()

comp.build()

status = domain.set_config(option = "lib", param = "XILTIMER_en_interval_timer", value = "true", lib_name="xiltimer")

status = domain.set_config(option = "lib", param = "XILTIMER_tick_timer", value = "ps7_ttc_0", lib_name="xiltimer")

status = domain.set_config(option = "lib", param = "XILTIMER_en_interval_timer", value = "false", lib_name="xiltimer")

comp.build()

status = platform.build()

component = client.get_component(name="eth_test0")

lscript = component.get_ld_script(path="/home/jkelley/Documents/Xilinx/zedboard_eth_test0/software/eth_test0/src/lscript.ld")

lscript.regenerate()

comp.build()

status = domain.set_config(option = "lib", param = "XILTIMER_tick_timer", value = "ps7_scutimer_0", lib_name="xiltimer")

status = platform.build()

status = domain.set_config(option = "lib", param = "lwip220_no_sys_no_timers", value = "true", lib_name="lwip220")

status = platform.build()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_no_sys_no_timers", value = "false", lib_name="lwip220")

comp.build()

status = platform.build()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_dhcp_debug", value = "true", lib_name="lwip220")

status = platform.build()

comp.build()

comp.build()

domain = platform.get_domain(name="zynq_fsbl")

status = domain.set_config(option = "lib", param = "XILTIMER_tick_timer", value = "ps7_scutimer_0", lib_name="xiltimer")

domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.set_config(option = "lib", param = "lwip220_temac_phy_link_speed", value = "CONFIG_LINKSPEED_AUTODETECT", lib_name="lwip220")

status = platform.build()

comp.build()

comp = client.get_component(name="lwip_echo_server")
comp.build()

comp = client.get_component(name="eth_test0")
comp.build()

comp.build()

status = platform.build()

comp.build()

comp.build()

comp.build()

status = platform.build()

lscript.regenerate()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

lscript.regenerate()

comp.build()

