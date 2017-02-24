
#include "stdafx.h"

#include <vector>
#include <string>
#include <regex>
#include "assert.h"
#include <sstream>
#include <functional>
#include <fstream>
#include "utility_lyf.h"


using namespace std;

string webpage_url = "../abc.htm";

void getstring_fromconsole(function<void(string&)> f)
{
	string content;
	while (cin >> content)
	{
		if (content == ".")
			break;
		f(content);
	}
}

vector<regex> readRegexRules()
{
	vector<string> rules;
	vector<regex> paterns;
	string temp;
	ifstream fin("rule.txt");
	while (getline(fin, temp))
		rules.push_back(temp);
	fin.close();
	for (auto s : rules)
	{
		cout << s << endl;
		try
		{
			paterns.push_back(regex(s));
		}
		catch (const std::exception& e)
		{
			cout << e.what();
		}
	}
	return paterns;
}

void parse_html_demo()
{
	vector<regex> paterns = readRegexRules();

	//readFileToString("a.txt", content);
	string content;
	assert(readFileToString(webpage_url, content));

	
	string header("null,null,null,null,null,null,null,0,null,[\"");
	auto start = content.cbegin() + content.find(header);
	//auto start = content.cbegin();
	auto end = content.cend();

	vector<string> usernames;
	vector<string> comments;
	ofstream fout("a.txt");
	auto proc = [&](){
		cout << "searching : \n";
		smatch cm;
		while(regex_search(start, end, cm, paterns[0]))
		{
			cout << cm[1] << endl;
			fout << "============================================================\n"
				 <<  cm[1] << endl;
			usernames.push_back(cm[1]);
			start = cm.suffix().first;

			[&,start,end, cm]() mutable ->void {
				start = cm[0].first;
				end = cm[0].second;
				ostringstream oss;
				while(regex_search(start, end, cm, paterns[1]))
				{
					if (!cm[1].matched)
						oss << endl;
					else
						oss << cm[1] << endl;
					start = cm.suffix().first;
				}
				cout << oss.str();
				fout << oss.str();
				comments.push_back(oss.str());
			}();
		}
	};

	//cout.imbue(locale("chs"));
	proc();

	system("pause");
	return;

}

void bug_demo();
void main()
{
	parse_html_demo();
}