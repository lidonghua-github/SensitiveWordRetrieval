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
    void AddSensitiveWord(std::wstring words);
    void DelSensitiveWord(std::wstring words);
    std::unordered_map<int, int> filter(std::wstring text);
private:
    void destroy(TreeNode* node);
};

