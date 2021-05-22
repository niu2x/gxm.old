#ifndef GXM_COMMON_H
#define GXM_COMMON_H

#include <cstring>
#include <exception>
#include <iostream>

namespace gxm {
class exception : public std::exception {
public:
    exception(const char *message, const char *file, uint32_t line) {
        snprintf(
            message_, max_msg_len, "%s\nat: %s line: %d", message, file, line);
    }
    virtual ~exception() {}
    virtual const char *what() const noexcept override {
        return message_;
    }

private:
    enum { max_msg_len = 2048 };
    char message_[max_msg_len];
};

} // namespace gxm

#define GXM_THROW(message) throw exception((message), __FILE__, __LINE__)

#define GXM_ASSERT(condtion, message)                                          \
    if (!(condtion)) {                                                         \
        GXM_THROW(message);                                                    \
    }

#endif