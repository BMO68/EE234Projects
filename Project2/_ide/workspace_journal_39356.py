# 2026-01-28T20:49:52.675390900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

vitis.dispose()

comp = client.get_component(name="part1")
comp.build()

comp = client.get_component(name="part4")
status = comp.clean()

comp.build()

comp = client.get_component(name="part4")
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

comp = client.create_app_component(name="chl1",platform = "$COMPONENT_LOCATION/../platform2/export/platform2/platform2.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/chl1/src/main.S"])

comp = client.get_component(name="chl1")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="chl2",platform = "$COMPONENT_LOCATION/../platform2/export/platform2/platform2.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="chl2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/chl2/src/main.S"])

vitis.dispose()

