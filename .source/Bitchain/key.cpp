#include "../../includes/Bitchain/key.h"

//& @struct: Data
// TODO - @defgroup: Overloads
//////////////////////////////////////////////////////
//* @public: Key(const string, const Data)
ostream &operator<<(ostream &out, const Data &data)
{
    out << "Username: " << data.username << endl
        << "Email: " << data.email << endl
        << "Password: " << data.password << endl;

    return out;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: operator=(const Data)
Data &Data::operator=(const Data &data)
{
    this->username = data.username;
    this->password = data.password;
    this->email = data.email;

    return *this;
}
//////////////////////////////////////////////////////

//& @class: Key
// TODO - @defgroup: Resources
//////////////////////////////////////////////////////
//* @public: Key(const string, const Data)
Key::Key(const string keyname, const Data keydata) : name(keyname)
{
    data = keydata;
    return;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: ~Key(void)
Key::~Key(void)
{
    return;
}
//////////////////////////////////////////////////////

// TODO - @defgroup: Mutators
//////////////////////////////////////////////////////
//* @public: setKeyname(const string)
void Key::setKeyname(const string keyname)
{
    name = keyname;
    return;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: setUsername(const string)
void Key::setUsername(const string username)
{
    data.username = username;
    return;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: setPassword(const string)
void Key::setPassword(const string password)
{
    data.password = password;
    return;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: setEmail(const string)
void Key::setEmail(const string email)
{
    data.email = email;
    return;
}
//////////////////////////////////////////////////////

// TODO - @defgroup: Accessors
//////////////////////////////////////////////////////
//* @public: getKeyname(void)
const string Key::getKeyname(void) { return name; }
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: getUsername()
const string Key::getUsername(void) { return data.username; }
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: getPassword()
const string Key::getPassword(void) { return data.password; }
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: getEmail()
const string Key::getEmail(void) { return data.email; }
//////////////////////////////////////////////////////

// TODO - @defgroup: Overloads
//////////////////////////////////////////////////////
//* @public: operator=(const Key&)
Key &Key::operator=(const Key &other)
{
    this->name = other.name;
    this->data = other.data;
    return *this;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//* @public: operator<<(ostream&, const Key&)
ostream &operator<<(ostream &out, const Key &key)
{
    out << "Keyname - " << key.name << endl
        << "--------------------------------------------------------------" << endl
        << "Contents" << endl
        << "\tUsername:\t" << key.data.username << endl
        << "\tEmail:\t\t" << key.data.email << endl
        << "\tPassword:\t" << key.data.password << endl
        << "--------------------------------------------------------------";

    return out;
}
//////////////////////////////////////////////////////