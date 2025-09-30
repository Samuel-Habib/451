**c syntax**
what does this snippet mean??
        ```
        prime_bits(uint64_t n) : // round up because we need n+1 bits
		n(n+1), num_words(n/64+1), p(new uint64_t[n/64+1]) {
			for (int i =0; i < num_words; i++)
			  prime_bits[i] = 0;
		}
        ```
- what does n(n+1) mean? are we calling a function n() or are we multipling n by n+1
    - I think it's not calling the function instead it's initlizing them in the class so the member variable n is initalized as being n +1
- why are there multiple variable names like this followed by a body?
    - the only acutal body is just p init
- how does p work is it just an array?
    - YES!

### clear_prime
- why is i divided by 128 in `p[i/128]`
- i don't even know why we're clearing it so we're going to is_prime for now

### is_prime
1LL << 
- shifted this way, it grows to the left
- it shrinks to the right
- so i is the index and we're dividing by 128, why? 
    - it's going to take every single odd number from 3 to 128
- checking if the array index and the shifted bits == 0 if they equal 0 then that's a prime which makes sense becaue that means it's a singular bit thats == 0 which is what we've decicded a prime is
- so all of 1 to 128 i is p[0]?
**what does this do**

1. okay so p[0] is the first 128 bits 
2. (i % 128) >> 1, this makes the odds sequential so 3, 5, 7 is 1, 2, 3
3. they use 128 indexing because a 128 window makes full use of the p[i] 64 bit length
(1LL << ((i%128) >> 1)) this is the position 

- is prime
    - checks if an i-th bit is prime or not, if 0 it is if 1 it's not
    - 

