/*
 * CS343 A6 MPRNG Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "PRNG.h"

_Monitor MPRNG : private PRNG {
    PRNG p;
  public:
    MPRNG(uint32_t s = 362436069) {
        // Initialize wrapped PRNG with s
        p(s);
    }
    void seed(uint32_t s) {
        p.seed(s);
    }
    uint32_t operator()() {
        return p();
    }
    uint32_t operator()(uint32_t u) {
        return p(u);
    }
    uint32_t operator()(uint32_t l, uint32_t u) {
        return p(l, u);
    }
};
