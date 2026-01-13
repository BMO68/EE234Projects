# 2025-12-23T14:54:54.282191500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part3")
comp.build()

status = comp.clean()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Project1/part3/src/main.s"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

