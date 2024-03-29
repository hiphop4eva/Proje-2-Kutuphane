#pragma once

#include <windows.h>

bool saveDatabase();

template <class C>
class BaseWindow {
public:
	static HRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
		C* pThis = NULL;
		
		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lparam;
			pThis = (C*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else {
			pThis = (C*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis) {
			return pThis->HandleMessage(uMsg, wparam, lparam);
		}
		else {
			return DefWindowProc(hwnd, uMsg, wparam, lparam);
		}
	}

	BaseWindow() : m_hwnd(NULL) {}

	BOOL Create(PCWSTR WindowName, DWORD Style, DWORD ExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HWND hwndParent = 0, HMENU hmenu = 0) {
		WNDCLASS wnd = {0};

		wnd.lpfnWndProc = C::WindowProc;
		wnd.hInstance = GetModuleHandle(NULL);
		wnd.lpszClassName = ClassName();
		
		RegisterClass(&wnd);

		m_hwnd = CreateWindowEx(ExStyle, ClassName(), WindowName, Style, x, y, width, height, hwndParent, hmenu, GetModuleHandle(NULL), this);

		return (m_hwnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hwnd; }

protected:
	HWND m_hwnd;

	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam) = 0;
};

class MainWindow : public BaseWindow<MainWindow> {
public:
	HWND log;
	HWND buttonSave;

	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam) {
		switch (uMsg) {

		case WM_CREATE:
			log        = CreateWindow(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 10, 10, 300, 300, m_hwnd, (HMENU)1, NULL, NULL);
			buttonSave = CreateWindow(L"BUTTON", L"Save", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 330, 60, 20, m_hwnd, (HMENU)2, NULL, NULL);
			
			return 0;

		case WM_COMMAND: {
			if (HIWORD(wparam) == BN_CLICKED) {
				if (lparam == LPARAM(buttonSave)) {
					saveDatabase();
					MessageBox(m_hwnd, L"Database saved", L"Success", MB_OK);
				}
			}
		}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
			EndPaint(m_hwnd, &ps);
		}
			return 0;

		default:
			return DefWindowProc(m_hwnd, uMsg, wparam, lparam);
		}
		return TRUE;
	}
};