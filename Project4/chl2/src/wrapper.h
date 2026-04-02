#include <stdio.h>
#include <stdlib.h>
#include <xsysmon.h>
#include <xadcps.h>
#include <xil_io.h>
#include <stdint.h>
#include <xsysmon_hw.h>


uint32_t read_xadc_voltage(void);

float convert_to_voltage(uint32_t adc_value);

void send_to_pc(float voltage);