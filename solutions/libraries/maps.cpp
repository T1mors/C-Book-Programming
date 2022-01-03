/*******************************************************************/
/*** Use of standard template library: map                       ***/
/*** Agents are initialized randomly, put in the map based       ***/
/*** on the x-y position as key. The the agents and all          ***/
/*** neigbors are printed                                        ***/
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
#include <map>
#include <cmath>

using namespace std;

struct agent_t
{
  int capacity;    // how much an agent can process 
  int range;       // interaction range 
};

struct agentkey_t
{
  int x,y;         // position of agent 
};

/** sorting criterion for agents **/
class AgentkeySortCriterion{
 public:
 bool operator() (const agentkey_t &k1, const agentkey_t &k2) const
   {
     return( (k1.x < k2.x)||( (k1.x == k2.x)&&(k1.y < k2.y) ));
   }
};

int main(int argc, char *argv[])
{
  typedef map<agentkey_t, agent_t, AgentkeySortCriterion> agentmap_t;
  agentmap_t m1;                                 // stores all agents
  int num_agents = 20;                           // number of agents 
  int sizex=10, sizey= 10;                       // size of system 
  agentkey_t k1;                                 // one key
  agent_t a1;                                    // one agent

  for(int i=0; i<num_agents; i++)                    // distr. agents 
  {
    k1.x = static_cast<int>(floor(sizex*drand48())); // random position 
    k1.y = static_cast<int>(floor(sizey*drand48()));
    a1.capacity = 100; 
    a1.range = 1 + static_cast<int>(floor(3*drand48()));
    m1[k1] = a1;
  }
  
  agentmap_t::iterator pos, pos2;                // to iterate in map
  for(pos=m1.begin(); pos != m1.end(); pos++)    // print all agents 
  {   
    int r = pos->second.range;
    cout << "Agent (" << pos->first.x << "," << pos->first.y <<
      "): cap=" << pos->second.capacity << ", range=" << r << endl;
    printf("neighbors:\n");
    for(k1.x=pos->first.x-r; k1.x<=pos->first.x+r; k1.x++)
      for(k1.y=pos->first.y-r; k1.y<=pos->first.y+r; k1.y++)
	if( ((k1.x != pos->first.x)||(k1.y != pos->first.y))&&
	    (k1.x>=0)&&(k1.x<sizex)&&(k1.y>=0)&&(k1.y<sizey))
	{                           // look for neighbors near agent 
	  pos2 = m1.find(k1);
	  if(pos2 != m1.end())
	    cout << "(" << pos2->first.x << "," << pos2->first.y
	         << ")\n";
	}
  }
}
