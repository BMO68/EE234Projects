# 2026-04-14T16:44:22.266281600
import vitis

client = vitis.create_client()
client.set_workspace(path="Project5")

platform = client.get_component(name="platform5")
domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.regenerate()

domain = platform.get_domain(name="zynq_fsbl")

status = domain.set_config(option = "os", param = "standalone_xpm_support", value = "true")

status = domain.set_config(option = "os", param = "standalone_xpm_support", value = "false")

status = client.rescan_embedded_sw_repo()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa")

status = platform.build()

client.delete_component(name="platform5")

platform = client.create_platform_component(name = "platform5",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

status = platform.build()

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

