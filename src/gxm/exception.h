#include <exception>

namespace gxm {

class exception : public std::exception {
public:
    exception(const char *message = "");
    virtual ~exception();
    virtual const char *what() const noexcept {
        return message_;
    }

private:
    static constexpr size_t max_message_len_ = 64;
    char                    message_[max_message_len_];
};

} // namespace gxm