# 2026-04-01T23:43:07.677456500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project4")

comp = client.create_app_component(name="chl1",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="chl1")
comp.build()

