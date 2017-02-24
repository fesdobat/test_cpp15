#include <string>
#include <fstream>
#include <sstream>

using namespace  std;

//=======================================================================
// 通过rdbuf进行数据拷贝。效率极大提升                                                                
//=======================================================================
bool readFileToString(const string& file_name, string& content)
{
	ifstream fin(file_name);
	if (!fin)
		return false;

	ostringstream oss;
	oss << fin.rdbuf();
	content = oss.str();

	return true;
}

//=======================================================================
// 通过steambuf_iterator进行数据拷贝                           
//=======================================================================
bool readFileToString2(const string& file_name, string& content) 
{
	ifstream fin(file_name);
	if (!fin)
		return false;

	//因为这里iftream指定了窄型，所以特化char型的没问题
	//如果是wifsteam,则要用wchar特化
	istreambuf_iterator<char> beg(fin), end;
	content = string(beg, end);

	return true;
}