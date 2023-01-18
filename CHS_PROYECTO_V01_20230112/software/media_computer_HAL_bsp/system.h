/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: ../../nios_system.sopcinfo
 *
 * Generated: Wed Oct 19 10:47:29 CEST 2022
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x08900020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1d
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_PERIPHERAL_REGION_BASE 0x10000000
#define ALT_CPU_PERIPHERAL_REGION_PRESENT
#define ALT_CPU_PERIPHERAL_REGION_SIZE 0x00004000
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x08900020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1d
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_PERIPHERAL_REGION_BASE 0x10000000
#define NIOS2_PERIPHERAL_REGION_PRESENT
#define NIOS2_PERIPHERAL_REGION_SIZE 0x00004000
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_GENERIC_TRISTATE_CONTROLLER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_AUDIO
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG
#define __ALTERA_UP_AVALON_CHARACTER_LCD
#define __ALTERA_UP_AVALON_PARALLEL_PORT
#define __ALTERA_UP_AVALON_PS2
#define __ALTERA_UP_AVALON_RS232
#define __ALTERA_UP_AVALON_SRAM
#define __ALTERA_UP_AVALON_VIDEO_CHARACTER_BUFFER_WITH_DMA
#define __ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA
#define __ALTERA_UP_SD_CARD_AVALON_INTERFACE


/*
 * HEX3_HEX0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX3_HEX0 altera_up_avalon_parallel_port
#define HEX3_HEX0_BASE 0x10000020
#define HEX3_HEX0_IRQ -1
#define HEX3_HEX0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX3_HEX0_NAME "/dev/HEX3_HEX0"
#define HEX3_HEX0_SPAN 16
#define HEX3_HEX0_TYPE "altera_up_avalon_parallel_port"


/*
 * HEX7_HEX4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX7_HEX4 altera_up_avalon_parallel_port
#define HEX7_HEX4_BASE 0x10000030
#define HEX7_HEX4_IRQ -1
#define HEX7_HEX4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX7_HEX4_NAME "/dev/HEX7_HEX4"
#define HEX7_HEX4_SPAN 16
#define HEX7_HEX4_TYPE "altera_up_avalon_parallel_port"


/*
 * SD_Card configuration
 *
 */

#define ALT_MODULE_CLASS_SD_Card Altera_UP_SD_Card_Avalon_Interface
#define SD_CARD_BASE 0x10000400
#define SD_CARD_IRQ -1
#define SD_CARD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SD_CARD_NAME "/dev/SD_Card"
#define SD_CARD_SPAN 1024
#define SD_CARD_TYPE "Altera_UP_SD_Card_Avalon_Interface"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x10001000
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x10001000
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x10001000
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_system"


/*
 * audio configuration
 *
 */

#define ALT_MODULE_CLASS_audio altera_up_avalon_audio
#define AUDIO_BASE 0x10000110
#define AUDIO_IRQ 6
#define AUDIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_NAME "/dev/audio"
#define AUDIO_SPAN 16
#define AUDIO_TYPE "altera_up_avalon_audio"


/*
 * audio_config configuration
 *
 */

#define ALT_MODULE_CLASS_audio_config altera_up_avalon_audio_and_video_config
#define AUDIO_CONFIG_BASE 0x10000100
#define AUDIO_CONFIG_IRQ -1
#define AUDIO_CONFIG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AUDIO_CONFIG_NAME "/dev/audio_config"
#define AUDIO_CONFIG_SPAN 16
#define AUDIO_CONFIG_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * char_lcd configuration
 *
 */

#define ALT_MODULE_CLASS_char_lcd altera_up_avalon_character_lcd
#define CHAR_LCD_BASE 0x10000090
#define CHAR_LCD_IRQ -1
#define CHAR_LCD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHAR_LCD_NAME "/dev/char_lcd"
#define CHAR_LCD_SPAN 2
#define CHAR_LCD_TYPE "altera_up_avalon_character_lcd"


/*
 * flash_controller configuration
 *
 */

#define ALT_MODULE_CLASS_flash_controller altera_generic_tristate_controller
#define FLASH_CONTROLLER_BASE 0x8000000
#define FLASH_CONTROLLER_HOLD_VALUE 0
#define FLASH_CONTROLLER_IRQ -1
#define FLASH_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FLASH_CONTROLLER_NAME "/dev/flash_controller"
#define FLASH_CONTROLLER_SETUP_VALUE 0
#define FLASH_CONTROLLER_SIZE 8388608u
#define FLASH_CONTROLLER_SPAN 8388608
#define FLASH_CONTROLLER_TIMING_UNITS "ns"
#define FLASH_CONTROLLER_TYPE "altera_generic_tristate_controller"
#define FLASH_CONTROLLER_WAIT_VALUE 0


/*
 * green_leds configuration
 *
 */

#define ALT_MODULE_CLASS_green_leds altera_up_avalon_parallel_port
#define GREEN_LEDS_BASE 0x10000010
#define GREEN_LEDS_IRQ -1
#define GREEN_LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GREEN_LEDS_NAME "/dev/green_leds"
#define GREEN_LEDS_SPAN 16
#define GREEN_LEDS_TYPE "altera_up_avalon_parallel_port"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x10001000
#define JTAG_UART_IRQ 8
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * mtl_char_buffer_avalon_char_buffer_slave configuration
 *
 */

#define ALT_MODULE_CLASS_mtl_char_buffer_avalon_char_buffer_slave altera_up_avalon_video_character_buffer_with_dma
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE 0x10001800
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_IRQ -1
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_NAME "/dev/mtl_char_buffer_avalon_char_buffer_slave"
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_SPAN 2048
#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_TYPE "altera_up_avalon_video_character_buffer_with_dma"


