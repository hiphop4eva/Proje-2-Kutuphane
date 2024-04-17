#pragma once

#include "library.h"

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

std::wstring Widen(std::string narrow) {
	wchar_t* buffer = new wchar_t[narrow.length() + 1];
	std::copy(narrow.begin(), narrow.end(), buffer);
	buffer[narrow.length()] = 0;

	std::wstring wide;
	wide.append(buffer);

	delete[] buffer;
	return wide;
}

std::wstring Widen(int narrowInt) {
	std::string narrow = std::to_string(narrowInt);
	wchar_t* buffer = new wchar_t[narrow.length() + 1];
	std::copy(narrow.begin(), narrow.end(), buffer);
	buffer[narrow.length()] = 0;

	std::wstring wide;
	wide.append(buffer);

	delete[] buffer;
	return wide;
}

std::string Narrowen(std::wstring wide){
	int len;
	int slength = wide.size();
	len = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, &r[0], len, 0, 0);
	return r;
}

std::string Narrowen(int wideInt) {
	std::wstring wide = std::to_wstring(wideInt);
	int len;
	int slength = wide.size();
	len = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, wide.c_str(), slength, &r[0], len, 0, 0);
	return r;
}

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
	HWND loginUserBorder;
	HWND loginUserBox;
	HWND loginPasswordBox;
	HWND loginUser;
	HWND loginPassword;
	HWND buttonLogin;
	HWND buttonRegister;
	HWND buttonLogout;

	HWND log;
	HWND buttonSave;
	HWND buttonAdd;
	HWND comboBoxPrimary;
	HWND comboBoxBook;
	HWND comboBoxUser;
	
	HWND logAdd;
	HWND buttonAddAlt;
	HWND buttonCancel;

	int colLoginUser = 20;
	int colLoginBorder = colLoginUser - 10;
	int colLoginPassword = colLoginUser;
	int colButtonLogin = colLoginBorder;
	int colButtonRegister = colButtonLogin + 60;
	int colButtonLogout = colButtonLogin;
	int rowLoginUser = 20;
	int rowLoginBorder = rowLoginUser - 20;
	int rowLoginPassword = rowLoginUser + 40;
	int rowButtonLogin = rowLoginBorder + 100;
	int rowButtonRegister = rowButtonLogin;
	int rowButtonLogout = rowButtonLogin;

	int colLog = 350;
	int colSave = colLog;
	int colAdd = colSave + 75;
	int colCBoxPrim = colLog + 350;
	int colCBoxSec = colCBoxPrim + 100;
	int rowLog = 10;
	int rowSave = rowLog + 320;
	int rowAdd = rowSave;
	int rowCBoxPrim = rowLog;
	int rowCBoxSec = rowCBoxPrim;
	
	int colLogAdd = colLog;
	int colAddAlt = colAdd;
	int colCancel = colSave;
	int rowLogAdd = rowLog;
	int rowAddAlt = rowAdd;
	int rowCancel = rowSave;

	int Login(std::string name, std::string password) {
		int feedback = 0;
		
		for (int i = 0; i <= userList.size(); i++) {
			if (i == userList.size()) {
				return feedback = -1;
			}
			else if (name == userList[i].getName()) {
				if (password == userList[i].getPassword()) {
					userList[i].login();
					return feedback = userList[i].getID();
				}
				else {
					return feedback = -2;
				}
			}
		}
		return feedback;
	}

	int Logout() {
		int feedback = 0;

		for (int i = 0; i <= userList.size(); i++) {
			if (i == userList.size()) {
				return feedback = -1;
			}
			else if (userList[i].getLogin() == true) {
				userList[i].logout();
				return userList[i].getID();
			}
		}
		return feedback;
	}

	void SwitchToAdd() {
		ShowWindow(log, SW_HIDE);
		ShowWindow(buttonSave, SW_HIDE);
		ShowWindow(buttonAdd, SW_HIDE);
		ShowWindow(comboBoxPrimary, SW_HIDE);
		ShowWindow(comboBoxBook, SW_HIDE);
		ShowWindow(comboBoxUser, SW_HIDE);

		ShowWindow(logAdd, SW_SHOW);
		ShowWindow(buttonAddAlt, SW_SHOW);
		ShowWindow(buttonCancel, SW_SHOW);
	}

	void SwitchToMain() {
		ShowWindow(log, SW_SHOW);
		ShowWindow(buttonSave, SW_SHOW);
		ShowWindow(buttonAdd, SW_SHOW);
		ShowWindow(comboBoxPrimary, SW_SHOW);
		ShowWindow(comboBoxBook, SW_SHOW);
		ShowWindow(comboBoxUser, SW_SHOW);

		ShowWindow(logAdd, SW_HIDE);
		ShowWindow(buttonAddAlt, SW_HIDE);
		ShowWindow(buttonCancel, SW_HIDE);
	}

	void SwitchLogin(int mode) {
		if (mode == 1) {
			ShowWindow(loginUser, SW_HIDE);
			ShowWindow(loginPassword, SW_HIDE);
			ShowWindow(buttonLogin, SW_HIDE);
			ShowWindow(buttonRegister, SW_HIDE);

			ShowWindow(loginUserBox, SW_SHOW);
			ShowWindow(loginPasswordBox, SW_SHOW);
			ShowWindow(buttonLogout, SW_SHOW);
		}
		else if (mode == 0) {
			ShowWindow(loginUser, SW_SHOW);
			ShowWindow(loginPassword, SW_SHOW);
			ShowWindow(buttonLogin, SW_SHOW);
			ShowWindow(buttonRegister, SW_SHOW);

			ShowWindow(loginUserBox, SW_HIDE);
			ShowWindow(loginPasswordBox, SW_HIDE);
			ShowWindow(buttonLogout, SW_HIDE);
		}
	}

	void InsertToCBoxBook() {
		bool cont = true;
		int count = SendMessage(comboBoxBook, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
		int len;
		std::wstring title;
		std::string titleNarrow;

		for (int i = 0; i < bookList.size(); i++) {
			for (int k = 0; k < count; k++) {
				len = SendMessage(comboBoxBook, CB_GETLBTEXTLEN, k, (LPARAM)0);
				title.resize(len);
				title = SendMessage(comboBoxBook, CB_GETLBTEXT, k, (LPARAM)&title.c_str()[0]);
				titleNarrow = Narrowen(title);
				if (bookList[i].getTitle() == titleNarrow) {
					cont = false;
					break;
				}
			}

			if (cont == false) { cont = true; continue; }
			std::string insertNarrow = bookList[i].getTitle();
			std::wstring insertWide = Widen(insertNarrow);

			SendMessage(comboBoxBook, CB_INSERTSTRING, (WPARAM)i, (LPARAM)insertWide.c_str());
		}
	}

	void InsertToCBoxUser() {
		bool cont = true;
		int count = SendMessage(comboBoxUser, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
		int len;
		std::wstring name;
		std::string nameNarrow;

		for (int i = 0; i < userList.size(); i++) {
			for (int k = 0; k < count; k++) {
				len = SendMessage(comboBoxUser, CB_GETLBTEXTLEN, k, (LPARAM)0);
				name.resize(len);
				SendMessage(comboBoxUser, CB_GETLBTEXT, k, (LPARAM)&name.c_str()[0]);
				nameNarrow = Narrowen(name);
				if (userList[i].getName() == nameNarrow) {
					cont = false;
					break;
				}
			}

			if (cont == false) { cont = true; continue; }
			std::string insertNarrow = userList[i].getName();
			std::wstring insertWide = Widen(insertNarrow);

			SendMessage(comboBoxUser, CB_INSERTSTRING, (WPARAM)i, (LPARAM)insertWide.c_str());
		}
	}

	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam) {
		switch (uMsg) {

		case WM_CREATE:
			loginUserBorder  = CreateWindow(WC_BUTTON, L"Login", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, colLoginBorder, rowLoginBorder, 120, 100, m_hwnd, NULL, NULL, NULL);
			loginUserBox     = CreateWindow(WC_STATIC, L"",              WS_CHILD | WS_BORDER, colLoginUser, rowLoginUser, 80, 20, m_hwnd, NULL, NULL, NULL);
			loginPasswordBox = CreateWindow(WC_STATIC, L"",              WS_CHILD | WS_BORDER, colLoginPassword, rowLoginPassword, 80, 20, m_hwnd, NULL, NULL, NULL);
			loginUser        = CreateWindow(WC_EDIT,   L"", WS_VISIBLE | WS_CHILD | WS_BORDER, colLoginUser, rowLoginUser, 80, 20, m_hwnd, NULL, NULL, NULL);
			loginPassword    = CreateWindow(WC_EDIT,   L"", WS_VISIBLE | WS_CHILD | WS_BORDER, colLoginPassword, rowLoginPassword, 80, 20, m_hwnd, NULL, NULL, NULL);
			buttonLogin      = CreateWindow(WC_BUTTON, L"Login",    WS_VISIBLE | WS_CHILD | WS_BORDER, colButtonLogin, rowButtonLogin, 50, 20, m_hwnd, NULL, NULL, NULL);
			buttonRegister   = CreateWindow(WC_BUTTON, L"Register", WS_VISIBLE | WS_CHILD | WS_BORDER, colButtonRegister, rowButtonRegister, 60, 20, m_hwnd, NULL, NULL, NULL);
			buttonLogout      = CreateWindow(WC_BUTTON, L"Logout",                WS_CHILD | WS_BORDER, colButtonLogout, rowButtonLogout, 50, 20, m_hwnd, NULL, NULL, NULL);
			
			log             = CreateWindow(WC_EDIT    , L""    , WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_MULTILINE, colLog, rowLog, 300, 300, m_hwnd, (HMENU)1, NULL, NULL);
			buttonSave      = CreateWindow(WC_BUTTON  , L"Save", WS_VISIBLE | WS_CHILD | WS_BORDER     , colSave, rowSave, 60, 20, m_hwnd, (HMENU)2, NULL, NULL);
			buttonAdd       = CreateWindow(WC_BUTTON  , L"Add" , WS_VISIBLE | WS_CHILD | WS_BORDER     , colAdd, rowAdd, 60, 20, m_hwnd, (HMENU)6, NULL, NULL);
			comboBoxPrimary = CreateWindow(WC_COMBOBOX, L""  , WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxPrim, rowCBoxPrim, 80, 500, m_hwnd, (HMENU)3, NULL, NULL);
			comboBoxBook    = CreateWindow(WC_COMBOBOX, L""  ,              WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxSec , rowCBoxSec, 100, 500, m_hwnd, (HMENU)4, NULL, NULL);
			comboBoxUser    = CreateWindow(WC_COMBOBOX, L""  ,              WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxSec , rowCBoxSec, 100, 500, m_hwnd, (HMENU)5, NULL, NULL);
			
			logAdd       = CreateWindow(WC_EDIT    , L"" , WS_CHILD | ES_AUTOHSCROLL | ES_MULTILINE, colLogAdd, rowLogAdd, 300, 300, m_hwnd, (HMENU)7, NULL, NULL);
			buttonCancel = CreateWindow(WC_BUTTON  , L"Cancel" , WS_CHILD | WS_BORDER , colCancel, rowCancel, 60, 20, m_hwnd, (HMENU)9, NULL, NULL);
			buttonAddAlt = CreateWindow(WC_BUTTON  , L"Add"    , WS_CHILD | WS_BORDER , colAddAlt, rowAddAlt, 60, 20, m_hwnd, (HMENU)8, NULL, NULL);
			
			SendMessage(comboBoxPrimary, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Books");
			SendMessage(comboBoxPrimary, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Users");
			SendMessage(comboBoxPrimary, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			
			if (!bookList.empty()) {
				InsertToCBoxBook();
				SendMessage(comboBoxBook, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			else {
				SendMessage(comboBoxBook, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
			}
			
			if (!userList.empty()) {
				InsertToCBoxUser();
				SendMessage(comboBoxUser, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			else {
				SendMessage(comboBoxUser, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
			}

			ShowWindow(comboBoxUser, SW_HIDE);
			ShowWindow(comboBoxBook, SW_SHOW);
			UpdateWindowBook(log, comboBoxBook);
			UpdateWindowUser(log, comboBoxBook);
			
			return 0;

		case WM_COMMAND: {
			if (HIWORD(wparam) == BN_CLICKED) {
				if (lparam == LPARAM(buttonSave)) {
					if (saveDatabase()) {
						MessageBox(m_hwnd, L"Database saved", L"Success", MB_OK | MB_ICONASTERISK);
					}
					else {
						MessageBox(m_hwnd, L"Error while saving database", L"Error", MB_OK | MB_ICONEXCLAMATION);
					}
				}
				else if (lparam == LPARAM(buttonAdd)) {
					SwitchToAdd();
				}
				else if (lparam == LPARAM(buttonCancel)) {
					SwitchToMain();
				}
				else if (lparam == LPARAM(buttonLogin)) {
					std::wstring name;
					std::wstring password;
					name.resize(SendMessage(loginUser, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
					password.resize(SendMessage(loginPassword, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
					SendMessage(loginUser, WM_GETTEXT, (WPARAM)name.size() + 1, (LPARAM)name.c_str());
					SendMessage(loginPassword, WM_GETTEXT, (WPARAM)password.size() + 1, (LPARAM)password.c_str());

					int feedback = Login(Narrowen(name), Narrowen(password));
					if (feedback == -1 || feedback == 0) {
						MessageBox(m_hwnd, L"Could not find this user.", L"Error", MB_OK);
					}
					else if (feedback == -2) {
						MessageBox(m_hwnd, L"Password is incorrect.", L"Error", MB_OK);
					}
					else {
						SwitchLogin(1);
						SendMessage(loginUserBorder, WM_SETTEXT, NULL, (LPARAM)L"Registered");
						SendMessage(loginUser, WM_SETTEXT, NULL, (LPARAM)L"");
						SendMessage(loginPassword, WM_SETTEXT, NULL, (LPARAM)L"");
						MessageBox(m_hwnd, L"Login successful.", L"Success", MB_OK);
					}
				}
				else if (lparam == LPARAM(buttonLogout)) {
						SwitchLogin(0);
						SendMessage(loginUserBorder, WM_SETTEXT, NULL, (LPARAM)L"Login");
						Logout();
						MessageBox(m_hwnd, L"Logout successful.", L"Success", MB_OK);
				}
				else if (lparam == LPARAM(buttonRegister)) {
					int confirm = MessageBox(m_hwnd, L"Do you want to register a user with this name and password?", L"Confirm", MB_OKCANCEL);
					if (confirm == IDOK) {
						std::wstring name;
						std::wstring password;
						name.resize(SendMessage(loginUser, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
						password.resize(SendMessage(loginPassword, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
						SendMessage(loginUser, WM_GETTEXT, (WPARAM)name.size() + 1, (LPARAM)name.c_str());
						SendMessage(loginPassword, WM_GETTEXT, (WPARAM)password.size() + 1, (LPARAM)password.c_str());
						ClassUser(userList.size() + 1, Narrowen(name), Narrowen(password));
						saveDatabase();
						readDatabase();
						InsertToCBoxUser();

						Login(Narrowen(name), Narrowen(password));
						SwitchLogin(1);
						SendMessage(loginUserBorder, WM_SETTEXT, NULL, (LPARAM)L"Registered");
						SendMessage(loginUser, WM_SETTEXT, NULL, (LPARAM)L"");
						SendMessage(loginPassword, WM_SETTEXT, NULL, (LPARAM)L"");
						MessageBox(m_hwnd, L"Register successful.", L"Success", MB_OK);
					}
				}
				return 0;
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
				return 0;
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
				ss << Widen(bookID) << "\r\n" << Widen(bookTitle) << "\r\n" << Widen(bookOwnerID) << "\r\n" << Widen(bookTimeBorrow) << "\r\n";
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
				ss << Widen(userID) << "\r\n" << Widen(userName) << "\r\n";
				logText.append(ss.str());

				SendMessage(log, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			}
		}
	}
}