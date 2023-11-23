#include <iostream>
#include <iomanip>
#include <climits>
//#include <locale>
#include <windows.h>
#include <algorithm>

using namespace std;

bool Permutation(int* perm) {
	const int n = 4;
	int i = 0, j = 0;

	// Меняем значение двух элементов
	std::swap(perm[j], perm[i]);

	// Ищем максимальный i, такой что perm[i] < perm[i + 1]
	for (i = n - 2; i >= 0; i--) {
		if (perm[i] < perm[i + 1]) {
			break;
		}
	}

	// Проверка на последнюю перестановку
	if (i == -1)
		return false;

	// Разворот подмассива с i+1 до конца
	std::reverse(perm + i + 1, perm + n);

	// Ищем первое perm[i] < perm[j] и меняем их местами
	j = i + 1;
	while (perm[i] < perm[j])
		j++;
	std::swap(perm[i], perm[j]);

	// Успешно завершено, следующая перестановка найдена
	return true;
}

const int V = 6;

void Dijkstra(int GR[V][V], int startVertex) {
	int distance[V];
	bool visited[V];
	int count, index, i, u;
	int sourceVertex = startVertex + 1;

	for (i = 0; i < V; i++) {
		distance[i] = INT_MAX;
		visited[i] = false;
	}
	distance[startVertex] = 0;

	for (count = 0; count < V - 1; count++) {
		int minDistance = INT_MAX;

		for (i = 0; i < V; i++) {
			if (!visited[i] && distance[i] <= minDistance) {
				minDistance = distance[i];
				index = i;
			}
		}

		u = index;
		visited[u] = true;

		for (i = 0; i < V; i++) {
			if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
				distance[u] + GR[u][i] < distance[i]) {
				distance[i] = distance[u] + GR[u][i];
			}
		}
	}

	cout << "Длина пути от вершины " << sourceVertex << " до других вершин:\n";
	for (i = 0; i < V; i++) {
		if (distance[i] != INT_MAX) {
			cout << sourceVertex << " > " << i + 1 << " = " << distance[i] << endl;
		}
		else {
			cout << sourceVertex << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
		}
	}
}

int main() {
	/*setlocale(LC_ALL, "Russian");*/
	//Для русского языка
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int start, GR[V][V] = {
		{0, 3, 0, 0, 0, 2},
		{0, 0, 2, 0, 0, 0},
		{0, 0, 0, 7, 1, 0},
		{0, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}

	};
	cout << "Начальная вершина >> ";
	cin >> start;
	Dijkstra(GR, start - 1);
	Permutation(GR[0]);
	return 0;
}
