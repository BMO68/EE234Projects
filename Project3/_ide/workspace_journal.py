# 2026-02-18T20:52:15.944504100
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.get_component(name="part3")
comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

