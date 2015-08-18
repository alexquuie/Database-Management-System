// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <set>       // std::vector

bool myfunction (int i,int j) { return (i<j); }

class myclass {
public:	
  myclass(int f){flag = f;}
  bool operator() (int i,int j) { 
	  if(flag==0)
	  return (i<j);
	  else
	  return (i>=j);}
private:
  int flag;
};

struct myOperator{
  bool operator() (int i,int j) { return (i<j);}
};
int main(){
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

	myclass myobject(0);
  // using object as comp
  std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

	std::set<int,myclass> tmpset(myints,myints+8,1);
	
	 // print out content:
  std::cout << "myvector contains:";
  for (std::set<int>::iterator it=tmpset.begin(); it!=tmpset.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  return 0;
}
