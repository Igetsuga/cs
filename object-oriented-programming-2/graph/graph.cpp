// релаксация ребра 
// алгоритм Дейкстры
// алгоритм Прима
// TestGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Edge {
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge &E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}
	int operator<(Edge &E)
	{
		return (weight < E.weight);
	}
	friend ostream &operator<<(ostream &s, Edge &e);
};

ostream &operator<<(ostream &s, Edge &e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

int main()
{

	vector<vector<int> > mat =
	{
	{0, 3, 1, 3, 0, 0, 0},
	{3, 0, 0, 3, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0},
	{3, 3, 1, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 2},
	{0, 0, 0, 0, 1, 0, 3},
	{0, 0, 0, 0, 2, 3, 0}
	};

	//used[i] = 0 вершина еще не появлялась при обработке
	//vector<int> used(7, 0);
	// vector<int> dist(7, -1);
	vector<int> dist(7, 10000000); // inf

	//BFS
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	int step = 0;

	while ( !q.empty() ) {
		
		int vertex = q.front();
		q.pop();

		// case: -1
		//for ( int i = 0; i < 7; i++ ) {
		//	//есть ребро vertex->i, в i не заходили
		//	if ( mat[vertex][i] > 0 && used[i] < 2 ) {
		//		q.push(i);
		//		//вершину видели, но не обработали
		//		used[i] = 1;

		//		if ( dist[i] < 0 ) dist[i] = dist[vertex] + mat[vertex][i];
		//		else {
		//			if ( dist[vertex] + mat[vertex][i] < dist[i] )
		//				dist[i] = dist[vertex] + mat[vertex][i];
		//		}
		//	}
		//}
		
		// case: inf
		for ( int i = 6; i >= 0; i-- ) {
			//есть ребро vertex->i, в i не заходили
			if ( mat[vertex][i] > 0 && dist[vertex] + mat[vertex][i] < dist[i] ) {
				dist[i] = dist[vertex] + mat[vertex][i];
				q.push(i);
			}
		}
		std::cout << '\n' << "steps: " << step << " dist: ";
		for ( int i = 0; i < 7; i++ ) {
			std::cout << " " << dist[i];
		}
		//обработка вершины закончена

		step++;
	}

	std::vector<std::vector<int> > mat1 =
	{
		{0, 1, 2, 3, 4, 5, 0},
		{1, 0, 0, 0, 0, 2, 0},
		{2, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 3, 0, 0},
		{4, 0, 0, 3, 0, 0, 0},
		{5, 2, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 5, 0}
	};
	int mst_weight = 0;


	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;

	mst_weight = 0;     //Текущий вес остова.
	//vector <int> used(7, 0); //использованные вершины
	//for ( int i = 0; i < 7; i++ ) used[i] = 0;
	vector<Edge> edges;		//рассматриваемые ребра
	vector<Edge> tree_edges;	//ребра в минимальном остове

	edges.push_back(Edge(0, 0, 0));     //Начнём с вершины 0.


	//while ( !edges.empty() ) {

	//}

	std::cout << "\nMinimum spanning tree weight: " << mst_weight << endl;
	for ( int i = 1; i < tree_edges.size(); i++ ) {
		cout << "\nEdge " << i << " ";
		cout << tree_edges[i];
	}

	//char c; cin >> c;

	return 0;
}
