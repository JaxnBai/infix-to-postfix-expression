#include<iostream>
#include<algorithm>
#include<stack>
#include<cstring>
#include<cmath>
using namespace std;
stack<char>res, op;
int priority(char c)
{
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '(' || c == ')')
		return 0;
	return 3;
}
void print(string s, int index, int len)
{
	for (int i = index; i < len-1; i++)
		cout << s[i] << ' ';
		cout << s[len-1] <<endl;
}
int str_to_num(string s)//将string变量转化为int类型的数据
{
	int res = 0,len=s.length();
	if (s[0] == '-')
	{
		for (int i = 1; i < len; i++)
			res = res * 10 + s[i] - '0';
		return -1 * res;
	}
	for (int i = 0; i < len; i++)
		res = res * 10 + s[i] - '0';
	return res;
}
string num_to_str(int x)//将int变量x转化成string类型变量
{
	int stack[100] = { 0 },cnt=0,len=0;
	int flag = 1;
	if (x)
		flag = x / abs(x);
	x = abs(x);
	string s;
	while (x)
	{
		stack[cnt++] = x % 10;
		x = x / 10;
	}
	cnt--;
	if (flag == -1)
	{
		string str;
		str = '-';
		s.insert(len, str);
		len++;
	}
	while (cnt >= 0)
	{
		string str;
		str = stack[cnt] + '0';
		s.insert(len, str);
		cnt--;
		len++;
	}
	return s;
}
int main()
{
	string s, num[100000];
	cin >> s;
	int len = s.length(),cnt=0,flag=0,i=0;
	while( i < len)
	{
		if (s[i] >= '0' && s[i] <= '9')
			res.push(s[i]);
		else if (s[i] == '(')
		{
			flag++;
			cnt+= 2;
			op.push(s[i]);
		}
		else if (s[i] == ')')
		{
			flag--;
			char c;
			while ((c = op.top()) != '(')
			{
				op.pop();
				res.push(c);
			}
			op.pop();
		}
		else {
			int f = 1;
			while (f&&!op.empty())
			{
				char c = op.top();
				int topp = priority(c);
				int newp = priority(s[i]);
				if ((newp > topp) || (newp == 3 && topp == 3))
					f = 0;
				else {
					res.push(c);
					op.pop();
					f = 1;
				}
			}
			op.push(s[i]);
		}
		 i++;
	}
	while (!op.empty())
	{
		res.push(op.top());
		op.pop();
	}
	len -= cnt;
	cnt = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		s[i] = res.top();
		res.pop();
	}
	print(s, 0, len);
	for ( i = 0; i<len; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			num[cnt++] = s[i];
		else {
			string num1 = num[cnt - 1];
			cnt--;
			string num2 = num[cnt - 1];
			cnt--;
			switch (s[i]) {
			case '+':num[cnt++] = num_to_str(str_to_num(num1)+str_to_num(num2)); break;
			case '-':num[cnt++] = num_to_str(str_to_num(num2)-str_to_num(num1)); break;
			case '*':num[cnt++] = num_to_str(str_to_num(num1) *str_to_num(num2)); break;
			case '/':num[cnt++] = num_to_str(str_to_num(num2)/str_to_num(num1)); break;
			case '^':num[cnt++] = num_to_str(pow(str_to_num(num2),str_to_num(num1))); break;
			}
			if (i < len - 1)
			{
				for (int i = 0; i < cnt; i++)
					cout << num[i] << ' ';
				print(s, i + 1, len);
			}
			else cout << num[0];

		}
	}
}
