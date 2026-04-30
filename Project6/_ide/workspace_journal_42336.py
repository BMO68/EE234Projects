# 2026-04-30T06:39:02.748977200
import vitis

client = vitis.create_client()
client.set_workspace(path="Project6")

component = client.get_component(name="part3")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project6\part3\src\lscript.ld")

lscript.regenerate()

comp = client.get_component(name="part1")
status = comp.clean()

lscript.regenerate()

comp = client.get_component(name="part3")
comp.build()

comp = client.clone_component(name="part3",new_name="part3copy")

client.delete_component(name="part3")

client.delete_component(name="componentName")

comp = client.get_component(name="part3copy")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "part3.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "part3.c", "spi.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["gtc_interrupt.c", "interrupt.c", "part3.c", "spi.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h", "spi.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h", "spi.h", "uart.h"])

comp = client.get_component(name="part3copy")
comp.build()

comp = client.create_app_component(name="part3",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

client.delete_component(name="part3copy")

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h", "spi.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "interrupt.h", "spi.h", "uart.h"])

comp = client.get_component(name="part3")
comp.build()

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h", "i2c.h"])

comp = client.get_component(name="part4")
comp.build()

comp.build()

comp = client.get_component(name="part3")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h", "interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h", "interrupt.h", "gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h", "interrupt.h", "gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["spi.h", "uart.h", "interrupt.h", "gtc_interrupt.h"])

comp = client.get_component(name="part3")
comp.build()

comp = client.get_component(name="part1")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["wrapper.h"])

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["i2c.h", "uart.h"])

comp = client.get_component(name="part4")
comp.build()

comp.build()

status = comp.clean()

component = client.get_component(name="part4")

lscript = component.get_ld_script(path="A:\WSU\EE_234\Projects\Project6\part4\src\lscript.ld")

lscript.regenerate()

comp.build()

comp.build()

lscript.regenerate()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_LINKER_SCRIPT", values = ["A:\WSU\EE_234\Projects\Project6\part4\src\lscript.ld"])

comp.set_app_config(key = "USER_LINKER_SCRIPT", values = ["A:\WSU\EE_234\Projects\Project6\part4\src\lscript.ld"])

comp = client.get_component(name="part4")
comp.build()

platform = client.get_component(name="platform6")
status = platform.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../../../blackboard.xsa")

lscript.regenerate()

comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_LINKER_SCRIPT", values = ["A:\WSU\EE_234\Projects\Project6\part4\src\lscript.ld"])

status = comp.import_files(from_loc="$COMPONENT_LOCATION/src", files=["i2c.c", "i2c.h", "part4.c", "uart.c", "uart.h"], dest_dir_in_cmp = "part4", is_skip_copy_sources = False)

status = platform.build()

comp = client.get_component(name="part4")
comp.build()

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["i2c.c", "part4.c", "uart.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part4.c", "uart.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["uart.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["A:/WSU/EE_234/Projects/Project6/part4/i2c.c", "A:/WSU/EE_234/Projects/Project6/part4/part4.c", "A:/WSU/EE_234/Projects/Project6/part4/uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = [""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["A:/WSU/EE_234/Projects/Project6/part4/i2c.h", "A:/WSU/EE_234/Projects/Project6/part4/uart.h"])

comp = client.get_component(name="part4")
comp.build()

comp = client.clone_component(name="part4",new_name="cgjcjj")

client.delete_component(name="part4")

comp = client.create_app_component(name="part4",platform = "$COMPONENT_LOCATION/../platform6/export/platform6/platform6.xpfm",domain = "standalone_ps7_cortexa9_0")

client.delete_component(name="cgjcjj")

comp = client.get_component(name="part4")
comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["uart.h", "i2c.h"])

comp = client.get_component(name="part4")
comp.build()

comp = client.clone_component(name="part4",new_name="part5")

comp = client.get_component(name="part5")
comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part5.c", "gtc_interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part5.c", "gtc_interrupt.c", "i2c.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part5.c", "gtc_interrupt.c", "i2c.c", "interrupt.c"])

comp.set_app_config(key = "USER_COMPILE_SOURCES", values = ["part5.c", "gtc_interrupt.c", "i2c.c", "interrupt.c", "uart.c"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h", "interrupt.h"])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h", "interrupt.h", ""])

comp.set_app_config(key = "USER_HEADER_SOURCES", values = ["gtc_interrupt.h", "i2c.h", "interrupt.h", "uart.h"])

comp = client.get_component(name="part5")
comp.build()

comp.build()

comp.build()

comp.build()

status = comp.clean()

comp.build()

comp.build()

comp.build()

vitis.dispose()

