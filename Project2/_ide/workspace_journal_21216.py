# 2026-01-13T10:17:26.663911100
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform2/export/platform2/platform2.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project2/part2/src/main.S"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp.build()

vitis.dispose()

