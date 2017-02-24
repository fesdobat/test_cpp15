#include "stdafx.h"
#include <regex>
#include <windows.h>

void bug_demo()
{
#if 1
	string s = "<cc>12dwdwdwd2ddddwdw���Ҷ��Ҷ����Ҷ��Ҷ���3��ζ��dwdwdc cecwcfd "
		"dwje28ye2830rh203ryh293r r2 r293ru-2923-ru23-0ru2 3-r3-ur-32r 23-ru -2r3-2 </cc>";
	string rs = R"(<cc>([\s\S]*)</cc>)";
	regex rule(rs);

	cout << "Ŀ���ַ����ǣ�" << endl;
	cout << s << endl;
	cout << "������ʽ�ǣ�" << endl;
	cout << rs << endl;
	system("pause");
	//wregex rule(LR"(<cc>([\w\W]*)</cc>)");
	//wregex rule(LR"(<cc>([\d\D]*)</cc>)");

	smatch sm;

	regex_search(s.cbegin(), s.cend(), sm, rule);
	string ss = sm[1];

	cout << "��regex�����ƥ���ǣ�" << endl;
	cout << ss << endl;
	system("pause");

#else
	wstring s = L"<cc>12dwdwdwd2ddddwdw���Ҷ��Ҷ����Ҷ��Ҷ���3��ζ��dwdwdc cecwcfd "
		"dwje28ye2830rh203ryh293r r2 r293ru-2923-ru23-0ru2 3-r3-ur-32r 23-ru -2r3-2 </cc>";
	wstring rs = LR"(<cc>([\s\S]*)</cc>)";
	wregex rule(rs);

	auto wl = [](const wchar_t* wstr) {
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), wstr, wcslen(wstr), NULL, NULL); 
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"\r\n", wcslen(L"\r\n"), NULL, NULL);
	};
	wl(L"Ŀ���ַ����ǣ�");
	wl(s.c_str());
	wl(L"������ʽ�ǣ�");
	wl(rs.c_str());
	system("pause");
	//wregex rule(LR"(<cc>([\w\W]*)</cc>)");
	//wregex rule(LR"(<cc>([\d\D]*)</cc>)");

	wsmatch sm;

	regex_search(s.cbegin(), s.cend(), sm, rule);
	wstring ss = sm[1];

	wl(L"��regex�����ƥ���ǣ�");
	wl(ss.c_str());
	system("pause");
#endif
}