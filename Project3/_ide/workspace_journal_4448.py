# 2026-03-12T11:44:00.143880900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project3")

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="chl3")
comp.build()

comp = client.get_component(name="chl4")
comp.build()

vitis.dispose()

