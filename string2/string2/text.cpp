#define  _CRT_SECURE_NO_WARNINGS
//using namespace std;
//namespace wyy
//{
//	class string
//	{
//		char* _str;
//	public:
//		/*string(string = "")
//		{
//			_str = nullptr;
//		}*/
//		void swap(string& s)
//		{
//			std::swap(s._str, _str);
//		}
//		/*string(const string& s)
//		{
//			string tmp = s;
//			swap(tmp);
//		}*/
//	};
//}
//int main()
//{
//	
//	wyy::string s1 = ("hello world");
//	wyy::string s2 = s1;
//	return 0;
//
//}
#include<iostream>
#include<assert.h>
using namespace std;
namespace wyy
{
	class string
	{
	public:
		/*string&operator=(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
			return *this;
		}*/
		//现代写法
		string& operator=(string tmp)
		{
			swap(tmp);
			return *this;
		}
		void swap(string&s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);

		}
		//现代写法
		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
		}
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		const char* c_str()const

		{
			return _str;
		}
		size_t size()
		{
			return _size;
		}
		size_t capacity()
		{
			return _capacity;
		}
		void  clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		//仅查找
		const char& operator[](size_t  n)const
		{
			if (n > _size)
			{
				assert("不存在");
			}
			return _str[n];
		}
		char& operator[](size_t  n)
		{
			if (n > _size)
			{
				assert("不存在");
			}
			return _str[n];
		}
		friend ostream& operator<<(ostream&out,const string& s)
		{
			out << s._str;
			return out;
		}
		//void  Text();
		//void reserve(size_t n);
		//void push_back(const char ch);
		////string& operator+=(const char ch);
		////string& operator= (const char* str);
		////string& operator=(const string& other);
		//void insert(size_t pos, char ch);
		//void erase(size_t pos, size_t len = INT16_MAX);
	private:
		char* _str;
		int  _size;
		int  _capacity;

	};
}

int main()
{
	wyy::string s1 = ("hello world");
	wyy::string s2 = s1;
	s1 = s2;
	cout << s1 << endl << s2 << endl;
	return 0;
}