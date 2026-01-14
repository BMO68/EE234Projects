# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\diskio.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ff.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\ffconf.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\sleep.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilffs_config.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xilrsa.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xiltimer.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\include\\xtimer_config.h"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilffs.a"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxilrsa.a"
  "C:\\WSU\\EE234\\EE234Projects\\Project2\\platform2\\zynq_fsbl\\zynq_fsbl_bsp\\lib\\libxiltimer.a"
  )
endif()
