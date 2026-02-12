# 2026-02-12T14:25:24.045047300
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.get_component(name="part1")
comp.build()

status = comp.clean()

comp.build()

comp = client.get_component(name="part2")
comp.build()

comp.build()

