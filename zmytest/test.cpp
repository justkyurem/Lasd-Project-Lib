#include "../zlasdtest/test.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"


using namespace std;
using namespace lasd;

// Utility for formatting test results
void printTestResult(const string& testName, bool success) {
    cout << (success ? " [PASS] " : "[ERROR] ") << testName << endl;
}

void testListConstructors() {
    cout << "\n=== List Constructors Test ===" << endl;
    bool allTestsPassed = true;

    // Default constructor test
    List<int> list1;
    bool defaultConstructorTest = (list1.Size() == 0 && list1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << list1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (list1.Empty() ? "true" : "false") << endl;
    allTestsPassed &= defaultConstructorTest;

    // Prepare a list for copy test
    List<int> sourceList;
    for (unsigned long i = 0; i < 5; i++) {
        sourceList.InsertAtBack(i);
    }

    // Copy constructor test
    List<int> list2(sourceList);
    bool copyConstructorSizeTest = (list2.Size() == 5 && !list2.Empty());
    printTestResult("Copy constructor (size)", copyConstructorSizeTest);
    cout << "  - Expected size: 5, Actual size: " << list2.Size() << endl;

    // Verify elements were copied correctly
    bool elementsCorrect = true;
    for (unsigned long i = 0; i < list2.Size(); i++) {
        if (list2[i] != static_cast<int>(i)) {
            elementsCorrect = false;
            break;
        }
    }
    printTestResult("Copy constructor (content)", elementsCorrect);
    cout << "  - Expected elements: 0 1 2 3 4" << endl;
    cout << "  - Actual elements: ";
    list2.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= (copyConstructorSizeTest && elementsCorrect);

    // Move constructor test
    List<int> list3(std::move(sourceList));
    bool moveConstructorTest = (list3.Size() == 5 && sourceList.Size() == 0);
    printTestResult("Move constructor", moveConstructorTest);
    cout << "  - Expected size of new list: 5, Actual size: " << list3.Size() << endl;
    cout << "  - Expected size of original list: 0, Actual size: " << sourceList.Size() << endl;
    cout << "  - Elements of new list: ";
    list3.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= moveConstructorTest;

    cout << "Overall constructors test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testListOperations() {
    cout << "\n=== List Basic Operations Test ===" << endl;
    bool allTestsPassed = true;

    List<int> list;

    // InsertAtFront and InsertAtBack test
    cout << "Inserting elements..." << endl;
    for (int i = 0; i < 3; i++) {
        list.InsertAtFront(i);
    }
    for (int i = 3; i < 6; i++) {
        list.InsertAtBack(i);
    }

    bool insertTest = (list.Size() == 6);
    printTestResult("Element insertion", insertTest);
    cout << "  - Expected size: 6, Actual size: " << list.Size() << endl;
    cout << "  - Expected elements (pre-order): 2 1 0 3 4 5" << endl;
    cout << "  - Actual elements (pre-order): ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Pre-order verification
    int preOrderExpected[] = {2, 1, 0, 3, 4, 5};
    bool preOrderCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != preOrderExpected[i]) {
            preOrderCorrect = false;
            break;
        }
    }
    printTestResult("Pre-order traversal verification", preOrderCorrect);

    // Post-order verification
    cout << "  - Expected elements (post-order): 5 4 3 0 1 2" << endl;
    cout << "  - Actual elements (post-order): ";
    list.PostOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= (insertTest && preOrderCorrect);

    // Front and Back test
    bool frontTest = (list.Front() == 2);
    bool backTest = (list.Back() == 5);
    printTestResult("Front and Back", frontTest && backTest);
    cout << "  - Expected Front: 2, Actual Front: " << list.Front() << endl;
    cout << "  - Expected Back: 5, Actual Back: " << list.Back() << endl;
    allTestsPassed &= (frontTest && backTest);

    // RemoveFromFront and RemoveFromBack test
    int frontValue = list.FrontNRemove();
    bool frontRemoveTest = (frontValue == 2 && list.Size() == 5);
    printTestResult("FrontNRemove", frontRemoveTest);
    cout << "  - Expected removed value: 2, Actual value: " << frontValue << endl;
    cout << "  - Expected new size: 5, Actual size: " << list.Size() << endl;

    list.RemoveFromBack();
    bool backRemoveTest = (list.Size() == 4);
    printTestResult("RemoveFromBack", backRemoveTest);
    cout << "  - Expected new size: 4, Actual size: " << list.Size() << endl;

    // Verify list after removals
    int afterRemovalExpected[] = {1, 0, 3, 4};
    bool afterRemovalCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != afterRemovalExpected[i]) {
            afterRemovalCorrect = false;
            break;
        }
    }
    printTestResult("List after removals", afterRemovalCorrect);
    cout << "  - Expected elements: 1 0 3 4" << endl;
    cout << "  - Actual elements: ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allTestsPassed &= (frontRemoveTest && backRemoveTest && afterRemovalCorrect);
    cout << "Overall operations test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testListMap() {
    cout << "\n=== List Map Test ===" << endl;
    bool allTestsPassed = true;

    List<int> list;
    for (int i = 1; i <= 5; i++) {
        list.InsertAtBack(i);
    }

    cout << "Original list: ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // PreOrderMap test
    cout << "Applying PreOrderMap (element * 2)..." << endl;
    list.PreOrderMap([](int& x) { x *= 2; });

    int expectedAfterPreMap[] = {2, 4, 6, 8, 10};
    bool preMapCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != expectedAfterPreMap[i]) {
            preMapCorrect = false;
            break;
        }
    }
    printTestResult("PreOrderMap", preMapCorrect);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // PostOrderMap test
    cout << "Applying PostOrderMap (element + 1)..." << endl;
    list.PostOrderMap([](int& x) { x += 1; });

    int expectedAfterPostMap[] = {3, 5, 7, 9, 11};
    bool postMapCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != expectedAfterPostMap[i]) {
            postMapCorrect = false;
            break;
        }
    }
    printTestResult("PostOrderMap", postMapCorrect);
    cout << "  - Expected elements: 3 5 7 9 11" << endl;
    cout << "  - Actual elements: ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allTestsPassed &= (preMapCorrect && postMapCorrect);
    cout << "Overall Map test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testListExceptions() {
    cout << "\n=== List Exceptions Test ===" << endl;
    bool allTestsPassed = true;

    List<int> emptyList;

    // Empty list exceptions test
    bool frontExceptionTest = false;
    try {
        emptyList.Front();
        cout << "ERROR: Front did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        frontExceptionTest = true;
        cout << "OK: Front threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Front() exception on empty list", frontExceptionTest);

    bool backExceptionTest = false;
    try {
        emptyList.Back();
        cout << "ERROR: Back did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        backExceptionTest = true;
        cout << "OK: Back threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Back() exception on empty list", backExceptionTest);

    bool removeExceptionTest = false;
    try {
        emptyList.RemoveFromFront();
        cout << "ERROR: RemoveFromFront did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        removeExceptionTest = true;
        cout << "OK: RemoveFromFront threw the expected exception: " << e.what() << endl;
    }
    printTestResult("RemoveFromFront() exception on empty list", removeExceptionTest);

    // Out of range index exception test
    List<int> smallList;
    smallList.InsertAtBack(1);

    bool indexExceptionTest = false;
    try {
        smallList[1]; // Out of range index
        cout << "ERROR: operator[] did not throw exception on out of range index" << endl;
    } catch (const std::out_of_range& e) {
        indexExceptionTest = true;
        cout << "OK: operator[] threw the expected exception: " << e.what() << endl;
    }
    printTestResult("operator[] exception with out of range index", indexExceptionTest);

    allTestsPassed &= (frontExceptionTest && backExceptionTest && removeExceptionTest && indexExceptionTest);
    cout << "Overall exceptions test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testListWithStrings() {
    cout << "\n=== List with Strings Test ===" << endl;
    bool allTestsPassed = true;

    List<string> stringList;

    // String insertion
    stringList.InsertAtBack("one");
    stringList.InsertAtBack("two");
    stringList.InsertAtFront("zero");

    bool stringInsertTest = (stringList.Size() == 3);
    printTestResult("String insertion", stringInsertTest);
    cout << "  - Expected size: 3, Actual size: " << stringList.Size() << endl;
    cout << "  - Expected elements: zero one two" << endl;
    cout << "  - Actual elements: ";
    stringList.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    // Map modification test
    stringList.Map([](string& s) {
        for (char& c : s) {
            c = toupper(c);
        }
    });

    string expectedAfterMap[] = {"ZERO", "ONE", "TWO"};
    bool mapCorrect = true;
    for (unsigned long i = 0; i < stringList.Size(); i++) {
        if (stringList[i] != expectedAfterMap[i]) {
            mapCorrect = false;
            break;
        }
    }
    printTestResult("Map on strings (uppercase transformation)", mapCorrect);
    cout << "  - Expected elements: ZERO ONE TWO" << endl;
    cout << "  - Actual elements: ";
    stringList.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    // Fold test (concatenation)
    string result = stringList.Fold<string>([](const string& s, const string& acc) -> string {
        return acc + s;
    }, "");

    bool foldCorrect = (result == "ZEROONETWO");
    printTestResult("Fold on strings (concatenation)", foldCorrect);
    cout << "  - Expected result: ZEROONETWO" << endl;
    cout << "  - Actual result: " << result << endl;

    allTestsPassed &= (stringInsertTest && mapCorrect && foldCorrect);
    cout << "Overall strings test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testListFold() {
    cout << "\n=== List Fold Test ===" << endl;
    bool allTestsPassed = true;

    List<int> list;
    for (int i = 1; i <= 5; i++) {
        list.InsertAtBack(i);
    }

    // PreOrderFold test (sum)
    int sum = list.PreOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc + x;
    }, 0);

    bool sumCorrect = (sum == 15); // 1+2+3+4+5 = 15
    printTestResult("PreOrderFold (sum)", sumCorrect);
    cout << "  - Expected sum: 15, Actual sum: " << sum << endl;

    // PostOrderFold test (product)
    int product = list.PostOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc * x;
    }, 1);

    bool productCorrect = (product == 120); // 1*2*3*4*5 = 120
    printTestResult("PostOrderFold (product)", productCorrect);
    cout << "  - Expected product: 120, Actual product: " << product << endl;

    // Exists test
    bool existsTest1 = list.Exists(3);
    bool existsTest2 = !list.Exists(10);
    printTestResult("Exists(3) [element present]", existsTest1);
    cout << "  - Expected result: true, Actual result: " << (existsTest1 ? "true" : "false") << endl;

    printTestResult("Exists(10) [element not present]", existsTest2);
    cout << "  - Expected result: false, Actual result: " << (!existsTest2 ? "true" : "false") << endl;

    allTestsPassed &= (sumCorrect && productCorrect && existsTest1 && existsTest2);
    cout << "Overall Fold test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testVectorConstructors() {
    cout << "\n=== Vector Constructors Test ===" << endl;
    bool allTestsPassed = true;

    // Default constructor test
    Vector<int> v1;
    bool defaultConstructorTest = (v1.Size() == 0 && v1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << v1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (v1.Empty() ? "true" : "false") << endl;
    allTestsPassed &= defaultConstructorTest;

    // Size constructor test
    Vector<int> v2(5);
    bool sizeConstructorTest = (v2.Size() == 5 && !v2.Empty());
    printTestResult("Size constructor", sizeConstructorTest);
    cout << "  - Expected size: 5, Actual size: " << v2.Size() << endl;
    cout << "  - Expected empty: false, Actual empty: " << (v2.Empty() ? "true" : "false") << endl;

    // Verify elements are initialized correctly
    bool initializationCorrect = true;
    for (unsigned long i = 0; i < v2.Size(); i++) {
        if (v2[i] != 0) {
            initializationCorrect = false;
            break;
        }
    }
    printTestResult("Element initialization", initializationCorrect);
    cout << "  - All elements should be 0" << endl;
    allTestsPassed &= (sizeConstructorTest && initializationCorrect);

    // Prepare a list for TraversableContainer constructor test
    List<int> sourceList;
    for (unsigned long i = 0; i < 5; i++) {
        sourceList.InsertAtBack(static_cast<int>(i));
    }

    // TraversableContainer constructor test
    Vector<int> v3(sourceList);
    bool containerConstructorTest = (v3.Size() == 5);
    printTestResult("TraversableContainer constructor (size)", containerConstructorTest);
    cout << "  - Expected size: 5, Actual size: " << v3.Size() << endl;

    // Verify elements were copied correctly
    bool elementsCorrect = true;
    for (unsigned long i = 0; i < v3.Size(); i++) {
        if (v3[i] != static_cast<int>(i)) {
            elementsCorrect = false;
            break;
        }
    }
    printTestResult("TraversableContainer constructor (content)", elementsCorrect);
    cout << "  - Expected elements: 0 1 2 3 4" << endl;
    cout << "  - Actual elements: ";
    v3.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= (containerConstructorTest && elementsCorrect);

    // Copy constructor test
    Vector<int> v4(v3);
    bool copyConstructorTest = (v4.Size() == v3.Size() && v4 == v3);
    printTestResult("Copy constructor", copyConstructorTest);
    cout << "  - Expected size: " << v3.Size() << ", Actual size: " << v4.Size() << endl;
    cout << "  - Identical elements: " << (v4 == v3 ? "true" : "false") << endl;
    allTestsPassed &= copyConstructorTest;

    // Move constructor test
    Vector<int> v5(std::move(v4));
    bool moveConstructorTest = (v5.Size() == 5 && v4.Size() == 0);
    printTestResult("Move constructor", moveConstructorTest);
    cout << "  - Expected size of new vector: 5, Actual size: " << v5.Size() << endl;
    cout << "  - Expected size of original vector: 0, Actual size: " << v4.Size() << endl;
    cout << "  - Elements of new vector: ";
    v5.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= moveConstructorTest;

    cout << "Overall constructors test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testVectorOperations() {
    cout << "\n=== Vector Basic Operations Test ===" << endl;
    bool allTestsPassed = true;

    // Create test vector
    Vector<int> v(5);
    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = static_cast<int>(i) + 1;
    }

    // operator[] test (read)
    bool operatorAccessTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != static_cast<int>(i) + 1) {
            operatorAccessTest = false;
            break;
        }
    }
    printTestResult("operator[] (read)", operatorAccessTest);
    cout << "  - Expected elements: 1 2 3 4 5" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allTestsPassed &= operatorAccessTest;

    // operator[] test (write)
    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = v[i] * 2;
    }

    bool operatorWriteTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            operatorWriteTest = false;
            break;
        }
    }
    printTestResult("operator[] (write)", operatorWriteTest);
    cout << "  - Expected elements after modification: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allTestsPassed &= operatorWriteTest;

    // Front and Back test
    bool frontTest = (v.Front() == 2);
    bool backTest = (v.Back() == 10);
    printTestResult("Front", frontTest);
    cout << "  - Expected Front: 2, Actual Front: " << v.Front() << endl;

    printTestResult("Back", backTest);
    cout << "  - Expected Back: 10, Actual Back: " << v.Back() << endl;
    allTestsPassed &= (frontTest && backTest);

    // Resize test (grow)
    v.Resize(7);
    bool resizeGrowTest = (v.Size() == 7);
    printTestResult("Resize (grow)", resizeGrowTest);
    cout << "  - Expected size: 7, Actual size: " << v.Size() << endl;
    cout << "  - Initial elements preserved: ";
    bool elementsPreservedGrow = true;
    for (unsigned long i = 0; i < 5; i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            elementsPreservedGrow = false;
            break;
        }
    }
    printTestResult("Initial elements preserved after growth", elementsPreservedGrow);
    cout << "  - Elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allTestsPassed &= (resizeGrowTest && elementsPreservedGrow);

    // Resize test (shrink)
    v.Resize(3);
    bool resizeShrinkTest = (v.Size() == 3);
    printTestResult("Resize (shrink)", resizeShrinkTest);
    cout << "  - Expected size: 3, Actual size: " << v.Size() << endl;

    bool elementsPreservedShrink = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            elementsPreservedShrink = false;
            break;
        }
    }
    printTestResult("Initial elements preserved after shrinking", elementsPreservedShrink);
    cout << "  - Expected elements: 2 4 6" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allTestsPassed &= (resizeShrinkTest && elementsPreservedShrink);

    // Clear test
    v.Clear();
    bool clearTest = (v.Size() == 0 && v.Empty());
    printTestResult("Clear", clearTest);
    cout << "  - Expected size: 0, Actual size: " << v.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (v.Empty() ? "true" : "false") << endl;
    allTestsPassed &= clearTest;

    cout << "Overall operations test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testVectorExceptions() {
    cout << "\n=== Vector Exceptions Test ===" << endl;
    bool allTestsPassed = true;

    Vector<int> emptyVector;

    // Empty vector exceptions test
    bool frontExceptionTest = false;
    try {
        emptyVector.Front();
        cout << "ERROR: Front did not throw exception on empty vector" << endl;
    } catch (const std::length_error& e) {
        frontExceptionTest = true;
        cout << "OK: Front threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Front() exception on empty vector", frontExceptionTest);

    bool backExceptionTest = false;
    try {
        emptyVector.Back();
        cout << "ERROR: Back did not throw exception on empty vector" << endl;
    } catch (const std::length_error& e) {
        backExceptionTest = true;
        cout << "OK: Back threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Back() exception on empty vector", backExceptionTest);

    // Out of range index exception test
    Vector<int> smallVector(1);
    smallVector[0] = 1;

    bool indexExceptionTest = false;
    try {
        smallVector[1]; // Out of range index
        cout << "ERROR: operator[] did not throw exception on out of range index" << endl;
    } catch (const std::out_of_range& e) {
        indexExceptionTest = true;
        cout << "OK: operator[] threw the expected exception: " << e.what() << endl;
    }
    printTestResult("operator[] exception with out of range index", indexExceptionTest);

    allTestsPassed &= (frontExceptionTest && backExceptionTest && indexExceptionTest);
    cout << "Overall exceptions test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testVectorTraverseAndMap() {
    cout << "\n=== Vector Traverse and Map Test ===" << endl;
    bool allTestsPassed = true;

    Vector<int> v(5);
    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = static_cast<int>(i) + 1;
    }

    // PreOrderTraverse test
    cout << "PreOrderTraverse test:" << endl;
    cout << "  - Expected elements: 1 2 3 4 5" << endl;
    cout << "  - Actual elements: ";
    v.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // PostOrderTraverse test
    cout << "PostOrderTraverse test:" << endl;
    cout << "  - Expected elements: 5 4 3 2 1" << endl;
    cout << "  - Actual elements: ";
    v.PostOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Map test
    v.Map([](int& x) { x *= 2; });

    bool mapTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            mapTest = false;
            break;
        }
    }
    printTestResult("Map (element * 2)", mapTest);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    v.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // PreOrderMap test
    v.PreOrderMap([](int& x) { x += 1; });

    bool preOrderMapTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2 + 1) {
            preOrderMapTest = false;
            break;
        }
    }
    printTestResult("PreOrderMap (element + 1)", preOrderMapTest);
    cout << "  - Expected elements: 3 5 7 9 11" << endl;
    cout << "  - Actual elements: ";
    v.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // PostOrderMap test
    v.PostOrderMap([](int& x) { x -= 1; });

    bool postOrderMapTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            postOrderMapTest = false;
            break;
        }
    }
    printTestResult("PostOrderMap (element - 1)", postOrderMapTest);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    v.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allTestsPassed &= (mapTest && preOrderMapTest && postOrderMapTest);
    cout << "Overall Traverse and Map test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testVectorFold() {
    cout << "\n=== Vector Fold Test ===" << endl;
    bool allTestsPassed = true;

    Vector<int> v(5);
    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = static_cast<int>(i) + 1;
    }

    // Fold test (sum)
    int sum = v.Fold<int>([](const int& x, const int& acc) -> int {
        return acc + x;
    }, 0);

    bool sumCorrect = (sum == 15); // 1+2+3+4+5 = 15
    printTestResult("Fold (sum)", sumCorrect);
    cout << "  - Expected sum: 15, Actual sum: " << sum << endl;

    // PreOrderFold test (product)
    int product = v.PreOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc * x;
    }, 1);

    bool productCorrect = (product == 120); // 1*2*3*4*5 = 120
    printTestResult("PreOrderFold (product)", productCorrect);
    cout << "  - Expected product: 120, Actual product: " << product << endl;

    // PostOrderFold test (index concatenation)
    string indices = v.PostOrderFold<string>([](const int& x, const string& acc) -> string {
        return acc + to_string(x);
    }, "");

    bool indicesCorrect = (indices == "54321"); // Reverse order
    printTestResult("PostOrderFold (index concatenation)", indicesCorrect);
    cout << "  - Expected indices: 54321, Actual indices: " << indices << endl;

    // Exists test
    bool existsTest1 = v.Exists(3);
    bool existsTest2 = !v.Exists(10);
    printTestResult("Exists(3) [element present]", existsTest1);
    cout << "  - Expected result: true, Actual result: " << (existsTest1 ? "true" : "false") << endl;

    printTestResult("Exists(10) [element not present]", existsTest2);
    cout << "  - Expected result: false, Actual result: " << (!existsTest2 ? "true" : "false") << endl;

    allTestsPassed &= (sumCorrect && productCorrect && indicesCorrect && existsTest1 && existsTest2);
    cout << "Overall Fold test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void testSortableVector() {
    cout << "\n=== SortableVector Test ===" << endl;
    bool allTestsPassed = true;

    // Create unsorted vector
    SortableVector<int> sv(7);
    sv[0] = 7;
    sv[1] = 3;
    sv[2] = 1;
    sv[3] = 5;
    sv[4] = 2;
    sv[5] = 6;
    sv[6] = 4;

    cout << "Unsorted vector: ";
    sv.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Sort test
    sv.Sort();

    bool sortTest = true;
    for (unsigned long i = 0; i < sv.Size(); i++) {
        if (sv[i] != static_cast<int>(i) + 1) {
            sortTest = false;
            break;
        }
    }
    printTestResult("Sort", sortTest);
    cout << "  - Expected elements after sorting: 1 2 3 4 5 6 7" << endl;
    cout << "  - Actual elements: ";
    sv.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // String test
    SortableVector<string> svStr(4);
    svStr[0] = "zebra";
    svStr[1] = "alpha";
    svStr[2] = "delta";
    svStr[3] = "beta";

    cout << "Unsorted string vector: ";
    svStr.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    // String Sort test
    svStr.Sort();

    string expectedOrder[] = {"alpha", "beta", "delta", "zebra"};
    bool sortStrTest = true;
    for (unsigned long i = 0; i < svStr.Size(); i++) {
        if (svStr[i] != expectedOrder[i]) {
            sortStrTest = false;
            break;
        }
    }
    printTestResult("String sort", sortStrTest);
    cout << "  - Expected elements after sorting: alpha beta delta zebra" << endl;
    cout << "  - Actual elements: ";
    svStr.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    allTestsPassed &= (sortTest && sortStrTest);
    cout << "Overall SortableVector test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

