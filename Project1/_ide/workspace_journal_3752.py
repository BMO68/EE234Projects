# 2026-01-08T02:24:05.475579100
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.get_component(name="chl3")
comp.build()

comp.build()

