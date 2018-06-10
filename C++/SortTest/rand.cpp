#include<bits/stdc++.h>
using namespace std;
int main()
{
	cout<<std::numeric_limits<short int>::max()<<endl;
	for(int i=1;i<std::numeric_limits<short int>::max();i++)
	{
	    cout<<i<<" "<<"a\n";
	}
	cout<<"1\n2\n3\n4\n5\n";
	cout<<std::numeric_limits<short int>::max()<<endl;
	for(int i=std::numeric_limits<short int>::max();i>1;i--)
	{
	    cout<<i<<" "<<"a\n";
	}
	cout<<"1\n2\n3\n4\n5\n";
	cout<<std::numeric_limits<short int>::max()<<endl;
	for(int i=0;i<std::numeric_limits<short int>::max();i++)
	{
	    cout<<rand()%std::numeric_limits<short int>::max()<<" "<<"a\n";
	}
	cout<<"1\n2\n3\n4\n6\n";
}