/*
 * mtl_char_buffer_avalon_char_control_slave configuration
 *
 */

#define ALT_MODULE_CLASS_mtl_char_buffer_avalon_char_control_slave altera_up_avalon_video_character_buffer_with_dma
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_BASE 0x10001200
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_IRQ -1
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_NAME "/dev/mtl_char_buffer_avalon_char_control_slave"
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_SPAN 8
#define MTL_CHAR_BUFFER_AVALON_CHAR_CONTROL_SLAVE_TYPE "altera_up_avalon_video_character_buffer_with_dma"


/*
 * mtl_pixel_buffer_dma configuration
 *
 */

#define ALT_MODULE_CLASS_mtl_pixel_buffer_dma altera_up_avalon_video_pixel_buffer_dma
#define MTL_PIXEL_BUFFER_DMA_BASE 0x10001100
#define MTL_PIXEL_BUFFER_DMA_IRQ -1
#define MTL_PIXEL_BUFFER_DMA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MTL_PIXEL_BUFFER_DMA_NAME "/dev/mtl_pixel_buffer_dma"
#define MTL_PIXEL_BUFFER_DMA_SPAN 16
#define MTL_PIXEL_BUFFER_DMA_TYPE "altera_up_avalon_video_pixel_buffer_dma"


/*
 * onchip_memory configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory altera_avalon_onchip_memory2
#define ONCHIP_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY_BASE 0x8800000
#define ONCHIP_MEMORY_CONTENTS_INFO ""
#define ONCHIP_MEMORY_DUAL_PORT 0
#define ONCHIP_MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_INIT_CONTENTS_FILE "nios_system_onchip_memory"
#define ONCHIP_MEMORY_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY_IRQ -1
#define ONCHIP_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY_NAME "/dev/onchip_memory"
#define ONCHIP_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY_SIZE_VALUE 32768
#define ONCHIP_MEMORY_SPAN 32768
#define ONCHIP_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY_WRITABLE 1


/*
 * performance_counter configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_BASE 0x10001080
#define PERFORMANCE_COUNTER_HOW_MANY_SECTIONS 3
#define PERFORMANCE_COUNTER_IRQ -1
#define PERFORMANCE_COUNTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_NAME "/dev/performance_counter"
#define PERFORMANCE_COUNTER_SPAN 64
#define PERFORMANCE_COUNTER_TYPE "altera_avalon_performance_counter"


/*
 * ps2_key configuration
 *
 */

#define ALT_MODULE_CLASS_ps2_key altera_up_avalon_ps2
#define PS2_KEY_BASE 0x10000060
#define PS2_KEY_IRQ 7
#define PS2_KEY_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PS2_KEY_NAME "/dev/ps2_key"
#define PS2_KEY_SPAN 8
#define PS2_KEY_TYPE "altera_up_avalon_ps2"


/*
 * ps2_mouse configuration
 *
 */

#define ALT_MODULE_CLASS_ps2_mouse altera_up_avalon_ps2
#define PS2_MOUSE_BASE 0x10000070
#define PS2_MOUSE_IRQ 17
#define PS2_MOUSE_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PS2_MOUSE_NAME "/dev/ps2_mouse"
#define PS2_MOUSE_SPAN 8
#define PS2_MOUSE_TYPE "altera_up_avalon_ps2"


/*
 * pushbuttons configuration
 *
 */

#define ALT_MODULE_CLASS_pushbuttons altera_up_avalon_parallel_port
#define PUSHBUTTONS_BASE 0x10000050
#define PUSHBUTTONS_IRQ 1
#define PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PUSHBUTTONS_NAME "/dev/pushbuttons"
#define PUSHBUTTONS_SPAN 16
#define PUSHBUTTONS_TYPE "altera_up_avalon_parallel_port"


/*
 * red_leds configuration
 *
 */

#define ALT_MODULE_CLASS_red_leds altera_up_avalon_parallel_port
#define RED_LEDS_BASE 0x10000000
#define RED_LEDS_IRQ -1
#define RED_LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RED_LEDS_NAME "/dev/red_leds"
#define RED_LEDS_SPAN 16
#define RED_LEDS_TYPE "altera_up_avalon_parallel_port"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 200.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 32
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 1
#define SDRAM_SPAN 134217728
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * serial_port configuration
 *
 */

#define ALT_MODULE_CLASS_serial_port altera_up_avalon_rs232
#define SERIAL_PORT_BASE 0x10000080
#define SERIAL_PORT_IRQ 10
#define SERIAL_PORT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SERIAL_PORT_NAME "/dev/serial_port"
#define SERIAL_PORT_SPAN 8
#define SERIAL_PORT_TYPE "altera_up_avalon_rs232"


/*
 * sram configuration
 *
 */

#define ALT_MODULE_CLASS_sram altera_up_avalon_sram
#define SRAM_BASE 0x9000000
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/sram"
#define SRAM_SPAN 2097152
#define SRAM_TYPE "altera_up_avalon_sram"


/*
 * switches configuration
 *
 */

#define ALT_MODULE_CLASS_switches altera_up_avalon_parallel_port
#define SWITCHES_BASE 0x10000040
#define SWITCHES_IRQ 2
#define SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SWITCHES_NAME "/dev/switches"
#define SWITCHES_SPAN 16
#define SWITCHES_TYPE "altera_up_avalon_parallel_port"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x10001040
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1665761409
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x10001020
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000
#define TIMER_IRQ 0
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999
#define TIMER_MULT 0.001
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
