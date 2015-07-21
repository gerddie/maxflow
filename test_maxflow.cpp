/*

    Copyright 2006-2015, 
    Vladimir Kolmogorov (vnk@ist.ac.at), Yuri Boykov (yuri@csd.uwo.ca)

    This file is part of MAXFLOW.

    MAXFLOW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MAXFLOW is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MAXFLOW.  If not, see <http://www.gnu.org/licenses/>.

*/


// Implement some simple tests for maxflow

#include <iostream>
#include <maxflow.h>

using std::cerr;
using std::pair;
using std::make_pair;
using maxflow::Graph_III; 

int test_node(const Graph_III& g, int id, Graph_III::termtype segment, const char *testid)
{
        if (g.what_segment(id) != segment) {
                cerr << testid << "Node " << id << "not es expected in "
                     << (segment == Graph_III::SOURCE ? "Source" : "Sink")
                     << " set\n"; 
                return 1; 
        }
        return 0; 
}

/*
  Test the following graph: 

  		         SOURCE
		       /       \
		     5/         \2
		     /      3    \
		   node0 -----> node1
		     |   <-----   |
		     |      4     |
		     \            /
		     1\          /6
		       \        /
		          SINK

  flow = 6 
  node 0 = source 
  node 1 = sink 
*/



pair<int,int> test_1()
{
        Graph_III g(2,1); 
        
	g.add_node(); 
	g.add_node(); 
        
	g.add_tweights( 0,   /* capacities */  5, 1 );
	g.add_tweights( 1,   /* capacities */  2, 6 );
	g.add_edge( 0, 1,    /* capacities */  3, 4 );
        
	int flow = g.maxflow();

        pair<int,int> result = make_pair(0, 3); 
        if (flow != 6) {
                cerr << "test_1: Flow = " <<  flow << ", " << "expected 6\n";
                ++result.first; 
        }

        result.first += test_node(g, 0, Graph_III::SOURCE, "test_1");
        result.first += test_node(g, 1, Graph_III::SINK,  "test_1"); 
        return result; 
}


/*
  Test the following graph: 

  		         SOURCE
		       /       \
		     1/         \2
		     /      3    \
		   node0 -----> node1
		     |   <-----   |
		     |      4     |
		     \            /
		     5\          /6
		       \        /
		          SINK

  flow = 3 
  node 0 = sink 
  node 1 = sink 
*/



pair<int,int> test_2()
{
        Graph_III g(2,1); 
        
	g.add_node(); 
	g.add_node(); 
        
	g.add_tweights( 0,   /* capacities */  1, 5 );
	g.add_tweights( 1,   /* capacities */  2, 6 );
	g.add_edge( 0, 1,    /* capacities */  3, 4 );
        
	int flow = g.maxflow();

        pair<int,int> result = make_pair(0, 3); 
        if (flow != 3) {
                cerr << "test_2: Flow = " <<  flow << ", " << "expected 3\n";
                ++result.first; 
        }

        result.first += test_node(g, 0, Graph_III::SINK, "test_2");
        result.first += test_node(g, 1, Graph_III::SINK, "test_2");

        return result;  
}


/*
  Test the following graph: 

  		        ---- SOURCE------
		       /                  \
		     6/                    \ 4
		     /      4           3   \
		   node0 -----> node1 ---->node2
                     |   <-----      <----- /            
		     |      2          5   |
		     \                    /
		     3\                  /6
		       \                /
		            SINK

  flow = 9 
  node 0 = source 
  node 1 = sink 
  node 2 = sink 
*/



pair<int,int> test_3()
{
        Graph_III g(3,2); 
        
	g.add_node(); 
	g.add_node();
        g.add_node(); 
        
	g.add_tweights( 0,   /* capacities */  6, 4 );
	g.add_tweights( 2,   /* capacities */  3, 6 );
	g.add_edge( 0, 1,    /* capacities */  2, 4 );
        g.add_edge( 1, 2,    /* capacities */  3, 5 );
        
        int flow = g.maxflow();

        pair<int,int> result = make_pair(0,4); 
                
        if (flow != 9) {
                cerr << "test_2: Flow = " <<  flow << ", " << "expected 9\n";
                ++result.first; 
        }

        result.first += test_node(g, 0, Graph_III::SOURCE, "test_3");
        result.first += test_node(g, 1, Graph_III::SINK, "test_3");
        result.first += test_node(g, 2, Graph_III::SINK, "test_3");
        
        return result; 
}

pair<int,int>& operator += (pair<int,int>& lhs, const pair<int,int>& rhs)
{
        lhs.first += rhs.first;
        lhs.second += rhs.second;
        return lhs; 
}

int main()
{
        pair<int,int> failures  = make_pair<int, int>(0,0);

        failures += test_1();
        failures += test_2();
        failures += test_3();

        cerr << failures.first << " of " << failures.second << " test failed\n"; 

	return failures.first > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

