# 2026-01-15T12:33:01.407187500
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part2")
comp.build()

