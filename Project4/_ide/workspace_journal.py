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

