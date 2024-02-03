#include <DoublyLinkedList.h>

void printElement(String s)
{
    Serial.print(s);
    Serial.print(" ");
}
void printElement(int s)
{
    Serial.print(s);
    Serial.print(" ");
}

void printError(const String &test, const String &out = "")
{
    Serial.print("ERROR: ");
    Serial.print(test);
    Serial.print(" ");
    Serial.println(out);
}

void printSuccess(const String &test, const String &out = "")
{
    Serial.print("SUCCESS: ");
    Serial.print(test);
    Serial.println(out);
}

bool testInsert()
{
    DoublyLinkedList<int> list;

    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(7);
    list.insert(1, 0);
    list.insert(6, 5);

    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] != i + 1)
        {
            printError("testInsert", "list[" + String(i) + "] must be " + String(i + 1));
            return false;
        }
    }

    if (list.getCursorPosition() != 1)
    {
        printError("testInsert", "cursor position must be 1");
        return false;
    }

    if (list.getCursorValue() != 2)
    {
        printError("testInsert", "cursor value must be 2");
        return false;
    }

    list.shiftCursor(2);
    if (list.getCursorPosition() != 3)
    {
        printError("testInsert", "cursor position must be 3");
        return false;
    }

    if (list.getCursorValue() != 4)
    {
        printError("testInsert", "cursor value must be 4");
        return false;
    }
    list.setCursorAt(1);
    if (list.getCursorPosition() != 1)
    {
        printError("testInsert", "cursor position must be 1");
        return false;
    }

    if (list.getCursorValue() != 2)
    {
        printError("testInsert", "cursor value must be 2");
        return false;
    }

    printSuccess("testInsert");
    return true;
}

bool testRemoveAt()
{
    DoublyLinkedList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.removeAt(2);
    for (int i = 0; i < 2; i++)
    {
        if (list[i] != i + 1)
        {
            printError("testRemoveAt", "list[" + String(i) + "] must be " + String(i + 1) + " and not " + String(list[i]));
            return false;
        }
    }

    for (int i = 3; i < list.size(); i++)
    {
        if (list[i] != i + 2)
        {
            printError("testRemoveAt", "list[" + String(i) + "] must be " + String(i + 2));
            return false;
        }
    }
    printSuccess("testRemoveAt");
    return true;
}

String replace(String e)
{
    return e == "Ciao" ? "Hello" : e;
}

bool testReplaceAll()
{
    DoublyLinkedList<String> list;

    list.insert("Hi");
    list.insert("Wei");
    list.insert("Bye");
    list.insert("Ciao");

    DoublyLinkedList<String> mappedList = list.map(replace);

    if (mappedList[-1] != "Hello")
    {
        printError("testReplaceAll", "list[-1] must be \"Hello\"");
        return false;
    }
    printSuccess("testReplaceAll");
    return true;
}

bool concat()
{
    DoublyLinkedList<int> list1(true);

    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    list1.insert(5);
    list1.insert(6);

    DoublyLinkedList<int> list2;

    list2.insert(7);
    list2.insert(8);
    list2.insert(9);
    list2.insert(10);

    DoublyLinkedList<int> list3;

    list3.insert(11);
    list3.insert(12);
    list3.insert(13);
    list3.insert(14);

    list1 += list2;
    list1 += list3;
    list2.clear();
    list3.clear();
    for (int i = 0; i < list1.size(); i++)
    {
        if (list1[i] != i + 1)
        {
            printError("testInsert", "list[" + String(i) + "] must be " + String(i + 1));
            return false;
        }
    }
    printSuccess("concat");
    return true;
}

uint16_t numTestRunned = 0;

void printTestInfo()
{
    Serial.print("TEST RUNNED: ");
    Serial.println(numTestRunned);
}

void runTest(bool (*func)(void))
{
    numTestRunned++;
    bool status = func();
    if (!status)
    {
        printTestInfo();
        while (true)
            ;
    }
}

void setup()
{
    Serial.begin(115200);
    runTest(testInsert);
    runTest(testRemoveAt);
    runTest(testReplaceAll);
    runTest(concat);
    printTestInfo();
    Serial.print("ALL TEST SUCCESS");
}

void loop()
{
}
