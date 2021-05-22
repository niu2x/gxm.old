#ifndef GXM_MAIN_INPUT_H
#define GXM_MAIN_INPUT_H

namespace gxm::main {

struct input {

    class event {
    public:
        enum event_type {
            close,
        };

        event(event_type t);
        event_type type() const noexcept {
            return type_;
        }

    private:
        event_type type_;
    };

    // class handler {
    // public:
    // 	handler() {}
    // 	virtual ~handler() {}
    // 	virtual void handle_input(const event &e) {}
    // };
};

}; // namespace gxm::main

#endif