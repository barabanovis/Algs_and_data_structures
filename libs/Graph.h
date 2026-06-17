#ifndef GRAPH_H
#define GRAPH_H

/*
ВАРИАНТ 4
использовать код лабы 2 (хеш таблица)
обход графа в глубину
поиск кратчайшего маршрута по алгоритму Дейкстры
*/


#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include <functional>
#include <fstream>
#include <filesystem>
#include "libs/UnorderedMap.h"

template<typename Vertex = int, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from;
		Vertex to;
		Distance dist;
		Edge() : from(0), to(0), dist(0) {};
		Edge(const Vertex& from, const Vertex& to, const Distance dist) :from(from), to(to), dist(dist) {};
	};
private:
	std::vector<Vertex> _vertices;

	UnorderedMap<Vertex, std::list<Edge>> _graph_table;


	void dfs(const Vertex& start_vertex, std::vector<Vertex>& walk_order, UnorderedMap<Vertex, int>& color, std::function<void(const Vertex&)>& action) const;
	void edge_relaxation(const Edge& edge, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const;
	std::vector<Edge> path_reconstruction(const Vertex& from, const Vertex& to, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const;

	size_t _negative_edges_num = 0;
public:
	
	Graph();
	// Добавьте в публичную секцию:
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);


	//проверка-добавление-удаление вершин
	bool has_vertex(const Vertex& v) const;
	bool add_vertex(const Vertex& v); // false если вершина уже есть
	bool remove_vertex(const Vertex& v);
	std::vector<Vertex> vertices() const;
	//проверка-добавление-удаление ребер
	void add_edge(const Vertex& from, const Vertex& to, const Distance& d);

	// УДАЛЯЕТ ВСЕ РЕБРА МЕЖДУ ДАННЫМИ ДВУМЯ ВЕРШИНАМИ
	bool remove_edge(const Vertex& from, const Vertex& to);

	// УДАЛЯЕТ ТОЛЬКО ОДНО ДАННОЕ РЕБРО
	bool remove_edge(const Edge& e); //c учетом расстояния
	bool has_edge(const Vertex& from, const Vertex& to) const;
	bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

	std::vector<Edge> edges(const Vertex& vertex) const; //получение всех ребер, выходящих из вершины
	size_t order() const; //порядок
	size_t degree(const Vertex& v) const; //степень вершины
	bool is_connected() const; //является ли граф сильносвязным
	  
	bool is_valid_for_deikstra() const;
	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;  //поиск кратчайшего пути 
	//с помощью алгоритма Дейкстры для графов с неотрицательными весами рёбер

	std::vector<Vertex> walk(const Vertex start_vertex, std::function<void(const Vertex&)> action)const; //обход
	void deikstra_alg(const Vertex& from, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const;

	
	void print(std::ostream& os) const;
	void export_to_csv(const std::string& filename, bool include_vertices = true) const;

	// Сделайте красивую визуализацию графа с помощью LLM. 
	// Можете красивый вывод в консоле сделать, можете сохранять как картинки. 
	// Пожалуйста, не поленитесь и сделайте визуализацию индивидуально.
};

template <typename Vertex, typename Distance>
Graph<Vertex, Distance>::Graph() :_vertices(), _graph_table(10) {};

// Реализация:

template<typename Vertex, typename Distance>
Graph<Vertex, Distance>::Graph(const Graph& other)
	: _vertices(), _graph_table(10), _negative_edges_num(other._negative_edges_num) {

	// Резервируем память для вершин
	_vertices.reserve(other._vertices.size());

	_vertices = other._vertices;

	// Копируем ребра
	for (const auto& vert : other._vertices) {
		const Vertex& vertex = vert;
		auto edges_list = other._graph_table.search(vertex);

		if (edges_list && !edges_list->empty()) {
			std::list<Edge> new_list;
			for (const auto& edge : *edges_list) {
				new_list.push_back(edge);
			}
			_graph_table.insert(vertex, new_list);
		}
	}
}

template<typename Vertex, typename Distance>
Graph<Vertex, Distance>& Graph<Vertex, Distance>::operator=(const Graph& other) {
	if (this == &other) {
		return *this; // Защита от самоприсваивания
	}

	// Очищаем текущий граф
	_vertices.clear();
	_negative_edges_num = 0;

	// Резервируем память для вершин
	_vertices.reserve(other._vertices.size());

	// Копируем вершины
	_vertices = other._vertices;

	// Копируем ребра
	for (const auto& vert : other._vertices) {
		const Vertex& vertex = vert;
		auto edges_list = other._graph_table.search(vertex);

		if (edges_list && !edges_list->empty()) {
			std::list<Edge> new_list;
			for (const auto& edge : *edges_list) {
				new_list.push_back(edge);
			}
			_graph_table.insert(vertex, new_list);
		}
	}

	_negative_edges_num = other._negative_edges_num;

	return *this;
}


template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
	return _graph_table.search(v);
}

