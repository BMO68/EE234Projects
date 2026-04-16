# 2026-04-16T06:42:02.424702900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project5")

comp = client.get_component(name="part1")
comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform5/export/platform5/platform5.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["soure.c", "wrapper.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "wrapper.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "wrapper.h", "main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "main.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform5/export/platform5/platform5.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part3")
comp.build()

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform5/export/platform5/platform5.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part4")
comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

