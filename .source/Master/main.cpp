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

//& @public: BITCHAIN(int, char**)
//& @def: parses program flags
int BITCHAIN(int argc, char **argv)
{
    if (argc == 1)
    {
        usage();
        return 0;
    }

    //* Program Components
    Account account;
    bool flag = true; //* @var: flags | return value

    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i]; //* grab argument

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Version
        //* @def: prints current program version
        if (arg == "-v" || arg == "--version")
        {
            cout << _version << endl;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Usage
        //* @def: prints how to navigate program
        else if (arg == "-h" || arg == "--help")
        {
            usage();
            flag = 0;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Create Bitchain Account
        //* @def: prompts for username & passkey, then initializes/saves account
        else if (arg == "-c" || arg == "--create")
        {
            //* @note: grab user data
            string username, passkey;
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
                cout << "Passkey: ";
                HideTerminal();
                getline(cin, passkey);
                ShowTerminal();

                if (passkey.empty())
                {
                    passkey = "passkey";
                    break;
                }
            } while (!InputVerification(passkey));

            //? @note: pass user data to account
            account.setUsername(username);
            account.setPasskey(passkey);
            account.setKeys(0);

            //* @note: saving successful
            if (account.save())
                cout << "<successs> -- saving completed" << endl;
            //! @note: saving failure
            else
                cerr << "<error> -- saving failed" << endl;

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Load Bitchain Account
        //* @def: prompts for user input then loads account data & store in cache.txt
        else if (arg == "-l" || arg == "--load")
        {
            //** code */
            //? prompt for username
            //? search accounts.txt
            //* if hit, place account in the cache
            //! if miss, report to console
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Delete Bitchain account
        //* @def: Delete [target] Bitchain Account
        else if (arg == "-d" || arg == "--delete")
        {
            //? @note: grab target argument
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                //? @note: pass argv into target & wipe it
                target = argv[i + 1];
                account.wipe(target);
            }
            else
                cerr << "<error> = no target given" << endl;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Add Key to Cached Account
        if (arg == "-a" || arg == "--add")
        {
            //** code */
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Removes [target] Key from Cached Account
        else if (arg == "-r" || arg == "--remove")
        {
            //** code */
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Prints [target] Key from Cached Account
        else if (arg == "-p" || arg == "--print")
        {
            //** code */
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
    }

    return flag;
}

//& @public: testbench(void)
//& @def: testing bench for main driver of program
int testbench(void)
{
    Account account("mjh2001", "changeme");

    account.load();
    account.print();
    account.add();
    account.save();

    return 0;
}

//* @public: main(int, char*)
//* @def: main program driver
int main(int argc, char *argv[])
{
    return BITCHAIN(argc, *&argv);
}