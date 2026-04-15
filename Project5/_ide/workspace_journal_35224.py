# 2026-04-12T20:02:36.383095700
import vitis

client = vitis.create_client()
client.set_workspace(path="Project5")

platform = client.get_component(name="platform5")
status = platform.build()

status = platform.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa")

status = platform.build()

