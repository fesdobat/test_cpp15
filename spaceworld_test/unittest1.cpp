#include "stdafx.h"
#include "CppUnitTest.h"
#include "../spaceworld_demo/spaceworld_impl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace spaceworld_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Logger::WriteMessage("test passed!");
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(TestMethod2)
		{
			Logger::WriteMessage("begin test !");
			Assert::AreEqual(1, 2);
			// TODO: 在此输入测试代码
		}
		TEST_METHOD(Test_FillCollisionMap)
		{
			auto& map = CollisionMap();
			Assert::AreEqual(8U, map.size());
		
			FillCollisionMap();

			auto&  clsmap = ClassMap_test();
			int nClass = clsmap.size()+1;
			char msg[512];
			sprintf(msg, "class in hierarchy : %d\n", nClass);
			Logger::WriteMessage(msg);
			int ncolision = (nClass + 1)*nClass / 2;
			Assert::AreEqual(ncolision, (int)map.size());
		}
	};
}