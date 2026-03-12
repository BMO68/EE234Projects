# 2026-03-12T01:51:21.330628700
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h", "TTC.h"])

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h", "TTC.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC.c"])

comp = client.get_component(name="part4")
comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

status = comp.clean()

comp.build()

status = comp.clean()

comp.build()

comp = client.create_app_component(name="chl4",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.create_app_component(name="chl3",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["TTC.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["TTC.h", "wrapper.h"])

comp = client.get_component(name="chl3")
comp.build()

comp.build()

comp = client.get_component(name="chl4")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="chl4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC."])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.c", "TTC.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h", "TTC.h"])

comp = client.get_component(name="chl4")
comp.build()

