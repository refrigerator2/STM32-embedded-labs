# STM32L4 Laboratory Tasks & Embedded Systems Exercises

This repository contains a complete series of hands-on embedded systems exercises implemented on the **KAmeleon-STM32L4** evaluation board (featuring the **STM32L496ZGT6** microcontroller).

The tasks cover foundational low-level programming concepts ranging from basic GPIO control using HAL libraries to register-level (Bare-metal) drivers, hardware timers, UART communication, interrupt-driven FIFO buffers, and interactive CLI menus.

---

## 🛠 Hardware & Tools

* **Microcontroller:** STM32L496ZGT6 (ARM Cortex-M4)
* **Evaluation Board:** KAmeleon-STM32L4
* **IDE & Toolchain:** STM32CubeIDE / GCC ARM Embedded Toolchain
* **Peripherals Used:** GPIO (LEDs, RGB LED, 5-position Joystick), 4-digit 7-Segment Display, TIM6 Basic Timer, LPUART1
* **Architecture:** 
  * Tasks 1–3: High-Level Abstraction via **STM32 HAL Library**
  * Tasks 4–8: Low-Level **Bare-Metal Programming** (Direct Register Manipulation via pointers and custom structs, no HAL)

---

## 📋 Summary of Tasks

### [Task 1: LED Diodes (HAL)](./task-01-led-diodes)
* **Objective:** Introduction to STM32CubeIDE, pin configuration, and GPIO output control.
* **Key Features:**
  * Implemented a "moving LED" algorithm across 8 board LEDs (`D1`–`D8`).
  * Support for configurable speed (`#define` macro directives) and direction bouncing/wrapping.
  * Encapsulated GPIO logic with zero magic numbers in code.

---

### [Task 2: RGB LED & Joystick (HAL)](./task-02-rgb-joystick)
* **Objective:** Simultaneous handling of GPIO outputs and input button polling.
* **Key Features:**
  * Concurrent execution of the Task 1 LED sequence and real-time Joystick state polling.
  * RGB LED control driven by joystick directions (Left, Right, Down $\rightarrow$ R, G, B; Center $\rightarrow$ All ON).
  * Non-blocking delay architecture guaranteeing responsive input checking without visible latency.

---

### [Task 3: 7-Segment Display (HAL)](./task-03-7-segment-display)
* **Objective:** Single-digit 7-segment display control and input-driven state machines.
* **Key Features:**
  * Up/Down counter (0–9) updating at 1-second intervals.
  * Direction dynamically toggled via Joystick `OK` button without affecting counting frequency.
  * Runtime digit switching (position selection) using Joystick `Left`/`Right` controls.

---

### [Task 4: 0–9999 Counter (Bare-metal)](./task-04-counter-0-9999)
* **Objective:** Direct register access (pointers/offsets) without using the STM32 HAL library.
* **Key Features:**
  * 4-digit multiplexed 7-segment display driver powering a full 0–9999 Up/Down counter.
  * Custom software delay loop accepting parameters in milliseconds.
  * Multiplexing loop tuned for flicker-free display rendering alongside non-blocking input sampling.

---

### [Task 5: TIM6 Basic Timer (Bare-metal)](./task-05-timer-tim6)
* **Objective:** Hardware timer configuration and precise timekeeping.
* **Key Features:**
  * Custom C structures mapping memory addresses for GPIO and `TIM6` peripheral registers.
  * Hardware-assisted millisecond delay function based on the `TIM6` counter, eliminating execution drift caused by CPU load.
  * Enhanced 0–9999 counter maintaining strict 1.0-second timing precision.

---

### [Task 6: LPUART Communication (Bare-metal)](./task-06-lpuart)
* **Objective:** Asynchronous serial communication via LPUART1 driver built from scratch.
* **Key Features:**
  * Register-mapped driver supporting `LPUART_init()`, `SendChar()`, `ReceiveChar()`, and `SendString()`.
  * Serial configuration: `115200 8N1`.
  * Boot banner transmission, ASCII alphabet streaming, and an echo loop converting incoming lowercase characters to uppercase in real-time.

---

### [Task 7: FIFO Buffer & Interrupts (Bare-metal)](./task-07-fifo-buffer)
* **Objective:** Asynchronous interrupt-driven I/O paired with a circular queue data structure.
* **Key Features:**
  * Thread-safe Ring/FIFO Buffer implementation (`fifo_put`, `fifo_get`, `is_empty`, `is_full`).
  * LPUART RX interrupt handler pushing incoming digits into the FIFO and sending terminal feedback (`echo`, `x` on full overflow, `.` on non-digit characters).
  * Main loop popping queued digits to update the 7-segment display at 1-second intervals.

---

### [Task 8: Hierarchical CLI Menu (Bare-metal)](./task-08-menu-system)
* **Objective:** Interactive command-line interface over serial terminal integrating all previously developed drivers.
* **Key Features:**
  * Cascading console menu system (`Top level`, `LED`, `7LED`, `Joy`, `LPUART`).
  * System command parser:
    * `LED>`: `Set`, `Clear`, `Blink`, `Status`, `Toggle` for LEDs `0–7` and `RGB`.
    * `7LED>`: `Display <val>` (0–9999) and `Read`.
    * `Joy>`: `Read <L,R,U,D,C,ALL>` joystick button states.
    * `LPUART>`: `Status` calculating real-time Baudrate and line parameters directly from hardware register states.

---

## 🛠 Project Structure

```text
.
├── task-01-led-diodes/       # Task 1: Moving LED pattern (HAL)
├── task-02-rgb-joystick/     # Task 2: RGB & Joystick polling (HAL)
├── task-03-7-segment-display/# Task 3: 1-digit counter (HAL)
├── task-04-counter-0-9999/   # Task 4: 4-digit multiplexed counter (Bare-metal)
├── task-05-timer-tim6/       # Task 5: TIM6 precise delay driver (Bare-metal)
├── task-06-lpuart/           # Task 6: LPUART driver & ASCII stream (Bare-metal)
├── task-07-fifo-buffer/      # Task 7: LPUART RX Interrupts + Circular FIFO (Bare-metal)
└── task-08-menu-system/      # Task 8: Interactive Cascading CLI (Bare-metal)
