# 2026-01-13T09:23:11.822638300
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part1")
comp.build()

platform = client.get_component(name="platform2")
status = platform.build()

status = platform.build()

status = platform.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa")

status = platform.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project2/part1/src/main.S"])

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

vitis.dispose()

