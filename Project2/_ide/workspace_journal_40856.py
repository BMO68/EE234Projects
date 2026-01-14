# 2026-01-12T00:50:46.349362500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

platform = client.create_platform_component(name = "platform2",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

comp = client.create_app_component(name="part1",platform = "$COMPONENT_LOCATION/../platform2/export/platform2/platform2.xpfm",domain = "standalone_ps7_cortexa9_0")

