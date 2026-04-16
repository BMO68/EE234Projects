#include "wrapper.h"

/* ========= ARM IRQ control ========= */
void disable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val |= 0x80U;                /* set I bit */
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val &= ~0x80U;               /* clear I bit */
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

/* ========= Xilinx IRQ table registration ========= */
void register_irq_handler(void (*handler)(void *))
{
    Xil_ExceptionRegisterHandler(5, (Xil_ExceptionHandler)handler, NULL);
}

/* ========= GIC helpers for interrupt ID 52 ========= */
static void disable_gic_distributor(void)
{
    ICDDCR = 0U;
}

static void enable_gic_distributor(void)
{
    ICDDCR = 1U;
}

static void drive_irq_from_gic(void)
{
    ICCICR = 0x3U;
}

static void set_gic_priority_mask(uint32_t priority)
{
    ICCPMR = (priority & 0xFFU);
}

static void disable_interrupt52(void)
{
    /* Interrupt 52: ICDISER/ICDICER index = 1, bit = 20
       Processor target byte is in ICDIPTR(13), first byte */
    ICDIPTR(13) &= ~0x000000FFU;
    ICDICER(1)   =  0x00100000U;
}

static void set_interrupt52_priority(uint8_t priority_val)
{
    ICDIPR(13) &= ~0x000000FFU;
    ICDIPR(13) |= ((uint32_t)(priority_val & 0xF8U));
}

static void set_interrupt52_sensitivity(uint8_t sens)
{
    /* Interrupt 52 uses ICDICFR(3), bits [9:8] */
    ICDICFR(3) &= ~0x00000300U;
    ICDICFR(3) |= (((uint32_t)sens & 0x3U) << 8);
}

static void enable_interrupt52(void)
{
    ICDIPTR(13) |= 0x00000001U;   /* target CPU0 */
    ICDISER(1)   = 0x00100000U;   /* enable ID 52 */
}

void configure_gic_gpio_interrupt(void)
{
    disable_gic_distributor();
    drive_irq_from_gic();
    set_gic_priority_mask(0xFFU);

    disable_interrupt52();
    set_interrupt52_priority(0xA0U);

    /* Reference example uses sensitivity setting 1 here */
    set_interrupt52_sensitivity(1U);

    enable_interrupt52();
    enable_gic_distributor();
}

/* ========= RGB LED helpers ========= */
void rgb_write(uint32_t val)
{
    val = (val & 0x7U) << 16;
    GPIO_DATA(RGB_BANK) = (GPIO_DATA(RGB_BANK) & ~RGB_MASK) | val;
}

void configure_rgb_led(void)
{
    GPIO_OEN(RGB_BANK) &= ~RGB_MASK;
    GPIO_DIRM(RGB_BANK) |= RGB_MASK;
    rgb_write(0x0U);
    GPIO_OEN(RGB_BANK) |= RGB_MASK;
}

void rgb_led_on(void)
{
    rgb_write(0x7U);
}

void rgb_led_off(void)
{
    rgb_write(0x0U);
}

/* ========= GPIO interrupt helpers ========= */
static void disable_gpio_interrupt(int bank, uint32_t mask)
{
    GPIO_INT_DIS(bank) = mask;
}

static void enable_gpio_interrupt(int bank, uint32_t mask)
{
    GPIO_INT_EN(bank) = mask;
}

static void set_gpio_int_edge_sens(int bank, uint32_t mask)
{
    GPIO_INT_TYPE(bank) |= mask;
}

static void set_gpio_int_pol_high(int bank, uint32_t mask)
{
    GPIO_INT_POL(bank) |= mask;
}

static void clear_gpio_int_any_edge(int bank, uint32_t mask)
{
    GPIO_INT_ANY(bank) &= ~mask;
}

uint32_t get_gpio_int_status(int bank, uint32_t mask)
{
    return GPIO_INT_STAT(bank) & mask;
}

void clear_gpio_int_status(int bank, uint32_t mask)
{
    GPIO_INT_STAT(bank) = mask;
}

void configure_button_interrupts(void)
{
    uint32_t both_buttons = BT4_MASK | BT5_MASK;

    /* mask button interrupts while configuring */
    disable_gpio_interrupt(BT4_BANK, both_buttons);

    /* rising edge: TYPE=1, POL=1, ANY=0 */
    set_gpio_int_edge_sens(BT4_BANK, both_buttons);
    set_gpio_int_pol_high(BT4_BANK, both_buttons);
    clear_gpio_int_any_edge(BT4_BANK, both_buttons);

    /* clear any stale flags before enabling */
    clear_gpio_int_status(BT4_BANK, both_buttons);

    /* enable button interrupts */
    enable_gpio_interrupt(BT4_BANK, both_buttons);
}