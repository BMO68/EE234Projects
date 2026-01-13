# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\diskio.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ff.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ffconf.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\sleep.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs_config.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilrsa.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xiltimer.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xtimer_config.h"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilffs.a"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilrsa.a"
  "A:\\WSU\\EE_234\\Projects\\Project1\\platform1\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxiltimer.a"
  )
endif()
