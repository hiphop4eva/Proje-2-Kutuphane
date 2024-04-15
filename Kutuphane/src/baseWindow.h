#pragma once

#include "library.h"

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

bool saveDatabase();

void UpdateWindowBook(HWND log, HWND comboBoxBook);
void UpdateWindowUser(HWND log, HWND comboBoxBook);

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
	HWND buttonAdd;
	HWND comboBoxPrimary;
	HWND comboBoxBook;
	HWND comboBoxUser;

	int rowLog = 10;
	int rowSave = rowLog;
	int rowAdd = rowSave + 100;
	int rowCBoxPrim = rowLog + 350;
	int rowCBoxSec = rowCBoxPrim + 100;
	int colLog = 10;
	int colSave = colLog + 320;
	int colAdd = colSave;
	int colCBoxPrim = colLog;
	int colCBoxSec = colCBoxPrim;

	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam) {
		switch (uMsg) {

		case WM_CREATE:
			log             = CreateWindow(WC_EDIT    , L""    , WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_MULTILINE, rowLog, colLog, 300, 300, m_hwnd, (HMENU)1, NULL, NULL);
			buttonSave      = CreateWindow(WC_BUTTON  , L"Save", WS_VISIBLE | WS_CHILD | WS_BORDER     , rowSave, colSave, 60, 20, m_hwnd, (HMENU)2, NULL, NULL);
			comboBoxPrimary = CreateWindow(WC_COMBOBOX, L""  , WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rowCBoxPrim, colCBoxPrim, 80, 100, m_hwnd, (HMENU)3, NULL, NULL);
			comboBoxBook    = CreateWindow(WC_COMBOBOX, L""  ,              WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rowCBoxSec , colCBoxSec, 100, 100, m_hwnd, (HMENU)4, NULL, NULL);
			comboBoxUser    = CreateWindow(WC_COMBOBOX, L""  ,              WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_HASSTRINGS, rowCBoxSec , colCBoxSec, 100, 100, m_hwnd, (HMENU)5, NULL, NULL);
			
			SendMessage(comboBoxPrimary, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Books");
			SendMessage(comboBoxPrimary, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Users");
			SendMessage(comboBoxPrimary, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			
			if (!bookList.empty()) {
				for (int i = 0; i < bookList.size(); i++) {
					std::string insertNarrow = bookList[i].getTitle();
					std::wstring insertWide = widen(insertNarrow);

					SendMessage(comboBoxBook, CB_INSERTSTRING, (WPARAM)i, (LPARAM)insertWide.c_str());
				}
				SendMessage(comboBoxBook, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			else {
				SendMessage(comboBoxBook, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
			}
			
			if (!userList.empty()) {
				for (int i = 0; i < userList.size(); i++) {
					std::string insertNarrow = userList[i].getName();
					std::wstring insertWide = widen(insertNarrow);

					SendMessage(comboBoxUser, CB_INSERTSTRING, (WPARAM)i, (LPARAM)insertWide.c_str());
				}
				SendMessage(comboBoxUser, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			else {
				SendMessage(comboBoxUser, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
			}

			ShowWindow(comboBoxBook, SW_SHOW);
			ShowWindow(comboBoxUser, SW_HIDE);
			UpdateWindowBook(log, comboBoxBook);

			return 0;

		case WM_COMMAND: {
			if (HIWORD(wparam) == BN_CLICKED) {
				if (lparam == LPARAM(buttonSave)) {
					saveDatabase();
					MessageBox(m_hwnd, L"Database saved", L"Success", MB_OK);
				}
			}
			else if (HIWORD(wparam) == CBN_SELCHANGE) {

				if (lparam == LPARAM(comboBoxPrimary)) {
					int selection = SendMessage(comboBoxPrimary, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					
					if (selection == 0) {
						ShowWindow(comboBoxBook, SW_SHOW);
						ShowWindow(comboBoxUser, SW_HIDE);
						UpdateWindowBook(log, comboBoxBook);
					}
					else if (selection == 1) {
						ShowWindow(comboBoxBook, SW_HIDE);
						ShowWindow(comboBoxUser, SW_SHOW);
						UpdateWindowUser(log, comboBoxUser);
					}
				}
				else if (lparam == LPARAM(comboBoxBook)) {
					UpdateWindowBook(log, comboBoxBook);
				}
				else if (lparam == LPARAM(comboBoxUser)) {
					UpdateWindowUser(log, comboBoxUser);
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

void UpdateWindowBook(HWND log, HWND comboBoxBook){
	int selection = SendMessage(comboBoxBook, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	if (selection == -1) {
		SendMessage(log, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	}
	else {
		int bookID;
		std::string bookTitle;
		int bookOwnerID;
		int bookTimeBorrow;
		std::wstring logText;
		std::wstringstream ss;

		for (int i = 0; i < bookList.size(); i++) {
			if (selection == i) {
				bookID = bookList[i].getID();
				bookTitle = bookList[i].getTitle();
				bookOwnerID = bookList[i].getOwnerID();
				bookTimeBorrow = bookList[i].getTimeBorrow();
				ss << widen(bookID) << "\r\n" << widen(bookTitle) << "\r\n" << widen(bookOwnerID) << "\r\n" << widen(bookTimeBorrow) << "\r\n";
				logText.append(ss.str());

				SendMessage(log, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			}
		}
	}
}

void UpdateWindowUser(HWND log, HWND comboBoxUser) {
	int selection = SendMessage(comboBoxUser, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	if (selection == -1) {
		SendMessage(log, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	}
	else {
		int userID;
		std::string userName;
		std::wstring logText;
		std::wstringstream ss;

		for (int i = 0; i < userList.size(); i++) {
			if (selection == i) {
				userID = userList[i].getID();
				userName = userList[i].getName();
				ss << widen(userID) << "\r\n" << widen(userName) << "\r\n";
				logText.append(ss.str());

				SendMessage(log, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			}
		}
	}
}