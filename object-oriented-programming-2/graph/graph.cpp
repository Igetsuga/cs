// релаксация ребра 
// алгоритм Дейкстры
// алгоритм Прима
// алгоритм Белмана-Форда
// алгоритм Крускала 2 варианта 

#include <iostream>
#include <vector>
#include <queue>

#define nline '\n'



class edge {
public:

	edge(int source = -1, int target = -1, int weight = 0) {
		_source = source;
		_target = target;
		_weight = weight;
	}

	edge (const typename edge &edge) {
		_source = edge._source;
		_target = edge._target;
		_weight = edge._weight;
	}



	const int &get_source() const noexcept {
		return _source;
	}

	const int &get_target() const noexcept {
		return _target;
	}

	const int &get_weight() const noexcept {
		return _weight;
	}




	bool operator < (const edge &edge) const noexcept {
		return (_weight < edge._weight);
	}



	friend std::ostream &operator << (std::ostream &output, const edge &edge);

private:
	int _source, _target;
	int _weight;
};

std::ostream &operator << (std::ostream &output, const edge &edge)
{
	output << nline << "From: " << edge.get_source() << ", to: " << edge.get_target() 
		<< ", weight: " << edge.get_weight();
	
	
	return output;
}

int main()
{

	std::vector<std::vector<int> > mat =
	{
		{0, 3, 1, 3, 0, 0, 0},
		{3, 0, 0, 3, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0},
		{3, 3, 1, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 2},
		{0, 0, 0, 0, 1, 0, 3},
		{0, 0, 0, 0, 2, 3, 0}
	                            };

	std::vector<int> used(7, 0);
	
	std::vector<int> distance(7, std::numeric_limits<int>::max()); // case_1
	// or 
	// std::vector<int> distance(7, std::numeric_limits<double>::infinity());
	// or 
	// std::vector<int> distance(7, -1); // case_2


	std::queue<int> queue_edges;
	
	queue_edges.push(0);
	distance[0] = 0;
    static int step = 0;

	while ( !queue_edges.empty() ) {
		
		int vertex = queue_edges.front();
		queue_edges.pop();
		
		// case_1
		for ( int i = 6; i >= 0; i-- ) {
			
			if ( mat[vertex][i] > 0 && ( distance[vertex] + mat[vertex][i] < distance[i] )  ) {
				distance[i] = distance[vertex] + mat[vertex][i];
				queue_edges.push(i);
			}

		}
		
		std::cout << nline << "steps: " << step << " dist.: ";
		
		for ( const auto &element : distance ) {
			std::cout << " " << element;
		}
		

		// TODO: переписать
	    // case_2 ЭТОТ СЛУЧАЙ НЕ БЫЛ РАЗОБРАН 
		//for ( int i = 0; i < 7; i++ ) {
		//	//есть ребро vertex->i, в i не заходили
		//	if ( mat[vertex][i] > 0 && used[i] < 2 ) {
		//		queue_edges.push(i);
		//		//вершину видели, но не обработали
		//		used[i] = 1;

		//		if ( distance[i] < 0 ) distance[i] = distance[vertex] + mat[vertex][i];
		//		else {
		//			if ( distance[vertex] + mat[vertex][i] < distance[i] )
		//				distance[i] = distance[vertex] + mat[vertex][i];
		//		}
		//	}
		//}


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


	std::cout << nline << "Minimum spanning tree weight: " << mst_weight << nline;

	mst_weight = 0;     // Текущий вес остова.
	
	//std::vector <int> used(7, 0); //использованные вершины
	//for ( int i = 0; i < 7; i++ ) used[i] = 0;
	
	std::vector<edge> edges;		// рассматриваемые ребра
	std::vector<edge> tree_edges;	// ребра в минимальном остове

	edges.push_back(edge(0, 0, 0));     // Начнём с вершины 0. // фиктивная вершина


	while ( !edges.empty() ) {
		
		auto iter = std::min_element(edges.begin(), edges.end());
		
		int target = iter->get_target();
		int source = iter->get_source();
		int weight = iter->get_weight();
		
		mst_weight += weight;
		edges.erase(iter);

		if ( used[target] ) { continue; }
		used[target] = 1;

		tree_edges.push_back(edge(source, target, weight));
		
		for ( int source_current = 0; source_current < 7 ; source_current++ ) {
			if ( mat[target][source_current] > 0 && used[source_current] ) {
				edges.push_back(edge(target, source_current, mat[target][source_current]));
			}
		}
	}

	std::cout << nline << "Minimum spanning tree weight: " << mst_weight << nline;
	
	for ( int i = 1; i < tree_edges.size(); i++ ) {
		std::cout << nline << "Edge " << i << " " << tree_edges[i];
	}



	return 0;
}
