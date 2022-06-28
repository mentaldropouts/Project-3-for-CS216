#include "Graph.h"

#include <map>
#include <queue>
#include <set>
#include <string>
#include <iostream>


//template <typename T>
template <class T>
Graph<T>::Graph()
{
}
//template <typename T>
template <class T>
bool Graph<T>::hasEdge(T v,T w) const
{//Purpose: determine if node v and w are connected in adjMap
//Pre-Cond: char v, char w, map<char, set<char>> adjMap
//Post-Cond: relationship between v and w represented in bool

	//find v n the map adjMap
	if(adjMap.find(v) == adjMap.end())
	{
		return 0;
	}

	//find if w is a member of adjMap.at(v)
	if(adjMap.at(v).find(w) != adjMap.at(v).end())
	{
		return true;
	}
	else
	{ 
		return false;
	}
}
//template <typename T>
template <class T>
void Graph<T>::addEdge(T v,T w) //aborts here
{
//Purpose: connect v and w in the adjMap map
//Pre-cond: char v, char w, map<char, set<char>> adjMap
//Post-cond: updated adjMap


	adjMap[v].insert(w); //putting w as a connection of v
	adjMap[w].insert(v); //putting v as a connection of w
}
//template <typename T>
template <class T>
int Graph<T>::BFS(T s,T t, map<T,int>&distance, map<T, T>& go_through) const
{	
//Purpose: determine the shortest path from node s to node t in adjMap
//Pre-Cond: char s, char t, map<char, int>& distance, map<char, char>& go_through, map<char,set<char>> adjMap
//Post:Cond: updated distance map, updated go_through map

	if (Graph::hasEdge(s,t) == false) 
	{
		if(s == t) 		//if the user enters the same numbers 
		{
			return 0;
		}

		//if source is not in map
		if(adjMap.find(s) == adjMap.end())
		{
			return INVALID_VERTEX;
		}
		//if destination is not in map
		if(adjMap.find(t) == adjMap.end())
		{
			return INVALID_VERTEX;
		}
	}	
	//if either adjMap[s] or adjMap [t] have no connected vertices
	if(adjMap.at(s).size() == 0 || adjMap.at(t).size() == 0 )
	{
		return NOPATH;
	}
	//setting all distance.first with NOPATH
	for(auto v:adjMap)
	{
       		distance[v.first] = NOPATH;
        }
	//configuring items for source
        queue <T> Q;
        distance[s] = 0;
        go_through[s] = s;
        Q.push(s);
       	auto current = s;
	//while Q has members and current isn't at destination
        while(!Q.empty() && current != t){
        	current = Q.front();	
               	Q.pop();
		//going through each node in the graph set by Lab11.cpp 
		for(auto w = adjMap.at(current).begin(); w != adjMap.at(current).end();++w) 
		{	
			//if node w has not been visited 
                	if(distance[*w] == NOPATH)
			{ 		
                       		distance[*w] = distance[current] + 1; 
                                go_through[*w] = current;
                                Q.push(*w);
                        }
                }
        }
        return distance[t]; //shortest path
}
   /* Graph_cpp */     
