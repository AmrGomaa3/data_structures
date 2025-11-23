#include "hash_table.h"
#include <cassert>
#include <string>
#include <iostream>


constexpr int ELEMENTS {1'000'000};


int main() {
    // Test 1: constructor
    HashTable<std::string, int> ht;
    assert(ht.isEmpty());
    assert(ht.size() == 0);

    // Test 2: basic operations
    ht.put("one", 1);
    ht.put("two", 2);
    ht.put("three", 3);
    assert(ht.get("one") == 1);
    assert(ht.get("two") == 2);
    assert(ht.containsKey("one"));
    assert(ht.containsKey("three"));
    assert(!ht.containsKey("four"));
    assert(ht.containsValue(2));
    assert(!ht.containsValue(5));
    assert(!ht.isEmpty());
    assert(ht.size() == 3);

    std::cout << "Test 1 passed\n";

    // Test 3: duplicate keys
    ht.put("one", 10);
    assert(ht.get("one") == 10);

    ht.put("one", 11);
    assert(ht.get("one") == 11);
    assert(ht.containsKey("one"));
    assert(!ht.containsValue(1));
    assert(!ht.containsValue(10));
    assert(ht.size() == 3);

    std::cout << "Test 2 passed\n";

    // Test 3: getOrDefault
    assert(ht.getOrDefault("four", 4));
    assert(!ht.containsKey("four"));
    assert(!ht.containsValue(4));
    assert(ht.getOrDefault("eleven", 11));
    assert(!ht.containsKey("eleven"));
    assert(ht.containsValue(11));

    std::cout << "Test 3 passed\n";

    // Test 4: remove/clear
    ht.remove("two");
    assert(!ht.containsKey("two"));
    assert(!ht.containsValue(2));
    assert(ht.size() == 2);

    ht.clear();
    assert(ht.isEmpty());
    assert(ht.size() == 0);

    std::cout << "Test 4 passed\n";

    // Test 5: stress testing (expand/shrink)
    HashTable<int, double> stress_ht{2};

    for (int i = 0; i < ELEMENTS; i++) stress_ht.put(i, static_cast<double>(i));

    assert(stress_ht.size() == ELEMENTS);

    for (int i = 0; i < ELEMENTS; i++) stress_ht.remove(i);

    assert(stress_ht.isEmpty());

    std::cout << "Test 5 passed\n";

    // Copy constructor tests
    // Test 6: empty assignment
    HashTable<int, double> ht1;
    assert(ht1.isEmpty());
    assert(ht1.size() == 0);

    HashTable<int, double> ht2(ht1);
    assert(ht2.isEmpty());
    assert(ht2.size() == 0);

    std::cout << "Test 6 passed\n";

    // Test 7: one node
    HashTable<int, double> ht3;
    ht3.put(1, 1.0);

    HashTable<int, double> ht4{ht3};
    assert(ht4.size() == 1);
    assert(ht4.get(1) == 1.0);
    assert(ht4.containsKey(1));
    assert(ht4.containsValue(1.0));

    std::cout << "Test 7 passed\n";

    // Test 8: multiple nodes
    HashTable<int, double> ht5;
    ht5.put(1, 1.0);
    ht5.put(2, 2.0);
    ht5.put(3, 3.0);

    HashTable<int, double> ht6{ht5};
    assert(ht6.size() == 3);
    assert(ht6.get(1) == 1.0);
    assert(ht6.get(2) == 2.0);
    assert(ht6.containsKey(3));
    assert(ht6.containsValue(3.0));

    std::cout << "Test 8 passed\n";

    // Copy assignment operator tests
    // Test 9: empty to empty
    HashTable<int, double> ht7;
    assert(ht7.isEmpty());

    HashTable<int, double> ht8;
    assert(ht8.isEmpty());

    ht8 = ht7;
    assert(ht8.isEmpty());
    assert(ht7.isEmpty());

    std::cout << "Test 9 passed\n";

    // Test 10: empty to non-empty - single node
    HashTable<int, double> ht9;

    HashTable<int, double> ht10;
    ht10.put(1, 1.0);
    
    ht10 = ht9;
    assert(ht10.isEmpty());
    assert(!ht10.containsKey(1));
    assert(!ht10.containsValue(1.0));

    std::cout << "Test 10 passed\n";

    // Test 11: empty to non-empty - multiple nodes
    HashTable<int, double> ht11;

    HashTable<int, double> ht12;
    ht12.put(1, 1.0);
    ht12.put(2, 2.0);
    ht12.put(3, 3.0);

    ht12 = ht11;
    assert(ht12.isEmpty());
    assert(!ht12.containsKey(1));
    assert(!ht12.containsValue(2.0));

    std::cout << "Test 11 passed\n";

    // Test 12: non-empty to empty - single node
    HashTable<int, double> ht13;
    ht13.put(1, 1.0);

    HashTable<int, double> ht14;

    ht14 = ht13;
    assert(ht14.size() == 1);
    assert(ht14.get(1) == 1.0);

    std::cout << "Test 12 passed\n";

    // Test 8: non-empty to empty - multiple nodes
    HashTable<int, double> ht15;
    ht15.put(1, 1.0);
    ht15.put(2, 2.0);
    ht15.put(3, 3.0);

    HashTable<int, double> ht16;
    
    ht16 = ht15;
    assert(ht16.size() == 3);
    assert(ht16.get(1) == 1.0);
    assert(ht16.get(2) == 2.0);
    assert(ht16.containsKey(3));
    assert(ht16.containsValue(3.0));

    std::cout << "Test 13 passed\n";

    // Test 14: non-empty to non-empty - same size (1)
    HashTable<int, double> ht17;
    ht17.put(1, 1.0);

    HashTable<int, double> ht18;
    ht18.put(2, 2.0);

    ht18 = ht17;
    assert(ht18.size() == ht17.size());
    assert(!ht18.containsKey(2));
    assert(ht18.get(1) == ht17.get(1));

    std::cout << "Test 14 passed\n";

    // Test 15: non-empty to non-empty - same size (2)
    HashTable<int, double> ht19;
    ht19.put(1, 1.0);
    ht19.put(2, 2.0);
    ht19.put(3, 3.0);

    HashTable<int, double> ht20;
    ht20.put(4, 4.0);
    ht20.put(5, 5.0);
    ht20.put(6, 6.0);

    ht20 = ht19;
    assert(ht20.size() == ht19.size());
    assert(!ht20.containsKey(5));
    assert(ht20.get(1) == ht19.get(1));
    assert(ht20.get(2) == ht19.get(2));
    
    std::cout << "Test 15 passed\n";

    // Test 16: non-empty to non-empty - different size (1)
    HashTable<int, double> ht21;
    ht21.put(1, 1.0);
    ht21.put(2, 2.0);
    ht21.put(3, 3.0);

    HashTable<int, double> ht22;
    ht22.put(4, 4.0);

    ht22 = ht21;
    assert(ht22.size() == ht21.size());
    assert(ht22.get(1) == ht21.get(1));
    assert(!ht22.containsKey(4));

    std::cout << "Test 16 passed\n";

    // Test 17: non-empty to non-empty - different size (2)
    HashTable<int, double> ht23;
    ht23.put(1, 1.0);
    ht23.put(2, 2.0);
    ht23.put(3, 3.0);

    HashTable<int, double> ht24;
    ht24.put(4, 4.0);
    ht24.put(5, 5.0);

    ht24 = ht23;
    assert(ht24.size() == ht23.size());
    assert(ht24.get(1) == ht23.get(1));
    assert(!ht24.containsKey(5));

    std::cout << "Test 17 passed\n";

    // Test 18: non-empty to non-empty - different size (3)
    HashTable<int, double> ht25;
    ht25.put(1, 1.0);

    HashTable<int, double> ht26;
    ht26.put(4, 4.0);
    ht26.put(5, 5.0);
    ht26.put(6, 6.0);

    ht26 = ht25;
    assert(ht26.size() == ht25.size());
    assert(ht26.get(1) == ht25.get(1));
    assert(!ht26.containsKey(5));

    std::cout << "Test 18 passed\n";

    // Test 19: non-empty to non-empty - different size (4)
    HashTable<int, double> ht27;
    ht27.put(1, 1.0);
    ht27.put(2, 2.0);

    HashTable<int, double> ht28;
    ht28.put(4, 4.0);
    ht28.put(5, 5.0);
    ht28.put(6, 6.0);

    ht28 = ht27;
    assert(ht28.size() == ht27.size());
    assert(ht28.get(1) == ht27.get(1));
    assert(!ht28.containsKey(5));

    std::cout << "Test 19 passed\n";

    // Test 20: self-assignment - empty
    HashTable<int, double> ht29;

    ht29 = ht29;
    assert(ht29.isEmpty());
    assert(ht29.size() == 0);

    std::cout << "Test 20 passed\n";

    // Test 21: self-assignment - single node
    HashTable<int, double> ht30;
    ht30.put(1, 1.0);

    ht30 = ht30;
    assert(ht30.size() == 1);
    assert(ht30.get(1) == 1.0);

    std::cout << "Test 21 passed\n";

    // Test 22: self-assignment - multiple nodes
    HashTable<int, double> ht31;
    ht31.put(1, 1.0);
    ht31.put(2, 2.0);
    ht31.put(3, 3.0);

    ht31 = ht31;
    assert(ht31.size() == 3);
    assert(ht31.get(1) == 1.0);
    assert(ht31.containsKey(2));

    std::cout << "Test 22 passed\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}

