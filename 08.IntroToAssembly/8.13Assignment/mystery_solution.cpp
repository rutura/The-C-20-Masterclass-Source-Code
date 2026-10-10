// Exercise 6 - solution.
//
// eax = n * n
// "test edi, 1" checks the lowest bit: it is 1 for an odd number, in two's
// complement for negative numbers too. When the bit is set the jz is NOT
// taken, so inc runs and the answer gets one added. Even numbers skip it.

int mystery_cpp(int n) {
    int result{n * n};
    if (n % 2 != 0) {       // odd, also for negative n (-3 % 2 is -1, not 0)
        ++result;
    }
    return result;
}
