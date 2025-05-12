#include "../../includes/Account/account.h"

//& @public: usage(void)
//& @def: prints program usage to terminal
void usage(void)
{
    cout << "Usage: bitchain [command] [target] ..." << endl
         << endl
         << "Commands: --example [argv]" << endl
         << "\t-v, --version\t\t\t\t\tPrint current program version" << endl
         << "\t-h, --help\t\t\t\t\tPrint program usage" << endl
         << "\t-c, --create\t\t\t\t\tCreates a new bitchain account" << endl
         << "\t-l, --load [target]\t\t\t\tLoads target bitchain account" << endl
         << "\t-d, --delete [target]\t\t\t\tDeletes target bitchain account" << endl
         << "\t-a, --add\t\t\t\t\tAdds new key to loaded account" << endl
         << "\t-r, --remove [target]\t\t\t\tRemoves target key from loaded account" << endl
         << "\t-p, --print [target]\t\t\t\tPrints target key to console from loaded account" << endl;

    return;
}

//& @public: flags(int, char**)
//& @def: parses program flags
int flags(int argc, char **argv)
{
    if (argc == 1)
    {
        usage();
        return 0;
    }

    int flag = 1;
    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i]; //* grab argument

        ///////////////////////////////////////////////////////
        //* @def: Bitchain Version
        if (arg == "-v" || arg == "--version")
        {
            cout << _version << endl;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Bitchain Usage
        if (arg == "-h" || arg == "--help")
        {
            usage();
            flag = 0;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Create Bitchain Account
        if (arg == "-c" || arg == "--create")
        {
            string username;
            if (argv[i + 1])
                username = argv[i + 1];
            else
            {
                cerr << "<error> - no username specified" << endl;
                return 1;
            }
            flag = 0;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Load [target] Bitchain Account
        if (arg == "-l" || arg == "--load")
        {
            cout << "in load account" << endl;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Delete [target] Bitchain Account
        if (arg == "-d" || arg == "--delete")
        {
            cout << "in delete account" << endl;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Add Key to Cached Account
        if (arg == "-a" || arg == "--add")
        {
            string username;
            if (argv[i + 1])
            {
                username = argv[i + 1];
                cout << username << endl;
            }
            else
            {
                cerr << "<error> - no username specified" << endl;
                return 1;
            }

            flag = 0;
        }
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Removes [target] Key from Cached Account
        if (arg == "-r" || arg == "--remove")
            cout << "in remove key" << endl;

        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //* @def: Prints [target] Key from Cached Account
        if (arg == "-p" || arg == "--print")
            cout << "in print" << endl;

        ///////////////////////////////////////////////////////
    }

    return flag;
}

//& @public: testbench(void)
//& @def: testing bench for main driver of program
int testbench(void)
{
    Account account;

    account.wipe(); 

    return 0;
}

//* @public: main(int, char*)
//* @def: main program driver
int main(int argc, char *argv[])
{
    return testbench();
}