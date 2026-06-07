# 2026-06-06T12:12:20.984022465
import vitis

client = vitis.create_client()
client.set_workspace(path="software")

platform = client.get_component(name="platform")
domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.set_config(option = "lib", param = "lwip220_debug", value = "false", lib_name="lwip220")

status = domain.set_config(option = "lib", param = "lwip220_debug_options", value = "false", lib_name="lwip220")

status = platform.build()

comp = client.get_component(name="eth_test0")
comp.build()

vitis.dispose()