template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
	if (has_vertex(v)) {
		return false;
	}
	_vertices.push_back(v);
	return _graph_table.insert(v, std::list<Edge>());
}

template <typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const{
	return _vertices;
}



template <typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
	if (!has_vertex(from)) {
		throw std::invalid_argument("FROM vertex does not exist!");
	}
	if (!has_vertex(to)) {
		throw std::invalid_argument("TO vertex does not exist!");
	}

	Edge new_edge(from, to, d);
	std::list<Edge>* list_to_push = _graph_table.search(from);
	list_to_push->push_back(new_edge);

	if (d < 0) {
		_negative_edges_num++;
	}

	return;
}

template <typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const { //порядок
	return _vertices.size();
}

template <typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
	if (!has_edge(from, to)) {
		throw std::invalid_argument("Edge does not exist!");
	}

	std::list<Edge>* list_ptr = _graph_table.search(from);

	// Проверка на nullptr
	if (!list_ptr) {
		return false;
	}

	size_t deleted_negative_edges = 0;

	// Используем const Edge& чтобы избежать копирования
	size_t old_size = list_ptr->size();
	list_ptr->remove_if([&to, &deleted_negative_edges](const Edge& e) {
		if (e.to == to) {
			if (e.dist < 0) {
				deleted_negative_edges++;
			}
			return true;
		}
		return false;
		});

	if (old_size != list_ptr->size()) {
		_negative_edges_num -= deleted_negative_edges;
		return true;
	}

	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& edge) {
	
	if (!has_vertex(edge.from)) {
		throw std::invalid_argument("FROM vertex does not exist!");
	}
	if (!has_vertex(edge.to)) {
		throw std::invalid_argument("TO vertex does not exist!");
	}

	std::list<Edge>* list_ptr = _graph_table.search(edge.from);

	// Проверка на nullptr
	if (!list_ptr) {
		return false;
	}
	size_t deleted_negative_edges = 0;
	// Используем const Edge& чтобы избежать копирования
	size_t old_size = list_ptr->size();
	list_ptr->remove_if([&edge, &deleted_negative_edges](const Edge& e) {
		if (e.to == edge.to && e.dist == edge.dist) {
			if (e.dist < 0) {
				deleted_negative_edges++;
			}
			return true;
		}
		return false;
		});

	if (old_size != list_ptr->size()) {
		_negative_edges_num -= deleted_negative_edges;
		return true;
	}

	return false;
}


