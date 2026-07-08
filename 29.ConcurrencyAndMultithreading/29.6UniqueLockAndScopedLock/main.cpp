// std::lock_guard always locks immediately and can only manage one mutex.
// Two situations it can't handle: locking later than construction, and
// safely locking two mutexes at once without risking deadlock.

#include <print>
#include <thread>
#include <mutex>

int main() {

    std::mutex m;

    // --- std::unique_lock: more flexible, at a small extra cost ---
    // std::defer_lock constructs the lock *without* locking yet - useful
    // when some setup needs to happen first.
    std::unique_lock<std::mutex> lock(m, std::defer_lock);
    std::println("lock.owns_lock() before locking : {}", lock.owns_lock());

    lock.lock(); // lock explicitly, whenever you're ready
    std::println("lock.owns_lock() after locking  : {}", lock.owns_lock());

    lock.unlock(); // unique_lock can unlock early, mid-scope, unlike lock_guard
    std::println("lock.owns_lock() after unlocking: {}", lock.owns_lock());
    // lock's destructor won't double-unlock here - it only unlocks if it
    // still owns the lock.

    // --- std::scoped_lock: locking two mutexes at once, deadlock-free ---
    // The classic deadlock: thread A locks account1 then waits for
    // account2, while thread B locks account2 then waits for account1 -
    // neither ever finishes. scoped_lock locks every mutex it's given
    // together, in a fixed internal order, so two threads transferring in
    // opposite directions can never deadlock against each other.
    struct Account {
        std::mutex mtx;
        int balance;
    };

    Account accountA{.balance = 100};
    Account accountB{.balance = 50};

    auto transfer = [](Account& from, Account& to, int amount) {
        std::scoped_lock lock(from.mtx, to.mtx); // locks both, together
        from.balance -= amount;
        to.balance += amount;
    };

    std::jthread t1(transfer, std::ref(accountA), std::ref(accountB), 30);
    std::jthread t2(transfer, std::ref(accountB), std::ref(accountA), 10);
    t1.join();
    t2.join();

    std::println("");
    std::println("accountA balance : {}", accountA.balance);
    std::println("accountB balance : {}", accountB.balance);
    std::println("total (should still be 150) : {}", accountA.balance + accountB.balance);

    return 0;
}
