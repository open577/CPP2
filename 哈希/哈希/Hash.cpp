#include"Hash.h"
int main()
{
	/*open_addressing::HashTable<int, int> a;
	int arr[] = { 19,30,5,36,13,20,21,12 };
	for (auto& e : arr)
	{
		a.Insert({ e,e });
	}
	a.Insert({ 89,89 });
	if (a.Find(19))
		cout << "找到了" << endl;
	if (a.Erase(19))
		cout << "已删除" << endl;
	if (a.Find(19))
		cout << "找到了" << endl;*/

	hash_bucket::HashTable<int, int> a1;
	int arr2[] = { 19,30,5,36,13,20,21,12,24,96 };
	for (auto& e : arr2)
	{
		a1.Insert({ e,e });
	}
	a1.Insert({ 89,89 });
	a1.Insert({ 101,101 });
	
	cout << a1.Find(19) << endl;
	cout << a1.Erase(19) << endl;
	cout << a1.Find(19) << endl;
	return 0;
}