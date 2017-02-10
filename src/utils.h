//
// Created by flx on 05.02.17.
//

#ifndef ACU_IMPL_UTILS_H
#define ACU_IMPL_UTILS_H

#include <chrono>
#include <string>

namespace beemaster {

    /// Checks, whether `needle` is part of `stack`.
    ///
    /// \param stack        The string to search in
    /// \param needle       The string to search for
    /// \param delimiter    Additional separator in the stack
    /// \return     True if found, false otherwise
    inline bool contains_string(const std::string stack, const std::string needle, const char delimiter) {
        return stack == needle
               || stack.find(needle + delimiter) == 0 //starts with
               || (int)stack.find(delimiter + needle) == std::max(0, (int)(stack.length() - needle.length() - 1)) //ends with
               || stack.find(delimiter + needle + delimiter) != std::string::npos;
    }

    /// \param ts   The timepoint to convert
    /// \return     The string representation of that point in time
    inline std::string time_to_string(const std::chrono::time_point<std::chrono::system_clock> ts) {
        auto value = std::chrono::duration_cast<std::chrono::milliseconds>(ts.time_since_epoch());
        return std::to_string(value.count());
    }

    /// Subtract value from a point in time and return that value as string
    ///
    /// \param ts       The timepoint to count from
    /// \param interval The number of minutes to subtract from ts
    /// \return     The newly changed time as string
    inline std::string decrement_minutes(const std::chrono::time_point<std::chrono::system_clock> ts,
                                  const uint64_t interval) {
        auto ts_inc = ts - std::chrono::minutes(interval);
        return time_to_string(ts_inc);
    }
}
#endif //ACU_IMPL_UTILS_H
