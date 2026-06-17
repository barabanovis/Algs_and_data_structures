#include "libs/Graph.h"
#include <string>
#include <filesystem>
#include <cstdlib>

using namespace std;

void run_python_script() {
    // Простой вызов
    int result = system("python ../../../visualization.py");

    if (result == 0) {
        std::cout << "Script executed successfully\n";
    }
    else {
        std::cout << "Script execution failed\n";
    }
}

// Stubs for functions that you will fill with your code
template <typename Vertex, typename Distance>
void demonstrateGraph(Graph<Vertex, Distance>& graph) {
    std::cout << "\n[Start] Demonstration of Graph class operation...\n";
    graph.export_to_csv("graph.csv");
    graph.export_to_csv("../../../graph.csv");

    run_python_script();


    vector<Graph<string, double>::Edge> path = graph.shortest_path("p", "Maze");
    for (auto u : path) {
        cout << u.from << " " << u.to << ' ' << u.dist << '\n';
    }
    cout << "Degree of p: " << graph.degree("p") << '\n';
    // Example: Graph g; g.print();
    std::cout << "[End] Demonstration successfully completed.\n";
}

template <typename Vertex, typename Distance>
void find_warehouse(Graph<Vertex, Distance>& graph) {
    vector<Vertex> vertexes = graph.vertices();

    Vertex ans_vertex = vertexes[0];
    double ans_aver = 1000000000;

    // Для каждой вершины применяем алгоритм дейкстры и считаем среднее
    for (auto vertex : vertexes) {
        UnorderedMap<Vertex, Distance> dist_from_start;
        UnorderedMap<Vertex, Vertex> prev_vertex;
        graph.deikstra_alg(vertex, dist_from_start, prev_vertex);

        // Просуммируем полученные значения для всех вершин и узнаем среднее
        double aver = 0;
        for (auto t : vertexes) {
            aver += *dist_from_start.search(t);
        }
        aver = aver / graph.order();

        if (aver < ans_aver) {
            ans_aver = aver;
            ans_vertex = vertex;
        }
    }
    

    cout << "Warehouse must be placed in vertex: " << ans_vertex << '\n';
    cout << "Average distance: " << ans_aver << '\n';
}

Graph<string, double> my_graph() {
    Graph<string, double> graph;
    graph.add_vertex("p");
    graph.add_vertex("Ozon");
    graph.add_vertex("WB");
    graph.add_vertex("Chizik");
    graph.add_vertex("Miko");
    graph.add_vertex("FixPrice");
    graph.add_vertex("Fashion");
    graph.add_vertex("Maze");

    graph.add_edge("p", "Ozon", 8);
    graph.add_edge("WB", "Ozon", 9);
    graph.add_edge("Chizik", "p", 18);
    graph.add_edge("p", "Chizik", 33);
    graph.add_edge("Chizik", "Ozon", 10);
    graph.add_edge("Ozon", "Chizik", 22);
    graph.add_edge("Ozon", "Miko", 14);
    graph.add_edge("Miko", "WB", 21);
    graph.add_edge("WB", "FixPrice", 7);
    graph.add_edge("Miko", "FixPrice", 2);
    graph.add_edge("FixPrice", "Maze", 1);
    graph.add_edge("Maze", "Miko", 0);
    graph.add_edge("Miko", "Maze", 23);
    graph.add_edge("Fashion", "Maze", 11);
    graph.add_edge("Fashion", "Maze", 52);
    graph.add_edge("Maze", "Fashion", 8);
    graph.add_edge("Chizik", "Miko", 8);
    graph.add_edge("Chizik", "Miko", 18);
    graph.add_edge("Chizik", "Fashion", 0);
    graph.add_edge("Chizik", "Fashion", 5);
    graph.add_edge("Fashion", "Chizik", 55);
    graph.print(cout);
    return graph;
}

template <typename Vertex, typename Distance>
void solveTask(Graph<Vertex, Distance> graph) {
    std::cout << "\n[Start] Solving task according to variant...\n";
    find_warehouse(graph);
    std::cout << "[End] Task solved.\n";
}



