# Ghost-Pulse: Microarchitectural Reflex Protocol & Decoy PIN Engine

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Architecture: ARM64 / Silicon](https://img.shields.io/badge/Architecture-ARM64%20%2F%20Tensor-orange)](https://luminiaproductions.com)
[![Author: Rayaan](https://img.shields.io/badge/Architect-Rayaan-green)](https://github.com/Rayaan-AP)

A zero-syscall covert microarchitectural reflex protocol implementing **Decoy PIN plausible deniability** and **hardware-enforced cryptographic shredding** via CPU cache eviction timing across isolated user domains.

---

## 🛑 The Threat Model: Forensic Coercion & Sandbox Traps

Under physical duress or forensic seizure, operators face a critical dilemma:
1. **Refusal to Unlock**: Triggers legal contempt or physical escalation.
2. **Standard Unlocking**: Exposes sovereign master keys, private enclaves, and encrypted storage.
3. **Software IPC Pitfalls**: Traditional software duress signals (inter-process communication, sockets, broadcast intents) are easily intercepted, sandboxed, or frozen by the operating system kernel.

---

## ⚡ The Ghost-Pulse Architecture

Ghost-Pulse eliminates operating system IPC dependencies entirely by establishing a **microarchitectural covert timing channel** directly through shared CPU cache slices:

```
┌─────────────────────────────────────────────────────────────┐
│                 PHYSICAL APPLICATION PROCESSOR              │
├──────────────────────────────┬──────────────────────────────┤
│  User 10 (Commercial Decoy)  │   User 0 (Sovereign Core)    │
│  - Plausible Deniability     │   - Hardware Keystore        │
│  - Decoy PIN ('1234')        │   - Sentinel Watchdog        │
│  - Banking & Normal Apps     │   - Titan M2 StrongBox       │
├──────────────────────────────┴──────────────────────────────┤
│               SHARED L2 / SYSTEM-LEVEL CACHE (SLC)          │
│               [Covert Cache-Eviction Channel]               │
│        Thrashing (1) vs Yield (0) @ PMCCNTR_EL0 Timing       │
└─────────────────────────────────────────────────────────────┘
                               │ (Duress Pulse Detected: 0xDEAD)
                               ▼
               [Titan M2 Hardware Key Shredder]
                   (<20ms Physical Erasure)
```

### Key Technical Mechanisms:
1. **3-Tier PIN Verification Pad**:
   - **Master PIN**: Grants access to the primary Sovereign profile (User 0).
   - **Decoy PIN**: Instantly switches user context via `am switch-user` to an unprivileged, realistic secondary profile (User 10) containing ordinary consumer apps, providing genuine plausible deniability.
   - **Nuke PIN**: Triggers immediate irreversible hardware key zeroization.
2. **Zero-Syscall Microarchitectural Signaling**:
   - The decoy environment thrashes a 2MB aligned memory buffer to modulate cache line evictions.
   - The listening Sentinel daemon on Core 0 monitors memory access latency using cycle-accurate hardware counters (`PMCCNTR_EL0`).
   - If a duress heartbeat (`0xDEAD`) or a missing periodic pulse is detected, the hardware shred trigger executes in `<20ms`.

---

## 🔬 Running the Reference Simulator

```bash
python3 src/decoy_pin_evaluator.py
```

---

## 🔗 Live Sovereign Systems
* Luminia Sovereign Phone Architecture: [luminiaproductions.com/technology/](https://luminiaproductions.com/technology/)
* Hardware Catalog: [luminiaproductions.com/store/](https://luminiaproductions.com/store/)

---

## Author
**Rayaan**  
Founder & Principal Systems Architect at Luminia Sovereign Systems  
GitHub: [@Rayaan-AP](https://github.com/Rayaan-AP)
