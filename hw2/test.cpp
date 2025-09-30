#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

class prime_bits {
private:
    uint64_t n;          // number of values we can represent (0..n)
    uint64_t num_words;  // count of 64-bit words
    uint64_t* p;         // backing store (0 = prime, 1 = composite for odds)

    // map integer i -> (word, bit) for the odd-only scheme
    static inline void map_odd(uint64_t i, uint64_t& w, uint64_t& bit) {
        // store only odds: 1 bit per odd, 64 bits per word -> 128 integers per word
        w   = i / 128;
        bit = (i % 128) >> 1;  // 0..63
    }

public:
    // allocate enough words for odds up to n (i=0..n). 128 ints per word.
    explicit prime_bits(uint64_t n_in)
        : n(n_in),
          num_words(n_in / 128 + 1),
          p(new uint64_t[n_in / 128 + 1]) {
        for (uint64_t i = 0; i < num_words; ++i) p[i] = 0;   // all "prime"
    }

    ~prime_bits() { delete[] p; }

    prime_bits(const prime_bits&)            = delete;
    prime_bits& operator=(const prime_bits&) = delete;

    // expose a few safe probes so you can test construction/layout
    uint64_t words() const { return num_words; }
    uint64_t capacity_n() const { return n; }
    uint64_t peek_word(uint64_t w) const { return p[w]; }
    void     poke_word(uint64_t w, uint64_t val) { p[w] = val; }

    // mark composite using the odd-only scheme (even > 2 are trivially composite)
    void mark_composite(uint64_t i) {
        if (i < 3) return;                 // ignore 0,1,2 here
        if ((i & 1) == 0) return;          // skip evens
        uint64_t w, b; map_odd(i, w, b);
        p[w] |= (1ULL << b);
    }

    bool is_prime(uint64_t i) const {
        if (i < 2) return false;
        if (i == 2) return true;
        if ((i & 1) == 0) return false;    // even
        uint64_t w, b; map_odd(i, w, b);
        return (p[w] & (1ULL << b)) == 0;
    }


    // very small demo sieve you can swap out later
    uint64_t demo_sieve() {
        // mark odd composites up to n using simple trial marking
        uint64_t lim = static_cast<uint64_t>(std::sqrt(static_cast<long double>(n)));
        for (uint64_t i = 3; i <= lim; i += 2) {
            if (is_prime(i)) {
                for (uint64_t j = i * i; j <= n; j += 2 * i) mark_composite(j);
            }
        }
        uint64_t count = (n >= 2) ? 1 : 0;  // include 2
        for (uint64_t i = 3; i <= n; i += 2) if (is_prime(i)) ++count;
        return count;
    }
};

int main(int argc, char** argv) {
    uint64_t N = (argc > 1) ? std::strtoull(argv[1], nullptr, 10) : 200;

    prime_bits pb(N);

    // Constructor sanity
    std::cout << "n=" << pb.capacity_n()
              << " words=" << pb.words()
              << " (64 bits per word, odds only)\n";

    // Poke and peek raw words
    if (pb.words() > 0) {
        std::cout << "word[0] before: 0x" << std::hex << std::setw(16) << std::setfill('0')
                  << pb.peek_word(0) << std::dec << "\n";
        pb.poke_word(0, 0xA5A5A5A5A5A5A5A5ULL);
        std::cout << "word[0] after : 0x" << std::hex << std::setw(16) << std::setfill('0')
                  << pb.peek_word(0) << std::dec << "\n";
        pb.poke_word(0, 0); // reset
    }



    /*
     * MISTAKES: 
    * 1. prime_sum[i] = 0 line 344
    * 
    */

    // APPROACHES: 
    //


    uint64_t eratosthenes(uint64_t size, uint64_t a, uint64_t b) {
        uint64_t count = 1; // 2 is a special case
        uint64_t lim = sqrt(b);
        for (uint64_t i = a; i <= b; i += 2)
            if (is_prime(i)) {
                count++;
                for (uint64_t j = i*i; j <= b; j += 2*i)
                    clear_prime(j);
            }
        for (uint64_t i = (lim + 1)| 1; i <= b; i += 2)
            if (is_prime(i))
                count++;
        return count;
    }






    // Mark a few composites manually
    pb.mark_composite(9);   // 3*3
    pb.mark_composite(25);  // 5*5
    std::cout << "is_prime(9)="  << pb.is_prime(9)
              << " is_prime(25)=" << pb.is_prime(25)
              << " is_prime(29)=" << pb.is_prime(29) << "\n";

    // Run a tiny sieve
    uint64_t count = pb.demo_sieve();
    std::cout << "primes up to " << N << " = " << count << "\n";

    // Spot check a few known values
    for (int x : {2,3,4,5,97,98,99,100}) {
        std::cout << x << (pb.is_prime(x) ? " prime\n" : " composite\n");
    }
}
