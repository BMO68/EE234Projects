# 2026-01-20T21:53:08.908190800
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/part3/src/main.S"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/part3/src/main.S"])

comp = client.get_component(name="part3")
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

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform2/export/platform2/platform2.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/part4/src/main.S"])

comp = client.get_component(name="part4")
comp.build()

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

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

