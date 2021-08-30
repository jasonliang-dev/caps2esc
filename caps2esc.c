#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HHOOK hHook = 0;

static LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode != HC_ACTION) {
    return CallNextHookEx(hHook, nCode, wParam, lParam);
  }

  KBDLLHOOKSTRUCT *evt = (KBDLLHOOKSTRUCT *)lParam;
  if (evt->vkCode != VK_CAPITAL) {
    return CallNextHookEx(hHook, nCode, wParam, lParam);
  }

  if (wParam == WM_KEYDOWN || wParam == WM_KEYUP) {
    keybd_event(VK_ESCAPE, 0x1, wParam == WM_KEYUP ? KEYEVENTF_KEYUP : 0, 0);
  }

  return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine,
                   int show) {
  (void)prevInstance;
  (void)cmdLine;
  (void)show;

  hHook = SetWindowsHookExA(WH_KEYBOARD_LL, &keyboardHook, hInstance, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hHook);
  return 0;
}
