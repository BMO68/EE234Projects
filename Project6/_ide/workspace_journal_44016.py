# 2026-04-30T04:13:09.805214
import vitis

client = vitis.create_client()
client.set_workspace(path="Project6")

comp = client.get_component(name="part1")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part2")
comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["spi.c", "uart.c", "part2.c"])

comp = client.get_component(name="part2")
comp.build()

comp.build()

status = comp.clean()

status = comp.clean()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

component = client.get_component(name="part2")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project6\part2\src\lscript.ld")

lscript.regenerate()

comp.build()

lscript.regenerate()

comp.build()

status = comp.clean()

comp.build()

status = comp.clean()

lscript.regenerate()

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_LINKER_SCRIPT", values = ["A:\WSU\EE_234\Projects\Project6\part2\src\lscript.ld"])

comp = client.get_component(name="part2")
comp.build()

lscript.regenerate()

comp.build()

comp = client.clone_component(name="part2",new_name="jkkjkl")

client.delete_component(name="part2")

comp = client.create_app_component(name="part2",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

client.delete_component(name="jkkjkl")

comp.build()

comp = client.get_component(name="part2")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["../part2.c", "uart.c", "spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["uart.c", "spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part2.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part2.c", "spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part2.c", "spi.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h", "spi.h"])

comp = client.get_component(name="part2")
comp.build()

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part3")
status = comp.import_files(from_loc="", files=["A:\WSU\EE_234\Projects\Project6\part2\src\part2.c", "A:\WSU\EE_234\Projects\Project6\part2\src\spi.c", "A:\WSU\EE_234\Projects\Project6\part2\src\spi.h", "A:\WSU\EE_234\Projects\Project6\part2\src\uart.c", "A:\WSU\EE_234\Projects\Project6\part2\src\uart.h"], is_skip_copy_sources = False)

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "spi.c", "part3.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "spi.c", "part3.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["interrupt.h", "spi.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["interrupt.h", "spi.h", "uart.h"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

status = comp.clean()

component = client.get_component(name="part3")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project6\part3\src\lscript.ld")

lscript.regenerate()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["interrupt.h", "spi.h", "uart.h", "gtc_interrupt.h"])

comp = client.get_component(name="part3")
comp.build()

comp.build()

comp.build()

comp.build()

lscript.regenerate()

lscript.regenerate()

comp.build()

comp.build()

vitis.dispose()

