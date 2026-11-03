#!/usr/bin/env python3
"""
decoy_pin_evaluator.py — Multi-Tier State Machine Simulation

Demonstrates an abstract state machine for multi-tier authentication
and alternative context modeling. Purely educational PoC; not intended
for production authentication.
"""

import sys
import time
import hmac
import hashlib
import secrets

class AbstractStateEngine:
    def __init__(self, primary_secret: str, secondary_secret: str, override_secret: str):
        self.salt = secrets.token_hex(16)
        self.primary_digest = self._derive_hash(primary_secret)
        self.secondary_digest = self._derive_hash(secondary_secret)
        self.override_digest = self._derive_hash(override_secret)

    def _derive_hash(self, secret: str) -> str:
        return hashlib.sha256((self.salt + secret).encode("utf-8")).hexdigest()

    def evaluate_token(self, candidate_token: str) -> dict:
        candidate_digest = self._derive_hash(candidate_token)

        # Unconditional evaluation of all digests to maintain constant operation count
        match_primary = hmac.compare_digest(candidate_digest, self.primary_digest)
        match_secondary = hmac.compare_digest(candidate_digest, self.secondary_digest)
        match_override = hmac.compare_digest(candidate_digest, self.override_digest)

        if match_primary:
            return {
                "result": "STATE_PRIMARY",
                "action": "Execute standard operational state"
            }
        elif match_secondary:
            return {
                "result": "STATE_ALTERNATIVE",
                "action": "Execute alternative operational state"
            }
        elif match_override:
            return {
                "result": "STATE_TERMINATED",
                "action": "Execute session termination state"
            }
        else:
            return {
                "result": "STATE_REJECTED",
                "action": "No operational transition"
            }

def main():
    print("==================================================================")
    print("  MULTI-TIER STATE MACHINE SIMULATOR")
    print("  Educational Reference Implementation")
    print("==================================================================\n")

    token_primary = secrets.token_hex(4)
    token_secondary = secrets.token_hex(4)
    token_override = secrets.token_hex(4)

    engine = AbstractStateEngine(token_primary, token_secondary, token_override)

    print("[*] Testing Primary Evaluation:")
    print("   ", engine.evaluate_token(token_primary))

    print("\n[*] Testing Alternative Context Evaluation:")
    print("   ", engine.evaluate_token(token_secondary))

    print("\n[*] Testing Override Evaluation:")
    print("   ", engine.evaluate_token(token_override))

    print("\n[*] Testing Unrecognized Token:")
    print("   ", engine.evaluate_token("invalid_sample"))

    print("\n[+] Demonstration completed cleanly.")

if __name__ == "__main__":
    main()
