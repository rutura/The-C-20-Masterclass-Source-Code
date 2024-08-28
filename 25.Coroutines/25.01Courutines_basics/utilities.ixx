module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import coro_basics_01;
import coro_basics_02;
import coro_basics_03;
import coro_basics_04;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void coro_basics_01_demo(){

	auto task = coro_basics_01::do_work();

    // Resume
    task.m_handle();
    fmt::println("coro done: {}", task.m_handle.done());

    // Resume for second time
	/*
    task.m_handle.resume();
    fmt::println("coro done: {}", task.m_handle.done());

    // Resume for third time
    task.m_handle.resume();
    fmt::println("coro done: {}", task.m_handle.done());
	*/

    // Resuming after coroutine has run to completion : BAD!
    // fmt::println("------");
    // task.m_handle.resume();

    fmt::println("Done!");
}


export void coro_basics_02_demo(){

	auto task = coro_basics_02::do_work();

    fmt::println("");  // Prints a newline
    task.m_handle.resume(); // Resumes the coroutine. When next suspension point is hit it pauses
    fmt::println("value: {}", task.m_handle.promise().m_value);

    fmt::println("");  // Prints a newline
    task.m_handle.resume(); // Resumes the coroutine. When next suspension point is hit it pauses
    fmt::println("value: {}", task.m_handle.promise().m_value);

    fmt::println("");  // Prints a newline
    task.m_handle.resume(); // Resumes the coroutine. When next suspension point is hit it pauses
    fmt::println("value: {}", task.m_handle.promise().m_value);
    fmt::println("coro done: {}", task.m_handle.done());

    fmt::println("------");
    task.m_handle.resume();
    fmt::println("coro done: {}", task.m_handle.done());

    fmt::println("Done!");
}

export void coro_basics_03_demo(){

	auto task = coro_basics_03::do_work();

    task.m_handle(); // This resumes the coroutine. When next suspension point is hit it pauses
    fmt::println("value: {}", task.m_handle.promise().m_value);

    fmt::println("");
    task.m_handle(); // This resumes the coroutine. When next suspension point is hit it pauses
    fmt::println("value: {}", task.m_handle.promise().m_value);
    fmt::println("coro done: {}", task.m_handle.done());

    fmt::println("");
    task.m_handle();
    fmt::println("value: {}", task.m_handle.promise().m_value);
    fmt::println("coro done: {}", task.m_handle.done());

    fmt::println("");
    task.m_handle();
    fmt::println("value: {}", task.m_handle.promise().m_value);
    fmt::println("coro done: {}", task.m_handle.done());

    fmt::println("Done!");
}


export void coro_basics_04_demo(){

    /*
    auto task1 = coro_basics_04::generate_numbers();

    fmt::println("value: {}", task1());

    fmt::println("");
    fmt::println("value: {}", task1());

    fmt::println("");
    fmt::println("value: {}", task1());
    fmt::println("coro done: {}", task1.m_handle.done());

    fmt::println("");
    task1();
    fmt::println("coro done: {}", task1.m_handle.done());
    */

    /*
    auto task2 = coro_basics_04::infinite_number_stream();
    for (size_t i{};; ++i) {
        fmt::println("value: {}", task2());
    }
    */


    // Range 
    auto task3 = coro_basics_04::range(0, 25);
    for (size_t i{}; i < 26; ++i) {
        fmt::println("value[{}]: {}", i, task3());
    }

    fmt::println("Done!");
}