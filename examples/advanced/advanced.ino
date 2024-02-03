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
