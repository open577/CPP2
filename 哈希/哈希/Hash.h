#include<iostream>
#include<vector>
using namespace std;
enum State
{
	EXIST,
	EMPTY,
	DELETE
};

template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

//库里面的扩容机制
inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}
namespace open_addressing
{
	template<class K, class V>
	struct HashTable
	{
	public:
		HashTable()
			:_tables(11)
			, _n(0)
		{
		}

		bool Insert(const pair<K, V>& kv)
		{
			//扩容
			if (_n * 10 / _tables.size() >= 7)
			{
				HashTable newtable;
				newtable._tables.resize(__stl_next_prime(newtable._n + 1));
				for (auto& tab : _tables)
				{
					// 旧表的数据映射到新表
					if (tab._state == EXIST)
						newtable.Insert(tab._kv);
				}

				/*for (auto& data : _tables)
				{

					if (data._state == EXIST)
					{
						newht.Insert(data._kv);
					}
				}*/
				_tables.swap(newtable._tables);
				swap(_n, newtable._n);

			}


			int i = 1;
			size_t hash0 = kv.first % _tables.size();
			size_t hashi = hash0;
			while (_tables[hashi]._state != EMPTY)
			{
				hashi = (hash0 + i) % _tables.size();
				i++;
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			_n++;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			size_t hash0 = key % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}

				hashi = (hash0 + i) % _tables.size();
				i++;
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				_n--;
				return true;
			}

			else
				return false;
		}
	private:
		vector<HashData<K, V>> _tables;
		size_t _n;
	};
}

namespace hash_bucket
{
	template<class K>
	struct HashFunc
	{
		size_t operator()(const K& key)
		{ 
			return (size_t)key;
		}
	};

	template<>
	struct HashFunc<string>
	{
		size_t operator()(const string& s)
		{
			size_t i = 0;
			for (auto ch : s)
			{
				i = i * 131 + ch;
			}
			return i;
		}
	};

	template<class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K,V>* _next;

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{ }
	};

	

	template<class K,class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_tables(11)
			,_n(0)
		{ }

		bool Insert(const pair<K,V>& kv)
		{
			Hash hash;
			//扩容
			if (_n == _tables.size())
			{
				vector<Node*> newtable(_tables.size() * 2);
				for (int i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						//size_t hashi = cur->_kv.first % newtable.size();//找到新位置
						size_t hashi = hash(cur->_kv.first) % newtable.size();//找到新位置
						//头插
						cur->_next = newtable[hashi];
						newtable[hashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				swap(newtable, _tables);
			}

			size_t hashi = hash(kv.first) % _tables.size();
			//头插
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			_n++;

			return true;
		}

		Node* Find(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
					return cur;

				cur = cur->_next;
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
						_tables[hashi] =cur->_next;

					else
						prev->_next = cur->_next;
					delete cur;
					--_n;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _n;
	};
}