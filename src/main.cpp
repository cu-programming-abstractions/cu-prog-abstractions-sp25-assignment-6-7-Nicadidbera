#include "list.h"
#include "list_utils.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

void printTestResult(const string& testName, bool passed) {
    cout << (passed ? "✓ " : "✗ ") << testName << endl;
}

void testBasicOperations() {
    cout << "\n=== Testing Basic Operations ===" << endl;

    LinkedList list;
    bool passed = true;

    passed &= list.isEmpty();
    printTestResult("Empty list is empty", passed);

    list.prepend(1);
    passed = !list.isEmpty();
    printTestResult("List not empty after prepend", passed);

    list.append(2);
    list.append(3);
    cout << "List after append: ";
    list.print(cout);
    cout << endl;

    int val = list.removeFront();
    passed = (val == 1);
    printTestResult("removeFront returns correct value", passed);
}

void testCopyOperations() {
    cout << "\n=== Testing Copy Operations ===" << endl;
    bool passed = true;

    LinkedList original;
    original.append(1);
    original.append(2);
    original.append(3);

    LinkedList copy1(original);
    passed = (length(copy1) == length(original));
    printTestResult("Copy constructor creates correct length", passed);

    LinkedList copy2;
    copy2 = original;
    passed = (length(copy2) == length(original));
    printTestResult("Assignment operator creates correct length", passed);

    original.append(4);
    passed = (length(copy1) == 3 && length(copy2) == 3);
    printTestResult("Copies are independent", passed);
}

void testUtilityFunctions() {
    cout << "\n=== Testing Utility Functions ===" << endl;
    bool passed = true;

    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);

    passed = (length(list) == 3);
    printTestResult("length returns correct value", passed);

    passed = (sum(list) == 6);
    printTestResult("sum returns correct value", passed);

    passed = contains(list, 2) && !contains(list, 4);
    printTestResult("contains works correctly", passed);

    reverse(list);
    passed = (list.removeFront() == 3);
    printTestResult("reverse works correctly", passed);

    list = LinkedList();
    list.append(2);
    list.append(1);
    list.append(4);
    list.append(5);

    passed = (nthFromEnd(list, 0) == 5 && nthFromEnd(list, 2) == 1);
    printTestResult("nthFromEnd works correctly", passed);
}

void testEdgeCases() {
    cout << "\n=== Testing Edge Cases ===" << endl;
    bool passed = true;

    LinkedList empty;
    try {
        empty.removeFront();
        passed = false;
    } catch (const runtime_error&) {
        passed = true;
    }
    printTestResult("removeFront throws on empty list", passed);

    try {
        nthFromEnd(empty, 0);
        passed = false;
    } catch (const runtime_error&) {
        passed = true;
    }
    printTestResult("nthFromEnd throws on invalid index", passed);

    LinkedList list;
    list.append(1);
    list = list;
    passed = (length(list) == 1);
    printTestResult("Self-assignment works correctly", passed);
}

void testMemoryManagement() {
    cout << "\n=== Testing Memory Management ===" << endl;
    bool passed = true;

    LinkedList list;
    for (int i = 0; i < 1000; i++) {
        list.append(i);
    }
    passed = (length(list) == 1000);
    printTestResult("Large list creation works", passed);
}

int main() {
    cout << "Starting Linked List Tests\n" << endl;

    try {
        testBasicOperations();
        testCopyOperations();
        testUtilityFunctions();
        testEdgeCases();
        testMemoryManagement();

        cout << "\nAll tests completed!" << endl;
    } catch (const exception& e) {
        cout << "\nTest failed with exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
