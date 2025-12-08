/**
 * @file gpio_definitions.h
 * @brief High-speed GPIO control definitions for ESP32.
 * @details This header provides direct memory access (MMIO) macros for
 * ultra-fast GPIO manipulation, bypassing the standard ESP-IDF driver overhead.
 * It supports atomic bit operations and parallel port writes.
 */
#include <stdint.h>

#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H

/**
 * @name Memory Map Base Addresses
 * @brief Base addresses for GPIO and IO MUX peripherals (Ref: ESP32 TRM).
 * @{
 */
#define DR_REG_GPIO_BASE 0x3FF44000	  ///< GPIO Controller Base Address
#define DR_REG_IO_MUX_BASE 0x3FF49000 ///< IO MUX Controller Base Address
/** @} */

/**
 * @name Pin Definitions
 * @brief GPIO Pin assignments based on hardware schematic.
 * @{
 */

/* Output Pins (Bank 0: GPIO 0~31) */
#define PIN_STATUS_LED 17 ///< System Status Indicator LED
#define PIN_CH1_LED 18	  ///< Channel 1 Status LED
#define PIN_CH2_LED 19	  ///< Channel 2 Status LED

/* Input Pins (Bank 0: GPIO 0~31) */
#define PIN_DEBUG_MODE 14	  ///< Debug Mode Switch (Active Low)
#define PIN_DRAIN_SENSOR_1 23 ///< CH1 Drain/Vibration Sensor
#define PIN_DRAIN_SENSOR_2 25 ///< CH2 Drain/Vibration Sensor
#define PIN_FLOW_SENSOR_1 27  ///< CH1 Flow Sensor (Pulse)
#define PIN_FLOW_SENSOR_2 26  ///< CH2 Flow Sensor (Pulse)

/* Input Pins (Bank 1: GPIO 32~39) - Input Only */
#define PIN_CH2_MODE 32	   ///< CH2 Mode Selector (Wash/Dry)
#define PIN_CH1_MODE 33	   ///< CH1 Mode Selector (Wash/Dry)
#define PIN_CT_SENSOR_2 34 ///< CH2 Current Sensor (ADC1_CH6)
#define PIN_CT_SENSOR_1 35 ///< CH1 Current Sensor (ADC1_CH7)
/** @} */

/**
 * @name Register Definitions (MMIO)
 * @brief Direct access pointers to hardware registers.
 * @note Accessing these pointers invokes direct load/store instructions to
 * hardware.
 * @{
 */

/* ---------------- Bank 0 (GPIO 0 ~ 31) ---------------- */

/**
 * @brief GPIO 0-31 Output Register.
 * @details Writing to this register affects all 32 pins simultaneously.
 * Useful for parallel port emulation.
 */
#define GPIO_OUT_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0004))

/**
 * @brief GPIO 0-31 Output Set Register (W1TS).
 * @details Writing 1 to a bit sets the corresponding pin High. Writing 0 has no
 * effect. Atomic operation.
 */
#define GPIO_OUT_W1TS_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0008))

/**
 * @brief GPIO 0-31 Output Clear Register (W1TC).
 * @details Writing 1 to a bit sets the corresponding pin Low. Writing 0 has no
 * effect. Atomic operation.
 */
#define GPIO_OUT_W1TC_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x000C))

/**
 * @brief GPIO 0-31 Output Enable Register.
 * @details Set bit to 1 for Output, 0 for Input (High-Z).
 */
#define GPIO_ENABLE_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0020))

/** @brief GPIO 0-31 Output Enable Set Register (W1TS). */
#define GPIO_ENABLE_W1TS_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0024))

/** @brief GPIO 0-31 Output Enable Clear Register (W1TC). */
#define GPIO_ENABLE_W1TC_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0028))

/** @brief GPIO 0-31 Input Value Register (Read-Only). */
#define GPIO_IN_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x003C))

/* ---------------- Bank 1 (GPIO 32 ~ 39) ---------------- */

/** @brief GPIO 32-39 Output Register. */
#define GPIO_OUT1_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0010))

/** @brief GPIO 32-39 Output Set Register (W1TS). */
#define GPIO_OUT1_W1TS_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0014))

/** @brief GPIO 32-39 Output Clear Register (W1TC). */
#define GPIO_OUT1_W1TC_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0018))

/** @brief GPIO 32-39 Output Enable Register. */
#define GPIO_ENABLE1_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x002C))

/** @brief GPIO 32-39 Output Enable Set Register (W1TS). */
#define GPIO_ENABLE1_W1TS_REG                                                  \
	(*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0030))

/** @brief GPIO 32-39 Output Enable Clear Register (W1TC). */
#define GPIO_ENABLE1_W1TC_REG                                                  \
	(*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0034))

/** @brief GPIO 32-39 Input Value Register (Read-Only). */
#define GPIO_IN1_REG (*(volatile uint32_t *)(DR_REG_GPIO_BASE + 0x0040))
/** @} */

/**
 * @name Ultra-Fast Macros
 * @brief Helper macros for optimized GPIO control.
 * @{
 */

/**
 * @brief Atomically sets a GPIO pin to High.
 * @param pin GPIO number (0-39).
 * @note Uses W1TS registers for atomic access.
 */
#define FAST_GPIO_SET(pin)                                                     \
	((pin < 32) ? (GPIO_OUT_W1TS_REG = (1UL << (pin)))                         \
				: (GPIO_OUT1_W1TS_REG = (1UL << ((pin) - 32))))

/**
 * @brief Atomically sets a GPIO pin to Low.
 * @param pin GPIO number (0-39).
 * @note Uses W1TC registers for atomic access.
 */
#define FAST_GPIO_CLEAR(pin)                                                   \
	((pin < 32) ? (GPIO_OUT_W1TC_REG = (1UL << (pin)))                         \
				: (GPIO_OUT1_W1TC_REG = (1UL << ((pin) - 32))))

/**
 * @brief Writes a value to the entire GPIO 0-31 port simultaneously.
 * @param val 32-bit value to write to GPIO_OUT_REG.
 * @warning This overwrites the state of ALL pins in Bank 0 (GPIO 0-31).
 */
#define FAST_GPIO_WRITE_ALL(val) (GPIO_OUT_REG = (val))

/**
 * @brief Reads the current input value of a GPIO pin.
 * @param pin GPIO number (0-39).
 * @return 1 if High, 0 if Low.
 */
#define FAST_GPIO_READ(pin)                                                    \
	((pin < 32) ? ((GPIO_IN_REG >> (pin)) & 1UL)                               \
				: ((GPIO_IN1_REG >> ((pin) - 32)) & 1UL))

/**
 * @brief Configures a pin as Output.
 * @param pin GPIO number (0-39).
 */
#define FAST_GPIO_OUTPUT_EN(pin)                                               \
	((pin < 32) ? (GPIO_ENABLE_W1TS_REG = (1UL << (pin)))                      \
				: (GPIO_ENABLE1_W1TS_REG = (1UL << ((pin) - 32))))

/**
 * @brief Configures a pin as Input (Disables Output).
 * @param pin GPIO number (0-39).
 */
#define FAST_GPIO_INPUT_EN(pin)                                                \
	((pin < 32) ? (GPIO_ENABLE_W1TC_REG = (1UL << (pin)))                      \
				: (GPIO_ENABLE1_W1TC_REG = (1UL << ((pin) - 32))))
/** @} */

#endif // GPIO_DEFINITIONS_H
