# Precision Load-Sensing Process Control Node

An embedded industrial process control system engineered by reverse-engineering a commercial strain-gauge cantilever load cell. The system isolates microvolt analog signals, digitizes them via an external 24-bit Sigma-Delta ADC, and implements real-time threshold monitoring to drive 5V TTL hardware interlocks.

---

## Architecture Overview

Consumer digital scales typically encapsulate their microcontroller and ADC die in a proprietary Chip-on-Board (COB) epoxy package and drive the display using multiplexed AC signals, making direct logic extraction impractical. 

This project bypasses the original digital subsystem and connects directly to the 4-wire Wheatstone bridge:
1. **Sensor:** Cantilever aluminum load cell (4-gauge Wheatstone bridge).
2. **Analog Front-End:** 24-bit HX711 Sigma-Delta ADC with built-in programmable gain amplifier (128x gain).
3. **Controller:** Open embedded firmware processing dynamic taring, calibration scaling, and digital noise filtering.
4. **Output Stage:** 5V TTL active interlock signal and audible alarm triggered at programmable weight thresholds.

---

## Hardware Interface & Wiring

| Load Cell Wire | Signal Function | HX711 Pin | Description |
| :--- | :--- | :--- | :--- |
| **Red** | Excitation + ($E+$) | `E+` | Regulated DC excitation voltage |
| **Black** | Excitation - ($E-$) | `E-` | System ground reference |
| **White** | Differential Signal + ($S+$) | `A+` | Positive microvolt analog output |
| **Yellow** | Differential Signal - ($S-$) | `A-` | Negative microvolt analog output |

### Microcontroller Pin Mapping
- `HX711 DOUT` $\to$ Digital Pin 3
- `HX711 PD_SCK` $\to$ Digital Pin 2
- `5V TTL Interlock Out` $\to$ Digital Pin 8
- `Buzzer Alarm Out` $\to$ Digital Pin 9

---

## Technical Specifications & Performance

- **ADC Resolution:** 24-bit Sigma-Delta (~2.4 µV/count over ±20 mV full-scale input).
- **Measurement Accuracy:** ±2 g to ±5 g (0.1% to 0.25% full scale).
- **Repeatability:** Standard deviation < 3 g across 20 consecutive test cycles.
- **Update Throughput:** 10 SPS (standard mode) / 80 SPS (high-speed mode), yielding 2–16 Hz filtered loop speed.
- **Industrial Interlock:** Direct 5V TTL logic level compatible with solid-state relays, PLCs, and optical isolators.

---

## Repository Structure

- `src/main_library.ino`: Complete firmware implementation using the HX711 library with threshold control logic.
- `src/main_bitbang.ino`: Bare-metal 24-bit serial shift-register implementation without external library dependencies.
- `docs/calibration_guide.md`: Derivation of the calibration math and multi-layer noise mitigation pipeline.
