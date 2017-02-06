//
// Created by flx on 05.02.17.
//

#ifndef ACU_IMPL_UTILS_H
#define ACU_IMPL_UTILS_H

namespace beemaster {

    inline bool contains_string(std::string stack, std::string needle, char delimiter) {
        return stack == needle
               || stack.find(needle + delimiter) == 0 //starts with
               || stack.find(delimiter + needle) == std::max((size_t)0, (stack.length() - needle.length() - 1)) //ends with
               || stack.find(delimiter + needle + delimiter) != std::string::npos;
    }

    inline std::string time_to_string(const std::chrono::time_point<std::chrono::system_clock> ts) {
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(ts.time_since_epoch());
        return std::to_string(value.count());
    }

    inline std::string decrement_minutes(const std::chrono::time_point<std::chrono::system_clock> ts,
                                  uint16_t interval) {
        auto ts_inc = ts - std::chrono::minutes(interval);
        return time_to_string(ts_inc);
    }
}
#endif //ACU_IMPL_UTILS_H
