# 2026-01-29T10:15:29.322301
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

platform = client.create_platform_component(name = "platform3",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

vitis.dispose()

