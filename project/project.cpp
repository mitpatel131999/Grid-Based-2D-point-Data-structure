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



class Ract               // Ract is class which store bottem left and upper right
{
    public:
    
    pair<int,int> x1;    // x1 for bottom left
    pair<int,int> x2;    // x2 for upper right
    
};


map<int,vector<pair<int,string> > > mapper;   // chice map a uniqe number to vector of bucket( pair < size , name of file >)  

 int cot=0;    // cot is global variable which will be used to set bucket name

vector<int> X;  // x contain all line who seperate buckets horizontaly in 400*400 grid
vector<int> Y;  // x contain all line who seperate buckets verticaly in 400*400 grid

map <int,Ract> mp;  // map which used to fine unique number to ractangale for logical 

int B;              // B is bucket size 

int matrix[402][402];  // grid of 400*400 to store unique bucket numver for each pair of (x,y)


int remove_bucket(int id)   // this function will removw bucker  whose id number is id
    {
     for(int i=0;i<mapper[id].size();i++)        // if in case of there are multipul chaning in bucket then it remove all
     {
     string s=to_string(id)+"-"+to_string(i)+".txt";
     string filename(s);
     remove(filename.c_str());
     }
     return 1;
    }

int set_matrix(Ract R)                             // vased on Ract R it will set that value in R region of matrix by unique numbet cot 
 {   pair<int,int> x1=R.x1;
     pair<int,int> x2=R.x2;
     for(int i=x1.first;i<x2.first;i++)
      {
          for(int j=x1.second;j<x2.second;j++)
           {
               matrix[i][j]=cot;
               
           }
           
      }
      mp[cot]=R;   // map value for uniq id of bucket to region R
      
      remove_bucket(cot);  // if there exist any file already then it remove it first then generate  new
      
      mapper[cot].push_back(make_pair(0,to_string(cot)+"-"+to_string(mapper[cot].size())+".txt"));   // map value to unique id of bucket to bucket <size,name>
      
      cot++;    // once cot is used we increment for next bucket
     return 1;
  }
  
 
 
 int append_data(pair<int,int> x,long long int y,int buck)               // append data to bucket uniq id is  buck 
   {
     string s=to_string(buck)+"-"+to_string(mapper[buck].size()-1)+".txt";  // chast bucket of chain of bucket for id == buck if there more then one bucket in chaning
     
     fstream new_file;
     new_file.open(s, std::ios_base::app);
    
     new_file<<y<<" "<<x.first<<" "<<x.second<<endl;                 // write data into file
     
     new_file.close();                                               // close file
     
     mapper[buck][mapper[buck].size()-1].first++;                    // increased size of that bucket
     return 1;
   }
   
 vector<pair<pair<int,int>,long long int>> read_bucket(int buck)     // this function will read bucket where if = buck
   {
     vector<pair<pair<int,int>,long long int>> result;           
     
     for(int j=0;j<mapper[buck].size();j++)                          // id there is channing then read all
     { 
       string s=to_string(buck)+"-"+to_string(j)+".txt";
       fstream new_file;
       new_file.open(s, ios::in);
      
      for(int i=0;!new_file.eof() && i<=B+1 && i < mapper[buck][j].first;i++)
        {
           int x,y,uniq_id;
        
           new_file>>uniq_id>>x>>y;
           result.push_back(make_pair(make_pair(x,y),uniq_id));
           
           if(new_file.eof()){ break; }
           
        }
       
       new_file.close();
      }
      return result;                    // return vector of all data point
   }
    
vector<Ract> update(Ract R)             // this function will list logical bucket  whithin region R 
  {   pair<int,int> x1=R.x1;
      pair<int,int> x2=R.x2;
     
      vector <int> tamp_x;
      vector <int> tamp_y;
      sort(X.begin(),X.end());
      sort(Y.begin(),Y.end());
     
      for(int i=0;i<X.size();i++)
        {
            if( X[i]>=x1.first && X[i]<=x2.first)
             {
                 tamp_x.push_back(X[i]);
             }
        }
      
      for(int i=0;i<Y.size();i++)
        {
            if( Y[i]>=x1.second && Y[i]<=x2.second)
             {
                 tamp_y.push_back(Y[i]);
             }
        }
       vector <Ract> list;
      for(int i=0;i<tamp_x.size()-1;i++)
        {
            for(int j=0;j<tamp_y.size()-1;j++)
              { Ract ri;
                ri.x1=make_pair(tamp_x[i],tamp_y[j]);
                ri.x2=make_pair(tamp_x[i+1],tamp_y[j+1]);
                list.push_back(ri);
              
              }
        }
       
      
     return list;                              // return all region in R
   }


