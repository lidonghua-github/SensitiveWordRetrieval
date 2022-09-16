#include "TreeTrie.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <winnls.h>
#include <stack>
#include <ctime>

void TreeTrie::destroy(TreeNode* node)
{
    if (node->subNodes.empty())
    {
        delete node;
        return;
    }
    std::unordered_map<wchar_t, TreeNode*>& nodesMap = node->subNodes;
    for (auto it = nodesMap.begin(); it != nodesMap.end();)
    {        
        TreeNode* tmp = it->second;
        it = nodesMap.erase(it);       
        destroy(tmp);          
    }
    destroy(node);
}

TreeTrie::TreeTrie()
{
    root = new TreeNode();
}

TreeTrie::~TreeTrie()
{
    if (root)
    {
        destroy(root);
        root = nullptr;
    }
}

void TreeTrie::AddSensitiveWord(std::wstring words)
{
    TreeNode* tempNode = root;
    for(int i = 0; i < words.length(); i++)
    {
        wchar_t c = words.at(i);
        auto it = tempNode->subNodes.find(c);
        if (it == tempNode->subNodes.end())
        {
            TreeNode* node = new TreeNode;
            tempNode->subNodes.insert(std::pair<wchar_t,TreeNode*>(c, node));
        }
        tempNode = tempNode->subNodes.at(c);
    }
    tempNode->isEnd = true;
}

void TreeTrie::DelSensitiveWord(std::wstring words)
{
    if (words == L"") return;
    TreeNode* tempNode = root;
    struct delNode {
        TreeNode* node;
        TreeNode* next;       
        wchar_t c;
    };
    std::stack<struct delNode> nodeStack;
    for (int i = 0; i < words.length(); i++)
    {
        wchar_t c = words.at(i);       
        auto it = tempNode->subNodes.find(c);
        if (it == tempNode->subNodes.end()) return;
        delNode node = {tempNode, it->second, c};
        nodeStack.push(node);
        tempNode = it->second;
    }
    if (!tempNode->isEnd) return;
    if (!tempNode->subNodes.empty()) 
    {
        tempNode->isEnd = false;
        return;
    }
    while (!nodeStack.empty())
    {
        delNode node = nodeStack.top();
        nodeStack.pop();      
        delete node.next;
        node.node->subNodes.erase(node.c);     
        if (node.node->isEnd || node.node->subNodes.size() > 0)
        {
            break;
        }       
    }
}

std::unordered_map<int, int> TreeTrie::filter(std::wstring text)
{
    std::unordered_map<int, int> positionMap;
    if (text == L"") return positionMap;
    TreeNode* tempNode = root;
    int begin = 0;
    int position = 0;
    while (position < text.length())
    { 
        wchar_t c = text.at(position);      
        auto it = tempNode->subNodes.find(c);
        if (it == tempNode->subNodes.end()) 
        {
            if (tempNode == root)
            {
                position++;              
            } else
            {
                tempNode = root;
            }
            begin = position;
            continue;
        }
        tempNode = it->second; 
        if (tempNode->isEnd)
        {         
            auto it = positionMap.find(begin);
            if (it == positionMap.end())
            {
                positionMap.insert(std::pair<int, int>(begin, position));
            } else
            {
                it->second = position;
            }
            position++;
            if (tempNode->subNodes.empty())
            {
                begin = position;
                tempNode = root;
            }
        } else 
        {
            position++;
        }
    }
    return positionMap;
}

std::string UTF8_To_string(const std::wstring& str) 
{
    char* pBuf = new char[str.length() * 2 + 1]();  
    WideCharToMultiByte(CP_ACP, 0, str.c_str(), int(str.length()), pBuf, int(str.length() * 2 + 1), NULL, NULL);
    std::string strRet = pBuf; 
    delete []pBuf; 
    pBuf = NULL; 
    return strRet; 
}

