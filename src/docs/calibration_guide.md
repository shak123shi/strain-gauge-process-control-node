# Calibration and Signal Conditioning Guide

## 1. Mathematical Calibration Model
The conversion factor transforms raw ADC counts into calibrated mass units (grams):

$$\text{Calibration Factor} = \frac{\text{Raw ADC}_{\text{Known Weight}} - \text{Raw ADC}_{\text{Tare}}}{\text{Known Weight (g)}}$$

### Example:
- Zero load reading: 0 counts
- 1000 g calibration test weight: -7,050,000 counts
- Calibration Factor = (-7,050,000 - 0) / 1000 = -7050.0

## 2. Multi-Layer Noise Mitigation Strategy
- **Hardware Layer:**
  - Differential lines (S+ and S-) use twisted-pair routing to maximize Common Mode Rejection Ratio (CMRR).
  - RC low-pass filtering on analog sensor outputs attenuates high-frequency EMI.
- **Software Layer:**
  - Moving-average filter (N = 5) suppresses high-frequency mechanical vibration.
  - Median filter discards transient outlier spikes caused by sudden mechanical shock.
