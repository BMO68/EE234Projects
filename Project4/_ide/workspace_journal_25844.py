# 2026-03-28T16:22:49.121264800
import vitis

client = vitis.create_client()
client.set_workspace(path="Project4")

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S", "UART.S"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["main.S", "UART.S"])

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S", "UART.S"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S", "UART.S"])

comp = client.get_component(name="part4")
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

comp.build()

comp.build()

comp = client.create_app_component(name="part5",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "UART.S"])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["main.h"])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp = client.create_app_component(name="part6",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp.build()

comp = client.get_component(name="part6")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["UART.c", "main.c"])

comp = client.get_component(name="part6")
comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part6")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part6")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

