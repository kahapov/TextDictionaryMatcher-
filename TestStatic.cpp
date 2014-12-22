#include "BaseTest.h"
#include "StaticMatcher.h"
using std::make_pair;
using std::vector;

BOOST_AUTO_TEST_CASE(StaticMatcherSimpleTest) {
	TStaticTemplateMatcher TestStatic1;
	std::vector<TStringID> templates;
	templates.push_back(TestStatic1.AddTemplate("aba"));
	templates.push_back(TestStatic1.AddTemplate("cac"));
	templates.push_back(TestStatic1.AddTemplate("bac"));
	templates.push_back(TestStatic1.AddTemplate("aca"));
	templates.push_back(TestStatic1.AddTemplate("ba"));
	templates.push_back(TestStatic1.AddTemplate("abacaba"));
	TStringStream teststream1("abacaba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templates[0]));
	TrueAns1.push_back(make_pair(6,templates[5]));
	TrueAns1.push_back(make_pair(6,templates[0]));
	TrueAns1.push_back(make_pair(3,templates[2]));
	TrueAns1.push_back(make_pair(4,templates[3]));
	TrueAns1.push_back(make_pair(2,templates[4]));
	TrueAns1.push_back(make_pair(6,templates[4]));
	BOOST_CHECK(CompareResults(TestStatic1.MatchStream(teststream1), TrueAns1));
	teststream1.reset();
	
	templates.clear();
	TStaticTemplateMatcher TestStatic2;
	templates.push_back(TestStatic2.AddTemplate("aba"));
	templates.push_back(TestStatic2.AddTemplate("cac"));
	templates.push_back(TestStatic2.AddTemplate("bac"));
	templates.push_back(TestStatic2.AddTemplate("aca"));
	templates.push_back(TestStatic2.AddTemplate("ba"));
	templates.push_back(TestStatic2.AddTemplate("abacaba"));
	templates.push_back(TestStatic2.AddTemplate("a"));
	TrueAns1.push_back(make_pair(0,templates[6]));
	TrueAns1.push_back(make_pair(2,templates[6]));
	TrueAns1.push_back(make_pair(4,templates[6]));
	TrueAns1.push_back(make_pair(6,templates[6]));
	BOOST_CHECK(CompareResults(TestStatic2.MatchStream(teststream1), TrueAns1));

	TStringStream teststream2("112312ba");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(7,templates[4]));
	TrueAns2.push_back(make_pair(7,templates[6]));
	BOOST_CHECK(CompareResults(TestStatic2.MatchStream(teststream2), TrueAns2));

	TStaticTemplateMatcher TestStatic3;
	TMatchResults TrueAns4;
	TStringStream teststream3("baacaababa");
	TStringID templateid= TestStatic3.AddTemplate("ba");
	TrueAns4.push_back(make_pair(1,templateid));
	TrueAns4.push_back(make_pair(7,templateid));
	TrueAns4.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns4,TestStatic3.MatchStream(teststream3)));
}

BOOST_AUTO_TEST_CASE(DynamicMatcherFailTest) {
	TDynamicTemplateMatcher TestDynamic1;
	TestDynamic1.AddTemplate("test");
	BOOST_CHECK_THROW(TestDynamic1.AddTemplate("test"),std::logic_error);

}