template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print(std::ostream& os) const {
	const std::string line = "----------------------------------------";

	os << "\n" << line << "\n";
	os << "         GRAPH VISUALIZATION\n";
	os << line << "\n\n";

	if (_vertices.empty()) {
		os << "  [Empty graph]\n";
		os << line << "\n";
		return;
	}

	// Вывод всех вершин с их ребрами
	for (size_t i = 0; i < _vertices.size(); ++i) {
		const Vertex& vertex = _vertices[i];
		auto edges = _graph_table.search(vertex);

		// Вывод текущей вершины
		os << "  Vertex [" << i << "]: " << vertex << "\n";
		os << "  " << line << "\n";

		if (edges && !edges->empty()) {
			int edge_num = 1;
			for (const auto& edge : *edges) {
				os << "    Edge " << edge_num++ << ": ";
				os << vertex << " --> " << edge.to;
				os << "  (distance = " << edge.dist << ")\n";
			}
		}
		else {
			os << "    No outgoing edges\n";
		}

		os << "\n";
	}

	// Подсчет общего количества ребер
	size_t total_edges = 0;
	for (const auto& v : _vertices) {
		auto edges = _graph_table.search(v);
		if (edges) {
			total_edges += edges->size();
		}
	}

	os << line << "\n";
	os << "  Statistics:\n";
	os << "    Vertices: " << _vertices.size() << "\n";
	os << "    Edges: " << total_edges << "\n";
	os << line << "\n\n";
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const { //степень вершины
	if (!has_vertex(v)) {
		throw std::invalid_argument("This vertex does not exist!");
	}

	size_t result = 0;
	for (auto vert : _vertices) {
		std::list<Edge>* list_ptr = _graph_table.search(vert);
		for (auto edge : *list_ptr) {
			if (edge.from == v || edge.to == v) {
				result++;
			}
		}
	}
	return result;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) const { //получение всех ребер, выходящих из вершины
	if (!has_vertex(vertex)) {
		throw std::invalid_argument("This vertex does not exist!");
	}

	std::list<Edge>* list_ptr = _graph_table.search(vertex);

	std::vector<Edge> result(0);
	for (const auto u : *list_ptr) {
		result.push_back(u);
	}
	return result;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
	if (!has_vertex(from) || !has_vertex(to)) {
		return false;
	}

	std::list<Edge>* list_ptr = _graph_table.search(from);
	// Пробег по списку, чтобы найти искомый конец
	for (auto u : *list_ptr) {
		if (u.to == to) {
			return true;
		}
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const { //c учетом расстояния в Edge
	if (!has_vertex(e.from) || !has_vertex(e.to)) {
		return false;
	}

	std::list<Edge>* list_ptr = _graph_table.search(e.from);
	// Пробег по списку, чтобы найти искомый конец
	for (auto u : *list_ptr) {
		if (u.to == e.to && u.dist == e.dist) {
			return true;
		}
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
	if (!has_vertex(v)) {
		throw std::invalid_argument("This vertex does not exist!");
	}

	// Удаляем все ребра, где v участвует как from или to
	for (auto vertex : _vertices) {
		std::list<Edge>* list_ptr = _graph_table.search(vertex);
		if (list_ptr) {
			// Используем remove_if для удаления рёбер с участием v
			list_ptr->remove_if([&v](const Edge& edge) {
				return edge.from == v || edge.to == v;
				});
		}
	}

	// Удаляем запись о вершине из вектора shared_ptr
	_vertices.erase(
		std::remove_if(_vertices.begin(), _vertices.end(),
			[&v](const std::shared_ptr<Vertex>& ptr) {
				return *ptr == v;  // сравниваем значения вершин
			}),
		_vertices.end()
	);
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex start_vertex, std::function<void(const Vertex&)> action)const {
	std::vector<Vertex> walk_order(0);
	/*
	color[u] = 1 белый
	color[u] = 0 серый
	color[u] = -1 черный
	*/
	UnorderedMap<Vertex, int> color;
	
	for (const auto& u : _vertices) {
		color.insert_or_assign(u, 1);
	}

	dfs(start_vertex,walk_order, color, action);
	return walk_order;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::dfs(const Vertex& start_vertex, std::vector<Vertex>& walk_order, UnorderedMap<Vertex, int>& color, std::function<void(const Vertex&)>& action) const {
	
	
	color.insert_or_assign(start_vertex, 0);

	std::list<Edge>* list_ptr = _graph_table.search(start_vertex);

	for (auto edge : *list_ptr) {
		if (*color.search(edge.to) == 1) {
			dfs(edge.to,walk_order, color, action);
		}
	}

	color.insert_or_assign(start_vertex, -1);
	action(start_vertex);
	walk_order.push_back(start_vertex);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::is_connected() const { //является ли граф сильносвязным
	// Иное определение сильносвязного графа:
	// Граф сильнсвязный, если из каждой вершины этого графа можно прийти во все остальные
	for (auto u : _vertices) {
		std::vector<Vertex> walk_vect = walk(u, [](Vertex v) {;});
		if (walk_vect.size() != order()) {
			return false;
		}
	}
	return true;
}


template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::is_valid_for_deikstra() const {
	return !_negative_edges_num;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::edge_relaxation(const Edge& edge, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const {
	Distance d_from = *dist_from_start.search(edge.from);
	Distance d_to = *dist_from_start.search(edge.to);
	if (d_to > d_from + edge.dist) {
		dist_from_start.insert_or_assign(edge.to, d_from + edge.dist);
		prev_vertex.insert_or_assign(edge.to, edge.from);
	}
}


template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::deikstra_alg(const Vertex& from, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const {
	// проверка графа на неотрицательный вес рёбер

	if (!is_valid_for_deikstra()) {
		throw std::invalid_argument("Graph has a edge with negative distance!");
	}

	// Непосредственно сам алгоритм Дейкстры
	for (auto u : _vertices) {
		dist_from_start.insert_or_assign(u, std::numeric_limits<Distance>::max());
	}
	dist_from_start.insert_or_assign(from, 0);




	std::vector<Vertex> unvisited = vertices();

	auto comparator = [&dist_from_start](Vertex a, Vertex b) {
		return (*dist_from_start.search(b)) < (*dist_from_start.search(a));
		};

	std::priority_queue<Vertex, std::vector<Vertex>, decltype(comparator)> queue(comparator, unvisited);
	while (!queue.empty()) {
		// Извлекаем вершину с минимальной оценкой расстояния
		Vertex u = queue.top();

		// теперь u есть вершина с минимальной оценкой пути
		for (const Edge& edge : edges(u)) {
			edge_relaxation(edge, dist_from_start, prev_vertex);
		}

		queue.pop();
	}
}


template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::path_reconstruction(const Vertex& from, const Vertex& to, UnorderedMap<Vertex, Distance>& dist_from_start, UnorderedMap<Vertex, Vertex>& prev_vertex) const {
	std::vector<Edge> inv_way;
	Vertex cur_vertex = to;
	while (cur_vertex != from) {
		Vertex prev_vert = *prev_vertex.search(cur_vertex);

		Distance edge_dist = *dist_from_start.search(cur_vertex) - *dist_from_start.search(prev_vert);
		Edge add_edge(prev_vert, cur_vertex, edge_dist);
		inv_way.push_back(add_edge);
		// Переход на предыдущую вершину
		cur_vertex = prev_vert;
	}
	std::reverse(inv_way.begin(), inv_way.end());
	return inv_way;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const {
	UnorderedMap<Vertex, Distance> dist_from_start;
	UnorderedMap<Vertex, Vertex> prev_vertex;
	deikstra_alg(from, dist_from_start, prev_vertex);

	//*******************************************************************************
	return path_reconstruction(from, to, dist_from_start, prev_vertex);
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::export_to_csv(const std::string& filename, bool include_vertices) const {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file: " + filename);
	}

	// Если нужно экспортировать вершины
	if (include_vertices) {
		file << "# Vertices\n";
		file << "vertex\n";
		for (const auto& v : _vertices) {
			file << v << "\n";
		}
		file << "\n";
	}

	// Экспорт ребер
	file << "# Edges (source,target,weight)\n";
	file << "source,target,weight\n";

	for (const auto& v : _vertices) {
		auto edges_list = _graph_table.search(v);
		if (edges_list) {
			for (const auto& edge : *edges_list) {
				file << edge.from << "," << edge.to << "," << edge.dist << "\n";
			}
		}
	}

	file.close();
}
#endif