vector<pair<pair<int,int>,long long int>> reverse_sort(vector<pair<pair<int,int>,long long int>> A)   // this function will sort data point by y coordinate
     {
      vector<pair<pair<int,int>,long long int>> tamp;
      
      for(int i=0;i<A.size();i++)
       {
         tamp.push_back(make_pair(make_pair(A[i].first.second,A[i].first.first),A[i].second));
       }
       
       sort(tamp.begin(),tamp.end());
       
       vector<pair<pair<int,int>,long long int>> tamp_2;
       
       for(int i=0;i<A.size();i++)
       {
         tamp_2.push_back(make_pair(make_pair(tamp[i].first.second,tamp[i].first.first),tamp[i].second));
       }
      
      return tamp_2;
     
     }
        
int partation(vector<pair<pair<int,int>,long long int>> list,int t)           // this function will make greedy partation
   { 
     
     vector<pair<pair<int,int>,long long int>> A,B;
     
     for(int i=0;i<list.size();i++)
       {
         A.push_back(list[i]);
       }
     sort(A.begin(),A.end());  // sort by X coordinate
     
     B=reverse_sort(list);     // sort by Y coordinate
     
     int m1,m2;
     
     m1=A.size()/2;           // median
     m2=B.size()/2;
     
     // find best partation
     while(true)
     {
        if(A.size()==1)
        {
         mapper[t].push_back(make_pair(0,to_string(cot)+"-"+to_string(mapper[t].size())+".txt"));
         return 0;
        }
        else    /// this will try to fine nearest median partation 
        {  char cr='P';
           int x1=m1,x2=m1,y1=m2,y2=m2;
           while( !(x1<0 && y1<0 && x1>=A.size() && y1>=B.size()))
           {
            if(x1>0)
              {
                if(A[x1].first.first !=A[x1-1].first.first)
                  {
                   cr='X';
                   m1=A[x1].first.first;
                   break;
                  }
               } 
              x1--;
               
             if(x2<A.size())
               { 
                if(A[x2].first.first !=A[x2-1].first.first)
                  {
                   cr='X';
                   m1=A[x2].first.first;
                   break;
                  }
                }
               x2++; 
                
              if(y1>0)
               {  
                if(B[y1].first.second != B[y1-1].first.second) 
                  {
                    cr='Y';
                    m2=B[y1].first.second;
                    break;
                  }
                }
                 y1--;
              if(y2<B.size())
               {  
                if(B[y2].first.second != B[y2-1].first.second) 
                  {
                    cr='Y';
                    m2=B[y2].first.second;
                    break;
                  }
                } 
                 y2++; 
               
               
            
           }
           if(cr=='X'){ X.push_back(m1); sort(X.begin(),X.end()); return 1;}
           if(cr=='Y'){ Y.push_back(m2); sort(X.begin(),X.end()); return 1;}  
           
           /* if partation is not possible then it will do channing by appending one more bucket to that Ract*/
           mapper[t].push_back(make_pair(0,to_string(t)+"-"+to_string(mapper[t].size())+".txt"));
           return 0;
        }
     
     }
     
   
   }   
  
  
