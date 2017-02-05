//
// Created by flx on 05.02.17.
//

#ifndef ACU_IMPL_UTILS_H
#define ACU_IMPL_UTILS_H

namespace beemaster {

    bool contains_string(std::string stack, std::string needle, char delimiter) {
        return stack == needle
               || stack.find(needle + delimiter) == 0 //starts with
               || stack.find(delimiter + needle) == std::max(0, (int)(stack.length() - needle.length() -1)) //ends with
               || stack.find(delimiter + needle + delimiter) != std::string::npos;
    }
}
#endif //ACU_IMPL_UTILS_H
