#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Node {
    string name;
    Node* parent;
    vector<Node*> children;
    Node(string n) : name(n), parent(nullptr) {}
};

class FamilyTree {
private:
    Node* root;
    map<string, Node*> nameMap;

    void cleanTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            cleanTree(child);
        }
        delete node;
    }

    // 修改后的祖先判断
    bool isAncestorHelper(Node* ancestor, Node* descendant) {
        if (!descendant || !ancestor) return false;
        if (ancestor == descendant) return true;
        return isAncestorHelper(ancestor, descendant->parent);
    }

public:
    FamilyTree() : root(nullptr) {}

    ~FamilyTree() {
        cleanTree(root);
    }

    void buildTree(vector<string>& lines) {
        nameMap.clear();
        if (lines.empty()) return;

        root = new Node(lines[0]);
        nameMap[lines[0]] = root;

        Node* lastNodes[71] = { nullptr };  // 增加数组大小以防溢出
        int lastIndents[71] = { 0 };
        lastNodes[0] = root;
        lastIndents[0] = 0;
        int lastLevel = 0;

        for (size_t i = 1; i < lines.size(); i++) {
            string& line = lines[i];
            int indent = 0;
            while (indent < line.length() && line[indent] == ' ') indent++;
            string name = line.substr(indent);

            Node* newNode = new Node(name);
            nameMap[name] = newNode;

            // 修改父节点查找逻辑
            int level = lastLevel;
            while (level >= 0 && lastIndents[level] >= indent) {
                level--;
            }

            newNode->parent = lastNodes[level];
            lastNodes[level]->children.push_back(newNode);

            lastLevel = level + 1;
            lastNodes[lastLevel] = newNode;
            lastIndents[lastLevel] = indent;
        }
    }

    // 修改关系判断函数
    bool isChild(const string& child, const string& parent) {
        if (!nameMap.count(child) || !nameMap.count(parent)) return false;
        if (child == parent) return false;  // 不能是自己的孩子
        Node* childNode = nameMap[child];
        return childNode->parent && childNode->parent->name == parent;
    }

    bool isParent(const string& parent, const string& child) {
        return isChild(child, parent);
    }

    bool isSibling(const string& name1, const string& name2) {
        if (!nameMap.count(name1) || !nameMap.count(name2)) return false;
        if (name1 == name2) return true;  // 可以是自己的兄弟
        Node* node1 = nameMap[name1];
        Node* node2 = nameMap[name2];
        return node1->parent && node2->parent &&
            node1->parent == node2->parent;
    }

    bool isDescendant(const string& descendant, const string& ancestor) {
        if (!nameMap.count(descendant) || !nameMap.count(ancestor)) return false;
        return isAncestorHelper(nameMap[ancestor], nameMap[descendant]);
    }

    bool isAncestor(const string& ancestor, const string& descendant) {
        return isDescendant(descendant, ancestor);
    }
};

bool processQuery(const string& query, FamilyTree& tree) {
    stringstream ss(query);
    string name1, is, a, relation, of, name2;
    ss >> name1 >> is >> a >> relation >> of >> name2;

    // 去除name2末尾的句号
    if (name2.back() == '.') {
        name2.pop_back();
    }

    if (relation == "child") {
        return tree.isChild(name1, name2);
    }
    else if (relation == "parent") {
        return tree.isParent(name1, name2);
    }
    else if (relation == "sibling") {
        return tree.isSibling(name1, name2);
    }
    else if (relation == "descendant") {
        return tree.isDescendant(name1, name2);
    }
    else if (relation == "ancestor") {
        return tree.isAncestor(name1, name2);
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n >> m && (n || m)) {
        cin.ignore();

        vector<string> lines;
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            while (!line.empty() && line.back() == ' ') {
                line.pop_back();  // 移除行尾空格
            }
            lines.push_back(line);
        }

        FamilyTree tree;
        tree.buildTree(lines);

        for (int i = 0; i < m; i++) {
            string query;
            getline(cin, query);
            cout << (processQuery(query, tree) ? "True" : "False") << endl;
        }
        cout << endl;
    }
    return 0;
}