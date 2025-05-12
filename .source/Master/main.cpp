#include "../../includes/Account/account.h"

//** @author:   mr-yellow   |   Matthew Hong                                                                     */
//** @brief:    Digital Keychain program designed to store passwords, emails, usernames for websites             */
//** @brief:    & applications securely while maintaining easy accessibility                                     */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//^ @fn: testbench(void)
int testbench(void)
{
    Account account("mjh2001", "changeme");

    account.load();
    account.print();
    account.add();
    account.save();

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//? @fn: usage(void)
void usage(void)
{
    cout << "Usage: bitchain [command] [target] ..." << endl
         << endl
         << "Commands: --example [argv]" << endl
         << "\t-v, --version\t\t\t\t\tPrint current program version" << endl
         << "\t-h, --help\t\t\t\t\tPrint program usage" << endl
         << "\t-R, --reset\t\t\t\t\tresets program save files" << endl
         << "\t-C, --clean\t\t\t\t\tclears program cache" << endl
         << "\t-c, --create\t\t\t\t\tCreates a new bitchain account" << endl
         << "\t-l, --load [target]\t\t\t\tLoads target bitchain account" << endl
         << "\t-d, --delete [target]\t\t\t\tDeletes target bitchain account" << endl
         << "\t-a, --add\t\t\t\t\tAdds new key to loaded account" << endl
         << "\t-r, --remove [target]\t\t\t\tRemoves target key from loaded account" << endl
         << "\t-p, --print [target]\t\t\t\tPrints target key to console from loaded account" << endl;

    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//? @fn: driver(int, char**)
int driver(int argc, char **argv)
{

    //? Program Components
    Account account;  //* @var: account
    bool flag = true; //* @var: flag

    //? Attempt Argument Handling
    if (argc == 1) //! @note: only one argument was passed
    {
        usage();
        return 0;
    }
    for (int i = 1; i < argc; i++) //* @note: multiple arguments were passed
    {
        //? @note: grabs current argument
        string arg = argv[i];

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Version -- done
        //* @def: prints current program version
        if (arg == "-v" || arg == "--version")
        {
            cout << _version << endl;
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Usage -- done
        //* @def: prints how to navigate program
        else if (arg == "-h" || arg == "--help")
        {
            usage();
            flag = true;
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Reset -- done
        //* @def: resets all bitchain save files
        if (arg == "-R" || arg == "--reset")
        {
            //? @note: attempt to reset bitchain
            if (Restart())
            {
                cout << "Bitchain Successfully Reset" << endl;
                flag = true;
            }
            else
            {
                cerr << "<error>=reset_failure" << endl;
                flag = false;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain Cache Cleaning -- done
        //* @def: clears any contents in cache
        if (arg == "-C" || arg == "--clean")
        {
            //? @note: attempt to clear cache
            if (ResetCache()) //* @note: cache cleared
            {
                cout << "Cache Cleaned" << endl;
                flag = true;
            }
            else //! @note: cache cleaning failed
            {
                cerr << "<error>=cache_cleaning>" << endl;
                flag = false;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Create Bitchain Account -- done
        //* @def: prompts for username & passkey, then initializes/saves account
        else if (arg == "-c" || arg == "--create")
        {
            //? @note: grab user data
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

            //? @note: attempt to save
            if (account.save()) //* @note: saving successful
            {
                cout << "Bitchain Account Created" << endl;
                flag = true;
            }
            else //! @note: saving failure
            {
                cerr << "<error>=saving_failure" << endl;
                flag = false;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def:
        if (arg == "-l" || arg == "--load")
        {
            //? @note: target was passed as argument
            string target; ///////////////////////////////////////////////////////////////////////////////////////////////////

            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                target = argv[i + 1];

                //? @note: attempt to load
                if (account.load(target)) //* @note: account loaded
                {
                    cout << "Bitchain Account Loaded" << endl;
                    account.cache();
                    flag = true;
                }
                else //! @note: file not loaded
                {
                    cerr << "<error> = loading failure" << endl;
                    flag = false;
                }
            }
            //? @note: attempt to load
            else if (account.load()) //* @note: account loaded
            {
                cout << "Bitchain Account Loaded" << endl;
                account.cache();
                flag = true;
            }
            else //! @note: file not loaded
            {
                cerr << "<error> = loading failure" << endl;
                flag = false;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Delete Bitchain Account
        else if (arg == "-d" || arg == "--delete")
        {
            //? @note: grab target argument
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                //? @note: pass argv into target, then delete if target is found
                target = argv[i + 1];

                //? @note: attempt deletion
                if (account.wipe(target)) //* @note: deletion success
                {
                    cout << "Bitchain Account Deleted" << endl;
                    flag = true;
                }
                else //! @note: deletion failed
                {
                    cerr << "<error> = deletion failure" << endl;
                    flag = false;
                }
            }
            else //! @note: no target given
            {
                cerr << "<error> = no target given" << endl;
                flag = false;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO @def: Add Key to Cached Account
        if (arg == "-a" || arg == "--add")
        {
            //** code */
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO @def: Removes [target] Key from Cached Account
        else if (arg == "-r" || arg == "--remove")
        {
            //** code */
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // TODO @def: Prints [target] Key from Cached Account
        else if (arg == "-p" || arg == "--print")
        {
            //** code */
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
    }

    return flag;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//* @main
int main(int argc, char *argv[])
{
    return driver(argc, *&argv);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////