int main(void)
{
    TreeTrie* tree = new TreeTrie;
    tree->AddSensitiveWord(L"�й�");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"��ս��");
    tree->AddSensitiveWord(L"ϰ��ƽ");
    tree->AddSensitiveWord(L"ϰ��ƽ��ϯ");
    tree->AddSensitiveWord(L"�й�");
    tree->AddSensitiveWord(L"�й�����");
    tree->AddSensitiveWord(L"����˹");
    tree->AddSensitiveWord(L"��ʮ��");
    tree->AddSensitiveWord(L"��ί");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"�������");
    tree->AddSensitiveWord(L"�ɲ�");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"������");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"�ձ���");
    tree->AddSensitiveWord(L"���˵�");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"ҽ��");
    tree->AddSensitiveWord(L"����");
    tree->AddSensitiveWord(L"��ȫ");
    tree->AddSensitiveWord(L"ȫ��");
    tree->AddSensitiveWord(L"˼��");
    tree->AddSensitiveWord(L"�ձ�");
    tree->AddSensitiveWord(L"�ձ�����");
    tree->AddSensitiveWord(L"�ձ���");
    tree->DelSensitiveWord(L"�ձ���");
    tree->DelSensitiveWord(L"�ձ�����");
    tree->AddSensitiveWord(L"�ձ���");
    tree->AddSensitiveWord(L"����");
    std::vector<std::wstring> textVec = {
        L"���߽춫��������̳ȫ��7�������ڶ���˹��������˹�п˾���",
        L"�й�ȫ���˴�ί��ίԱ����ս���ϯ��������Ϊ���ƶ�����༫�����̿������������ƪ�¡����´�",
        L"����˹��ͳ�վ��������ҹ���ίԱ����ϯ���������ɹŹ�������ƶ���ǡ���������������ʲ�����ϯ���鲢�´�",
        L"ӡ������Ī�ϡ���������������˹������Խ����������������Ƶ�´�",
        L"��ս��˵��ϰ��ƽ��ϯ�Ⱥ�����Ӧ�վ���ͳ�����ϯ����������̳��������Ҫ�´�",
        L"�������з��Է�չ�ж��ϵ���ƽ�������������ά��������ƽ�ȶ������źͳ���",
        L"�ڹ�������������ҷ��졣���춫��������̳�ԡ�ͨ��༫����֮·��Ϊ���⣬������ʱ",
        L"����༫������ʷ��չ�Ĵ��ƣ�Ҳ�ǹ��������ձ��ڴ�",
        L"ȥ��������ϰ��ƽ��ϯ�Ⱥ����ȫ��չ�����ȫ��ȫ����",
        L"�õ����Ϲ��ȹ�����֯�Լ���������˹���ڵ��ڶ������Ӧ֧��",
        L"Ϊ����ע���ȶ��Ժ���������Ϊ�ƽ�ʱ�����⹱�����й��ǻۺ��й�����",
        L"�з�Ը����ͬ�������һ�����Գ��������ľٴ룬�ƶ�������������������������Ϊ��������������ʵʵ���ڵ�����",
        L"��ս��ָ��������2�£�ϰ��ƽ��ϯͬ�վ���ͳ����չ����ȫ��λ��ʵ���������й��̹��������ȫ������۴�������Ҫ��ʶ",
        L"�й��Ƕ���˹Զ����������Ҫ������飬�ж�չԶ������������Ԫ�������ƶ��͹滮����Ҫ��������",
        L"�з�����һ����ǿͬ����˹��ó�ס���Դ��ũҵ��������ʩ���衢�Ƽ���������ҽ�ơ��Ļ��������ȫ��λ����",
        L"����֧�ֺͲ������˹Զ�������������й�����ȫ���������Զ����������ս����ȶԽӣ��ٽ��ж���Զ������ȡ�÷�˶�ɹ�",
        L"��ս��ǿ�����������ǵ���������߻����ĵ���֮һ",
        L"�Զ���������������Ϊ�ٽ��������İ�ȫ�뷢չ�ṩ��Ҫ����",
        L"һ��Ҫ����ȫ��ȫ���飬ά��������ƽ�ȶ�",
        L"�����г�����Ĺ�ͬ��԰������������Ψ�и���Я�ֺ��������ֹ�ͬ���ۺϡ�����",
        L"�ɳ����İ�ȫ�ۣ��Ի������Կ������������ˣ��Ž���Ƿ��ѣ���ְ�ȫ���ɷָ�",
        L"����Ϊά��������ƽ�ȶ�ע��������",
        L"����Ҫ��ʵȫ��չ���飬�ٽ����򿪷��ںϡ�Ҫ����չ����ϵ����ۺ�����Դ��ƽ̨",
        L"��ǿ��չ������ͨ���ھ�������Ǳ����ά����ҵ����Ӧ����ȫ��ͨ",
        L"��������ȶ�����ȫ�����ɵ�ó��Ͷ�ʻ�����Ϊ�ٽ�����ȫ�򻯽���ע���¶���",
        L"����Ҫ���չս�ԶԽӣ������ж�Զ������",
        L"�з���ȫ����ʵ��ϰ��ƽ��ϯ���վ���ͳ��ɵ���Ҫ��ʶ",
        L"������չ��һ��һ·�������ŷ�Ǿ������˶ԽӺ������ḻ�ж�Զ�������ں�",
        L"������������Ҫ��ǿЭ����Ϊ���ṩ��������",
        L"��ս���ʾ���й�������༫���ļᶨ֧���ߺͻ����ƶ���",
        L"�й�Ըͬ��������˹���ڵ��������һ�����������һ��һ·��",
        L"��д�����������������ƪ�£�Ϊ�ƶ������������˹�ͬ�����иŬ��",
        L"�ڻ����������ڣ���ս��͵�ǰ�ж��ϵ�Լ��ж�Զ������ǰ���ش���ȫ������������",
        L"8�����磬��ս�����˶���˹�����߽����������ٿ������ǿ�",
        L"���������з����뽨��ķ�������˹�п������Ļ��ۺ���",
        L"�й��������ξֳ�ί�������ί������ּ�8�ճ�ϯȫ���ͼ���ϵͳ���ô�Ტ����",
        L"��ǿ�����ͼ������Ҫ����ѧϰ�᳹ϰ��ƽ��ʱ���й���ɫ�������˼��",
        L"����ΰ�󽨵���������Ҹ������񣬷����Ƚ�����ʾ���������ã����õ����е��º��ܷ������ְ��",
        L"�ᶨ�����ƽ�ȫ������ε���������������ͷ����ܶ�������ʵ���ж�ӭ�ӵ��Ķ�ʮ��ʤ���ٿ�",
        L"���ּ�ָ��������ϰ��ƽͬ־Ϊ���ĵĵ������ǿ�쵼��",
        L"ʮ�Ž������ί�͸����ͼ����������᳹��ʵȫ������ε�ս�Բ���",
        L"�ᶨ���ס��������£���ʵ��ְ����������ͷ���ȡ���½�չ�³�Ч",
        L"���ͼ���ɲ��μ�ʹ�����������У�������ĥ�¿��飬��������Ҫ����",
        L"ӿ�ֳ�һ���Ƚ����ͣ������������ҳϼᶨ��������������ط����������������Ʒ��;����ò",
        L"Ҫѧϰ�����Ƚ�ģ���������Ƚ����;��񣬼���ȫϵͳ�����Ƚ�",
        L"ѧϰ�Ƚ��������Ƚ����ٽ���ʱ���ͼ��칤����������չ",
        L"���ּ�ǿ����Ҫ����α���Ϊ��������ʱ�����ǿ�ͼ������������",
        L"��ֲ�и�ƽ��ͼ���ϵͳ���Ҹ�����Ŭ������һ֧�ҳϸɾ�����",
        L"���׿��ſɾ��ļͼ���ɲ����顣Ҫ�����������ȷ�����ľ���������",
        L"�Ծ���ǿ���ĸ���ʶ�����ᶨ���ĸ����š�������������ά��������ǿ�������ν���",
        L"��������ж���������������������ִ��������˼�����������ж���ͬ�����뱣�ָ߶�һ��",
        L"�����ι�Ӳ�ı��ʡ��Ծ����������𡢸������ڶ���������Ե�����������",
        L"����ʵ�����������ߣ���׼�������߲��ԣ����ڿ�չ����ϸ�µ�˼�����ι������������ǿ�ı���",
        L"�Ծ����ص��͹������ϸ�ִ��ִ������ǿ�淶�������λ������滯���裬��ǿ������ʶ",
        L"������ʶ��֤����ʶ���Է���˼ά�ͷ��η�ʽ���練�����üͷ���Ϊ������Խ�ĵ��ߣ����ͷ������ı���",
        L"�Ծ����С�������ʵ���������������࣬��ִ�����������Ӳ������ʹȨ������֮����",
        L"������Լ������֮���ϣ�ʼ�ձ���ǫ��������佾���꣬ʼ�ձ���������ʵ",
        L"�ɾ����࣬�����ֹ�����ºڡ��������������ı���",
        L"�й��������ξ�ίԱ�������ί��������������ֱ��ô��",
        L"��������˱��þ�����Ϊ�ܱ��ô���佱",
        L"�ܱ��õļ���͸��˴����ڻ������˷���",
        L"�Ǹ������ձ��ձ����������й��˲�ϲ����",
        L"�ձ��й����Ҳ��ɷָ��һ����"
    };
   time_t now = time(0);  
   char* dt = ctime(&now);
   std::cout << "�������ں�ʱ�䣺" << dt << std::endl;
    for(int i = 0; i < 1000000; i++)
    {
        for(auto it = textVec.begin(); it != textVec.end(); it++)
        {
            std::unordered_map<int, int> positionVec = tree->filter(*it);
            if (!positionVec.empty())
            {
                std::cout << UTF8_To_string(*it) << std::endl;
                std::wstring text = *it;
                for (auto itP = positionVec.begin(); itP != positionVec.end(); itP++)
                {
                    text.replace(itP->first, itP->second - itP->first + 1, itP->second - itP->first + 1, 42);   
                }
                std::cout << UTF8_To_string(text) << std::endl;                
            }       
        }        
    }
    now = time(0);  
    dt = ctime(&now);
    std::cout << "�������ں�ʱ�䣺" << dt << std::endl;
    delete tree;
    getchar();
    return 0;
}