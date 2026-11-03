#define _POSIX_C_SOURCE 199309L

/**
 * @file ghost_pulse_timing.c
 * @brief Conceptual Timing Differential Simulator
 *
 * Demonstrates an abstract software model of timing-differential simulation
 * across modeled workloads using standard POSIX clocks.
 * Purely for research and educational modeling.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <inttypes.h>

typedef enum {
    MODE_BASELINE = 0,
    MODE_CONTEXT_A = 1,
    MODE_CONTEXT_B = 2
} simulation_mode_t;

#define LATENCY_ALERT_THRESHOLD_NS (5000ULL)

static bool sample_timestamp_ns(uint64_t *out_ns) {
    if (!out_ns) {
        return false;
    }
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return false;
    }
    *out_ns = ((uint64_t)ts.tv_sec * 1000000000ULL) + (uint64_t)ts.tv_nsec;
    return true;
}

bool run_abstract_workload(simulation_mode_t mode, uint64_t *out_elapsed_ns) {
    if (!out_elapsed_ns) {
        return false;
    }

    uint64_t start = 0, end = 0;
    if (!sample_timestamp_ns(&start)) {
        return false;
    }

    volatile uint64_t accum = 0;
    switch (mode) {
        case MODE_BASELINE:
            for (size_t i = 0; i < 500; i++) {
                accum += (i ^ 0x0F);
            }
            break;
        case MODE_CONTEXT_A:
            for (size_t i = 0; i < 25000; i++) {
                accum += (i ^ 0x33);
            }
            break;
        case MODE_CONTEXT_B:
            for (size_t i = 0; i < 50000; i++) {
                accum += (i ^ 0xAA);
            }
            break;
    }

    if (!sample_timestamp_ns(&end)) {
        return false;
    }

    (void)accum;
    *out_elapsed_ns = (end >= start) ? (end - start) : 0;
    return true;
}

const char* classify_latency(uint64_t elapsed_ns) {
    if (elapsed_ns < LATENCY_ALERT_THRESHOLD_NS) {
        return "BASELINE_PASS (Nominal execution signature)";
    }
    return "DIFFERENTIAL_TRIGGER (Context shift detected)";
}

int main(void) {
    printf("========================================================\n");
    printf("  CONCEPTUAL TIMING DIFFERENTIAL SIMULATOR\n");
    printf("  Educational Reference Model\n");
    printf("========================================================\n\n");

    int exit_status = EXIT_SUCCESS;
    uint64_t lat = 0;

    if (run_abstract_workload(MODE_BASELINE, &lat)) {
        printf("[1] Mode: BASELINE    | Latency: %" PRIu64 " ns | Classification: %s\n",
               lat, classify_latency(lat));
    } else {
        fprintf(stderr, "[1] Mode: BASELINE    | Error reading monotonic clock\n");
        exit_status = EXIT_FAILURE;
    }

    if (run_abstract_workload(MODE_CONTEXT_A, &lat)) {
        printf("[2] Mode: CONTEXT_A   | Latency: %" PRIu64 " ns | Classification: %s\n",
               lat, classify_latency(lat));
    } else {
        fprintf(stderr, "[2] Mode: CONTEXT_A   | Error reading monotonic clock\n");
        exit_status = EXIT_FAILURE;
    }

    if (run_abstract_workload(MODE_CONTEXT_B, &lat)) {
        printf("[3] Mode: CONTEXT_B   | Latency: %" PRIu64 " ns | Classification: %s\n",
               lat, classify_latency(lat));
    } else {
        fprintf(stderr, "[3] Mode: CONTEXT_B   | Error reading monotonic clock\n");
        exit_status = EXIT_FAILURE;
    }

    if (exit_status == EXIT_SUCCESS) {
        printf("\n[+] Simulation finished successfully. Zero hardware registers referenced.\n");
    } else {
        fprintf(stderr, "\n[-] Simulation encountered errors during clock acquisition.\n");
    }

    return exit_status;
}
