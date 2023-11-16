#include <iostream>
using namespace std;
int* preProcess(string s) {
	int* LPS = new int[s.size()];
	LPS[0] = 0;
	int pos = 1;
	int len = 0;
	while (pos < s.size()) {
		if (s[len] == s[pos]) {
			LPS[pos] = LPS[pos - 1] + 1;
			len++;
			pos++;
		}
		else {
			if (len == 0) {
				LPS[pos] = 0;
				pos++; 
				len=0;
			}
			else {
				len = LPS[len - 1];

			}
		}
	}
	return LPS;
}

int find(string s, string pattern) {
	int* LPS = preProcess(pattern);
	int pos1 = 0, pos2 = 0;
	while (pos1 < s.size() && pos2 < pattern.size()) {
		if (s[pos1] == pattern[pos2]) {
			pos1++;
			pos2++;
		}
		else {
			if (pos2 == 0) {
				pos1++;
				pos2++;
				
			}
			else {
				pos2 = LPS[pos2 - 1];
				
			}


		}
	}
	if (pos1 == s.size())
		return -1;
	else
		return pos1 - pattern.size();

}
int main()
{
	string s1,s2;
	cin >> s1>>s2;
	cout << find(s1, s2);

	



}
