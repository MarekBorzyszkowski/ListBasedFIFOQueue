#include "pch.h"
#include "CppUnitTest.h"
#include "../projekt_3_list_based_fifo_queue/circulardoublelinkedlist.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(NodeTest)
	{
	public:
		TEST_METHOD(EmptyNodeTest)
		{
			Node<int> emptyNode;
			emptyNode.value = nullptr;
			Assert::AreEqual(emptyNode.value, (int*)nullptr);
		}
		TEST_METHOD(EqualNodeIntTest) {
			Node<int> emptyNode;
			int* a = new int(1);
			emptyNode.value = a;
			Assert::AreEqual(emptyNode.value, a);
		}
		TEST_METHOD(EqualNodeDoubleTest) {
			Node<double> emptyNode;
			double* a = new double(1.12037123);
			emptyNode.value = a;
			Assert::AreEqual(emptyNode.value, a);
		}
		TEST_METHOD(EqualNodepointerTest) {
			Node<double> emptyNode;
			double* a = new double(1.1);
			emptyNode.value = a;
			 a = new double(1.2);
			//Assert::AreEqual(emptyNode.value, a);
			Assert::AreNotEqual(*emptyNode.value, *a);
		}
		TEST_METHOD(EqualNodeReferenceTest) {
			Node<double> emptyNode;
			double* a = new double(1.1);
			emptyNode.value = a;
			a = new double(1.2);
			//*a = 1.1;
			Assert::AreNotEqual(emptyNode.value, a);
		}
	};
}