int insert(pair<int,int> x,long long int id)   // this function will used to insert  data
   {
       int t=matrix[x.first][x.second];    // t hase unique id of respactive x data point
       
       
       if(mapper[t][mapper[t].size()-1].first <B )  // if bucket is not full then diract insert data
          {
           append_data(x,id,t);
          }
        else    // if bucket is full
          {   
           
             Ract R=mp[t];
             vector<Ract> list=update(R);   // try to make all possible privious possible partation
           
             if(list.size()<=1)            // if ther is not any pre existing line in logical bucket(Ract) then we need to make partation line
               {
                   
                   vector<pair<pair<int,int>,long long int>> bu=read_bucket(t);  // read bucket id=t
                   
                   bu.push_back(make_pair(x,id));         // write current inserted element in bu
                   
                   
                   if(partation(bu,t))                    // if partation is possible
                   {
                     remove_bucket(t);                    // if yes then remove bucket id =t
                     vector <Ract> list_2=update(R);      // update logical region
                   
                     for(int i=0;i<list_2.size();i++) 
                     { 
                      set_matrix(list_2[i]);              //  set matrix according new partation
                     }
                     for(int i=0;i<bu.size();i++)
                      { 
                        insert(bu[i].first,bu[i].second); // then insert all element into their currousponding bucket 
                      }
                    }
                   else
                    {
                       insert(x,id);                     // if partation is not possible then just append thet data into chain bucket  
                    }
                
                   
               }
             
             else                                             // in this else part there is already pre existing lines so we try to make bucket from that line
               {         
                 for(int i=0;i<list.size();i++)
                 {   
                    set_matrix(list[i]);                      // set matrix according to that pri existing line
                 }
                 vector<pair<pair<int,int>,long long int>> bu=read_bucket(t); // reaf bucket
                 bu.push_back(make_pair(x,id));                 // add current input (inserted data)
                 
                 remove_bucket(t);                              // remove bucket t
                 
                 
                 for(int i=0;i<bu.size();i++)
                 { 
                   insert(bu[i].first,bu[i].second);           // then try to insert all element in new bucket
                 }
                 
                 // case panding 
                 
                int tamp=matrix[x.first][x.second];
                if(mapper[tamp][mapper[tamp].size()-1].first >B )  // if pre existing partation is not able to locate then make partation
                {
                                           
                                                                  
                   vector<pair<pair<int,int>,long long int>> bu=read_bucket(t); // read file t
                   
                   
                   if(partation(bu,t))                        // make partation
                   {
                     remove_bucket(t); 
                     vector <Ract> list_2=update(R);      
                   
                     for(int i=0;i<list_2.size();i++)
                     { 
                      set_matrix(list_2[i]);                 // set matrix accrding to new logical Ract
                     }
                     for(int i=0;i<bu.size();i++)
                      { 
                        insert(bu[i].first,bu[i].second);    // insert all element in to their bucket
                      }
                    }
                    else
                    {
                       insert(x,id);                        // partation is not pssible then just chain the file
                    }
                  
                 }
                
               }
               
             
         }
        return 1; 
   }

vector <int> possible_bucket(Ract R)             // return all bucket id thode has data which is lies in region(Ract)  R
   { pair<int,int> x1=R.x1;
     pair<int,int> x2=R.x2;
     
     vector <int> list;
     set    <int> s;                             // s is used to find uniquely bucket id 
     for(int i=x1.first;i<=x2.first;i++)
      {
          for(int j=x1.second;j<=x2.second;j++)
           {
               s.insert(matrix[i][j]);
           }
       }
      
       
        list.resize(0); 
        for(auto it=s.begin();it!=s.end();it++)
        {
         
         list.push_back(*it);                   // append all bucket to list
         
        }
       return list;                            // return list
   }

int inside(Ract R,pair<pair<int,int>,long long int> a)  // this function will give you that point 'a' is inside region R or not 
    {
       int x=a.first.first;
       int y=a.first.second;
       if( x>= R.x1.first && x<= R.x2.first &&  y>= R.x1.second && y <= R.x2.second )
          { return 1;}
       else{ return 0;} 
    
    }
int query(Ract R)             // whis function will return all data point who are inside that region R
   {  
      vector<pair<pair<int,int>,long long int>> result; 
      
      cout<<"=================================================================>\n";
      
      vector<int> list=possible_bucket(R);                   // fine bucket which are lies inside region R 
      
      cout<<"list of bucket  --> "<<list.size()<<endl;       // print totel bucket inside region
      
      for(int i=0;i<list.size();i++){ cout<<"  "<<list[i]; } cout<<endl;  // print bucket id
      
      for(int i=0;i<list.size();i++)                     // for each bucket inside the region
       {
           vector<pair<pair<int,int>,long long int >> tamp=read_bucket(list[i]);  // it read bucket
           for(int j=0;j<tamp.size();j++)
             {
              if(inside(R,tamp[j]))                      /* check it lies inside R or not becuause of
                                                           boundary line bucket may possible that half 
                                                           is inside R and other half is out side so*/
                {result.push_back(tamp[j]); }            // if inside then push into result
             }
           
       }
       
       
       cout<<"out put of query -->\n";
       cout<<result.size()<<endl;                   // total number point lies inside region R
       
       
       string s="output.txt";
       
       fstream new_file;                          // write all those point into output.txt file
       new_file.open(s, ios::out);
       
       for(int i=0;i<result.size();i++)
        {
         cout<<result[i].second<<" "<<result[i].first.first<<"  "<<result[i].first.second<<"  "<<endl;
         new_file<<result[i].second<<" "<<result[i].first.first<<"  "<<result[i].first.second<<"  "<<endl;
        
        }
        new_file.close();
        return 1;
   }
   
