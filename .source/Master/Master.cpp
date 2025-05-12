#include "../../includes/Master/Master.h"

//& @def: Termios
//////////////////////////////////////////////////////////////////
//& @struct:
struct termios TerminalVisible, TerminalHidden;
//////////////////////////////////////////////////////////////////

//^ @def: Functions
//////////////////////////////////////////////////////////////////
//^ @fn: HideTerminal(void)
void HideTerminal(void)
{
    tcgetattr(STDIN_FILENO, &TerminalVisible);

    TerminalHidden = TerminalVisible;
    TerminalHidden.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &TerminalHidden);

    return;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//^ @fn: ShowTerminal(void)
void ShowTerminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &TerminalVisible);
    cout << endl;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//^ @fn: InputVerification(const string)
bool InputVerification(const string input)
{
    string verification;
    do
    {
        cout << "Re-enter Password: ";
        HideTerminal();

        cin >> verification;
        ShowTerminal();
    } while (!InputValidation(verification));

    if (input == verification)
        return true;

    return false;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//^ @fn: InputValidation(const string)
bool InputValidation(const string input)
{
    for (char character : input)
    {
        switch (character)
        {
        case ' ':
            return false;

        case '#':
            return false;

        case '%':
            return false;

        case ':':
            return false;

        case ';':
            return false;

        case '/':
            return false;

        case '\\':
            return false;

        case '<':
            return false;

        case '>':
            return false;

        case '"':
            return false;

        case '\'':
            return false;

        default:
            break;
        }
    }

    return true;
}
//////////////////////////////////////////////////////////////////
