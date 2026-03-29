# 2026-03-26T16:56:34.040203200
import vitis

client = vitis.create_client()
client.set_workspace(path="Project4")

comp = client.get_component(name="part1")
comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S", "UART.S"])

comp = client.get_component(name="part1")
comp.build()

comp.build()

platform = client.get_component(name="platform4")
status = platform.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

vitis.dispose()

