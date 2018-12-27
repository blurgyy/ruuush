// Solution to Floating Formation
// Author: Alex ten Brink

// Time complexity: O(n + m)
// Memory: O(n + m)

// @EXPECTED_RESULTS@: CORRECT

#include <stack>
#include <vector>
#include <iostream>
using namespace std;

struct Node
{
    Node* next;
    Node* previous;
    int key;
    int value;
    Node(int key, int value) : next(nullptr), previous(nullptr), key(key), value(value)
    {
    }
    Node* Append(int value)
    {
        Node* newNode = new Node(key, value);
        if (next != nullptr)
        {
            next->previous = newNode;
            newNode->next = next;
        }
        next = newNode;
        newNode->previous = this;
        return newNode;
    }
    void Remove()
    {
        if (previous != nullptr)
        {
            previous->next = next;
        }
        if (next != nullptr)
        {
            next->previous = previous;
        }
        next = nullptr;
        previous = nullptr;
    }
};

struct BoundedHeap
{
    Node** bins;
    int capacity;
    int currentMax = -1;
    BoundedHeap(int capacity) : capacity(capacity)
    {
        bins = new Node*[capacity];
	for (int i = 0; i < capacity; i++) bins[i] = nullptr;
    }
    Node* Add(int key, int value)
    {
        if (currentMax == -1)
        {
            currentMax = key;
        }
        if (key > currentMax)
        {
            currentMax = key;
        }
        if (bins[key] == nullptr)
        {
            return bins[key] = new Node(key, value);
        }
        else
        {
            return bins[key]->Append(value);
        }
    }
    Node* DecreaseKey(Node* node, int newkey)
    {
        Remove(node);
        return Add(newkey, node->value);
    }
    Node* GetMax()
    {
        while (currentMax >= 0)
        {
            if (bins[currentMax] != nullptr)
                return bins[currentMax];
            currentMax--;
        }
        return nullptr;
    }
    Node* Get(int key)
    {
        if (bins[key] != nullptr)
            return bins[key];
        return nullptr;
    }
    void Remove(Node* node)
    {
        int key = node->key;
        if (bins[key] == node)
        {
            bins[key] = node->next;
        }
        node->Remove();
    }
};

struct Vertex
{
    Vertex(Node* node) : parent(nullptr), node(node), isattachedtree(false), depth(0) { }
    vector<Vertex*> chilren;
    Vertex* parent;
    Node* node;
    bool isattachedtree;
    int depth;
    int indexofmax;
};

int main()
{
	int runs;
	cin >> runs;
	while (runs > 0)
	{
        int n, m, k;
        cin >> n >> m >> k;
	if (n > 10000) { cerr << "Too many vertices" << endl; exit(1); }
	if (m > 10000) { cerr << "Too many edges" << endl; exit(1); }
	if (k > 10000) { cerr << "Too many spare boats" << endl; exit(1); }

        vector<int>* edges = new vector<int>[n];

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
		if (a > n || a < 1 || b > n || b < 1) { cerr << "Edge out of range" << endl; exit(1); }
            edges[a-1].push_back(b-1);
            edges[b-1].push_back(a-1);
        }

        BoundedHeap verticesbydegree(n+1);
        Vertex** vertices = new Vertex*[n];
        for (int i = 0; i < n; i++)
        {
            vertices[i] = new Vertex(verticesbydegree.Add(edges[i].size(), i));
        }

        while (verticesbydegree.Get(1) != nullptr)
        {
            Node* current = verticesbydegree.Get(1);
            int x = current->value;
            vertices[x]->isattachedtree = true;
            for (unsigned int i = 0; i < edges[x].size(); i++)
            {
                int y = edges[x][i];
                if (vertices[y]->isattachedtree)
                {
                    vertices[y]->parent = vertices[x];
                    vertices[x]->chilren.push_back(vertices[y]);
                }
                else
                {
                    vertices[y]->node = verticesbydegree.DecreaseKey(vertices[y]->node, vertices[y]->node->key-1);
                }
            }
            verticesbydegree.Remove(current);
        }
        BoundedHeap verticesbydepth(n);
        int sizeof2core = 0;
        for (int i = 0; i < n; i++)
        {
            if (!vertices[i]->isattachedtree)
            {
                sizeof2core++;
            }
            if (vertices[i]->isattachedtree && vertices[i]->parent == nullptr)
            {
                // Found root vertex
                // We push vertices on totalstack in such a way that all children
                // of a node are higher on the stack than their parents
                stack<int> workingstack;
                stack<int> totalstack;
                workingstack.push(i);
                while (!workingstack.empty())
                {
                    int current = workingstack.top();
                    workingstack.pop();
                    if (vertices[current]->chilren.size() > 0)
                    {
                        for (unsigned int j = 0; j < vertices[current]->chilren.size(); j++)
                        {
                            workingstack.push(vertices[current]->chilren[j]->node->value);
                        }
                        totalstack.push(current);
                    }
                    else
                    {
                        vertices[current]->depth = 1;
                        vertices[current]->node = verticesbydepth.Add(1, current);
                    }
                }
                while (!totalstack.empty())
                {
                    int current = totalstack.top();
                    totalstack.pop();
                    int maxofchildren = 0;
                    int indexofmax = 0;
                    for (unsigned int j = 0; j < vertices[current]->chilren.size(); j++)
                    {
                        if (vertices[current]->chilren[j]->depth > maxofchildren)
                        {
                            maxofchildren = vertices[current]->chilren[j]->depth;
                            indexofmax = j;
                        }
                    }
                    vertices[current]->depth = maxofchildren + 1;
                    vertices[current]->indexofmax = indexofmax;
                    vertices[current]->node = verticesbydepth.Add(maxofchildren + 1, current);
                }
            }
        }

        int saveddesigns = 0;
        for (int i = 0; (i < k) && (verticesbydepth.GetMax() != nullptr); i++)
        {
            Node* maxnode = verticesbydepth.GetMax();
            saveddesigns += maxnode->key;
            Vertex* currentvertex = vertices[maxnode->value];
            while (currentvertex->chilren.size() > 0)
            {
                verticesbydepth.Remove(currentvertex->node);
                currentvertex = currentvertex->chilren[currentvertex->indexofmax];
            }
            verticesbydepth.Remove(currentvertex->node);
        }

        delete[] vertices;
        delete[] edges;

        cout << (n - sizeof2core - saveddesigns) << endl;

		runs--;
	}
	return 0;
}
