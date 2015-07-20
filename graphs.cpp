#include <iostream>
#include <list>
#include <map>

using namespace std;

class Graph
{
	int V;
	list<int> *adj;
	void DFSUtil(int v, bool visited[]);
public:
	Graph(int V);
	void addEdge(int v, int w);
	void DFS();
	void isReachable(int v,int w);
	void BFS(int s);
};

Graph::Graph(int V)
{
	this->V=V;
	adj= new list<int>[V];
}

void Graph::addEdge(int v,int w)
{
	adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[])
{
	visited[v]=true;
	cout << v << " ";

	list<int>::iterator i;
	for(i=adj[v].begin(); i!=adj[v].end();i++)
	{
		if(!visited[*i])
			DFSUtil(*i,visited);
	}
}

void Graph::DFS()
{
	bool *visited=new bool[V];
	for(int i=0;i<V;i++)
		visited[i]=false;

	for(int v=0;v<V;v++)
		if(visited[v]==false) {
			cout<<endl;
			DFSUtil(v,visited);
		}
}

void Graph::BFS(int s)
{
	bool *visited=new bool[V];
	for(int i=0;i<V;i++)
		visited[i]=false;

	list<int> queue;

	visited[s]=true;
	queue.push_back(s);

	list<int>::iterator i;

	while(!queue.empty())
	{
		s=queue.front();
		cout << s << " ";
		queue.pop_front();

		for(i=adj[s].begin();i!=adj[s].end();i++)
		{
			if(!visited[*i])
			{
				queue.push_back(*i);
				visited[*i]=true;
			}
		}
	}

	for(int v=0;v<V;v++)
		if(visited[v]==false)
		{
			cout<<endl;
			DFSUtil(v,visited);
		}
}

void Graph::isReachable(int v, int w)
{
	bool *visited=new bool[V];
	for(int i=0;i<V;i++)
		visited[i]=false;

	DFSUtil(v,visited);

	if(visited[w])
		cout<<"yes"<<endl;
	else
		cout<<"No"<<endl;
}

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(4, 3);

    //g.DFS();

    g.BFS(0);

    cout<<endl;

    //g.isReachable(1,4);
	return 0;
}
