# 2026-02-10T19:18:52.295773100
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

platform = client.get_component(name="platform3")
status = platform.build()

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

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform3/export/platform3/platform3.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

