#include "../../includes/Account/account.h"

//? @defgroup: Helpers
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//^ @protected: lookup(const string)
//^ @def: searches for target username in accounts.txt & stores the associated data

bool Account::lookup(const string target)
{
    //* @note: validate inputfile
    ifstream inputfile(".resources/Accounts/accounts.txt");
    if (!FileValidation(inputfile))
    {
        cout << "Account file failed to load" << endl;
        return false;
    }

    //* @note: begin file parsing
    string line;
    while (getline(inputfile, line))
    {
        stringstream currentline(line);
        string nUsername;

        if (getline(currentline, nUsername, ',') && nUsername == target)
        {
            //* @note: lookup hit, grab data
            string nPasskey, nKeys;
            getline(currentline, nPasskey, ',');
            getline(currentline, nKeys);

            //? @note: update account contents
            username = nUsername;
            passkey = nPasskey;
            keys = atoi(nKeys.c_str());

            return true;
        }
    }

    //! @note: lookup miss
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Resources
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: Account(const string, const string) -- done
Account::Account(const string newUsername, const string newPasskey) : username(newUsername), passkey(newPasskey), keys(0), bitchain() { return; }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: ~Account(void) -- done
Account::~Account(void) { return; }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @defgroup: Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: add(void) -- done
void Account::add(void)
{
    cin.ignore();
    //* @note: grab keyname, username, email, & password
    string keyname, username, email, password;
    do
    {
        cout << "Keyname: ";
        getline(cin, keyname);

        if (keyname.empty())
        {
            keyname = "keyname";
            break;
        }
    } while (!InputValidation(keyname));
    do
    {
        cout << "Username: ";
        getline(cin, username);

        if (username.empty())
        {
            username = "username";
            break;
        }
    } while (!InputValidation(username));
    do
    {
        cout << "Email: ";
        getline(cin, email);

        if (email.empty())
        {
            email = "email";
            break;
        }
    } while (!InputValidation(email));
    do
    {
        cout << "Password: ";
        HideTerminal();
        getline(cin, password);
        ShowTerminal();

        if (password.empty())
        {
            password = "password";
            break;
        }
    } while (!InputVerification(password));

    //* @note: pass user input into key object
    Key key(keyname, {username, password, email});

    //* @note: add key to bitchain
    cout << "Add Key | ";
    if (ConfirmOperation())
    {
        bitchain.add(key);
        keys++;
        cout << "Added '" << keyname << "'" << endl;
    }
    else
        cout << "Operation Terminated" << endl;

    return;
}
//* @public: add(const Key&) -- done
void Account::add(const Key &key)
{
    bitchain.add(key);
    keys++;
    cout << "Added Key" << endl;
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: remove(void) -- done
void Account::remove(void)
{
    cin.ignore();

    //* @note: grab target keyname to remove
    string target;
    do
    {
        cout << "Target: ";
        getline(cin, target);

        //! @note: target not given
        if (target.empty())
        {
            cout << "Target not specified" << endl;
            return;
        }
    } while (!InputValidation(target));

    //* @note: search for target
    if (bitchain.search(target))
    {
        cout << "Remove Key | ";
        if (ConfirmOperation())
        {
            bitchain.remove(target);
            keys--;
            cout << "Removed '" << target << "'" << endl;
        }
        else
            cout << "Operation Terminated" << endl;
    }
    else
        cout << "'" << target << "' not found" << endl; //! @note: miss

    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: search(void) -- done
void Account::search(void)
{
    //* @note: grab search target
    string target;
    do
    {
        cout << "Target: ";
        cin >> target;
    } while (!InputValidation(target));

    //* @note: search bitchain for user' target
    if (bitchain.search(target))
        cout << "Target Found: " << target << endl; //* target found
    else
        cout << "<error> = '" << target << "' doesn't exist" << endl; //! target not found

    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: print(void) -- done
void Account::print(void)
{
    cout << bitchain;
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: save(void) -- done
bool Account::save(void)
{
    //* @note: grab & validate resource savefile
    ofstream outputfile(".resources/Accounts/accounts.txt", ios::app);
    if (!FileValidation(outputfile))
    {
        cerr << "<error> = file failed to open" << endl;
        return false;
    }

    //* @note: grab user confirmation
    cout << "Save Bitchain Account | ";
    if (!ConfirmOperation())
    {
        cout << "Operation Terminated" << endl;
        outputfile.close();
        return false;
    }

    //* @note: write Account contents to 'accounts.txt'
    outputfile << username << "," << passkey << "," << keys << endl;

    //* @note: write Bitchain contents to 'username.txt'
    ofstream bitchainfile(".resources/Bitchains/" + username + ".txt");
    if (bitchain.save(bitchainfile))
    {
        // ? @note : close files to avoid leaks
        outputfile.close();
        return true;
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public:cache(void)
bool Account::cache(void)
{
    //? @note: grab & validate cache
    ofstream cachefile(".resources/Accounts/cache.txt");
    if (!FileValidation(cachefile))
    {
        cerr << "<error>==file_opening" << endl;
        return false;
    }

    //? @note: write Account data to cache
    cachefile << username << "," << passkey << "," << keys << endl;
    cachefile.close();
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: wipe(void) -- done
bool Account::wipe(void)
{

    //? @note: grab & validate inputfile, create new tempfile
    ifstream inputfile(".resources/Accounts/accounts.txt");
    if (!FileValidation(inputfile))
    {
        cerr << "File failed to open" << endl;
        return false;
    }

    //* @note: grab user confirmation
    cout << "Delete Bitchain Account | ";
    if (!ConfirmOperation())
    {
        cerr << "<Operation Terminated>" << endl;
        inputfile.close();
        return false;
    }

    //* @note: delete bitchain savefile
    string WipeBitchain = "rm -rf .resources/Bitchains/" + username + ".txt";
    system(WipeBitchain.c_str());

    ofstream tempfile(".resources/Accounts/temp.txt");

    //* @note: copy all inputfile contents except target
    string line;
    while (getline(inputfile, line))
    {
        if (line.find(username) == string::npos)
            tempfile << line << endl;
    }

    //? @note: close files
    inputfile.close();
    tempfile.close();
    rename(".resources/Accounts/temp.txt", ".resources/Accounts/accounts.txt");

    return true;
}
//* @public: wipe(const string) -- done
bool Account::wipe(const string target)
{
    if (lookup(target))
    {
        wipe();
        return true;
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: load(void) -- done
bool Account::load(void)
{
    //? @note: prompt for target username
    string target;
    do
    {
        cout << "Target: ";
        getline(cin, target);

        //! @note: no target was given
        if (target.empty())
        {
            cout << "Target not specified" << endl;
            return false;
        }
    } while (!InputValidation(target));

    //! @note: target miss
    if (lookup(target))
    {
        //* @note: target hit
        cout << "Target Found: " << target << endl;
        ifstream bitchainfile(".resources/Bitchains/" + username + ".txt");

        if (bitchain.load(bitchainfile))
            return true;
    }

    cerr << "<error>==miss" << endl; //! @note: loading failure
    return false;
}
//* @public: load(const string) -- done
bool Account::load(const string target)
{
    //* @note: target hit
    if (lookup(target))
    {
        ifstream bitchainfile(".resources/Bitchains/" + target + ".txt");
        if (bitchain.load(bitchainfile))
            return true;
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Mutators
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: setUsername(const string) -- done
void Account::setUsername(const string nUsername)
{
    username = nUsername;
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: setPasskey(const string) -- done
void Account::setPasskey(const string nPasskey)
{
    passkey = nPasskey;
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: setKeys(const int) -- done
void Account::setKeys(const int nKeys)
{
    keys = nKeys;
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Accessors
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: getUsername(void) -- done
const string Account::getUsername(void) { return username; }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: getPasskey(void) -- done
const string Account::getPasskey(void) { return passkey; }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: getKeys(void) -- done
int Account::getKeys(void) { return keys; }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//? @defgroup: Overloads
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @public: operator<<(ostream&, const Account&) -- done
ostream &operator<<(ostream &out, const Account &account)
{
    out << "|--------------------------------------------------|" << endl
        << "   Bitchain Account" << endl
        << "\t- Username:\t" << account.username << endl
        << "\t- Passkey:\t" << account.passkey << endl
        << "\t- Keys:\t\t" << account.keys << endl
        << "|--------------------------------------------------|";

    return out;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
