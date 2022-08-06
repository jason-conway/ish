// Spin-lock barrier for n threads, where n is a power of two.
// Initialize *barrier to zero.
static void barrier_wait(int *barrier, int n)
{
    int v = __atomic_add_fetch(barrier, 1, __ATOMIC_SEQ_CST);
    if (v & (n - 1)) {
        for (v &= n; (__atomic_load_n(barrier, __ATOMIC_SEQ_CST)&n) == v;);
    }
}

