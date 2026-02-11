# 2026-02-10T19:18:52.295773100
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

platform = client.get_component(name="platform3")
status = platform.build()

comp = client.get_component(name="part1")
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

