#include <iostream>
#include <regex>
#include <set>
#include <cpr/cpr.h>

using namespace std;

set<string> getUrls(istream& in, regex reg)
{
	set<string> strs;
	smatch m;
	for (string s; getline(in, s);) // read a line
		if (regex_search(s, m, reg))
			strs.insert(m[0]); // save match in set
	return strs;
}

int main() {
	auto response = cpr::Get(cpr::Url{ "https://git-scm.com/" });
	//auto response = cpr::Get(cpr::Url{ "https://mail.ru" });
	//std::cout << response.text << std::endl;
	std::ofstream out("a.txt", std::ios::out);
	out << response.text;
	out.close();
	std::ifstream in("a.txt");
	regex reg{ R"((https?|ftp):\/\/([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w\.-]*)*\/?)" }; // URL
	for (auto x : getUrls(in, reg)) // look for URLs
		cout << x << '\n';
	return 0;
}