//************************************************************************************************************** */
//** @author:   mr-yellow   |   Matthew Hong                                                                     */
//** @brief:    Digital Keychain program designed to store passwords, emails, usernames for websites             */
//** @brief:    & applications securely while maintaining easy accessibility                                     */
//************************************************************************************************************** */

#include "../../includes/Account/account.h"

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
//? @fn: usage(void)
void usage(void)
{
    //? @note: usage will change eventually once we move to the parent folder

    cout << "==============================================================================================" << endl
         << endl
         << "Bitchain Usage:" << endl
         << "\tbitchain --command 'arg'" << endl
         << endl
         << "Bitchain Commands:" << endl
         << "\t| -General- |" << endl
         << "\t\t--version\t\t\tDisplay Program Version" << endl
         << "\t\t--help\t\t\t\tDisplay Program Usage" << endl
         << "\t\t--reset\t\t\t\tReset Program" << endl
         << "\t\t--clean\t\t\t\tClear Program Cache" << endl
         << endl
         << "\t| -Bitchain Accounts- |" << endl
         << "\t\t--create\t\t\tCreate Bitchain Account" << endl
         << "\t\t--load\t\t\t\tLoad Bitchain Account" << endl
         << "\t\t--delete\t\t\tDelete Bitchain Account" << endl
         << "\t\t--display\t\t\tDisplay Bitchain Accounts" << endl
         << endl
         << "\tBitchain Keys:" << endl
         << "\t\t--add\t\t\t\tAdds a key" << endl
         << "\t\t--remove\t\t\tDeletes a key" << endl
         << "\t\t--show\t\t\t\tShows a key" << endl
         << endl
         << "==============================================================================================" << endl;

    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//? @fn: driver(int, char**)
int driver(int argc, char **argv)
{
    //? Program Components
    Account account; //* @var: account
    int flag = 0;    //* @var: flag

    //? Argument Handling
    if (argc == 1) //! @note: only one argument was passed
    {
        usage();
        return flag;
    }
    for (int i = 1; i < argc; i++) //* @note: multiple arguments were passed
    {
        string arg = argv[i]; //* @note: grab current argument

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || version
        if (arg == "-v" || arg == "--version")
        {
            cout << _version << endl;
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || usage
        if (arg == "-h" || arg == "--help")
        {
            usage();
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || reset
        if (arg == "--reset")
        {
            //? @note: attempt to reset bitchain
            if (Restart())
                cout << "User Reset Bitchain" << endl;
            else
            {
                cerr << "<error>=reset_failure" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || clean cache
        if (arg == "--clean")
        {
            //& @note: attempt to clean cache
            if (ResetCache()) //* @note: cache cleared
                cout << "User Cleaned Cache" << endl;
            else //! @note: cache cleaning failed
            {
                cerr << "<error>=cache_cleaning_failure" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || create
        if (arg == "--create")
        {
            //& @note: grab account data
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

            //& @note: pass input data into account
            account.setUsername(username);
            account.setPasskey(passkey);
            account.setKeys(0);

            //& @note: attempt to save account
            if (account.save()) //* @note: saving successful
            {
                cout << "Bitchain Account Created" << endl;
            }
            else //! @note: saving failure
            {
                cerr << "<error>=saving_failure" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || load
        if (arg == "--load")
        {
            //? @note: target was passed as argument
            string target;

            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                target = argv[i + 1];

                //? @note: attempt to load
                if (account.load(target)) //* @note: account loaded
                {
                    cout << "Bitchain Account Loaded" << endl;
                    account.cache();
                }
                else //! @note: file not loaded
                {
                    cerr << "<error>=loading_miss" << endl;
                    flag = 1;
                }
            }
            //? @note: attempt to load
            else if (account.load()) //* @note: account loaded
            {
                cout << "Bitchain Account Loaded" << endl;
                account.cache();
            }
            else //! @note: file not loaded
            {
                cerr << "<error>=loading_failure" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || delete
        if (arg == "--delete")
        {
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                target = argv[i + 1]; //* @note: grab target argument

                //& @note: attempt deletion
                if (account.wipe(target)) //* @note: deletion success
                    cout << "Bitchain Account Deleted" << endl;
                else //! @note: deletion failed
                {
                    cerr << "<error>=deletion_failure" << endl;
                    flag = 1;
                }
            }
            else //! @note: no target given
            {
                cerr << "<error>=no_target" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || display
        if (arg == "--display")
        {
            //& @note: run global 'list account' function here
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || add
        if (arg == "-a" || arg == "--add")
        {
            //& @note: attempt to add key
            if (!CacheEmpty()) //* @note: add key
                cout << "<implementation goes here>" << endl;
            else //! @note: cache is empty, cancel operation
            {
                cerr << "<error>=empty_cache" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || remove
        if (arg == "-r" || arg == "--remove")
        {
            //** code */
            //& @note: attempt to delete key
            if (!CacheEmpty()) //* @note: delete key
                cout << "<implementation goes here>" << endl;
            else //! @note: cache is empty, cancel operation
            {
                cerr << "<error>=empty_cache" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || show
        if (arg == "--show")
        {
            //& @note: attempt to show key
            if (CacheEmpty())
            {
                cerr << "<error>=empty_cache" << endl;
                flag = 1;
            }
            else
                cout << "show bitchain key" << endl;

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
    }
    return flag;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO - @fn: main(int, char*)
int main(int argc, char *argv[])
{
    return driver(argc, *&argv);
}
