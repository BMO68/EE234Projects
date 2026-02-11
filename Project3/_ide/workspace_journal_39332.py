# 2026-02-04T18:36:45.388829600
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.create_app_component(name="part1",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project3/part1/src/wrapper.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "main.c", "../source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["../../common/src/wrapper.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["../../common/src/source.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["../../common/src/source.c", "../../common/src/main.c"])

comp = client.get_component(name="part1")
status = comp.clean()

comp.build()

platform = client.get_component(name="platform3")
status = platform.build()

comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project3/part1/src/source.c", "../../common/src/main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["source.c", "C:/WSU/EE234/EE234Projects/Project3/part1/src/main.c"])

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project3/part1/src/wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project3/part1/src/wrapper.h"])

vitis.dispose()

