<<<<<<< HEAD
# 2026-01-22T09:25:40.707830200
=======
# 2026-01-21T20:42:58.867378200
>>>>>>> c08ab5e82ed0c62da43b13c467665e75ac67c012
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.get_component(name="app1")
comp.build()

comp = client.get_component(name="part2")
comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project1/part2/.gitignore"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project1/part2/src/main.s"])

comp = client.get_component(name="part2")
comp.build()

component = client.get_component(name="part2")

lscript = component.get_ld_script(path="C:\WSU\EE234\EE234Projects\Project1\part2\src\lscript.ld")

lscript.regenerate()

status = comp.clean()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project1/part3/src/main.s"])

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project1/part4/src/main.s"])

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part5")
comp.build()

comp = client.get_component(name="chl1")
comp.build()

comp = client.get_component(name="chl2")
comp.build()

comp = client.get_component(name="chl3")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

