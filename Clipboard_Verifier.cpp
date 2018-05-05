// Clipboard_Verifier.cpp : Defines the entry point for the console application.
//

#include <string>
#include <Windows.h>
#include <tchar.h>
#include <iostream>

std::wstring GetClipboardText()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
		return _TEXT("error");

			// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_UNICODETEXT); // Change CF_UNICODETEXT to CF_TEXT if you are using for ANSI text
	if (hData == nullptr)
		return _TEXT("error");

			// Lock the handle to get the actual text pointer
		TCHAR * pszText = static_cast<TCHAR*>(GlobalLock(hData));
	if (pszText == nullptr)
		return _TEXT("error");

			// Save text in a string class instance
		std::wstring text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}

int main()
{
	std::wstring result = GetClipboardText();
	std::wcout << result << std::endl;
	for (int i = 0; i < result.length(); i++) {
		std::wcout << result[i] << ":" << std::hex << static_cast<int>(result[i]) << " ";
	}

	system("PAUSE");

	return 0;
}

