#include "../../includes/Bitchain/bitchain.h"

//? @defgroup: Helpers
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: addKey(const Key&)
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

    return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: removeKey(const string)
bool Bitchain::rmKey(const string target)
{
    //* @note: only one key is stored & is target
    if (head == tail && head->getKey().getKeyname() == target)
    {
        delete head;
        head = tail = nullptr;

        return true;
    }

    Node *copy = head, *prv = nullptr;

    //* @note: first element in keychain is the target
    if (copy->getKey().getKeyname() == target)
    {
        head = head->getNext();
        head->setPrev(tail);
        tail->setNext(head);

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
//^ @protected: searchKey(const string)
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
////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: showKey(const string)
bool Bitchain::showKey(const string target)
{
    Node *copy = head;

    if (copy == nullptr)
        return false;
    if (!searchKey(target))
        return false;
    if (copy->getKey().getKeyname() == target)
    {
        cout << copy->getKey() << endl;
        return true;
    }

    copy = copy->getNext();
    while (copy != head)
    {
        if (copy->getKey().getKeyname() == target)
        {
            cout << copy->getKey() << endl;
            return true;
        }
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Resources
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: Bitchain(void)
Bitchain::Bitchain(void) : head(nullptr), tail(nullptr) { return; }

//? @public: Bitchain(const Bitchain&)
Bitchain::Bitchain(const Bitchain &bitchain) : head(bitchain.head), tail(bitchain.tail) { return; }
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: ~Bitchain(void)
Bitchain::~Bitchain(void)
{
    if (head == tail && tail == nullptr)
        return;

    Node *tmp = head, *nxt = nullptr;

    do
    {
        nxt = tmp->getNext();
        delete tmp;
        tmp = nxt;
    } while (tmp != head);

    return;
}
////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Functions
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: add(const Key&)
bool Bitchain::add(const Key &key)
{
    if (addKey(key))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: remove(const string)
bool Bitchain::remove(const string target)
{
    if (rmKey(target))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: search(const string)
bool Bitchain::search(const string target)
{
    if (searchKey(target))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: show(const string)
bool Bitchain::show(const string target)
{
    if (showKey(target))
        return true;

    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: isEmpty(void)
bool Bitchain::isEmpty(void)
{
    if (head == tail && tail == nullptr)
        return false;

    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: save(ofstream&)
bool Bitchain::save(ofstream &writefile)
{
    //* @note: file validation
    if (!FileValidation(writefile))
    {
        cerr << "Bitchain File failed to open" << endl;
        return false;
    }

    if (head == nullptr)
        return true;

    Node *copy = head;
    writefile << copy->getKey().getKeyname() << "," << copy->getKey().getUsername() << "," << copy->getKey().getEmail() << "," << copy->getKey().getPassword() << endl;

    copy = copy->getNext();
    while (copy != head)
    {
        writefile << copy->getKey().getKeyname() << "," << copy->getKey().getUsername() << "," << copy->getKey().getEmail() << "," << copy->getKey().getPassword() << endl;
        copy = copy->getNext();
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: load(ifstream&)
bool Bitchain::load(ifstream &readfile)
{
    //* @note: file validation
    if (!FileValidation(readfile))
    {
        cerr << "Bitchain File failed to open" << endl;
        return false;
    }

    string line;
    while (getline(readfile, line))
    {
        stringstream currentline(line);
        string field;

        string nKeyname, nUsername, nEmail, nPassword;

        if (getline(currentline, nKeyname, ',') && getline(currentline, nUsername, ',') && getline(currentline, nEmail, ',') && getline(currentline, nPassword))
        {
            Key key(nKeyname, {nUsername, nPassword, nEmail});
            if (!addKey(key))
                cerr << "<error>=adding_key" << endl;
        }
    }

    readfile.close();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Overloads
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: operator<<(ostream&, const Bitchain&)
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
////////////////////////////////////////////////////////////////////////////////////////////
//* @public: operator=(const Bitchain&)
Bitchain &Bitchain::operator=(const Bitchain &other)
{
    this->head = other.head;
    this->tail = other.tail;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////
