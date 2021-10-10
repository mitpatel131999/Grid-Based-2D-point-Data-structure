/*
  
  PGLAB- 5

  Mit Patel    - 2020CSM1016
  Satbir Singh - 2020AIM1016

  Date 7-5-2021 
-----------------------------------------------------

*/



// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;



class Ract
{
    public:
    
    pair<int,int> x1;
    pair<int,int> x2;
    
};



int inside(Ract R,pair<pair<int,int>,int> a)
    {
       int x=a.first.first;
       int y=a.first.second;
       if( x>= R.x1.first && x<= R.x2.first &&  y>= R.x1.second && y <= R.x2.second )
          { return 1;}
       else{ return 0;} 
    
    }
    
int generate_input(int n)
   { int c=1;
     string s="input.txt";
     //cout<<s<<endl;
     fstream new_file;
     new_file.open(s,  ios::out);
     //cout<<x.first<<" "<<x.second<<" "<<y<<endl;
     
     for(int i=0;i<n;i++)
     {
      new_file<<c<<" "<<rand()%401<<" "<<rand()%401<<endl;
      c++;
     }
     new_file.close();
   }
int main()
   {
     int n;
     cout<<"Enter input size :";
     cin>>n;
     generate_input(n);
   
   }   
   
   