BOOST_AUTO_TEST_CASE(DynamicMatcherSimpleTest) {
	TDynamicTemplateMatcher TestDynamic1;
	std::vector<TStringID> templates;
	templates.push_back(TestDynamic1.AddTemplate("aba"));
	templates.push_back(TestDynamic1.AddTemplate("cac"));
	templates.push_back(TestDynamic1.AddTemplate("bac"));
	templates.push_back(TestDynamic1.AddTemplate("aca"));
	templates.push_back(TestDynamic1.AddTemplate("ba"));
	templates.push_back(TestDynamic1.AddTemplate("abacaba"));
	TStringStream teststream1("abacaba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templates[0]));
	TrueAns1.push_back(make_pair(6,templates[5]));
	TrueAns1.push_back(make_pair(6,templates[0]));
	TrueAns1.push_back(make_pair(3,templates[2]));
	TrueAns1.push_back(make_pair(4,templates[3]));
	TrueAns1.push_back(make_pair(2,templates[4]));
	TrueAns1.push_back(make_pair(6,templates[4]));
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	templates.push_back(TestDynamic1.AddTemplate("a"));
	TrueAns1.push_back(make_pair(0,templates[6]));
	TrueAns1.push_back(make_pair(2,templates[6]));
	TrueAns1.push_back(make_pair(4,templates[6]));
	TrueAns1.push_back(make_pair(6,templates[6]));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	TStringStream teststream2("112312ba");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(7,templates[4]));
	TrueAns2.push_back(make_pair(7,templates[6]));
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream2), TrueAns2));
	templates.clear();
	TDynamicTemplateMatcher TestDynamic3;
	templates.push_back(TestDynamic3.AddTemplate("a"));
	templates.push_back(TestDynamic3.AddTemplate("aa"));
	templates.push_back(TestDynamic3.AddTemplate("aaa"));
	TStringStream teststream3("aaaaaaa");
	TMatchResults TrueAns3;
	TrueAns3.push_back(make_pair(0,templates[0]));
	TrueAns3.push_back(make_pair(1,templates[0]));
	TrueAns3.push_back(make_pair(2,templates[0]));
	TrueAns3.push_back(make_pair(3,templates[0]));
	TrueAns3.push_back(make_pair(4,templates[0]));
	TrueAns3.push_back(make_pair(5,templates[0]));
	TrueAns3.push_back(make_pair(6,templates[0]));
	TrueAns3.push_back(make_pair(1,templates[1]));
	TrueAns3.push_back(make_pair(2,templates[1]));
	TrueAns3.push_back(make_pair(3,templates[1]));
	TrueAns3.push_back(make_pair(4,templates[1]));
	TrueAns3.push_back(make_pair(5,templates[1]));
	TrueAns3.push_back(make_pair(6,templates[1]));
	TrueAns3.push_back(make_pair(2,templates[2]));
	TrueAns3.push_back(make_pair(3,templates[2]));
	TrueAns3.push_back(make_pair(4,templates[2]));
	TrueAns3.push_back(make_pair(5,templates[2]));
	TrueAns3.push_back(make_pair(6,templates[2]));
	BOOST_CHECK(CompareResults(TestDynamic3.MatchStream(teststream3),TrueAns3));
	TDynamicTemplateMatcher TestDynamic4;
	TMatchResults TrueAns4;
	TStringStream teststream4("baacaababa");
	TStringID templateid= TestDynamic4.AddTemplate("ba");
	TrueAns4.push_back(make_pair(1,templateid));
	TrueAns4.push_back(make_pair(7,templateid));
	TrueAns4.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns4,TestDynamic4.MatchStream(teststream4)));
}

BOOST_AUTO_TEST_CASE(T2DSingleMatcherSimpleTest) {
	T2DSingleTemplateMatcher TestT2DSingle1;
	vector<string> A;
	vector<string> B;
	A.push_back("ab");
	A.push_back("ab");
	B.push_back("aabb");
	B.push_back("abab");
	B.push_back("abab");
	B.push_back("bbaa");
	TestT2DSingle1.AddTemplateTable(A);
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,1));
	TrueAns1.push_back(make_pair(2,3));
	BOOST_CHECK(CompareResults(TestT2DSingle1.MatchTable(B),TrueAns1));
	T2DSingleTemplateMatcher TestT2DSingle2;
	A.clear();
	B.clear();
	A.push_back("bca");
	A.push_back("bab");
	B.push_back("ababcaab");
	B.push_back("bbcbabca");
	B.push_back("abcaabab");
	B.push_back("baabcbab");
	B.push_back("bbcaaabc");
	B.push_back("cbabacca");
	TMatchResults TrueAns2;
	TestT2DSingle2.AddTemplateTable(A);
	TrueAns2.push_back(make_pair(1,5));
	TrueAns2.push_back(make_pair(2,7));
	TrueAns2.push_back(make_pair(5,3));
	BOOST_CHECK(CompareResults(TestT2DSingle2.MatchTable(B),TrueAns2));
}