Graph<string, double> my_graph2() {
    Graph<string, double> graph;

    // Добавление вершин (города и точки интереса)
    graph.add_vertex("Moscow");
    graph.add_vertex("SPb");
    graph.add_vertex("Kazan");
    graph.add_vertex("Novosibirsk");
    graph.add_vertex("Vladivostok");
    graph.add_vertex("Sochi");
    graph.add_vertex("Ekaterinburg");
    graph.add_vertex("Krasnoyarsk");
    graph.add_vertex("Irkutsk");
    graph.add_vertex("Khabarovsk");
    graph.add_vertex("Yakutsk");

    // Добавление ребер (расстояния между городами в сотнях км)
    // Центральная Россия
    graph.add_edge("Moscow", "SPb", 7.0);
    graph.add_edge("SPb", "Moscow", 7.0);
    graph.add_edge("Moscow", "Kazan", 8.0);
    graph.add_edge("Kazan", "Moscow", 8.0);
    graph.add_edge("Moscow", "Sochi", 15.0);
    graph.add_edge("Sochi", "Moscow", 15.0);
    graph.add_edge("Moscow", "Ekaterinburg", 17.0);
    graph.add_edge("Ekaterinburg", "Moscow", 17.0);

    // Урал и Сибирь
    graph.add_edge("Kazan", "Ekaterinburg", 9.0);
    graph.add_edge("Ekaterinburg", "Kazan", 9.0);
    graph.add_edge("Ekaterinburg", "Novosibirsk", 15.0);
    graph.add_edge("Novosibirsk", "Ekaterinburg", 15.0);
    graph.add_edge("Novosibirsk", "Krasnoyarsk", 7.0);
    graph.add_edge("Krasnoyarsk", "Novosibirsk", 7.0);
    graph.add_edge("Krasnoyarsk", "Irkutsk", 10.0);
    graph.add_edge("Irkutsk", "Krasnoyarsk", 10.0);

    // Дальний Восток
    graph.add_edge("Irkutsk", "Yakutsk", 14.0);
    graph.add_edge("Yakutsk", "Irkutsk", 14.0);
    graph.add_edge("Irkutsk", "Khabarovsk", 30.0);
    graph.add_edge("Khabarovsk", "Irkutsk", 30.0);
    graph.add_edge("Khabarovsk", "Vladivostok", 7.0);
    graph.add_edge("Vladivostok", "Khabarovsk", 7.0);
    graph.add_edge("Novosibirsk", "Yakutsk", 28.0);
    graph.add_edge("Yakutsk", "Novosibirsk", 28.0);

    // Южные маршруты
    graph.add_edge("Sochi", "Kazan", 13.0);
    graph.add_edge("Kazan", "Sochi", 13.0);
    graph.add_edge("Sochi", "Ekaterinburg", 20.0);
    graph.add_edge("Ekaterinburg", "Sochi", 20.0);

    // Транссибирская магистраль (главные связи)
    graph.add_edge("Moscow", "Novosibirsk", 28.0);
    graph.add_edge("Novosibirsk", "Moscow", 28.0);
    graph.add_edge("Moscow", "Vladivostok", 70.0);
    graph.add_edge("Vladivostok", "Moscow", 70.0);

    // Дополнительные связи
    graph.add_edge("SPb", "Kazan", 10.0);
    graph.add_edge("Kazan", "SPb", 10.0);
    graph.add_edge("Krasnoyarsk", "Yakutsk", 18.0);
    graph.add_edge("Yakutsk", "Krasnoyarsk", 18.0);

    // Вывод информации о графе
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║              TRANSPORT NETWORK OF RUSSIA                    ║\n";
    cout << "╠══════════════════════════════════════════════════════════════╣\n";
    cout << "║  Cities: 11                                                    ║\n";
    cout << "║  Routes: 32                                                    ║\n";
    cout << "║  Type: Bidirectional weighted graph                           ║\n";
    cout << "║  Unit: Hundreds of kilometers (100 km)                        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";

    graph.print(cout);
    return graph;
}

int main() {
    // Enable Russian language support in console (for Windows)
    std::setlocale(LC_ALL, "Russian");

    int choice = 0;
    Graph<string, double> graph = my_graph();
    do {
        
        // Display menu on screen
        cout << "\n================ MENU ================\n";
        cout << "1) Demonstrate Graph class operation\n";
        cout << "2) Solve task according to variant\n";
        cout << "3) Exit program\n";
        cout << "======================================\n";
        cout << "Select menu item (1-3): ";

        // Input validation (to prevent program freezing on letter input)
        if (!(std::cin >> choice)) {
            std::cout << "\nError! Please enter a numeric value.\n";
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
            continue; // Return to loop start
        }

        // Processing user choice
        switch (choice) {
        case 1:
            demonstrateGraph(graph);
            break;
        case 2:
            solveTask(graph);
            break;
        case 3:
            std::cout << "\nExiting program. Goodbye!\n";
            break;
        default:
            std::cout << "\nInvalid option! Please select from 1 to 3.\n";
            break;
        }

    } while (choice != 3); // Loop continues until user chooses to exit

    return 0;
}