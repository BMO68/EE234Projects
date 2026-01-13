# 2025-12-22T16:33:08.378527800
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

platform = client.create_platform_component(name = "platform1",hw_design = "$COMPONENT_LOCATION/../../blackboard.xsa",os = "standalone",cpu = "ps7_cortexa9_0",domain_name = "standalone_ps7_cortexa9_0",compiler = "gcc")

platform = client.get_component(name="platform1")
status = platform.build()

domain = platform.get_domain(name="zynq_fsbl")

status = domain.regenerate()

domain = platform.get_domain(name="standalone_ps7_cortexa9_0")

status = domain.update_path(option = "OS",name="standalone", new_path = "A:/AMD/2025.2/Vitis/data/embeddedsw/lib/bsp/standalone_v9_4")

status = platform.build()

comp = client.create_app_component(name="app1",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="app1")
comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

component = client.get_component(name="app1")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Project1\app1\src\lscript.ld")

lscript.regenerate()

comp = client.get_component(name="app1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Project1/app1/src/main.s"])

comp = client.get_component(name="app1")
comp.build()

comp.build()

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Project1/part2/src/main.s"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

