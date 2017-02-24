#include <string>
#include <fstream>
#include <sstream>

using namespace  std;

//=======================================================================
// ͨ��rdbuf�������ݿ�����Ч�ʼ�������                                                                
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
// ͨ��steambuf_iterator�������ݿ���                           
//=======================================================================
bool readFileToString2(const string& file_name, string& content) 
{
	ifstream fin(file_name);
	if (!fin)
		return false;

	//��Ϊ����iftreamָ����խ�ͣ������ػ�char�͵�û����
	//�����wifsteam,��Ҫ��wchar�ػ�
	istreambuf_iterator<char> beg(fin), end;
	content = string(beg, end);

	return true;
}