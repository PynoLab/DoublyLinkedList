#include <DoublyLinkedList.h>

void printElement(int e)
{
  Serial.print(e);
  Serial.print(" ");
}

void setup()
{
  Serial.begin(9600);

  DoublyLinkedList<int> list(true);

  list.insert(1);
  list.insert(2);
  list.insert(3);
  list.insert(4);
  list.insert(5);
  list.insert(6);
  list.insert(7);
  list.insert(8);

  list.removeAt(-1);

  list.remove(2);

  list.foreach (printElement);
  Serial.println();
}

void loop()
{
}
