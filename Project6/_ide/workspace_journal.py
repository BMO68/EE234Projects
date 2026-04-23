# 2026-04-22T19:38:18.689961900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project6")

platform = client.create_platform_component(name = "platform6",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

comp = client.create_app_component(name="part1",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

platform = client.get_component(name="platform6")
status = platform.build()

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "../source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "main.c"])

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

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

status = comp.clean()

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

