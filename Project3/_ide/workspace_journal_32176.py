# 2026-02-12T14:25:24.045047300
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.get_component(name="part1")
comp.build()

status = comp.clean()

comp.build()

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp = client.get_component(name="part2")
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

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["../source.c", "main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "main.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

