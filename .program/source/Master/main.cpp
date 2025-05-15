//************************************************************************************************************** */
//** @author:   mr-yellow   |   Matthew Hong                                                                     */
//** @brief:    Digital Keychain program designed to store passwords, emails, usernames for websites             */
//** @brief:    & applications securely while maintaining easy accessibility                                     */
//************************************************************************************************************** */

#include "../../includes/Account/account.h"

//^ @fn: testbench(void)
int testbench(void)
{
    //? @note: debug list
    //! 1. dont save a profile with the same username again to avoid duplicates
    //! 2. reconfigure copy constructor memory handling in Bitchain, shallow copy is breaking program
    //! 3. create showKey function in bitchain to display an individual key
    //! TBD...

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
         << "\t| -Bitchain Keys- |" << endl
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
            //& @note: bitchain version
            cout << _version << endl;
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || usage
        if (arg == "-h" || arg == "--help")
        {
            //& @note: bitchain usage
            usage();
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || reset
        if (arg == "--reset")
        {
            //& note: reset bitchain
            if (Restart())
                cout << "User Reset Bitchain" << endl;

            //! @note: bitchain reset failed
            else
            {
                cerr << "<error>=reset_failed" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @note: Bitchain || clean cache
        if (arg == "--clean")
        {
            //& @note: clean cache
            if (ResetCache())
                cout << "User Cleaned Cache" << endl;

            //! @note: cache cleaning failed
            else
            {
                cerr << "<error>=cacheCleaning_failed" << endl;
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

            //! @note: account saving failed
            else
            {
                cerr << "<error>=accountSave_failed" << endl;
                flag = 1;
            }

            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || load
        if (arg == "--load")
        {
            //& @note: target was given
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr)
            {
                target = argv[i + 1];

                //? @note: attempt to load
                if (account.load(target)) //* @note: account loaded
                {
                    cout << "Bitchain Account Loaded" << endl;
                    account.saveToCache();
                }
                else //! @note: file not loaded
                {
                    cerr << "<error>=loading_miss" << endl;
                    flag = 1;
                }
            }

            //& @note: prompt for user input
            else if (account.load()) //* @note: account loaded
            {
                cout << "Bitchain Account Loaded" << endl;
                account.saveToCache();
            }

            //! @note: account loading failed
            else
            {
                cerr << "<error>=accountLoading_failed" << endl;
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

                //! @note: account deletion failure
                else
                {
                    cerr << "<error>=accountDelete_failed" << endl;
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
            //! @note: Cache is empty
            if (CacheEmpty())
            {
                cerr << "<error>=cache_empty" << endl;
                flag = 1;
            }

            //& @note: attempt to display account information
            if (account.loadFromCache())
            {
                cout << endl;
                cout << account << endl;
            }

            //! @note: display account failed
            else
            {
                cerr << "<error>=displayAccount_failed" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || add
        if (arg == "-a" || arg == "--add")
        {
            //! @note: Cache is empty
            if (CacheEmpty())
            {
                cerr << "<error>=cache_empty" << endl;
                flag = 1;
            }

            //& @note: attempt to add key
            if (account.loadFromCache())
            {
                cout << endl;
                account.add();

                account.save();
                account.saveToCache();
                cout << account << endl;
            }

            //! @note: add key failed
            else
            {
                cerr << "<error>=addKey_failed" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // todo @def: Bitchain || remove
        if (arg == "-r" || arg == "--remove")
        {
            //! @note: cache is empty
            if (CacheEmpty())
            {
                cerr << "<error>=cache_empty" << endl;
                flag = 1;
            }

            //& @note: remove key
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr && account.loadFromCache())
            {
            }

            //! @note: remove key failed
            else
            {
                cerr << "<error>=removeKey_failed" << endl;
                flag = 1;
            }
            break;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //* @def: Bitchain || show
        if (arg == "--show")
        {
            //! @note: cache is empty
            if (CacheEmpty())
            {
                cerr << "<error>=cache_empty" << endl;
                flag = 1;
            }

            //& @note: attempt to display key
            string target;
            if (i + 1 < argc && argv[i + 1] != nullptr && account.loadFromCache())
            {
                target = argv[i + 1];
                cout << endl;

                if (target == "all")
                    account.print();
                else
                    account.print(target);
            }

            //! @note: show key failed
            else
            {
                cerr << "<error>=showKey_failed" << endl;
                flag = 1;
            }
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
