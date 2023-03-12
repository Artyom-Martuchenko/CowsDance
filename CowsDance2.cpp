#include<iostream>
#include<vector>
#include<fstream>
#include<String>
using namespace std;
//--------------------------------------------------------------------------------------------------
void reading(vector<vector<int>>& graph, vector<int>& used);
void writing(int answer);
void dfs_childgraph(vector<vector<int>>& graph, vector<int>& used);
void dfs_cycle(vector<vector<int>>& child_graph, int& number_groups);
int return_index(vector<vector<int>>& graph, int v1, int v2);
void searching_neighbour_graphs(vector<vector<int>>& graph, vector<vector<int>>& stack, vector<int>& used, int v2);
void searching_child_graphs(vector<vector<int>>& graph, vector<vector<int>>& child_graph, vector<int>& used);
void deleting_childgraph_from_graph(vector<vector<int>>& graph, vector<vector<int>>& child_graph, vector<int>& used);
//--------------------------------------------------------------------------------------------------
void reading(vector<vector<int>>& graph, vector<int>& used) //чтение графа
{
    int n, m;
    int v1, v2; 
    ifstream in("prom.10.in");
    in >> n >> m;
    used.resize(m, 0);//если размер used не равен m, то заполняется нулями
    while (!in.eof())
    {
        in >> v1 >> v2;
        vector<int> temp;
        temp.push_back(v1);
        temp.push_back(v2);
        graph.push_back(temp);
    }
    in.close();
}

void writing(int answer)
{
    ofstream out("prom.out");
    out << answer;
    out.close();
}

void dfs_childgraph(vector<vector<int>>& graph, vector<int>& used)
{
    vector<vector<int>> stack; 
    stack.push_back(graph[graph.size() - 1]);
    while (stack.size() != 0)
    {
        int index = return_index(graph, stack[stack.size() - 1][0], stack[stack.size() - 1][1]);
        if (used[index] == 0)
        {
            used[index] = 1;
            searching_neighbour_graphs(graph, stack, used, stack[stack.size() - 1][1]);
        }
        else if (used[index] == 1)
        {
            stack.erase(stack.begin() + return_index(stack, stack[stack.size() - 1][0], stack[stack.size() - 1][1]));
        }
    }
}

int return_index(vector<vector<int>>& graph, int v1, int v2) //Возвращает индекс вершины
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i][0] == v1 && graph[i][1] == v2)
        {
            return i;
        }
    }
    return 0;
}

void searching_neighbour_graphs(vector<vector<int>>& graph, vector<vector<int>>& stack, vector<int>& used, int v2) //Ищет белые соседние вершины 
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i][0] == v2 && used[i] == 0)
        {
            stack.push_back(graph[i]);
        }
    }
}

void searching_child_graphs(vector<vector<int>>& graph, vector<vector<int>>& child_graph, vector<int>& used) 
{
    for (int i = 0; i < used.size(); i++)
    {
        if (used[i] == 1)
        {
            child_graph.push_back(graph[i]);
        }
    }
}

void deleting_childgraph_from_graph(vector<vector<int>>& graph, vector<vector<int>>& child_graph, vector<int>& used)//удаление подграфа 
{
    vector<vector<int>> temp_graph;
    for (int i = 0; i < graph.size(); i++)
    {
        bool check = true;
        for (int j = 0; j < child_graph.size(); j++)
        {
            if (child_graph[j] == graph[i])
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            temp_graph.push_back(graph[i]);
        }
    }
    graph = temp_graph;
    used.clear();
    used.resize(graph.size(), 0);
}

void dfs_cycle(vector<vector<int>>& child_graph, int& number_groups)
{
    vector<vector<int>> stack; 
    vector<int> used; //использованные вершины
    stack.push_back(child_graph[child_graph.size() - 1]);
    used.resize(child_graph.size(), 0);
    while (stack.size() != 0)
    {
        int index = return_index(child_graph, stack[stack.size() - 1][0], stack[stack.size() - 1][1]);
        if (used[index] == 0)
        {
            used[index] = 1;
            searching_neighbour_graphs(child_graph, stack, used, stack[stack.size() - 1][1]);
        }
        else if (used[index] == 1)
        {
            number_groups++;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int number_groups = 0;
    vector<vector<int>> graph; //граф
    vector<vector<int>> child_graph; //подграф
    vector<int> used; //массив использованных вершин
    reading(graph, used); //чтение 
    while (graph.size() > 1)
    {
        dfs_childgraph(graph, used); //нахождение циклов подграфов
        searching_child_graphs(graph, child_graph, used); //нахождение подграфов
        deleting_childgraph_from_graph(graph, child_graph, used); //удаление подграфов с графа 
        dfs_cycle(child_graph, number_groups); //нахождение циклов 
        child_graph.clear(); //Очищение массива вершин подграфов
    }
    writing(number_groups);
    return 0;
}