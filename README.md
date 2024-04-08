# DoublyLinkedList

## Description

The `DoublyLinkedList` class implements a doubly linked list. Each element in the list is represented by an object of type `Node`. The list can be either circular or non-circular, depending on the configuration. The class provides a set of operations for insertion, removal, and manipulation of elements in the list. Additionally, the class features a cursor, allowing for easy navigation through the list.

It is possible to use negative indices for backward traversal. For example, `list[-1]` retrieves the last element of the list.

Moreover, the DoublyLinkedList class offers functions for easily obtaining a new list using methods such as map or filter, leveraging functional programming techniques.

### Example

```cpp
#include <DoublyLinkedList.h>

// Function to print an element
void printElement(int e)
{
  Serial.print(e);
  Serial.print(" ");
}

// Function to calculate the cube of an element
int cube(int e)
{
  return e * e * e;
}

// Function to filter odd elements
bool oddFilter(int e)
{
  return e % 2;
}

void setup()
{
  Serial.begin(115200);

  // Create a circular doubly linked list
  DoublyLinkedList<int> list(true);

  // Insert elements into the list
  list.insert(1);
  list.insert(2);
  list.insert(3);
  list.insert(4);
  list.insert(5);
  list.insert(6);
  list.insert(7);
  list.insert(8);

  // Remove the last element in the list (negative index)
  list.removeAt(-1);

  // Remove element with value 2 from the list
  list.remove(2);

  // Create a new list by applying the cube function to each element
  DoublyLinkedList<int> mappedList = list.map(cube);

  Serial.println("Mapped list");
  // Print each element in the mapped list
  mappedList.foreach(printElement);
  Serial.println();

  // Create a new list by filtering out odd elements from the mapped list
  DoublyLinkedList<int> filteredList = mappedList.filter(oddFilter);

  Serial.println("Filtered list");
  // Print each element in the filtered list
  filteredList.foreach(printElement);
  Serial.println();

  Serial.println("Original list");
  // Print each element in the original list
  list.foreach(printElement);
  Serial.println();

  // Create a new list by concatenating the original, mapped, and filtered lists
  DoublyLinkedList<int> allList;
  allList += list;
  allList += mappedList;
  allList += filteredList;

  // Clear individual lists
  list.clear();
  mappedList.clear();
  filteredList.clear();

  Serial.println("All list concatenated");
  // Print each element in the concatenated list
  allList.foreach(printElement);
  Serial.println();

  // Clear the concatenated list
  allList.clear();
}

void loop()
{
}

```

## Constructor

### `DoublyLinkedList(bool circular = false) : circular(circular)`

The constructor takes a boolean parameter, which is false by default, and determines whether the list is circular or not.

## List Manipulation Operations

### `setIsCircular(bool value)`

Sets the circular flag for the list. If `value` is true, it makes the list circular; otherwise, it makes the list non-circular.

### `insert(const T value, int64_t index)`

Inserts a new element with the specified value at the given index in the list.

### `insert(const T value)`

Inserts a new element with the specified value at the end of the list.

### `size() const`

Returns the number of elements in the list.

### `removeAt(int64_t index)`

Removes the element at the specified index from the list.

### `remove(T value)`

Removes the first occurrence of the specified value from the list.

### `indexOf(T value) const`

Returns the index of the first occurrence of the specified value in the list.

### `set(int64_t index, T value)`

Modifies the value of the element at the specified index.

### `pop()`

Removes and returns the last element of the list.

### `getCursorValue() const`

Returns the value of the current element.

### `getCursorPosition() const`

Returns the position of the current element in the list.

### `shiftCursor(const int64_t offset)`

Shifts the cursor forward or backward by a specified number of positions.

### `setCursorAt(const int64_t pos)`

Sets the cursor to the specified position in the list.

### `clear()`

Completely empties the list.

## Transformation and Iteration Operations

### `filter(bool (*func)(T))`

It takes a function as a parameter, which returns a boolean and accepts a parameter of type T.

Executes a specified function on each element of the list.

### `map(T (*func)(T)) const`

It takes a function as a parameter, which returns a T type and accepts a parameter of type T.

Creates and returns a new list obtained by applying a specified function to each element of the list.

## Operators

### `+=`

Appends all elements from another list to the end of this list.

## Access Operators

### `operator[](const int64_t index) const`

Returns the value of the element at the specified index in the list.
