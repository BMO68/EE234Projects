# 2026-04-30T07:25:23.547908400
import vitis

client = vitis.create_client()
client.set_workspace(path="Project6")

comp = client.get_component(name="part1")
comp.build()

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

comp = client.clone_component(name="part5",new_name="part5copy")

comp = client.get_component(name="part5copy")
comp.build()

client.delete_component(name="part5copy")

comp = client.get_component(name="part5")
comp.build()

comp.build()

component = client.get_component(name="part5")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project6\part5\src\lscript.ld")

lscript.regenerate()

comp.build()

comp.build()

comp.build()

platform = client.get_component(name="platform6")
domain = platform.get_domain(name="zynq_fsbl")

status = domain.regenerate()

comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h", "gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h", "gtc_interrupt.h", "interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h", "gtc_interrupt.h", "interrupt.h", "uart.h"])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_LINK_OTHER_FLAGS", values = ["arm-none-eabi-gcc -o part5.elf"])

comp = client.get_component(name="part5")
comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_LINK_OTHER_FLAGS", values = [" -o part5.elf"])

comp = client.get_component(name="part5")
comp.build()

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_LINK_OTHER_FLAGS", values = [""])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

comp.build()

lscript.regenerate()

comp.build()

comp = client.create_app_component(name="part5copy",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

client.delete_component(name="part5")

client.delete_component(name="componentName")

comp = client.get_component(name="part5copy")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "i2c.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "i2c.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "i2c.c", "interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "i2c.c", "interrupt.c", "part5.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "i2c.c", "interrupt.c", "part5.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h", "uart.h"])

comp = client.get_component(name="part5copy")
comp.build()

comp.build()

comp = client.get_component(name="part5copy")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h", "uart.h", "interrupt.h"])

comp = client.get_component(name="part5copy")
comp.build()

comp.build()

