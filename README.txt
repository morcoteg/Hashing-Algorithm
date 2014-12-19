// Author: Gabriel Morcote

Hash Set implementation:

1. NumBuckets: The number of hash buckets used by the set
2. Contains: Checks whether an item is in the set
3. Insert: Adds an item to the set (if it was not already there). Returns
whether the addition was successful.
4. Remove: Removes an item from the set. Returns whether the removal was
successful.
5. Clear: Removes all items from the set.
6. ForEach: Invokes a function on each element of the set. The ordering is
undened, but it must be invoked precisely once on each item.
7. MaxBucketSize: The number of items in the most full bucket.
8. PercentEmptyBuckets: The percentage of buckets that contain no items.


You may also need to make adjustments to the constructor and destructor.
Additionally, you will be required to implement three dierent hash functions
of your choosing in HashFunc.cpp. The hash functions must have signicant
dierences. You should cite where each hash function comes from. Some options
appear on page 195 of your textbook. Other options include the Java String
hashCode, FNV hash, Jenkins hash, CRC32, MurmurHash, or Pearson hashing.
