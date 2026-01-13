# 2025-12-31T12:47:19.682300800
import vitis

client = vitis.create_client()
client.set_workspace(path="Project1")

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project1/part4/src/main.s"])

comp = client.get_component(name="part4")
comp.build()

