struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// creating map using the given hash function
unordered_map<long long, int, custom_hash> safe_map;
gp_hash_table<long long, int, custom_hash> safe_hash_table;

/*
In the first case we can now only define map whose key(first) value is and int long long or of similar type.

If we define it as a string then we will get an error. So be careful or write a function to hash string
and then create the map.

If you have a pair of integers you'd like to hash, you can use the custom hash function above on each of them to get two values a and b.
Then combine them in any way you like, e.g., a + b. The one issue with a + b is that swapping the two elements of the pair will lead 
to the same hash value. This isn't a problem from a theory point of view since "O(1) collisions on average" is still valid, but to 
avoid this situation you can switch to a non-symmetric function such as 3 * a + b or a ^ (b >> 1).
*/