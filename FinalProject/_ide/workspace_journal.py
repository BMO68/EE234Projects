# 2026-04-27T23:47:47.317322400
import vitis

client = vitis.create_client()
client.set_workspace(path="FinalProject")

platform = client.create_platform_component(name = "platformfinal",hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

comp = client.create_app_component(name="partfinal",platform = "$COMPONENT_LOCATION/../platformfinal/export/platformfinal/platformfinal.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="partfinal")
comp.build()

comp = client.get_component(name="partfinal")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="partfinal")
comp.build()

status = comp.clean()

comp = client.get_component(name="partfinal")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="partfinal")
comp.build()

platform = client.get_component(name="platformfinal")
status = platform.build()

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

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

