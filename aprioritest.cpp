#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

map<set<char>,int> calculate(vector<vector<char>>&transactions,int size)
{map<set<char>,int>freq;
    for(auto &transaction:transactions)
{if(transaction.size()>=size)
{vector<bool>v(transaction.size(),true);
for(int i=0;i<size;i++)
{v[i]=false;}

do{
set<char>a;
for(int i=0;i<transaction.size();i++)
{if(!v[i])
{
a.insert(transaction[i]);
}}

freq[a]++;

}while(next_permutation(v.begin(),v.end()));}}
return freq;}

int main()
{
    cout<<"enter minimum support";
    int minsupport;
    cin>>minsupport;
    vector<vector<char>>transactions={{'A','B'},{'A'},{'A','B'}};
    int maxisize=0;
    set<set<char>>itemsets;
    for(int i=0;i<transactions.size();i++)
    {maxisize=max(static_cast<int>(transactions[i].size()),maxisize);}
    for(int i=1;i<=maxisize;i++)
    {map<set<char>,int>temp=calculate(transactions,i);
    for(auto it=temp.begin();it!=temp.end();it++)
    {if(it->second>=minsupport)
    {itemsets.insert(it->first);}}}
    
     for(auto it=itemsets.begin();it!=itemsets.end();it++)
    {for(char ch:*it)
        {
        cout<<ch;
    }cout<<"   ";}

    
    
    
    
    
    return 0;}