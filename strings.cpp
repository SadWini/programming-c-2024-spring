#include <string>
#include <iostream>
#include <vector>

using namespace std;
bool checkIP(string s) {
	int current, count = 0;
	string temp;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '.') {
			count += 1;
			if (count > 3 || temp == "")
				return false;
			current = stoi(temp);
			if (current < 0 || current > 255)
				return false;
			temp = "";
		}
		else {
			temp += s[i];
		}
	}
	current = stoi(temp);
	if (current < 0 || current > 255)
		return false;
	return true;
}

void parenthesisSubstr(string &x, string &y) {
	int index = x.find(y);
	int temp = 0;
	while (index != -1) {
		x.insert(index + y.length(), ")");
		x.insert(index, "(");
		temp = index + y.length() + 2;
		index = x.find(y, temp);
	}
}

void doSum(string &s) {
	string temp1, temp2;
	int x, y;
	string res;
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i])) {
			temp1 = s[i];
			i += 1;
			while (isdigit(s[i]) || s[i] == '+') {
				if (s[i] == '+') {
					if (temp2 != "") {
						x = stoi(temp1);
						y = stoi(temp2);
						temp1 = to_string(x + y);
						temp2 = "";
					} else {
						i += 1;
						if (isdigit(s[i])) {
							temp2 += s[i];
							i += 1;
							while (isdigit(s[i])) {
								temp2 += s[i];
								i++;
							}
							x = stoi(temp1);
							y = stoi(temp2);
							temp1 = to_string(x + y);
							temp2 = "";
						}
						else {
							res += temp1 + "+";
							i -= 1;
						}
					}
				} else {
					temp1 += s[i];
					i++;
				}
			}
			res += temp1;
			i -= 1;
		}else {
			temp1 = "";
			temp2 = "";
			res += s[i];
		}
	}
	s = res;
}

void fullStrSimple(string &s) {
	int f = s.find_first_of('{');
	int l = s.find_last_of('}');
	string temp, res;
	for (int i = f + 1; i <= l; i++) {
		if (s[i] != ',' && s[i] != '}')
			temp += s[i];
		else {
			res += s.substr(0, f) + temp + s.substr(l + 1) + ',';
			temp = "";
		}
	}
	s = res.substr(0, res.length() - 1);
}

vector<string> unpack(string s);

vector<string> split(string s) {
	vector<string> list;
	int level = 0;
	string block = "";
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '{') ++level;
		else if (s[i] == '}') --level;
		if (s[i] == ',' && level == 0) {
			vector<string> unpacked = unpack(block);
			list.insert(list.end(), unpacked.begin(), unpacked.end());
			block = "";
		}
		else block += s[i];
	}
	vector<string> unpacked = unpack(block);
	list.insert(list.end(), unpacked.begin(), unpacked.end());
	return list;
}

vector<string> unpack(string s) {
	vector<string> list = { "" };
	int level = 0;
	string block = "";
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '{' && level++ == 0) {
			for (int j = 0; j < list.size(); ++j) {
				list[j] += block;
			}
			block = "";
		}
		else if (s[i] == '}' && --level == 0) {
			vector<string> parts = split(block);
			vector<string> newlist;
			for (int j = 0; j < list.size(); ++j) {
				for (int k = 0; k < parts.size(); ++k) {
					newlist.push_back(list[j] + parts[k]);
				}
			}
			list = newlist;
			block = "";
		}
		else {
			block += s[i];
		}
	}
	for (int j = 0; j < list.size(); ++j) {
		list[j] += block;
	}
	return list;
}

int main() {
	string s, temp;
	s = "192.255..50";
	cout << checkIP(s) << endl;
	string x, y;
	x = "ertabcsdftyuabczevbh";
	y = "abc";
	parenthesisSubstr(x, y);
	cout << x << endl;
	string t = "5+26-72+35gh32+45";
	doSum(t);
	cout << t << endl;
	string data = "abc{def,gh,ijkl}mn";
	fullStrSimple(data);
	cout << data << endl;

	string input = "ab{cde{fg,h}xy,st{uv,zx}d}wer";
	string res = "";
	vector<string> result = unpack(input);
	for (const auto& word : result) {
		res += word + ",";
	}
	res = res.erase(res.length() - 1, 1);
	cout << res << endl;
	return 0;
}