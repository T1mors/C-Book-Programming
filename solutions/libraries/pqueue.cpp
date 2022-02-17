/*******************************************************************/
/*** Use of standard template library: priority queue            ***/
/*** Events are initialized randomly, put in the queue and       ***/
/*** obtained from the queue in the order of increasing times    ***/
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
#include <cstdlib>

#include <vector>
#include <queue>

using namespace std;

/** data type for events **/
struct event_t
{
  int part1, part2;    // IDs of particles colliding
  double time;         // time of collision 
};


/** sorting criterion for priority queues of events **/
class EventSortCriterion{
 public:
 bool operator() (const event_t &e1, const event_t &e2) 
   {
     return(e1.time > e2.time);
   }
};



int main(int argc, char *argv[])
{
  priority_queue<event_t, vector<event_t>, EventSortCriterion >  q;
  event_t e;                             // one event 
  int i;                                 // loop counter 
  int num_events = 20;                                 

  srand48(1000);
  for(i=0; i<num_events; i++)           // put events into queue 
  {
    e.part1 = i;
    e.part2 = i+10;
    e.time = 1000*drand48();
    q.push(e);
  }
  
  while(!q.empty())                     // get events from queue 
  {
    e = q.top();                        // get smallest event  
    q.pop();                            // remove it 
    cout << "(" << e.part1 << "," <<  e.part2 << ") at t=" 
         << e.time << endl;
  }

  return(0);
}
