#include "../../includes/Bitchain/bitchain.h"

//^ @defgroup: Helpers Functions
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: addKey(const Key&) -- done
bool Bitchain::addKey(const Key &key)
{
    Node *newNode = new Node(key);
    bool flag = false;

    //* @note: both head & tail are empty
    if (head == nullptr && tail == nullptr)
    {
        head = tail = newNode;
        head->setPrev(tail);
        head->setNext(tail);

        flag = true;
    }
    //* @note: only head node contains data
    else if (head != nullptr && tail == head)
    {
        tail = newNode;
        tail->setNext(head);
        tail->setPrev(head);
        head->setPrev(tail);
        head->setNext(tail);

        flag = true;
    }
    //* @note: both head & tail occupied
    else
    {
        newNode->setPrev(tail);
        newNode->setNext(head);
        head->setPrev(newNode);
        tail->setNext(newNode);
        tail = newNode;

        flag = true;
    }

    if (flag)
        keys++;

    return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: removeKey(const string) -- done
bool Bitchain::rmKey(const string target)
{
    //* @note: only one key is stored & is target
    if (head == tail && head->getKey().getKeyname() == target)
    {
        delete head;
        head = tail = nullptr;
        keys = 0;

        return true;
    }

    Node *copy = head, *prv = nullptr;

    //* @note: first element in keychain is the target
    if (copy->getKey().getKeyname() == target)
    {
        head = head->getNext();
        head->setPrev(tail);
        tail->setNext(head);
        keys--;

        return true;
    }

    copy = head->getNext();
    while (copy != head)
    {
        //* @note: target found within chain
        if (copy->getKey().getKeyname() == target)
        {
            prv = copy->getPrev();
            prv->setNext(copy->getNext());
            copy->getNext()->setPrev(prv);
            keys--;

            if (copy == tail)
                tail = prv;

            delete copy;
            return true;
        }
        copy = copy->getNext();
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: searchKey(const string) -- done
bool Bitchain::searchKey(const string target)
{
    Node *copy = head;

    if (copy == nullptr)
        return false;
    if (copy->getKey().getKeyname() == target)
        return true;

    copy = copy->getNext();

    while (copy != head)
    {
        if (copy->getKey().getKeyname() == target)
            return true;

        copy = copy->getNext();
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Resources
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: Bitchain(void) -- done
Bitchain::Bitchain(void) : head(nullptr), tail(nullptr), keys(0) { return; }
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: ~Bitchain(void) -- done
Bitchain::~Bitchain(void)
{
    if (head == tail && tail == nullptr)
        return;

    Node *tmp = head, *nxt = nullptr;

    do
    {
        cout << "destroying " << tmp->getKey().getKeyname() << endl;
        nxt = tmp->getNext();
        delete tmp;
        tmp = nxt;
    } while (tmp != head);

    return;
}
////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Functions
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: add(const Key&) -- done
bool Bitchain::add(const Key &key)
{
    if (addKey(key))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: remove(const string) -- done
bool Bitchain::remove(const string target)
{
    if (rmKey(target))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: search(const string) -- done
bool Bitchain::search(const string target)
{
    if (searchKey(target))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: save(void)
bool Bitchain::save(void) { return false; }
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: wipe(void)
bool Bitchain::wipe(void) { return false; }
////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Mutators
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: setKeys(const int) -- done
void Bitchain::setKeys(const int nKeys) { keys = nKeys; }
////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Accessors
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: getKeys(void) -- done
int Bitchain::getKeys(void) { return keys; }
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: isEmpty(void) -- done
bool Bitchain::isEmpty(void)
{
    if (keys != 0)
        return false;

    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Overloads
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: operator<<(ostream&, const Bitchain&) -- done
ostream &operator<<(ostream &out, const Bitchain &bitchain)
{
    Node *copy = bitchain.head;

    if (!copy)
        out << "Bitchain Empty";
    else
    {
        out << copy->getKey();

        copy = copy->getNext();

        while (copy != bitchain.head)
        {
            out << endl
                << endl
                << copy->getKey();

            copy = copy->getNext();
        }
    }

    return out;
}
////////////////////////////////////////////////////////////////////////////////////////////
