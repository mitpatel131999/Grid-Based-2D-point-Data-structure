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
    
 vector< pair<pair<int,int>,int> > take_input(string s)
   {
      string input_file=s;
    
      fstream new_file;
      new_file.open(input_file, ios::in);
      
      vector< pair<pair<int,int>,int> > result;
      
      
      for(int i=0;!new_file.eof();i++)
        {
           int x,y,uniq_id;
        
           new_file>>uniq_id>>x>>y;
           result.push_back(make_pair(make_pair(x,y),uniq_id));
           
           //cout<<x<<"  "<<y<<"  "<<uniq_id<<endl;
        }
      result.resize(result.size()-1);
      
      new_file.close();
      
      return result;
   }
  
int test(vector< pair<pair<int,int>,int> > A,vector< pair<pair<int,int>,int> > B)

    {  
    
       cout<<"\n project code output \n";
       sort(A.begin(),A.end());
       
       for(int i=0;i<A.size();i++)
        {
         cout<<A[i].second<<" "<<A[i].first.first<<" "<<A[i].first.second<<endl;
        }
        
       cout<<"\n naive code output \n"; 
       sort(B.begin(),B.end());
       for(int i=0;i<A.size();i++)
        {
         cout<<B[i].second<<" "<<B[i].first.first<<" "<<B[i].first.second<<endl;
        }
       
       cout<<"\n\n======================================\n\n";
       
       if(A.size()!=B.size()){ cout<<"not same output size "<<A.size()<<"  "<<B.size()<<endl;  return 0;}
       int c=0;
       for(int i=0;i<B.size();i++)
       {
         
         if(A[i]!=B[i])
          { c++;
            cout<<"out put is not corect";
            cout<<"   "<<i+1<<endl;
          }
       
       }
       
       if (c==0){ cout<<"output is correct\n\n"; return 1; }
    
      return 0; 
    } 

  int main()
  {
     Ract Q;
     Q.x1=make_pair(0,0);
     Q.x2=make_pair(100,100);
     
     int x,y;
     cout<<" Enter bottom left point  eg.  15 25 : ";
     cin>>x>>y;
     Q.x1=make_pair(x,y);
    
     cout<<" Enter upper right point  eg.  75 95 : ";
     cin>>x>>y;
     Q.x2=make_pair(x,y);
  
     vector< pair<pair<int,int>,int> >file_out;
     file_out=take_input("output.txt");
     
     vector< pair<pair<int,int>,int> >actual_out,B;
     
     B=take_input("input.txt");
     
     for(int i=0;i<B.size();i++)
     {
     if(inside(Q,B[i])){ actual_out.push_back(B[i]); }
     
     }  
    
     test(file_out,actual_out); 
  
  } 
