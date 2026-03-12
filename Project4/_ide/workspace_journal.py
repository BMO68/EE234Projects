# 2026-03-12T02:56:17.974586
import vitis

client = vitis.create_client()
client.set_workspace(path="Project4")

platform = client.create_platform_component(name = "platform4",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

platform = client.create_platform_component(name = "platform4",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

comp = client.create_app_component(name="part1",platform = "$COMPONENT_LOCATION/../platform4/export/platform4/platform4.xpfm",domain = "standalone_ps7_cortexa9_0")

