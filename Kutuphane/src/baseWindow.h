#pragma once

#include "library.h"

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

struct LogStruct {
	HWND LogID;
	HWND LogTitle;
	HWND LogIsOwned;
	HWND LogTimeBorrow;
	HWND LogOwnerID;
};

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

void UpdateWindowBook(LogStruct logStruct, HWND comboBoxBook);
void UpdateWindowUser(LogStruct logStruct, HWND comboBoxBook);

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

	HWND logID;
	HWND logTitle;
	HWND logIsOwned;
	HWND logTimeBorrow;
	HWND logOwnerID;

	HWND textID;
	HWND textTitle;
	HWND textIsOwned;
	HWND textTimeBorrow;
	HWND textOwnerID;

	HWND buttonBorrow;
	HWND buttonAdd;
	HWND comboBoxPrimary;
	HWND comboBoxBook;
	HWND comboBoxUser;
	
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

	int colLogID = 450;
	int colLogTitle = colLogID;
	int colLogIsOwned = colLogID;
	int colLogTimeBorrow = colLogID;
	int colLogOwnerID = colLogID;
	int rowLogID = 10;
	int rowLogTitle = rowLogID + 20;
	int rowLogIsOwned = rowLogTitle + 20;
	int rowLogTimeBorrow = rowLogIsOwned + 20;
	int rowLogOwnerID = rowLogTimeBorrow + 20;

	int colTextID = colLogID - 100;
	int colTextTitle = colLogTitle - 100;
	int colTextIsOwned = colLogIsOwned - 100;
	int colTextTimeBorrow = colLogTimeBorrow - 100;
	int colTextOwnerID = colLogOwnerID - 100;
	int rowTextID = rowLogID;
	int rowTextTitle = rowLogTitle;
	int rowTextIsOwned = rowLogIsOwned;
	int rowTextTimeBorrow = rowLogTimeBorrow;
	int rowTextOwnerID = rowLogOwnerID;

	int colAdd = colTextID;
	int colBorrow = colAdd + 75;
	int colCBoxPrim = colLogID + 350;
	int colCBoxSec = colCBoxPrim + 100;
	int rowAdd = rowTextID + 320;
	int rowBorrow = rowAdd;
	int rowCBoxPrim = rowLogID;
	int rowCBoxSec = rowCBoxPrim;
	
	int colAddAlt = colAdd;
	int colCancel = colBorrow;
	int rowAddAlt = rowAdd;
	int rowCancel = rowBorrow;

	int BorrowBook() {
		int selection = SendMessage(comboBoxBook, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
		int userID = -1;
		bool cont = true;

		if (bookList[selection].getTimeBorrow() != 0) {
			MessageBox(m_hwnd, L"This book is already borrowed.", L"Error", MB_OK);
			cont = false;
		}

		for (int i = 0; i <= userList.size(); i++) {
			if (i == userList.size()) {
				cont = false;
				break;
			}
			else if (userList[i].getLogin()) {
				userID = i;
				break;
			}
		}

		if (!cont) {
			MessageBox(m_hwnd, L"A user needs to be signed in to borrow books.", L"Error", MB_OK);

			return -1;
		}
		else {
			bookList[selection].SetOwnerID(userID);
			bookList[selection].SetTimeBorrow(7);
			MessageBox(m_hwnd, L"You have borrowed this book for 7 days.", L"Success", MB_OK);
		}

		return userID;
	}

	int Login(std::string name, std::string password) {
		int feedback = -1;
		
		for (int i = 0; i <= userList.size(); i++) {
			if (i == userList.size()) {
				return feedback = -1;
			}
			else if (name == userList[i].getName()) {
				if (password == userList[i].getPassword()) {
					userList[i].login();
					feedback = userList[i].getID() - 1;

					if (userList[feedback].getMod()) {
						ShowWindow(comboBoxPrimary, SW_SHOW);
					}

					return feedback;
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
				ShowWindow(comboBoxPrimary, SW_HIDE);

				LogStruct logStruct;
				logStruct.LogID = logID;
				logStruct.LogTitle = logTitle;
				logStruct.LogIsOwned = logIsOwned;
				logStruct.LogTimeBorrow = logTimeBorrow;
				logStruct.LogOwnerID = logOwnerID;

				UpdateWindowBook(logStruct, comboBoxBook);

				return userList[i].getID();
			}
		}

		

		return feedback;
	}

	void SwitchToAdd() {
		ShowWindow(logID, SW_HIDE);
		ShowWindow(textID, SW_HIDE);
		ShowWindow(logIsOwned, SW_HIDE);
		ShowWindow(textIsOwned, SW_HIDE);
		ShowWindow(logTimeBorrow, SW_HIDE);
		ShowWindow(textTimeBorrow, SW_HIDE);
		ShowWindow(logOwnerID, SW_HIDE);
		ShowWindow(textOwnerID, SW_HIDE);

		ShowWindow(buttonBorrow, SW_HIDE);
		ShowWindow(buttonAdd, SW_HIDE);
		ShowWindow(comboBoxPrimary, SW_HIDE);
		ShowWindow(comboBoxBook, SW_HIDE);
		ShowWindow(comboBoxUser, SW_HIDE);

		SendMessage(logID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logTitle, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logIsOwned, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logTimeBorrow, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logOwnerID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");

		ShowWindow(buttonAddAlt, SW_SHOW);
		ShowWindow(buttonCancel, SW_SHOW);
	}

	void SwitchToMain() {
		ShowWindow(logID, SW_SHOW);
		ShowWindow(textID, SW_SHOW);
		ShowWindow(logIsOwned, SW_SHOW);
		ShowWindow(textIsOwned, SW_SHOW);
		ShowWindow(logTimeBorrow, SW_SHOW);
		ShowWindow(textTimeBorrow, SW_SHOW);
		ShowWindow(logOwnerID, SW_SHOW);
		ShowWindow(textOwnerID, SW_SHOW);

		ShowWindow(buttonBorrow, SW_SHOW);
		ShowWindow(buttonAdd, SW_SHOW);
		ShowWindow(comboBoxPrimary, SW_SHOW);
		ShowWindow(comboBoxBook, SW_SHOW);
		ShowWindow(comboBoxUser, SW_SHOW);

		ShowWindow(buttonAddAlt, SW_HIDE);
		ShowWindow(buttonCancel, SW_HIDE);
	}

	void SwitchToBook() {
		LogStruct logStruct;
		logStruct.LogID = logID;
		logStruct.LogTitle = logTitle;
		logStruct.LogIsOwned = logIsOwned;
		logStruct.LogTimeBorrow = logTimeBorrow;
		logStruct.LogOwnerID = logOwnerID;

		ShowWindow(comboBoxBook, SW_SHOW);
		ShowWindow(buttonBorrow, SW_SHOW);
		ShowWindow(logIsOwned, SW_SHOW);
		ShowWindow(textIsOwned, SW_SHOW);
		ShowWindow(logTimeBorrow, SW_SHOW);
		ShowWindow(textTimeBorrow, SW_SHOW);
		ShowWindow(logOwnerID, SW_SHOW);
		ShowWindow(textOwnerID, SW_SHOW);

		ShowWindow(comboBoxUser, SW_HIDE);
		UpdateWindowBook(logStruct, comboBoxBook);
	}

	void SwitchToUser(){
		LogStruct logStruct;
		logStruct.LogID = logID;
		logStruct.LogTitle = logTitle;
		logStruct.LogIsOwned = logIsOwned;
		logStruct.LogTimeBorrow = logTimeBorrow;
		logStruct.LogOwnerID = logOwnerID;

		ShowWindow(comboBoxBook, SW_HIDE);
		ShowWindow(buttonBorrow, SW_HIDE);
		ShowWindow(logIsOwned, SW_HIDE);
		ShowWindow(textIsOwned, SW_HIDE);
		ShowWindow(logTimeBorrow, SW_HIDE);
		ShowWindow(textTimeBorrow, SW_HIDE);
		ShowWindow(logOwnerID, SW_HIDE);
		ShowWindow(textOwnerID, SW_HIDE);

		ShowWindow(comboBoxUser, SW_SHOW);
		UpdateWindowUser(logStruct, comboBoxUser);
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
				SendMessage(comboBoxBook, CB_GETLBTEXT, k, (LPARAM)&title.c_str()[0]);
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
			buttonLogout     = CreateWindow(WC_BUTTON, L"Logout",                WS_CHILD | WS_BORDER, colButtonLogout, rowButtonLogout, 50, 20, m_hwnd, NULL, NULL, NULL);
			
			logID         = CreateWindow(WC_EDIT, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, colLogID, rowLogID, 150, 20, m_hwnd, (HMENU)1, NULL, NULL);
			logTitle      = CreateWindow(WC_EDIT, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, colLogTitle, rowLogTitle, 150, 20, m_hwnd, (HMENU)1, NULL, NULL);
			logIsOwned    = CreateWindow(WC_EDIT, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, colLogIsOwned, rowLogIsOwned, 150, 20, m_hwnd, (HMENU)1, NULL, NULL);
			logTimeBorrow = CreateWindow(WC_EDIT, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, colLogTimeBorrow, rowLogTimeBorrow, 150, 20, m_hwnd, (HMENU)1, NULL, NULL);
			logOwnerID    = CreateWindow(WC_EDIT, L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, colLogOwnerID, rowLogOwnerID, 150, 20, m_hwnd, (HMENU)1, NULL, NULL);
			
			textID         = CreateWindow(WC_STATIC, L"ID:",          WS_VISIBLE | WS_CHILD | WS_BORDER, colTextID, rowTextID, 90, 20, m_hwnd, (HMENU)1, NULL, NULL);
			textTitle      = CreateWindow(WC_STATIC, L"Title:",       WS_VISIBLE | WS_CHILD | WS_BORDER, colTextTitle, rowTextTitle, 90, 20, m_hwnd, (HMENU)1, NULL, NULL);
			textIsOwned    = CreateWindow(WC_STATIC, L"Is Owned:",    WS_VISIBLE | WS_CHILD | WS_BORDER, colTextIsOwned, rowTextIsOwned, 90, 20, m_hwnd, (HMENU)1, NULL, NULL);
			textTimeBorrow = CreateWindow(WC_STATIC, L"Borrow Time:", WS_VISIBLE | WS_CHILD | WS_BORDER, colTextTimeBorrow, rowTextTimeBorrow, 90, 20, m_hwnd, (HMENU)1, NULL, NULL);
			textOwnerID    = CreateWindow(WC_STATIC, L"Owner ID:",    WS_VISIBLE | WS_CHILD | WS_BORDER, colTextOwnerID, rowTextOwnerID, 90, 20, m_hwnd, (HMENU)1, NULL, NULL);

			buttonBorrow    = CreateWindow(WC_BUTTON  , L"Borrow", WS_VISIBLE | WS_CHILD | WS_BORDER     , colBorrow, rowBorrow, 60, 20, m_hwnd, (HMENU)2, NULL, NULL);
			buttonAdd       = CreateWindow(WC_BUTTON  , L"Add" , WS_VISIBLE | WS_CHILD | WS_BORDER     , colAdd, rowAdd, 60, 20, m_hwnd, (HMENU)6, NULL, NULL);
			comboBoxPrimary = CreateWindow(WC_COMBOBOX, L""  ,                WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxPrim, rowCBoxPrim, 80, 500, m_hwnd, (HMENU)3, NULL, NULL);
			comboBoxBook    = CreateWindow(WC_COMBOBOX, L""  ,   WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxSec , rowCBoxSec, 100, 500, m_hwnd, (HMENU)4, NULL, NULL);
			comboBoxUser    = CreateWindow(WC_COMBOBOX, L""  ,                WS_CHILD | WS_OVERLAPPED | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | CBS_HASSTRINGS, colCBoxSec , rowCBoxSec, 100, 500, m_hwnd, (HMENU)5, NULL, NULL);
			
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

			return 0;

		case WM_COMMAND: {
			if (HIWORD(wparam) == BN_CLICKED) {
				if (lparam == LPARAM(buttonBorrow)) {
					if (BorrowBook() != -1) {
						saveDatabase();
						readDatabase();

						LogStruct logStruct;
						logStruct.LogID = logID;
						logStruct.LogTitle = logTitle;
						logStruct.LogIsOwned = logIsOwned;
						logStruct.LogTimeBorrow = logTimeBorrow;
						logStruct.LogOwnerID = logOwnerID;

						UpdateWindowBook(logStruct, comboBoxBook);
					}
				}
				else if (lparam == LPARAM(buttonAdd)) {
					SwitchToAdd();
				}
				else if (lparam == LPARAM(buttonCancel)) {
					SwitchToMain();
				}
				else if (lparam == LPARAM(buttonAddAlt)){
					int confirm = MessageBox(m_hwnd, L"Do you want add a book with these attributes?", L"Confirm", MB_OKCANCEL);
					if (confirm == IDOK) {
						std::wstring title;

						for (int i = 0; i <= bookList.size(); i++) {
							title.resize(SendMessage(logTitle, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
							SendMessage(logTitle, WM_GETTEXT, (WPARAM)title.size() + 1, (LPARAM)title.c_str());

							if (i == bookList.size()) {
								ClassBook(bookList.size() + 1, Narrowen(title));
								saveDatabase();
								readDatabase();
								InsertToCBoxBook();

								MessageBox(m_hwnd, L"Addition successful.", L"Success", MB_OK);
								break;
							}
							else if (title.empty()) {
								MessageBox(m_hwnd, L"Books must have a name.", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(title) == "Start book") {
								MessageBox(m_hwnd, L"A book's name cannot be \"Start book\".", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(title) == "End book") {
								MessageBox(m_hwnd, L"A book's name cannot be \"End book\".", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(title) == bookList[i].getTitle()) {
								MessageBox(m_hwnd, L"A book with this title already exists.", L"Error", MB_OK);
								break;
							}
						}
					}
				}
				else if (lparam == LPARAM(buttonLogin)) {
					std::wstring name;
					std::wstring password;
					name.resize(SendMessage(loginUser, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
					password.resize(SendMessage(loginPassword, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
					SendMessage(loginUser, WM_GETTEXT, (WPARAM)name.size() + 1, (LPARAM)name.c_str());
					SendMessage(loginPassword, WM_GETTEXT, (WPARAM)password.size() + 1, (LPARAM)password.c_str());

					int feedback = Login(Narrowen(name), Narrowen(password));
					if (feedback == -1) {
						MessageBox(m_hwnd, L"Could not find this user.", L"Error", MB_OK);
					}
					else if (feedback == -2) {
						MessageBox(m_hwnd, L"Password is incorrect.", L"Error", MB_OK);
					}
					else {
						SwitchLogin(1);
						SendMessage(loginUserBorder, WM_SETTEXT, NULL, (LPARAM)name.c_str());
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

						for (int i = 0; i <= userList.size(); i++) {
							name.resize(SendMessage(loginUser, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
							password.resize(SendMessage(loginPassword, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0));
							SendMessage(loginUser, WM_GETTEXT, (WPARAM)name.size() + 1, (LPARAM)name.c_str());
							SendMessage(loginPassword, WM_GETTEXT, (WPARAM)password.size() + 1, (LPARAM)password.c_str());

							if (i == userList.size()) {
								ClassUser(userList.size() + 1, Narrowen(name), Narrowen(password), 0);
								saveDatabase();
								readDatabase();
								InsertToCBoxUser();

								Login(Narrowen(name), Narrowen(password));
								SwitchLogin(1);
								SendMessage(loginUserBorder, WM_SETTEXT, NULL, (LPARAM)L"Registered");
								SendMessage(loginUser, WM_SETTEXT, NULL, (LPARAM)L"");
								SendMessage(loginPassword, WM_SETTEXT, NULL, (LPARAM)L"");
								MessageBox(m_hwnd, L"Register successful.", L"Success", MB_OK);
								break;
							}
							else if (name.empty()) {
								MessageBox(m_hwnd, L"Users must have a name.", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(name) == "Start user") {
								MessageBox(m_hwnd, L"A book's name cannot be \"Start user\".", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(name) == "End book") {
								MessageBox(m_hwnd, L"A book's name cannot be \"End user\".", L"Error", MB_OK);
								break;
							}
							else if (Narrowen(name) == userList[i].getName()) {
								MessageBox(m_hwnd, L"This name has already been taken.", L"Error", MB_OK);
								break;
							}
						}
					}
				}
				return 0;
			}

			else if (HIWORD(wparam) == CBN_SELCHANGE) {

				if (lparam == LPARAM(comboBoxPrimary)) {
					int selection = SendMessage(comboBoxPrimary, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					
					if (selection == 0) {
						SwitchToBook();
					}
					else if (selection == 1) {
						SwitchToUser();
					}
				}
				else if (lparam == LPARAM(comboBoxBook)) {
					LogStruct logStruct;
					logStruct.LogID = logID;
					logStruct.LogTitle = logTitle;
					logStruct.LogIsOwned = logIsOwned;
					logStruct.LogTimeBorrow = logTimeBorrow;
					logStruct.LogOwnerID = logOwnerID;

					UpdateWindowBook(logStruct, comboBoxBook);
				}
				else if (lparam == LPARAM(comboBoxUser)) {
					LogStruct logStruct;
					logStruct.LogID = logID;
					logStruct.LogTitle = logTitle;
					logStruct.LogIsOwned = logIsOwned;
					logStruct.LogTimeBorrow = logTimeBorrow;
					logStruct.LogOwnerID = logOwnerID;

					UpdateWindowUser(logStruct, comboBoxUser);
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

void UpdateWindowBook(LogStruct logStruct, HWND comboBoxBook){
	int selection = SendMessage(comboBoxBook, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	if (selection == -1) {
		SendMessage(logStruct.LogID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogTitle, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogIsOwned, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogTimeBorrow, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogOwnerID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	}
	else {
		int bookID;
		std::string bookTitle;
		int bookOwnerID;
		int bookTimeBorrow;
		std::wstring logText;

		for (int i = 0; i < bookList.size(); i++) {
			if (selection == i) {
				bookID = bookList[i].getID();
				bookTitle = bookList[i].getTitle();
				bookOwnerID = bookList[i].getOwnerID();
				bookTimeBorrow = bookList[i].getTimeBorrow();

				logText = Widen(bookID);
				SendMessage(logStruct.LogID, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());

				logText = Widen(bookTitle);
				SendMessage(logStruct.LogTitle, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
				
				if (bookOwnerID == 0) {
					logText = L"No";
					SendMessage(logStruct.LogIsOwned, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
				}
				else{
					logText = L"Yes";
					SendMessage(logStruct.LogIsOwned, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
				}

				logText = Widen(bookTimeBorrow);
				SendMessage(logStruct.LogTimeBorrow, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());

				logText = Widen(bookOwnerID);
				SendMessage(logStruct.LogOwnerID, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			}
		}
	}
}

void UpdateWindowUser(LogStruct logStruct, HWND comboBoxUser) {
	int selection = SendMessage(comboBoxUser, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	if (selection == -1) {
		SendMessage(logStruct.LogID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogTitle, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogIsOwned, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogTimeBorrow, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
		SendMessage(logStruct.LogOwnerID, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	}
	else {
		int userID;
		std::string userName;
		std::wstring logText;

		for (int i = 0; i < userList.size(); i++) {
			if (selection == i) {
				userID = userList[i].getID();
				userName = userList[i].getName();

				logText = Widen(userID);
				SendMessage(logStruct.LogID, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			
				logText = Widen(userName);
				SendMessage(logStruct.LogTitle, WM_SETTEXT, (WPARAM)0, (LPARAM)logText.c_str());
			}
		}
	}
}