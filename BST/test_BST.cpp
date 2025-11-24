#include "BST.h"
#include <cassert>
#include <string>
#include <iostream>


constexpr int ELEMENTS {10'000};


int main() {
    // Test 1: constructor
    BST<std::string, int> bst;
    assert(bst.isEmpty());
    assert(bst.size() == 0);

    std::cout << "Test 1 passed\n";

    // Test 2: basic operations
    bst.put("two", 2);
    bst.put("one", 1);
    bst.put("three", 3);
    assert(bst.get("one") == 1);
    assert(bst.get("two") == 2);
    assert(bst.contains("one"));
    assert(bst.contains("three"));
    assert(!bst.contains("four"));
    assert(!bst.isEmpty());
    assert(bst.size() == 3);

    std::cout << "Test 2 passed\n";

    // Test 3: duplicate keys
    bst.put("one", 10);
    assert(bst.get("one") == 10);

    bst.put("one", 11);
    assert(bst.get("one") == 11);
    assert(bst.contains("one"));
    assert(bst.size() == 3);

    std::cout << "Test 3 passed\n";

    // Test 4: remove/clear
    bst.remove("two");
    assert(!bst.contains("two"));
    assert(bst.size() == 2);

    bst.clear();
    assert(bst.isEmpty());
    assert(bst.size() == 0);

    std::cout << "Test 4 passed\n";

    // Test 5: stress testing (expand/shrink)
    BST<int, double> stress_bst1;
    BST<int, double> stress_bst2;

    for (int i = 0; i < ELEMENTS; i++) {
        stress_bst1.put(i, static_cast<double>(i));
        stress_bst2.put(i, static_cast<double>(i));

        assert(stress_bst1.contains(i));
    }

    assert(stress_bst1.size() == ELEMENTS);
    assert(stress_bst2.size() == ELEMENTS);

    stress_bst2.clear();

    assert(stress_bst2.size() == 0);
    assert(stress_bst2.isEmpty());

    for (int i = 0; i < ELEMENTS; i++) stress_bst1.remove(i);

    assert(stress_bst1.isEmpty());

    std::cout << "Test 5 passed\n";

    // Copy constructor tests
    // Test 6: empty assignment
    BST<int, double> bst1;
    assert(bst1.isEmpty());
    assert(bst1.size() == 0);

    BST<int, double> bst2(bst1);
    assert(bst2.isEmpty());
    assert(bst2.size() == 0);

    std::cout << "Test 6 passed\n";

    // Test 7: one node
    BST<int, double> bst3;
    bst3.put(1, 1.0);

    BST<int, double> bst4{bst3};
    assert(bst4.size() == 1);
    assert(bst4.get(1) == 1.0);
    assert(bst4.contains(1));

    std::cout << "Test 7 passed\n";

    // Test 8: multiple nodes
    BST<int, double> bst5;
    bst5.put(2, 2.0);
    bst5.put(1, 1.0);
    bst5.put(3, 3.0);

    BST<int, double> bst6{bst5};
    assert(bst6.size() == 3);
    assert(bst6.get(1) == 1.0);
    assert(bst6.get(2) == 2.0);
    assert(bst6.contains(3));
    
    std::cout << "Test 8 passed\n";

    // Copy assignment operator tests
    // Test 9: empty to empty
    BST<int, double> bst7;
    assert(bst7.isEmpty());

    BST<int, double> bst8;
    assert(bst8.isEmpty());

    bst8 = bst7;
    assert(bst8.isEmpty());
    assert(bst7.isEmpty());

    std::cout << "Test 9 passed\n";

    // Test 10: empty to non-empty - single node
    BST<int, double> bst9;

    BST<int, double> bst10;
    bst10.put(1, 1.0);
    
    bst10 = bst9;
    assert(bst10.isEmpty());
    assert(!bst10.contains(1));

    std::cout << "Test 10 passed\n";

    // Test 11: empty to non-empty - multiple nodes
    BST<int, double> bst11;

    BST<int, double> bst12;
    bst12.put(1, 1.0);
    bst12.put(2, 2.0);
    bst12.put(3, 3.0);

    bst12 = bst11;
    assert(bst12.isEmpty());
    assert(!bst12.contains(1));

    std::cout << "Test 11 passed\n";

    // Test 12: non-empty to empty - single node
    BST<int, double> bst13;
    bst13.put(1, 1.0);

    BST<int, double> bst14;

    bst14 = bst13;
    assert(bst14.size() == 1);
    assert(bst14.get(1) == 1.0);

    std::cout << "Test 12 passed\n";

    // Test 8: non-empty to empty - multiple nodes
    BST<int, double> bst15;
    bst15.put(2, 2.0);
    bst15.put(1, 1.0);
    bst15.put(3, 3.0);

    BST<int, double> bst16;
    
    bst16 = bst15;
    assert(bst16.size() == 3);
    assert(bst16.get(1) == 1.0);
    assert(bst16.get(2) == 2.0);
    assert(bst16.contains(3));

    std::cout << "Test 13 passed\n";

    // Test 14: non-empty to non-empty - same size (1)
    BST<int, double> bst17;
    bst17.put(1, 1.0);

    BST<int, double> bst18;
    bst18.put(2, 2.0);

    bst18 = bst17;
    assert(bst18.size() == bst17.size());
    assert(!bst18.contains(2));
    assert(bst18.get(1) == bst17.get(1));

    std::cout << "Test 14 passed\n";

    // Test 15: non-empty to non-empty - same size (2)
    BST<int, double> bst19;
    bst19.put(2, 2.0);
    bst19.put(1, 1.0);
    bst19.put(3, 3.0);

    BST<int, double> bst20;
    bst20.put(5, 5.0);
    bst20.put(4, 4.0);
    bst20.put(6, 6.0);

    bst20 = bst19;
    assert(bst20.size() == bst19.size());
    assert(!bst20.contains(5));
    assert(bst20.get(1) == bst19.get(1));
    assert(bst20.get(2) == bst19.get(2));
    
    std::cout << "Test 15 passed\n";

    // Test 16: non-empty to non-empty - different size (1)
    BST<int, double> bst21;
    bst21.put(2, 2.0);
    bst21.put(1, 1.0);
    bst21.put(3, 3.0);

    BST<int, double> bst22;
    bst22.put(4, 4.0);

    bst22 = bst21;
    assert(bst22.size() == bst21.size());
    assert(bst22.get(1) == bst21.get(1));
    assert(!bst22.contains(4));

    std::cout << "Test 16 passed\n";

    // Test 17: non-empty to non-empty - different size (2)
    BST<int, double> bst23;
    bst23.put(2, 2.0);
    bst23.put(1, 1.0);
    bst23.put(3, 3.0);

    BST<int, double> bst24;
    bst24.put(4, 4.0);
    bst24.put(5, 5.0);

    bst24 = bst23;
    assert(bst24.size() == bst23.size());
    assert(bst24.get(1) == bst23.get(1));
    assert(!bst24.contains(5));

    std::cout << "Test 17 passed\n";

    // Test 18: non-empty to non-empty - different size (3)
    BST<int, double> bst25;
    bst25.put(1, 1.0);

    BST<int, double> bst26;
    bst26.put(5, 5.0);
    bst26.put(4, 4.0);
    bst26.put(6, 6.0);

    bst26 = bst25;
    assert(bst26.size() == bst25.size());
    assert(bst26.get(1) == bst25.get(1));
    assert(!bst26.contains(5));

    std::cout << "Test 18 passed\n";

    // Test 19: non-empty to non-empty - different size (4)
    BST<int, double> bst27;
    bst27.put(1, 1.0);
    bst27.put(2, 2.0);

    BST<int, double> bst28;
    bst28.put(5, 5.0);
    bst28.put(4, 4.0);
    bst28.put(6, 6.0);

    bst28 = bst27;
    assert(bst28.size() == bst27.size());
    assert(bst28.get(1) == bst27.get(1));
    assert(!bst28.contains(5));

    std::cout << "Test 19 passed\n";

    // Test 20: self-assignment - empty
    BST<int, double> bst29;

    bst29 = bst29;
    assert(bst29.isEmpty());
    assert(bst29.size() == 0);

    std::cout << "Test 20 passed\n";

    // Test 21: self-assignment - single node
    BST<int, double> bst30;
    bst30.put(1, 1.0);

    bst30 = bst30;
    assert(bst30.size() == 1);
    assert(bst30.get(1) == 1.0);

    std::cout << "Test 21 passed\n";

    // Test 22: self-assignment - multiple nodes
    BST<int, double> bst31;
    bst31.put(2, 2.0);
    bst31.put(1, 1.0);
    bst31.put(3, 3.0);

    bst31 = bst31;
    assert(bst31.size() == 3);
    assert(bst31.get(1) == 1.0);
    assert(bst31.contains(2));

    std::cout << "Test 22 passed\n";

    std::cout << "All tests passed successfully\n";

    return 0;
}

