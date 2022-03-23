#include <iostream>
#include <assert.h>
using namespace std;

//--------------------------------Patient class-------------------------------------------
class patient
{
public:
    patient();
    int em_ID;
    string pname;
    string address;
    unsigned int contact;

    bool operator ==(const patient& p);
    bool  operator >=(const patient& compareditem);
    patient operator =(const patient& p);
    void print();
    friend ostream& operator<<(ostream& out, const patient& pat);
};
patient::patient() //Patient constructor
{
    em_ID = NULL;
    pname = " ";
    address = " ";
    contact = NULL;
}
void patient::print() //print patient
{
    cout << "Emirates id: " << em_ID << endl;
    cout << "patient's name: " << pname << endl;
    cout << "address: " << address << endl;
    cout << "contact: " << contact << endl;
}
bool patient:: operator ==(const patient& p)
{
    if (em_ID == p.em_ID && pname == p.pname && address == p.address && contact == p.contact)
        return true;
    else
        return false;
}
patient patient:: operator =(const patient& p)
{
    em_ID = p.em_ID;
    pname = p.pname;
    address = p.address;
    contact = p.contact;
    return *this;

}
bool  patient::operator >=(const patient& compareditem)
{
    return(em_ID >= compareditem.em_ID);
}
ostream& operator<<(ostream& out, const patient& pat) //overload cout to be able to print it in the main 
{
    out << "Emirates ID: " << pat.em_ID << endl << "patient's name: " << pat.pname << endl << "Address: " << pat.address << endl << "contact: " << pat.contact << endl << endl;
    return out;
}

//--------------------------------NodeType and Ordered Linked List---------------------------------   
template<class type>
struct nodetype
{
    type info;
    nodetype<type>* link;
};
template<class type>
class orderedLinkedList
{
public:
    orderedLinkedList();//constructor
    ~orderedLinkedList();//destructor
    orderedLinkedList(const orderedLinkedList<type>& copy); //copy constructor
    void Initialize_list();
    bool isFull() const;
    bool isEmpty() const;
    void print() const;
    unsigned int listSize();
    bool search(const type& searchItem) const;
    type front();
    type back();
    void destroyList();
    void deleteItem(const type& deleteItem);
    void insertFront(const type& newItem);
    void insertBack(const type& newItem);
    bool  operator ==(const orderedLinkedList<type>& compareditem);//comparing operator
    const orderedLinkedList<type>& operator = (const orderedLinkedList<type>&); //assignment operator
protected:
    unsigned int count;
    nodetype<type>* first;
    nodetype<type>* last;
private:
    void insert(const type& newItem);
    void copylist(const orderedLinkedList<type>& otherList);
};


template <class type> // Constructor 
orderedLinkedList<type>::orderedLinkedList()
{
    first = NULL;
    last = NULL;
    count = 0;
}

template <class type> // destructor 
orderedLinkedList<type>::~orderedLinkedList()
{
    destroyList();
}


template<class type>
void orderedLinkedList<type>::Initialize_list()
{
    destroyList();
}

//2
template<class type>
bool orderedLinkedList<type> ::isEmpty() const
{
    return(first == NULL);
}
template<class type>
bool orderedLinkedList<type> ::isFull() const
{
    return false; //Linked list can never be full unless i put a size for it but I dont see a point for putting a size so it will always return false
}




