#ifndef INCLUDED_CORO_UNIQUE_GENERATOR_H
#define INCLUDED_CORO_UNIQUE_GENERATOR_H

// Original source:
// https://github.com/lewissbaker/llvm/blob/9f59dcce/coroutine_examples/manual_lifetime.hpp
// https://github.com/lewissbaker/llvm/blob/9f59dcce/coroutine_examples/generator.hpp

#if __has_include(<coroutine>)
#include <coroutine>
#else
#include <experimental/coroutine>
namespace std {
    using std::experimental::suspend_always;
    using std::experimental::suspend_never;
    using std::experimental::noop_coroutine;
    using std::experimental::coroutine_handle;
}
#endif // __has_include(<coroutine>)

#include <iterator>
#include <memory>
#include <utility>

#ifndef INCLUDED_CORO_MANUAL_LIFETIME_H
#define INCLUDED_CORO_MANUAL_LIFETIME_H

template<class T>
struct manual_lifetime {
public:
    manual_lifetime() noexcept {}
    ~manual_lifetime() noexcept {}

    template<class... Args>
    void construct(Args&&... args) {
        ::new (static_cast<void*>(std::addressof(value))) T(static_cast<Args&&>(args)...);
    }

    void destruct() noexcept {
        value.~T();
    }

    T& get() & { return value; }
    const T& get() const & { return value; }
    T&& get() && { return (T&&)value; }
    const T&& get() const && { return (const T&&)value; }

private:
  union { T value; };
};

template<class T>
struct manual_lifetime<T&> {
    manual_lifetime() noexcept = default;

    void construct(T& value) noexcept {
        ptr = std::addressof(value);
    }
    void destruct() noexcept {
        ptr = nullptr;
    }

    T& get() const noexcept { return *ptr; }

private:
    T *ptr = nullptr;
};

template<class T>
struct manual_lifetime<T&&> {
    manual_lifetime() noexcept = default;

    void construct(T&& value) noexcept {
        ptr = std::addressof(value);
    }
    void destruct() noexcept {
        ptr = nullptr;
    }

    T&& get() const noexcept { return *ptr; }

private:
    T *ptr = nullptr;
};

template<>
struct manual_lifetime<void> {
    void construct() noexcept {}
    void destruct() noexcept {}
    void get() const noexcept {}
};

#endif // INCLUDED_CORO_MANUAL_LIFETIME_H

template<class Ref, class Value = std::decay_t<Ref>>
class unique_generator {
public:
    class promise_type {
    public:
        promise_type() noexcept = default;

        ~promise_type() noexcept {
            clear_value();
        }

        void clear_value() {
            if (hasValue_) {
                hasValue_ = false;
                ref_.destruct();
            }
        }

        unique_generator get_return_object() noexcept {
            return unique_generator(
                std::coroutine_handle<promise_type>::from_promise(*this)
            );
        }

        auto initial_suspend() noexcept {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept {
            return std::suspend_always{};
        }

        auto yield_value(Ref ref)
            noexcept(std::is_nothrow_move_constructible_v<Ref>)
        {
            ref_.construct(std::move(ref));
            return std::suspend_always{};
        }

        void return_void() {}

        void unhandled_exception() {
            throw;
        }

        Ref get() {
            return ref_.get();
        }



    private:
        manual_lifetime<Ref> ref_;
        bool hasValue_ = false;
    };

    using handle_t = std::coroutine_handle<promise_type>;

    unique_generator(unique_generator&& g) noexcept :
        coro_(std::exchange(g.coro_, {}))
    {}

    ~unique_generator() {
        if (coro_) {
            coro_.destroy();
        }
    }

    struct sentinel {};

    class iterator {
    public:
        using reference = Ref;
        using value_type = Value;
        using difference_type = std::ptrdiff_t;
        using pointer = std::add_pointer_t<Ref>;
        using iterator_category = std::input_iterator_tag;

        iterator() noexcept {}

        explicit iterator(handle_t coro) noexcept :
            coro_(coro)
        {}

        reference operator*() const {
            return coro_.promise().get();
        }

        iterator& operator++() {
            coro_.promise().clear_value();
            coro_.resume();
            return *this;
        }

        void operator++(int) {
            coro_.promise().clear_value();
            coro_.resume();
        }

        friend bool operator==(const iterator& it, sentinel) noexcept { return it.coro_.done(); }
        friend bool operator==(sentinel, const iterator& it) noexcept { return it.coro_.done(); }
        friend bool operator!=(const iterator& it, sentinel) noexcept { return !it.coro_.done(); }
        friend bool operator!=(sentinel, const iterator& it) noexcept { return !it.coro_.done(); }

    private:
        handle_t coro_;
    };

    iterator begin() {
        coro_.resume();
        return iterator{coro_};
    }

    sentinel end() {
        return {};
    }

    auto operator()(){
        coro_.resume();
        return coro_.promise().get();
    }

private:

    explicit unique_generator(handle_t coro) noexcept :
        coro_(coro)
    {}

    handle_t coro_;
};

#endif // INCLUDED_CORO_UNIQUE_GENERATOR_H