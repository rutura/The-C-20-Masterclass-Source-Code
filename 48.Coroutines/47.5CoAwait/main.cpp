#include <fmt/format.h>
#include <coroutine>


struct CoroType {
    struct promise_type { 
        CoroType get_return_object() { return CoroType(this); }    
        std::suspend_always initial_suspend() { return {}; }        
        std::suspend_always final_suspend() noexcept{ return {}; }
      
        void unhandled_exception() noexcept
        {
            std::rethrow_exception(std::current_exception());
        }
        void return_void(){};
       
    };
    CoroType(promise_type* p)
         : m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    ~CoroType()
     {
         fmt::println( "Handle destroyed..." );
          m_handle.destroy();
     }
    std::coroutine_handle<promise_type>   m_handle;
};


CoroType do_work() {
    fmt::println( "Doing first thing... " );
    co_await std::suspend_always{};
    fmt::println( "Doing second thing..." );
    co_await std::suspend_always{};
    fmt::println( "Doing Third thing..." );
}

int main(){

    auto task = do_work();

    //Resume
    task.m_handle();
    fmt::println( "coro done : {}" , task.m_handle.done() );


    //Resume for second time
    task.m_handle.resume();
    fmt::println( "coro done : {}" , task.m_handle.done() );

    //Resume for third time
    task.m_handle.resume();
    fmt::println( "coro done : {}" , task.m_handle.done() );


    //Resuming after coroutine has run to completion : BAD!
   // fmt::println( "------" );
   // task.m_handle.resume();

    fmt::println( "Done!" );

    return 0;
}