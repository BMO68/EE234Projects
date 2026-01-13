# 2025-12-27T01:47:05.524708300
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

platform = client.get_component(name="platform1")
status = platform.build()

comp = client.get_component(name="app1")
comp.build()

comp = client.get_component(name="app1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/app1/src/main.s"])

comp = client.get_component(name="app1")
comp.build()

comp.build()

comp = client.get_component(name="part2")
comp.build()

comp.build()

status = comp.clean()

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/part2/src/main.s"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

component = client.get_component(name="part2")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project1\part2\src\lscript.ld")

lscript.regenerate()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/part2/src/main.s"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

status = comp.clean()

status = comp.clean()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/part3/src/main.s"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.s"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["main.s"])

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform1/export/platform1/platform1.xpfm",domain = "standalone_ps7_cortexa9_0")

