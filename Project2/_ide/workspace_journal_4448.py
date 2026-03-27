# 2026-01-29T09:43:03.466589700
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

<<<<<<< HEAD
=======
comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="chl1")
comp.build()

>>>>>>> 9e17625abe46840829ea30a6bf7a73a56a7ba036
vitis.dispose()

