
/*
Implement an LRU cache which includes the following features:
  Expire Time - after which an entry in the cache is invalid
  Priority - lower priority entries should be evicted before higher priority entries

The Cache eviction strategy should be as follows:
  Evict expired entries first
  If there are no expired items to evict then evict the lowest priority entries
    Tie breaking among entries with the same priority is done via least recently used.

You can use any language.

Your task is to implement a PriorityExpiryCache cache with a max capacity.  Specifically please fill out the data structures on the PriorityExpiryCache object and implement the entry eviction method.

You do NOT need to implement the get or set methods.

It should support these operations:
  Get: Get the value of the key if the key exists in the cache and is not expired.
  Set: Update or insert the value of the key with a priority value and expiretime.
    Set should never ever allow more items than maxItems to be in the cache.
    When evicting we need to evict the lowest priority item(s) which are least recently used.

Example:
p5 => priority 5
e10 => expires at 10 seconds since epoch


 - We care about performance. Time > memory.
 
 
*/

#include <iostream>
#include <chrono>
#include <thread>

typedef int time_t

time_t g_Time = 0;

typedef int UnderlyingData;

struct CacheData {
  string key;
  UnderlyingData data;
  time_t lastAccessed;
  time_t expiryInSecs;
  int priority;
  deque<CacheData*>::iterator priorityDeque, expiryDeque;
};

struct PriorityExpiryCache {
  int maxItems;
  // TODO(interviewee): implement this
  
  PriorityExpiryCache(const int maxItems) {
    //
  }
  
  map<time_t,deque<CacheData*>> cachedDataByExp;
  map<int,deque<CacheData*>> cachedDataByPri;
  
  unordered_map<string,CacheData> dataMap;
  
  
  CacheData* Get(std::string key) {
    // ... the interviewee does not need to implement this now.
    // Assume that this will return the value for the key in the cache
    return nullptr;
  }
  
  void Set(std::string key, CacheData value, int priority, int expiryInSecs) {
    // ... the interviewee does not need to implement this now.
    // Assume that this will add this key, value pair to the cache
    EvictItems();
  }
  
  void SetMaxItems(int numItems) {
    maxItems = numItems;
    EvictItems();
  }
  
  void DebugPrintKeys() {
    // ... the interviewee does not need to implement this now.
    // Prints all the keys in the cache for debugging purposes
  }
  
  void EvictItems() {
    // TODO(interviewee): implement this
  }
};


int main() {

  PriorityExpirtyCache c(5);
  
      //key val pri exp
  c.Set("A", 1, 5,  100 );
  c.Set("B", 2, 15, 3   );
  c.Set("C", 3, 5,  10  );
  c.Set("D", 4, 1,  15  );
  c.Set("E", 5, 5,  150 );
  c.Get("C");


  // Current time = 0
  c.SetMaxItems(5);
  // Keys in C = ["A", "B", "C", "D", "E"]
  // space for 5 keys, all 5 items are included
  c.DebugPrintKeys();

  // Sleep for 5 secs
  g_Time += 5;

  // Current time = 5
  c.SetMaxItems(4);
  // Keys in C = ["A", "C", "D", "E"]
  // "B" is removed because it is expired.  e3 < e5
  c.DebugPrintKeys();

  c.SetMaxItems(3);
  // Keys in C = ["A", "C", "E"]
  // "D" is removed because it the lowest priority
  // D's expire time is irrelevant.
  c.DebugPrintKeys();

  c.SetMaxItems(2);
  // Keys in C = ["C", "E"]
  // "A" is removed because it is least recently used."
  // A's expire time is irrelevant.
  c.DebugPrintKeys();

  c.SetMaxItems(1);
  // Keys in C = ["C"]
  // "E" is removed because C is more recently used (due to the Get("C") event).
  c.DebugPrintKeys();
  
  return 0;
}

