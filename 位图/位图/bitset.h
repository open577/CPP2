#include<iostream>
#include<vector>
using namespace std;
namespace wyy
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			_bs.resize(N / 32 + 1);//进一，防止数据丢失
		}

		//x映射的位标记为1
		void set(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] |= (1 << j);
		}

		//x映射位标记为0
		void reset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bs[i] &= (~(1 << j));
		}

		//x映射的位为1，返回1
		//x映射的位为0，返回0
		bool test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			return  _bs[i] & (1 << j);
		}
	private:
		vector<int> _bs;
	};
}