// Generic Set test - common functions for both implementations
template <typename SetType>
void testSetConstructorsAndBasicOperations() {
    cout << "\n=== Constructors and Basic Operations Test ===" << endl;
    bool allTestsPassed = true;

    // Default constructor test
    SetType s1;
    bool defaultConstructorTest = (s1.Size() == 0 && s1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << s1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (s1.Empty() ? "true" : "false") << endl;
    allTestsPassed &= defaultConstructorTest;

    // Insert and ordered structure test
    bool insertionTest = true;
    s1.Insert(5);
    s1.Insert(3);
    s1.Insert(7);
    s1.Insert(1);
    s1.Insert(9);

    bool sizeAfterInsertTest = (s1.Size() == 5);
    printTestResult("Size after insertions", sizeAfterInsertTest);
    cout << "  - Expected size: 5, Actual size: " << s1.Size() << endl;

    // Verify element order
    int expectedOrder[] = {1, 3, 5, 7, 9};
    cout << "  - Expected elements (in order): 1 3 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s1.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Verify order with operator[]
    bool orderTest = true;
    for (unsigned long i = 0; i < s1.Size(); i++) {
        if (s1[i] != expectedOrder[i]) {
            orderTest = false;
            break;
        }
    }
    printTestResult("Element order", orderTest);
    allTestsPassed &= (insertionTest && sizeAfterInsertTest && orderTest);

    // Duplicate Insert test (should not add elements)
    bool duplicateTest = !s1.Insert(5);
    bool sizeAfterDuplicateTest = (s1.Size() == 5);
    printTestResult("Duplicate insertion (should fail)", duplicateTest);
    printTestResult("Size after duplicate insertion attempt", sizeAfterDuplicateTest);
    cout << "  - Expected size: 5, Actual size: " << s1.Size() << endl;
    allTestsPassed &= (duplicateTest && sizeAfterDuplicateTest);

    // Remove test
    bool removeTest = s1.Remove(3);
    bool sizeAfterRemoveTest = (s1.Size() == 4);
    printTestResult("Element removal", removeTest);
    printTestResult("Size after removal", sizeAfterRemoveTest);
    cout << "  - Expected size: 4, Actual size: " << s1.Size() << endl;

    // Verify order after removal
    int expectedOrderAfterRemove[] = {1, 5, 7, 9};
    bool orderAfterRemoveTest = true;
    for (unsigned long i = 0; i < s1.Size(); i++) {
        if (s1[i] != expectedOrderAfterRemove[i]) {
            orderAfterRemoveTest = false;
            break;
        }
    }
    printTestResult("Order after removal", orderAfterRemoveTest);
    cout << "  - Expected elements: 1 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s1.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Non-existent element removal test
    bool removeNonExistentTest = !s1.Remove(3);
    printTestResult("Non-existent element removal", removeNonExistentTest);
    allTestsPassed &= (removeTest && sizeAfterRemoveTest && orderAfterRemoveTest && removeNonExistentTest);

    // Exists test
    bool existsTest1 = s1.Exists(5);
    bool existsTest2 = !s1.Exists(3);
    printTestResult("Exists(5) [element present]", existsTest1);
    printTestResult("Exists(3) [element not present]", existsTest2);
    allTestsPassed &= (existsTest1 && existsTest2);

    // Copy constructor test
    SetType s2(s1);
    bool copyConstructorTest = (s2.Size() == s1.Size());
    printTestResult("Copy constructor (size)", copyConstructorTest);
    cout << "  - Expected size: " << s1.Size() << ", Actual size: " << s2.Size() << endl;

    // Verify copied elements
    bool copyElementsTest = true;
    for (unsigned long i = 0; i < s2.Size(); i++) {
        if (s2[i] != s1[i]) {
            copyElementsTest = false;
            break;
        }
    }
    printTestResult("Copy constructor (content)", copyElementsTest);
    cout << "  - Expected elements: 1 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s2.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= (copyConstructorTest && copyElementsTest);

    // Clear test
    s2.Clear();
    bool clearTest = (s2.Size() == 0 && s2.Empty());
    printTestResult("Clear", clearTest);
    cout << "  - Expected size: 0, Actual size: " << s2.Size() << endl;
    allTestsPassed &= clearTest;

    cout << "Overall constructors and basic operations test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

template <typename SetType>
void testOrderedDictionaryOperations() {
    cout << "\n=== OrderedDictionary Operations Test ===" << endl;
    bool allTestsPassed = true;

    SetType s;
    // Element insertion for tests
    int values[] = {10, 5, 15, 3, 7, 12, 20};
    for (int val : values) {
        s.Insert(val);
    }

    cout << "Test set: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    // Min and Max test
    bool minTest = (s.Min() == 3);
    bool maxTest = (s.Max() == 20);
    printTestResult("Min", minTest);
    cout << "  - Expected Min: 3, Actual Min: " << s.Min() << endl;
    printTestResult("Max", maxTest);
    cout << "  - Expected Max: 20, Actual Max: " << s.Max() << endl;
    allTestsPassed &= (minTest && maxTest);

    // Predecessor and Successor test
    bool predecessorTest = (s.Predecessor(10) == 7);
    bool successorTest = (s.Successor(10) == 12);
    printTestResult("Predecessor(10)", predecessorTest);
    cout << "  - Expected Predecessor: 7, Actual Predecessor: " << s.Predecessor(10) << endl;
    printTestResult("Successor(10)", successorTest);
    cout << "  - Expected Successor: 12, Actual Successor: " << s.Successor(10) << endl;
    allTestsPassed &= (predecessorTest && successorTest);

    // MinNRemove test
    int minValue = s.MinNRemove();
    bool minNRemoveTest = (minValue == 3 && s.Size() == 6 && !s.Exists(3));
    printTestResult("MinNRemove", minNRemoveTest);
    cout << "  - Expected removed Min: 3, Actual removed Min: " << minValue << endl;
    cout << "  - Elements after MinNRemove: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= minNRemoveTest;

    // MaxNRemove test
    int maxValue = s.MaxNRemove();
    bool maxNRemoveTest = (maxValue == 20 && s.Size() == 5 && !s.Exists(20));
    printTestResult("MaxNRemove", maxNRemoveTest);
    cout << "  - Expected removed Max: 20, Actual removed Max: " << maxValue << endl;
    cout << "  - Elements after MaxNRemove: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= maxNRemoveTest;

    // PredecessorNRemove test
    int predValue = s.PredecessorNRemove(12);
    bool predNRemoveTest = (predValue == 10 && s.Size() == 4 && !s.Exists(10));
    printTestResult("PredecessorNRemove(12)", predNRemoveTest);
    cout << "  - Expected removed Predecessor: 10, Actual removed Predecessor: " << predValue << endl;
    cout << "  - Elements after PredecessorNRemove: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= predNRemoveTest;

    // SuccessorNRemove test
    int succValue = s.SuccessorNRemove(7);
    bool succNRemoveTest = (succValue == 12 && s.Size() == 3 && !s.Exists(12));
    printTestResult("SuccessorNRemove(7)", succNRemoveTest);
    cout << "  - Expected removed Successor: 12, Actual removed Successor: " << succValue << endl;
    cout << "  - Elements after SuccessorNRemove: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= succNRemoveTest;

    // RemoveMin test
    s.RemoveMin();
    bool removeMinTest = (s.Size() == 2 && !s.Exists(5) && s.Min() == 7);
    printTestResult("RemoveMin", removeMinTest);
    cout << "  - Elements after RemoveMin: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= removeMinTest;

    // RemoveMax test
    s.RemoveMax();
    bool removeMaxTest = (s.Size() == 1 && !s.Exists(15) && s.Max() == 7);
    printTestResult("RemoveMax", removeMaxTest);
    cout << "  - Elements after RemoveMax: ";
    s.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allTestsPassed &= removeMaxTest;

    cout << "Overall OrderedDictionary operations test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

template <typename SetType>
void testSetExceptions() {
    cout << "\n=== Exceptions Test ===" << endl;
    bool allTestsPassed = true;

    SetType emptySet;

    // Empty set exceptions test
    bool minExceptionTest = false;
    try {
        emptySet.Min();
        cout << "ERROR: Min did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        minExceptionTest = true;
        cout << "OK: Min threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Min() exception on empty set", minExceptionTest);

    bool maxExceptionTest = false;
    try {
        emptySet.Max();
        cout << "ERROR: Max did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        maxExceptionTest = true;
        cout << "OK: Max threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Max() exception on empty set", maxExceptionTest);

    bool removeMinExceptionTest = false;
    try {
        emptySet.RemoveMin();
        cout << "ERROR: RemoveMin did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        removeMinExceptionTest = true;
        cout << "OK: RemoveMin threw the expected exception: " << e.what() << endl;
    }
    printTestResult("RemoveMin() exception on empty set", removeMinExceptionTest);

    bool predecessorExceptionTest = false;
    try {
        emptySet.Predecessor(5);
        cout << "ERROR: Predecessor did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        predecessorExceptionTest = true;
        cout << "OK: Predecessor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Predecessor() exception on empty set", predecessorExceptionTest);

    // Non-empty set with missing elements exceptions
    SetType nonEmptySet;
    nonEmptySet.Insert(5);
    nonEmptySet.Insert(10);

    bool predecessorNotFoundTest = false;
    try {
        nonEmptySet.Predecessor(5); // 5 has no predecessor
        cout << "ERROR: Predecessor did not throw exception when no predecessor exists" << endl;
    } catch (const std::length_error& e) {
        predecessorNotFoundTest = true;
        cout << "OK: Predecessor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Predecessor() exception when no predecessor exists", predecessorNotFoundTest);

    bool successorNotFoundTest = false;
    try {
        nonEmptySet.Successor(10); // 10 has no successor
        cout << "ERROR: Successor did not throw exception when no successor exists" << endl;
    } catch (const std::length_error& e) {
        successorNotFoundTest = true;
        cout << "OK: Successor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Successor() exception when no successor exists", successorNotFoundTest);

    allTestsPassed &= (minExceptionTest && maxExceptionTest && removeMinExceptionTest &&
                     predecessorExceptionTest && predecessorNotFoundTest && successorNotFoundTest);

    cout << "Overall exceptions test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

template <typename SetType>
void testSetWithStrings() {
    cout << "\n=== Set with Strings Test ===" << endl;
    bool allTestsPassed = true;

    SetType stringSet;

    // String insertion
    stringSet.Insert("banana");
    stringSet.Insert("apple");
    stringSet.Insert("cherry");
    stringSet.Insert("date");

    bool sizeTest = (stringSet.Size() == 4);
    printTestResult("Size after string insertion", sizeTest);
    cout << "  - Expected size: 4, Actual size: " << stringSet.Size() << endl;

    // Verify alphabetical order
    string expectedOrder[] = {"apple", "banana", "cherry", "date"};
    bool orderTest = true;
    for (unsigned long i = 0; i < stringSet.Size(); i++) {
        if (stringSet[i] != expectedOrder[i]) {
            orderTest = false;
            break;
        }
    }
    printTestResult("Alphabetical order", orderTest);
    cout << "  - Expected elements: apple banana cherry date" << endl;
    cout << "  - Actual elements: ";
    stringSet.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    // Specific operations test
    bool minTest = (stringSet.Min() == "apple");
    bool maxTest = (stringSet.Max() == "date");
    printTestResult("Min (first string alphabetically)", minTest);
    cout << "  - Expected Min: apple, Actual Min: " << stringSet.Min() << endl;
    printTestResult("Max (last string alphabetically)", maxTest);
    cout << "  - Expected Max: date, Actual Max: " << stringSet.Max() << endl;

    bool predecessorTest = (stringSet.Predecessor("cherry") == "banana");
    bool successorTest = (stringSet.Successor("banana") == "cherry");
    printTestResult("Predecessor of 'cherry'", predecessorTest);
    cout << "  - Expected Predecessor: banana, Actual Predecessor: " << stringSet.Predecessor("cherry") << endl;
    printTestResult("Successor of 'banana'", successorTest);
    cout << "  - Expected Successor: cherry, Actual Successor: " << stringSet.Successor("banana") << endl;

    allTestsPassed &= (sizeTest && orderTest && minTest && maxTest && predecessorTest && successorTest);
    cout << "Overall strings test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

template <typename SetType>
void testConstructorFromContainers() {
    cout << "\n=== Constructors from Containers Test ===" << endl;
    bool allTestsPassed = true;

    // Create a list with duplicates and unsorted values
    List<int> list;
    list.InsertAtBack(5);
    list.InsertAtBack(3);
    list.InsertAtBack(7);
    list.InsertAtBack(3); // Duplicate
    list.InsertAtBack(1);
    list.InsertAtBack(5); // Duplicate

    // TraversableContainer constructor test
    SetType setFromList(list);
    bool sizeTest = (setFromList.Size() == 4); // Only 4 unique elements
    printTestResult("TraversableContainer constructor (duplicate removal)", sizeTest);
    cout << "  - Expected size: 4, Actual size: " << setFromList.Size() << endl;

    // Verify order
    int expectedOrder[] = {1, 3, 5, 7};
    bool orderTest = true;
    for (unsigned long i = 0; i < setFromList.Size(); i++) {
        if (setFromList[i] != expectedOrder[i]) {
            orderTest = false;
            break;
        }
    }
    printTestResult("Element order after construction from TraversableContainer", orderTest);
    cout << "  - Expected elements: 1 3 5 7" << endl;
    cout << "  - Actual elements: ";
    setFromList.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allTestsPassed &= (sizeTest && orderTest);
    cout << "Overall constructors from containers test result: " << (allTestsPassed ? "SUCCESS" : "FAILURE") << endl;
}

void runSetLstTests() {
    cout << "\n======= TESTS FOR SETLST CLASS =======" << endl;

    testSetConstructorsAndBasicOperations<SetLst<int>>();
    testOrderedDictionaryOperations<SetLst<int>>();
    testSetExceptions<SetLst<int>>();
    testSetWithStrings<SetLst<string>>();
    testConstructorFromContainers<SetLst<int>>();

    cout << "\n======= END OF SETLST TESTS =======" << endl;
}

void runSetVecTests() {
    cout << "\n======= TESTS FOR SETVEC CLASS =======" << endl;

    testSetConstructorsAndBasicOperations<SetVec<int>>();
    testOrderedDictionaryOperations<SetVec<int>>();
    testSetExceptions<SetVec<int>>();
    testSetWithStrings<SetVec<string>>();
    testConstructorFromContainers<SetVec<int>>();

    cout << "\n======= END OF SETVEC TESTS =======" << endl;
}

void compareSetImplementations() {
    cout << "\n======= IMPLEMENTATION COMPARISON =======" << endl;

    // Create two sets with the same elements
    SetLst<int> setLst;
    SetVec<int> setVec;

    // Generate random numbers for insertion
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 1000);

    const int numElements = 1000;

    // Insert the same elements in both sets
    cout << "Inserting " << numElements << " elements in both implementations..." << endl;

    for (int i = 0; i < numElements; i++) {
        int value = distr(gen);
        setLst.Insert(value);
        setVec.Insert(value);
    }

    cout << "SetLst size: " << setLst.Size() << endl;
    cout << "SetVec size: " << setVec.Size() << endl;

    // Verify equivalent functionality
    bool sameSizeTest = (setLst.Size() == setVec.Size());
    printTestResult("Same size after random insertions", sameSizeTest);

    // Verify Min, Max
    bool sameMinTest = (setLst.Min() == setVec.Min());
    bool sameMaxTest = (setLst.Max() == setVec.Max());
    printTestResult("Same minimum value", sameMinTest);
    cout << "  - SetLst Min: " << setLst.Min() << ", SetVec Min: " << setVec.Min() << endl;
    printTestResult("Same maximum value", sameMaxTest);
    cout << "  - SetLst Max: " << setLst.Max() << ", SetVec Max: " << setVec.Max() << endl;

    cout << "\n======= END OF COMPARISON =======" << endl;
}


void runVectorTests() {
    cout << "\n======= TESTS FOR VECTOR CLASS =======" << endl;

    testVectorConstructors();
    testVectorOperations();
    testVectorExceptions();
    testVectorTraverseAndMap();
    testVectorFold();
    testSortableVector();

    cout << "\n======= END OF VECTOR TESTS =======" << endl;
}


void runListTests() {
    cout << "\n======= TESTS FOR LIST CLASS =======" << endl;

    testListConstructors();
    testListOperations();
    testListMap();
    testListExceptions();
    testListWithStrings();
    testListFold();

    cout << "\n======= END OF LIST TESTS =======" << endl;
}



// Main menu
void mytest() {
    bool selection = false;
    while (!selection) {
        auto testtype = 0;
        cout << endl
                << "======================" << endl
             << "           TEST MENU " << endl
             << "1. LasdTest" << endl
             << "2. MyTest" << endl
             << "0. Exit" << endl
             << "======================" << endl;           
        cout << "Select test type -> ";
        string input;
        cin >> input;
        testtype = stoi(input);
        switch (testtype) {
            case 0:
                selection = true;
                break;
            case 1:
                lasdtest();
                break;
            case 2:
                runListTests();
                runVectorTests();
                runSetLstTests();
                runSetVecTests();
                compareSetImplementations();
                break;
            default:
                cout << "Invalid input" << endl;
        }
    }
}