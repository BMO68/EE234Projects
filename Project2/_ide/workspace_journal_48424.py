# 2026-01-28T09:26:17.549314900
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

vitis.dispose()