template<class type>
void orderedLinkedList<type>::print() const
{
    nodetype<type>* temp;
    if (first == NULL)
        cout << "No element in list " << endl;
    else
    {
        temp = first;
        while (temp != NULL)
        {
            cout << temp->info;
            temp = temp->link;
        }
    }
}
template<class type>
unsigned int orderedLinkedList<type>::listSize()
{
    return count;
}
template<class type>
bool orderedLinkedList<type>::search(const type& searchItem) const
{
    bool found = false;
    nodetype<type>* current;
    current = first;
    while (current != NULL && !found)
        if (current->info >= searchItem)
            found = true;
        else
            current = current->link;
    if (found)
        found = (current->info == searchItem); //test for equality
    return found;
}
template<class type>
void orderedLinkedList<type>::destroyList()
{
    nodetype<type>* temp;
    while (first != NULL)
    {
        temp = first;
        first = first->link;
        delete temp;
    }
    last = NULL;
    count = 0;
}
template<class type>
type orderedLinkedList<type>::front()
{
    assert(first != NULL);
    return first->info;
}
template<class type>
type orderedLinkedList<type>::back()
{
    assert(last != NULL);
    return last->info;
}
template<class type>
void orderedLinkedList<type>::insertFront(const type& newItem) //since it is an ordered list we shouldnt insert at front or back but we should see where the item fits and then add it so this is why i call the insert function in both insertfirst and insertback
{
    insert(newItem);
}
template<class type>
void orderedLinkedList<type>::insertBack(const type& newItem)
{
    insert(newItem);
}
template <class type>
void orderedLinkedList<type>::insert(const type& newItem)
{
    nodetype<type>* current;
    nodetype<type>* trailCurrent = NULL;
    nodetype<type>* newNode;
    bool found;
    newNode = new nodetype<type>;
    newNode->info = newItem;
    newNode->link = NULL;
    if (first == NULL)
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else
    {
        current = first;
        found = false;
        while (current != NULL && !found)
            if (current->info >= newItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }
        if (current == first)
        {
            newNode->link = first;
            first = newNode;
            count++;
        }
        else
        {
            trailCurrent->link = newNode;
            newNode->link = current;
            if (current == NULL)
                last = newNode;
            count++;
        }
    }
}
template <class type>
void orderedLinkedList<type>::deleteItem(const type& deleteItem)
{
    nodetype<type>* current;
    nodetype<type>* trailCurrent = NULL;
    bool found;
    if (first == NULL)
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        current = first;
        found = false;
        while (current != NULL && !found)
            if (current->info >= deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }
        if (current == NULL)
            cout << "The item to be deleted is not in the list." << endl;
        else
            if (current->info == deleteItem)
            {
                if (first == current)
                {
                    first = first->link;
                    if (first == NULL)
                        last = NULL;
                    delete current;
                }
                else
                {
                    trailCurrent->link = current->link;
                    if (current == last)
                        last = trailCurrent;
                    delete current;
                }
                count--;
            }
            else
                cout << "The item to be deleted is not in the list." << endl;
    }
}
template <class type>
void orderedLinkedList<type>::copylist(const orderedLinkedList<type>& otherList)
{
    nodetype<type>* newNode;
    nodetype<type>* current;
    if (first != NULL)
        destroyList();
    if (otherList.first == NULL)
    {
        first = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
        current = otherList.first;
        count = otherList.count;
        first = new nodetype<type>;
        first->info = current->info;
        first->link = NULL;
        last = first;
        current = current->link;
        while (current != NULL)
        {
            newNode = new nodetype<type>;
            newNode->info = current->info;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }

}
template<class type>
bool orderedLinkedList<type>::operator==(const orderedLinkedList<type>& comparedList)
{
    nodetype<type>* current;
    nodetype<type>* currentC;
    current = first;
    currentC = comparedList.first;
    bool equal = false;

    if (count != comparedList.count)
    {
        return false;
    }
    else
    {
        if (first == NULL)
            return true;
        else
        {
            while ((current->info) == (currentC->info))
            {
                current = current->link;
                currentC = currentC->link;
                if (current == NULL && currentC == NULL)
                    return true;
            }
            return false;
        }
    }
}

template<class type>
const orderedLinkedList<type>& orderedLinkedList<type>::operator=(const orderedLinkedList<type>& copy)
{
    if (this != &copy)
    {
        copylist(copy);
    }
    return *this;
}

template<class type>
orderedLinkedList<type>::orderedLinkedList(const orderedLinkedList<type>& copy)
{
    first = NULL;
    copylist(copy);
}







//----------------------------------MAIN---------------------------------------------
int main()
{

    orderedLinkedList<patient> list1, list2, list3;
    patient patient1, patient2, patient3, patient4, patient5;

    patient1.em_ID = 12345;
    patient1.pname = "Mohammed";
    patient1.address = "Ajman";
    patient1.contact = 6812323;

    patient2.em_ID = 12346;
    patient2.pname = "Ayman";
    patient2.address = "sharjah";
    patient2.contact = 6812525;

    patient3.em_ID = 12347;
    patient3.pname = "Ahmed";
    patient3.address = "Dubai";
    patient3.contact = 6812626;

    cout << "lets test if list1 is empty before adding any nodes, is list1 empty?" << list1.isEmpty() << endl << endl;
    list1.insertFront(patient1);
    list1.insertBack(patient2);
    list1.insertBack(patient3);
    list1.print();
    cout << "lets test if list1 is it full after adding these  nodes to the list, is list1 full?" << list1.isFull() << endl << "of course it cant be full silly because that is the whole point of linked lists but you can set a max size for it but i dont see a point of doing that :)" << endl;
    list3.insertBack(patient2);
    list3.insertBack(patient3);

    patient4 = list1.front();
    cout << "The first element in the list info is: " << endl;
    patient4.print();
    cout << endl;

    patient5 = list1.back();
    cout << "The last element in the list info is: " << endl;
    patient5.print();
    cout << endl;

    cout << "is patient1 there? " << list1.search(patient1) << endl;

    list1.deleteItem(patient3);
    cout << "List after deleting patient3 is: " << endl;
    list1.print();

    cout << "Is the  patient3 in the list? " << list1.search(patient3) << endl;

    list2 = list1;
    cout << "List 1 is: " << endl;
    list1.print();
    cout << "List 2 is: " << endl;
    list2.print();

    cout << "Size of list1 is :" << list1.listSize() << endl;
    bool equal;
    equal = list1 == list2;
    cout << "is list1==list2?" << equal << endl;

    equal = list1 == list3;
    cout << "is list1==list3?" << equal << endl;

    cout << "List 1 after destroying it is: " << endl;
    list1.destroyList();
    list1.print();

    return 0;
}
