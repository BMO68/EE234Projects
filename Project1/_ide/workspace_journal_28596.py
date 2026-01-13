# 2026-01-02T05:25:58.799194500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.get_component(name="part4")
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

comp = client.create_app_component(name="part5",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/part5/src/main.s"])

comp = client.get_component(name="part5")
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

comp = client.create_app_component(name="chl1",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/chl1/src/main.s"])

comp = client.get_component(name="chl1")
comp.build()

comp.build()

comp = client.get_component(name="chl1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/chl1/src/main.s"])

comp = client.get_component(name="chl1")
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

comp.build()

comp = client.create_app_component(name="chl2",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl2")
status = comp.clean()

comp = client.get_component(name="chl2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/chl2/src/main.s"])

comp = client.get_component(name="chl2")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="chl3",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl3")
comp.build()

comp = client.get_component(name="chl3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/chl3/src/main.s"])

comp = client.get_component(name="chl3")
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

