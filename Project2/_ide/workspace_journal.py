# 2026-01-28T20:49:52.675390900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

vitis.dispose()

comp = client.get_component(name="part1")
comp.build()

