# 2026-01-16T09:00:38.377234200
import vitis

client = vitis.create_client()
client.set_workspace(path="Project2")

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["C:/WSU/EE234/EE234Projects/Project2/part1/src/main.S"])

comp = client.get_component(name="part1")
comp.build()

vitis.dispose()

