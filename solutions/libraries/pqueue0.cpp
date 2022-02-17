/*******************************************************************/
/*** Use of standard template library: priority queue            ***/
/*** which stores string                                         ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Libraries                                          ***/
/*** Section:  Standard Template Library                         ***/
/*******************************************************************/

#include <iostream>
#include <queue>
#include <string>

using namespace std;



int main(int argc, char *argv[])
{
  priority_queue<string> q2;    
  q2.push("hello");                      // fill priority queue 
  q2.push("you");
  q2.push("are");
  q2.push("welcome");

  while(!q2.empty())                     // get events from queue 
  {
    string s;
    s = q2.top();                        // get "smallest" string 
    q2.pop();                            // remove it 
    cout << s << endl;
  }

  return(0);
}
