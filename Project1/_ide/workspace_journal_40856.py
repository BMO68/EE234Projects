# 2026-01-13T08:06:02.015963800
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.get_component(name="app1")
comp.build()

component = client.get_component(name="app1")

lscript = component.get_ld_script(path="C:\WSU\EE234\EE234Projects\Project1\app1\src\lscript.ld")

lscript.regenerate()

platform = client.get_component(name="platform1")
status = platform.build()

comp.build()

vitis.dispose()

