#include <iostream>
#include <coroutine>


struct CoroType {
    struct promise_type { 
        int m_value;
        CoroType get_return_object() { return CoroType(this); }    
        std::suspend_always initial_suspend() { return {}; }        
        std::suspend_always final_suspend() noexcept{ return {}; }
      
        void unhandled_exception() noexcept
        {
            std::rethrow_exception(std::current_exception());
        }
        std::suspend_always yield_value(int val) {
            m_value = val; 
            return {};
        }
       
    };
    CoroType(promise_type* p)
         : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    ~CoroType()
     {
         std::cout << "Handle destroyed..." << std::endl;
          m_handle.destroy();
     }
    std::coroutine_handle<promise_type>   m_handle;
};


CoroType do_work() {
    std::cout << "Starting the coroutine..." << std::endl;
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return;
}




int main(){

    auto task = do_work();

    std::cout << std::endl;
    task.m_handle.resume(); // This resumes the couroutine. When next suspension point is hit it pauses
    std::cout << "value : " << task.m_handle.promise().m_value << std::endl;

    std::cout << std::endl;
    task.m_handle.resume(); // This resumes the couroutine. When next suspension point is hit it pauses
    std::cout << "value : " << task.m_handle.promise().m_value << std::endl;

    std::cout << std::endl;
    task.m_handle.resume(); // This resumes the couroutine. When next suspension point is hit it pauses
    std::cout << std::boolalpha;
    std::cout << "value : " << task.m_handle.promise().m_value << std::endl;
    std::cout << "coro done : " << task.m_handle.done() << std::endl;


    std::cout << "------" << std::endl;
    task.m_handle.resume();
    std::cout << "coro done : " << task.m_handle.done() << std::endl;

    std::cout << "Done!" << std::endl;

    return 0;
}