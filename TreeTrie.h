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
    // 添加敏感词
    void AddSensitiveWord(std::wstring words);
    // 删除敏感词
    void DelSensitiveWord(std::wstring words);
    /*
    检索敏感词
    返回一个标记所有敏感词位置的map, map的key为敏感词的起点，value为敏感词的结束位置
    */
    std::unordered_map<int, int> filter(std::wstring text);
private:
    void destroy(TreeNode* node);
};

