//
// Created by Kirill Zhukov on 22.09.2023.
//

#include "DurationCounter.h"

uint64_t BasicDurationCounter::finishManually() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
}
