#pragma once
#include <unordered_map>
#include <string>

class TreeNode {
public:
    bool isEnd = false;
    std::unordered_map<wchar_t, TreeNode*> subNodes;   
};

class TreeTrie {
private:
    TreeNode* root = nullptr;
public:
    TreeTrie();
    ~TreeTrie();
public:
    // ������д�
    void AddSensitiveWord(std::wstring words);
    // ɾ�����д�
    void DelSensitiveWord(std::wstring words);
    /*
    �������д�
    ����һ������������д�λ�õ�map, map��keyΪ���дʵ���㣬valueΪ���дʵĽ���λ��
    */
    std::unordered_map<int, int> filter(std::wstring text);
private:
    void destroy(TreeNode* node);
};

