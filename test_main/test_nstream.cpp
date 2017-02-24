// test_main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../LIB_nstream/lyf_nstream.h"
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
using namespace lyf;

void parse_url(const string& url, string& host, string& target)
{
	regex parse_rule("(http://)?([^/]+)(.*)");

	smatch sm;
	if(regex_match(url, sm, parse_rule))
	{ 
		host = sm[2];
		target = sm[3];
	}
}

//////////////////////////////////////////////////////////////////////////
void test_nstream(const string& url, const string& path)
{
	bool bSucc = nstream_startup();

	string remote = "tieba.baidu.com";
	string target = "p/4911617890";
	parse_url(url, remote, target);

	nstream ns;
	ns.open(remote);

	stringstream ss;
	ss << "GET " << target << " HTTP/1.1\r\n"
	<< "Host: "<<remote << "\r\n"
	<< "Accept: */*\r\n"
	<< "Connection:close\r\n" //重要！阻止recv在接受完数据后空等待
	<< "\r\n";

	ns << ss.str();
	string html;
	ns >> html;

	ofstream fout(path);
	fout << html;

	fout.close();

	nstream_shutdown();
}

void main()
{
	string url;
	cin >> url;
	test_nstream(url, "b.txt");

	system("start notepad b.txt");

}


