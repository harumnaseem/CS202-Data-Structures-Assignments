#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <list>
using namespace std;


int c = 0; 
Graph::Graph(string filename, bool isUnitLength)
{

	ifstream file;
	file.open(filename);

	if(file.fail())
	{
		cout<<"File couldn't open"<<endl;
	}
	else
	{
		string Name;
		file>>Name>>Name;

		while(Name != "CONNECTIONS")
		{
			node* temp = new node;
			temp->name = Name;
			temp->visit = 0;
			cities.push_back(temp);

			file>>Name;
		}

		while(!file.eof())
		{
			string x1, x2;
			float num;

			file>>x1>>x2>>num;

			node* temp = NULL;
			node* temp2 = NULL;

			for(int i = 0; i < cities.size(); i++)
			{
				if(cities[i] != NULL && cities[i]->name == x1)
				{
					temp = cities[i];
					break;
				}


			}

			if(temp == NULL)
			{
				continue;
			}

			for(int i = 0; i< cities.size(); i++)
			{
				if(cities[i] != NULL && cities[i]->name == x2)
				{
					temp2 = cities[i];
					break;
				}

			}

			if(temp2 == NULL)
			{
				continue;
			}

			edge E;
			E.Origin = temp;
			E.Dest = temp2;

			if(isUnitLength == true)
			{
				E.weight = 1;
			}
			else
			{
				E.weight = num;
			}

			edge E1;
			E1.Origin = temp2;
			E1.Dest = temp;

			if(isUnitLength == true)
			{
				E1.weight = 1;
			}
			else
			{
				E1.weight = num;
			}

			temp->edges.push_back(E);
			temp2->edges.push_back(E1);
			arcs.push_back(E);

		}

	}

	// for(int i = 0; i < cities.size(); i++)
	// {
	// 	display(cities[i]);
	// }
	// cout<<endl;

}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		cout <<endl<< temp->name<<" -> " << temp->edges[i].Dest->name<< "   weight is "<< temp->edges[i].weight;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);

	}
}

bool Graph::Reachable(string start, string dest)
{
	if(start == dest)
		return true;

	node* temp;
	for(int i = 0; i < cities.size(); i++)
	{
		if(cities[i] != NULL && cities[i]->name == start)
		{
			temp = cities[i];
			break;
		}
		else if(i == cities.size() - 1)
		{
			return false;
		}
	}
	if(temp == NULL)

	{
		return false;
	}
	else if(temp->visit == 1)
	{
		return false;
	}
	else
	{
		temp->visit = 1;
	}

	for(int i = 0; i < temp->edges.size(); i++)
	{
		node* temp2 = temp->edges[i].Dest;

		if(Reachable(temp2->name, dest))
			return true;	
	}

	return false;


}

vector<node*> Graph::Kruskal()
{	
	for(int i = 0; i < cities.size(); i++)
	{
		cities[i]->visit = 0;
	}

	priority_queue <edge, vector<edge>, greater<edge> > queue;
	for(int i = 0; i< arcs.size(); i++)
	{
		queue.push(arcs[i]);
	}

	vector<set<node*> > setC;

	for(int i = 0; i < cities.size(); i++)
	{
		set<node*> temp;
		temp.insert(cities[i]);
		setC.push_back(temp);
	}

	vector<edge> spanningEdges;

	while(!queue.empty())
	{
		edge minimumEdge = queue.top();
		queue.pop();
		node* minimumEdgeOrigin = minimumEdge.Origin;
		node* minimumEdgeDest = minimumEdge.Dest;
		int OriginIndex = 0;
		int DestIndex = 0;
		for(int i = 0; i<setC.size(); i++)
		{
			
			if(setC[i].find(minimumEdgeOrigin)!= setC[i].end())
			{
				OriginIndex = i;
			}

			if(setC[i].find(minimumEdgeDest) != setC[i].end())
			{
				DestIndex = i;
			}
		}

		if(OriginIndex != DestIndex)
		{
			spanningEdges.push_back(minimumEdge);
			setC[OriginIndex].insert(setC[DestIndex].begin(), setC[DestIndex].end());
			setC.erase(setC.begin() + DestIndex);
		}
	}

	float w;
	for(int i = 0; i< spanningEdges.size(); i++)
	{
		w = w + spanningEdges[i].weight;
		cout<<spanningEdges[i].Origin->name<<" - "<<spanningEdges[i].Dest->name<<endl;
	}

	cout<<"Total weight is "<<w<<endl;
	vector<node*> finalPath;
	for(int i = 0; i < cities.size(); i++)
	{
		node* n = new node;
		n->name = cities[i]->name;
		n->visit = 0;
		for(int i = 0; i < spanningEdges.size(); i++)
		{
			if(spanningEdges[i].Origin->name == cities[i]->name)
			{
				n->edges.push_back(spanningEdges[i]);
			}
		}
		finalPath.push_back(n);

	}
	return finalPath;
}

bool operator > (edge a, edge b)
{
	if(a.weight > b.weight)
	{
		return true;
	}
	else
	{
		return false;
	}
}