int take_input(string s)
   {
      string input_file="input.txt";    // read input data from input.txt <id> <x> <y>
    
      fstream new_file;
      new_file.open(input_file, ios::in);
      
      vector< pair<pair<int,int>,long long int> > result;
      for(int i=0;!new_file.eof();i++)
        {
           int x,y;
           long long uniq_id;
        
           new_file>>uniq_id>>x>>y;
           result.push_back(make_pair(make_pair(x,y),uniq_id));
           
        }
      result.resize(result.size()-1);
     
      for(int i=0;i<result.size();i++)
       {
        insert(result[i].first,result[i].second);
        
       }  
      
      new_file.close();
      
      return 1;
   
   }
int print_logical(Ract R)       // print all logical Ract 
   {
     
     cout<<"\n\n=====  LOGICAL BUCKET (RECTANGLE) ======:\n\n";
     vector<Ract> list=update(R);
     
     cout<<"\n  X line :";
     for(int i=0;i<X.size();i++){ cout<<X[i]<<" ";}
     
     cout<<"\n  Y line :";
     for(int i=0;i<Y.size();i++){ cout<<Y[i]<<" ";}
     
     /* 
         all possible Ract (x1,y1) and (X2,y2) 
        x1,y1 is part of Ract but X2 and y2 is not part of Ract 
        that means any point who hase any coordinate is x2 or y2 
        is not part of Ract (x1,y1)--(X2,y2)
    
    */
     
     
     cout<<"\n\n  Regions\n";
     
     for(int i=0;i<list.size();i++)
        {
        
         cout<<"\n  "<<i+1<<".   ("<<list[i].x1.first<<","<<list[i].x1.second<<")"<<"---"<<"("<<list[i].x2.first<<","<<list[i].x2.second<<")\n\n";
        
         cout<<"----------------------------------------------------\n";
        }
     
   
     return 1;
   
   }
   
 int print_physical(Ract R)      // print all physical bucket with their region coordinate <bottom left> <upper right> and file name 
   {
     R.x2.first--;
     R.x2.second--;
     vector<int> list_bucket=possible_bucket(R);
     cout<<"\n\n=====  PHYSICAL BUCKET (RECTANGLE) ======:\n\n";
     
     for(int i=0;i<list_bucket.size();i++)
     {
       Ract r=mp[list_bucket[i]];
       cout<<"\n  "<<i+1<<".   ("<<r.x1.first<<","<<r.x1.second<<")"<<"---"<<"("<<r.x2.first<<","<<r.x2.second<<")\n\n";
       
       vector<pair<int,string> > tamp=mapper[list_bucket[i]];
       
       for(int j=0;j<tamp.size();j++)
         {
         
          cout<<"           "<<tamp[j].second<<"\n";
         
         }
        cout<<"----------------------------------------------------\n"; 
     }
   
     return 1;
   
   
   }
int main() {
    // Write C++ code here
    
    
    Ract R;                       // initial grid
    R.x1=make_pair(0,0);          
    R.x2=make_pair(401,401);     
    /* 
        401 is out side for all possible Ract (x1,y1) and (X2,y2) 
        x1,y1 is part of Ract but X2 and y2 is not part of Ract 
    
    */
    
    set_matrix(R);
    
    
    B=25;  // bucket size
    cout<<" Enter  size of bucket :=";
    cin>>B;
    
    X.push_back(0);   // push initial value to X and Y boundary 
    X.push_back(401);
    Y.push_back(0);
    Y.push_back(401);
    
    
    string s="input.txt";
    take_input(s);
    
    print_logical(R); // print logical bucket
    
    print_physical(R); // print physical bucket
    
    Ract Q;            // print Query into output.txt
    int x,y;
    cout<<" Enter bottom left point  eg.  15 25 : ";
    cin>>x>>y;
    Q.x1=make_pair(x,y);
    
    cout<<" Enter upper right point  eg.  75 95 : ";
    cin>>x>>y;
    Q.x2=make_pair(x,y);
    query(Q);
    
    //std::cout << "Hello world!";

    return 0;
}
