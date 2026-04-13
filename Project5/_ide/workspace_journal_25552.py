# 2026-04-07T09:38:35.872938500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project5")

platform = client.create_platform_component(name = "platform5",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

comp = client.create_app_component(name="part1",platform = "$COMPONENT_LOCATION/../platform5/export/platform5/platform5.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

vitis.dispose()