vector<string> Graph::Dijkstra(string start, string dest, float &d)
{	
	vector<string> path;
	vector<node*> duplicate;
	for(int i = 0; i< cities.size(); i++)
	{
		duplicate.push_back(cities[i]);
	}

	for(int i = 0; i < duplicate.size(); i++)
	{
		duplicate[i]->distance = INT_MAX;
		duplicate[i]->visit = 0;
	}


	node* temp;
	for(int i = 0; i < duplicate.size(); i++)
	{
		if(duplicate[i]->name == start)
		{
			temp = duplicate[i];
			break;
		}
		else if(i == duplicate.size() - 1)
			return path;
	}



	temp->distance = 0;
	node* t;
	while(true)
	{
		float minimumDistance = duplicate[0]-> distance;
		int minimumIndex = 0;

		for(int i = 1; i < duplicate.size(); i++)
		{
			if(minimumDistance > duplicate[i]->distance)
			{
				minimumDistance = duplicate[i]->distance;
				minimumIndex = i;
			}
		}

		node* minimumNode = duplicate[minimumIndex];
		duplicate.erase(duplicate.begin() + minimumIndex);

		if(minimumNode->name == dest)
		{
			t = minimumNode;
			break;
		}
		minimumNode->visit = 1;

		for(int i = 0; i< minimumNode->edges.size(); i++)
		{
			node* temp3 = minimumNode->edges[i].Dest;
			if(temp3->visit == 0)
			{
				float weightEdge = minimumNode->edges[i].weight;
				float newDistance = minimumNode->distance + weightEdge;
				if(temp3->distance > newDistance)
				{
					temp3->distance = newDistance;
					temp3->pathTracker = minimumNode;
					
				} 
			}
		}

	}

	d = t->distance;

	while (true)
	{
		if(t != temp)
		{
			path.push_back(t->name);
			t= t->pathTracker;
		}
		else
			break;
	}
	path.push_back(start);
	

	vector<string> path2;

	for(int i = path.size()-1; i >= 0; i--)
	{
		path2.push_back(path[i]);
	}
	
	return path2;


}
void Graph::setVisit()
{
	for(int i = 0; i < cities.size(); i++)
	{
		cities[i]->visit = 0;
	}
}

int main()
{
	Graph G("friends.txt", false);
	
	G.setVisit();
	cout<<"PART 1:"<<endl<<endl;
	bool answer = G.Reachable( "Mannan", "Ali");
	
	if(answer)
	{
		cout<<"Path between Mannan and Ali exists."<<endl<<endl;
	}
	else
	{
		cout<<"Path between Mannan and Ali does not exist."<<endl<<endl;
	}

	G.setVisit();
	bool answer2 = G.Reachable( "Trump", "Mannan");
	
	if(answer2)
	{
		cout<<"Path between Mannan and Trump exists."<<endl<<endl;
	}
	else
	{
		cout<<"Path between Mannan and Trump does not exist."<<endl<<endl;
	}
	G.setVisit();

	bool answer3 = G.Reachable( "Ali", "Trump");
	
	if(answer3)
	{
		cout<<"Path between Ali and Trump exists."<<endl<<endl;
	}
	else
	{
		cout<<"Path between Ali and Trump does not exist."<<endl<<endl;
	}


	cout<<"PART 2:"<<endl<<endl;
	Graph K("friends.txt", true);
	float d = 0;
	vector<string> path = K.Dijkstra("Ali", "Trump", d);
	for(int i = 0; i < path.size(); i++)
	{
		cout<<path[i];
		if(i < path.size()-1)
		{
			cout<<" -> ";
		}
	}
	cout<<endl<<"Ali is "<<d<<" hops away from Trump."<<endl<<endl;


	K.setVisit();
	cout<<"PART 3:"<<endl<<endl;
	d = 0;
	vector<string> path2 = K.Dijkstra("Mannan", "Trump", d);
	for(int i = 0; i < path2.size(); i++)
	{
		cout<<path2[i];
		if(i < path2.size()-1)
		{
			cout<<" -> ";
		}
	}
	cout<<endl<<"Mannan is "<<d<<" hops away from Trump."<<endl<<endl;

	K.setVisit();

	cout<<"PART 4:"<<endl<<endl;
	float d1 = 0;
	vector<string> path3 = G.Dijkstra("Ali", "Trump", d1);
	for(int i = 0; i < path3.size(); i++)
	{
		cout<<path3[i];
		if(i < path3.size()-1)
		{
			cout<<" -> ";
		}
	}
	cout<<endl<<"Ali is "<<d1<<" distance away from Trump."<<endl<<endl;


	G.setVisit();

	float d2 = 0;
	vector<string> path4 = G.Dijkstra("Mannan", "Trump", d2);
	for(int i = 0; i < path4.size(); i++)
	{
		cout<<path4[i];
		if(i < path4.size()-1)
		{
			cout<<" -> ";
		}
	}
	cout<<endl<<"Mannan is "<<d2<<" distance away from Trump."<<endl<<endl;

	G.setVisit();

	if(d1 > d2)
	{
		cout<<"Ali -> Trump has a smaller index of frienship compared to Mannan -> Trump."<<endl;
	}
	
	cout<<endl<<endl<<"PART 5: "<<endl<<endl;
	cout<<"Edges of MST with isUnitLength = true: "<<endl<<endl;
	vector<node*> n = K.Kruskal();
	cout<<endl;
	cout<<"Edges of MST with isUnitLength = false: "<<endl<<endl;
	vector<node*> L = G.Kruskal();
	cout<<endl;
	cout<<"There can be a lot of MST for a graph because the end sum of the weights can be the same. There will be n-1 number of MST if all the n edges have the same weight in this this when isUnitLength is 1."<<endl;
	cout<<"Applications: "<<endl;
	cout<<"1. Road Network App"<<endl;
	cout<<"2. Computer networks"<<endl;

	return 0;


}

#endif
