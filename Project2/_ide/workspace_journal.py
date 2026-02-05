# 2026-01-29T09:43:03.466589700
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="chl1")
comp.build()

vitis.dispose()

