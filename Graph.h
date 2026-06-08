#ifndef GRAPH_H
#define GRAPT_H

#include <iostream>
#include <vector>

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {/*...*/ }
	//проверка-добавление-удаление вершин
	bool has_vertex(const Vertex& v) const;
	bool add_vertex(const Vertex& v); // false если вершина уже есть
	bool remove_vertex(const Vertex& v);
	std::vector<Vertex> vertices() const;
	//проверка-добавление-удаление ребер
	void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
	bool remove_edge(const Vertex& from, const Vertex& to);
	bool remove_edge(const Edge& e); //c учетом расстояния
	bool has_edge(const Vertex& from, const Vertex& to) const;
	bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

	std::vector<Edge> edges(const Vertex& vertex); //получение всех ребер, выходящих из вершины
	size_t order() const; //порядок
	size_t degree(const Vertex& v) const; //степень вершины
	bool is_connected() const; //является ли граф сильносвязным
	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;  //поиск кратчайшего пути 
	std::vector<Vertex> walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action)const; //обход
	void print();

	// Сделайте красивую визуализацию графа с помощью LLM. 
	// Можете красивый вывод в консоле сделать, можете сохранять как картинки. 
	// Пожалуйста, не поленитесь и сделайте визуализацию индивидуально.
};
#endif