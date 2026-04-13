# 2026-04-01T23:43:07.677456500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project4")

comp = client.create_app_component(name="chl1",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="chl1")
comp.build()

comp = client.get_component(name="part1")
comp.build()

platform = client.get_component(name="platform4")
status = platform.build()

comp.build()

comp = client.get_component(name="part2")
comp.build()

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part5")
comp.build()

comp = client.get_component(name="part6")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="chl1")
comp.build()

comp = client.create_app_component(name="chl2",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

comp.build()

comp = client.get_component(name="chl2")
comp.build()

comp.build()

vitis.dispose()

