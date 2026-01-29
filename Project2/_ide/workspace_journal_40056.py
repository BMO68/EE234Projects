# 2026-01-29T00:03:22.685481
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="chl1")
comp.build()

comp = client.get_component(name="chl2")
comp.build()

comp.build()

comp.build()

comp = client.get_component(name="chl2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project2/chl2/src/main.S"])

comp = client.get_component(name="chl2")
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

vitis.dispose()

