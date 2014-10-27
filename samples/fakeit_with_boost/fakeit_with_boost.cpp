// fakeit_with_boost.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define BOOST_TEST_MODULE MyTest
#include "boost/test/unit_test.hpp"

int add(int i, int j) { return i + j; }

#include "fakeit.hpp"
#include "IGraphic.hpp"
#include "SquareTool.hpp"

using namespace fakeit;

struct S
{
	virtual void f() = 0;
};

struct C
{
	virtual void f() {}
};

BOOST_AUTO_TEST_CASE(TestClass)
{
	Mock<IGraphics> graphicsMock;
	Fake(Method(graphicsMock, DrawLine));

	SquareTool squareTool;
	squareTool.setStart(0, 0);
	squareTool.setSize(10);
	squareTool.DrawOn(graphicsMock.get());

	Verify(Method(graphicsMock, DrawLine)(0, 0, 10, 0));
	Verify(Method(graphicsMock, DrawLine)(10, 0, 10, 10));
	Verify(Method(graphicsMock, DrawLine)(10, 10, 0, 10));
	Verify(Method(graphicsMock, DrawLine)(0, 10, 0, 0));

	Verify(Method(graphicsMock, DrawLine)(0, 0, 10, 0) + Method(graphicsMock, DrawLine)(0, 0, 10, 10));

	// Will file since there are more invocations.
	VerifyNoOtherInvocations(Method(graphicsMock, DrawLine));
}