#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

struct intLink
{
    int value;
    intLink* next;
};

unsigned int count(intLink* header)
{
    unsigned int count = 0;
    intLink* position = header;

    while (position != nullptr)
    {
        count++;
        position = (*position).next;
    }

    return count;
}


void printLinkedList(intLink* header)
{
    cout << "...now printing out the linked list, with " << count(header) << " members..." << endl;
    intLink* position = header;

    while (position != nullptr)
    {
        cout << "value: " << (*position).value << " next: " << (*position).next << endl;
        position = (*position).next;
    }

    cout << "...finished printing out linked list..." << endl;
}


intLink* createNewLink(int value)
{
    intLink *newLink = new intLink;
    (*newLink).value = value;
    (*newLink).next = nullptr;

    return newLink;
}

intLink* createNewLink(int value, intLink* next)
{
    intLink* newLink = createNewLink(value);
    (*newLink).next = next;

    return newLink;
}

intLink* createNewLink(intLink* previous, int value)
{

    intLink* newLink = createNewLink(value);
    (*newLink).next = nullptr;
    (*previous).next = newLink;

    return newLink;
}

intLink* createNewLink(intLink* previous, int value, intLink* next)
{
    intLink* newLink = createNewLink(value, next);
    assert((*newLink).next == next);
    (*previous).next = newLink;

    return newLink;
}

intLink* findTail(intLink* header)
{
    if (header == nullptr)
    {
        return nullptr;
    }

    intLink* position = header;

    while ((*position).next != nullptr)
    {
        position = (*position).next;
    }

    return position;
}

void add(intLink* header, int value)
{
    intLink* tail = findTail(header);

    assert(tail != nullptr);

    createNewLink(tail, value);
}

intLink* insert(intLink* header, unsigned int index, int value) //have to return header as inserting at start changes the header
{
    assert(count(header) >= index);

    if (index == 0)
    {
        //insert at start
        intLink* newLink = createNewLink(value);
        (*newLink).next = header;
        header = newLink;
    }
    else if (count(header) == index)
    {
        //insert at the end
        add(header, value);
    }
    else
    {
        unsigned int loc = 1; //start at one, because if index is 1, want to add right after the header
        intLink* position = header;

        while (loc < index)
        {
            loc++;
            position = (*position).next;
        }

        intLink* next = (*position).next;
        intLink* newLink = createNewLink(position, value, next);
    }

    return header;
}

intLink* removeByIndex(intLink* header, unsigned int index)
{
    assert(index >= 0 && index < count(header));

    if (index == 0)
    {
        intLink* newHeader = (*header).next;

        (*header).next = nullptr;
        delete header;

        return newHeader;
    }

    unsigned int loc = 0;
    intLink* currentPosition = header;
    intLink* previousPosition = nullptr;

    while (loc < index)
    {
        loc++;
        previousPosition = currentPosition;
        currentPosition = (*currentPosition).next;
    }

    intLink* nextPosition = (*currentPosition).next;
    (*previousPosition).next = nextPosition;

    delete currentPosition;

    return header;
}


intLink* removeByValue(intLink* header, int valueToRemove)
{

    if ((*header).value == valueToRemove)
    {
        intLink* temp = header;
        header = (*header).next;
        delete temp;

        return header;
    }

    intLink* positionBeforeRemoval = header;

    while (positionBeforeRemoval != nullptr && (*(*positionBeforeRemoval).next).value != valueToRemove)
    {
        positionBeforeRemoval = (*positionBeforeRemoval).next;
    }

    if (positionBeforeRemoval != nullptr)
    {
        intLink* toRemove = (*positionBeforeRemoval).next;
        intLink* afterRemoval = (*toRemove).next;
        (*positionBeforeRemoval).next = afterRemoval;

        delete toRemove;
    }

    return header;
}



int main()
{
    cout << "starting....\n" << endl;

    intLink* header = nullptr;

    assert(count(header) == 0);
    printLinkedList(header);

    cout << "creating header" << endl;

    header = createNewLink(0);
    printLinkedList(header);

    assert(count(header) == 1);

    cout << "adding 3 links" << endl;
    add(header, 1);
    add(header, 2);
    add(header, 5);

    assert(count(header) == 4);
    printLinkedList(header);

    cout << "insert at start" << endl;
    header = insert(header, 0, -1);
    assert(count(header) == 5);
    printLinkedList(header);

    cout << "insert at end" << endl;
    header = insert(header, count(header), 7);
    assert(count(header) == 6);
    printLinkedList(header);

    cout << "insert at index" << endl;
    header = insert(header, 4, 3);
    header = insert(header, 6, 6);
    header = insert(header, 5, 4);
    header = insert(header, 1, 0);
    assert(count(header) == 10);
    printLinkedList(header);


    cout << "remove by index" << endl;
    header = removeByIndex(header, 0);
    header = removeByIndex(header, 8);
    header = removeByIndex(header, 1);
    assert(count(header) == 7);
    printLinkedList(header);

    cout << "remove by value" << endl;
    header = removeByValue(header, 0);
    header = removeByValue(header, 6);
    header = removeByValue(header, 3);
    assert(count(header) == 4);
    printLinkedList(header);

    cout << "\nfinished" << endl;

    return 0;
}