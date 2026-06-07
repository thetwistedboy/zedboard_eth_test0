# 2026-06-04T20:45:23.786986473
import vitis

client = vitis.create_client()
client.set_workspace(path="software")

platform = client.create_platform_component(name = "platform",hw_design = "$COMPONENT_LOCATION/../../hardware/design_1_wrapper.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

platform = client.get_component(name="platform")
domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.set_lib(lib_name="lwip220", path="/opt/Xilinx/2025.2/Vitis/data/embeddedsw/ThirdParty/sw_services/lwip220_v1_3")

status = platform.build()

comp = client.create_app_component(name="eth_test0",platform = "$COMPONENT_LOCATION/../platform/export/platform/platform.xpfm",domain = "standalone_ps7_cortexa9_0")

status = domain.set_config(option = "lib", param = "lwip220_no_sys_no_timers", value = "false", lib_name="lwip220")

status = platform.build()

component = client.get_component(name="eth_test0")

lscript = component.get_ld_script(path="/home/jkelley/Documents/Xilinx/zedboard_eth_test0/software/eth_test0/src/lscript.ld")

lscript.regenerate()

comp = client.get_component(name="eth_test0")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_dhcp", value = "true", lib_name="lwip220")

status = platform.build()

status = domain.set_config(option = "lib", param = "lwip220_lwip_dhcp_does_acd_check", value = "true", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "lwip220_pbuf_pool_bufsize", value = "2048", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "lwip220_pbuf_pool_bufsize", value = "1700", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "lwip220_pbuf_pool_size", value = "2048", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "XILTIMER_en_interval_timer", value = "true", lib_name="xiltimer")

status = platform.build()

lscript.regenerate()

comp.build()

comp = client.create_app_component(name="lwip_echo_server",platform = "$COMPONENT_LOCATION/../platform/export/platform/platform.xpfm",domain = "standalone_ps7_cortexa9_0",template = "lwip_echo_server")

component = client.get_component(name="lwip_echo_server")

lscript = component.get_ld_script(path="/home/jkelley/Documents/Xilinx/zedboard_eth_test0/software/lwip_echo_server/src/lscript.ld")

lscript.regenerate()

comp = client.get_component(name="lwip_echo_server")
comp.build()

comp.build()

status = comp.clean()

comp.build()

status = platform.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="eth_test0")
comp.build()

status = domain.set_config(option = "lib", param = "lwip220_dhcp", value = "false", lib_name="lwip220")

status = platform.build()

status = domain.set_config(option = "lib", param = "lwip220_lwip_dhcp_does_acd_check", value = "false", lib_name="lwip220")

status = platform.build()

component = client.get_component(name="eth_test0")

lscript = component.get_ld_script(path="/home/jkelley/Documents/Xilinx/zedboard_eth_test0/software/eth_test0/src/lscript.ld")

lscript.regenerate()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_temac_phy_link_speed", value = "CONFIG_LINKSPEED1000", lib_name="lwip220")

comp.build()

status = platform.build()

comp.build()

comp.build()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_temac_phy_link_speed", value = "CONFIG_LINKSPEED_AUTODETECT", lib_name="lwip220")

status = platform.build()

lscript.regenerate()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_ip_debug", value = "true", lib_name="lwip220")

comp.build()

comp.build()

status = platform.build()

comp.build()

status = domain.set_config(option = "lib", param = "lwip220_debug", value = "true", lib_name="lwip220")

status = platform.build()

comp.build()

vitis.dispose()

