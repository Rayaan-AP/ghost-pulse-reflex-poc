# Ghost-Pulse: Conceptual Multi-Tier State Machine & Timing Simulator

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A conceptual reference model demonstrating **multi-tier state evaluation** and **timing-differential simulation** in software.

---

## 📌 Overview

This repository provides educational simulations illustrating abstract state-switching logic and workload-induced latency observation:
1. **Multi-Tier State Machine**: Models deterministic state transitions across primary, alternative, and termination states.
2. **Timing Differential Simulation**: Models observable latency differences across distinct software workloads.

---

## 🔬 Running the Simulators

### 1. Multi-Tier State Machine Simulator (Python)
Evaluates candidate tokens against simulated operational states:

```bash
python3 src/decoy_pin_evaluator.py
```

### 2. Timing Differential Simulator (C)
Simulates workload latency classification using POSIX monotonic timing:

```bash
gcc -Wall -Wextra -pedantic -std=c11 -O2 src/ghost_pulse_timing.c -o ghost_pulse_sim
./ghost_pulse_sim
```

---

## ⚠️ Scope & Disclaimer

This project is a high-level educational reference model intended for software research and demonstration purposes. It is not intended for production authentication or hardware deployment.
