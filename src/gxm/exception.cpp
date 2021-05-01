#include "exception.h"

#include <string.h>

namespace gxm {

exception::exception(const char *message) {
    strncpy(message_, message, max_message_len_);
}

exception::~exception() {}

} // namespace gxm