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
    tree->AddSensitiveWord(L"中国");
    tree->AddSensitiveWord(L"国家");
    tree->AddSensitiveWord(L"国民");
    tree->AddSensitiveWord(L"栗战书");
    tree->AddSensitiveWord(L"习近平");
    tree->AddSensitiveWord(L"习近平主席");
    tree->AddSensitiveWord(L"中共");
    tree->AddSensitiveWord(L"中共中央");
    tree->AddSensitiveWord(L"俄罗斯");
    tree->AddSensitiveWord(L"二十大");
    tree->AddSensitiveWord(L"纪委");
    tree->AddSensitiveWord(L"政治");
    tree->AddSensitiveWord(L"社会主义");
    tree->AddSensitiveWord(L"干部");
    tree->AddSensitiveWord(L"经济");
    tree->AddSensitiveWord(L"腐败");
    tree->AddSensitiveWord(L"反腐败");
    tree->AddSensitiveWord(L"世界");
    tree->AddSensitiveWord(L"区域");
    tree->AddSensitiveWord(L"总理");
    tree->AddSensitiveWord(L"自由");
    tree->AddSensitiveWord(L"法治");
    tree->AddSensitiveWord(L"日本狗");
    tree->AddSensitiveWord(L"王八蛋");
    tree->AddSensitiveWord(L"垃圾");
    tree->AddSensitiveWord(L"鬼子");
    tree->AddSensitiveWord(L"革命");
    tree->AddSensitiveWord(L"政策");
    tree->AddSensitiveWord(L"精神");
    tree->AddSensitiveWord(L"联盟");
    tree->AddSensitiveWord(L"医疗");
    tree->AddSensitiveWord(L"持续");
    tree->AddSensitiveWord(L"安全");
    tree->AddSensitiveWord(L"全球");
    tree->AddSensitiveWord(L"思想");
    tree->AddSensitiveWord(L"日本");
    tree->AddSensitiveWord(L"日本鬼子");
    tree->AddSensitiveWord(L"日本人");
    tree->DelSensitiveWord(L"日本人");
    tree->DelSensitiveWord(L"日本鬼子");
    tree->AddSensitiveWord(L"日本狗");
    tree->AddSensitiveWord(L"东方");
    std::vector<std::wstring> textVec = {
        L"第七届东方经济论坛全会7日下午在俄罗斯符拉迪沃斯托克举行",
        L"中国全国人大常委会委员长栗战书出席并作了题为《推动世界多极化进程开启区域合作新篇章》的致辞",
        L"俄罗斯总统普京、缅甸国家管理委员会主席敏昂莱、蒙古国总理奥云额尔登、亚美尼亚总理帕什尼扬出席会议并致辞",
        L"印度总理莫迪、马来西亚总理伊斯迈尔、越南总理范明政发表视频致辞",
        L"栗战书说，习近平主席先后两次应普京总统邀请出席东方经济论坛并发表重要致辞",
        L"阐述了中方对发展中俄关系、推进区域互利合作、维护地区和平稳定的主张和倡议",
        L"在国际社会引发热烈反响。本届东方经济论坛以“通向多极世界之路”为主题，正当其时",
        L"世界多极化是历史发展的大势，也是国际社会的普遍期待",
        L"去年以来，习近平主席先后提出全球发展倡议和全球安全倡议",
        L"得到联合国等国际组织以及包括俄罗斯在内的众多国家响应支持",
        L"为世界注入稳定性和正能量，为破解时代难题贡献了中国智慧和中国方案",
        L"中方愿继续同国际社会一道，以持续有力的举措，推动两大倡议落地生根、开花结果，为世界各国人民带来实实在在的利益",
        L"栗战书指出，今年2月，习近平主席同普京总统就拓展两国全方位务实合作、践行共商共建共享的全球治理观达成许多重要共识",
        L"中国是俄罗斯远东开发的重要合作伙伴，中俄开展远东合作是两国元首亲自推动和规划的重要合作内容",
        L"中方将进一步加强同俄罗斯的贸易、能源、农业、基础设施建设、科技、教育、医疗、文化等领域的全方位合作",
        L"继续支持和参与俄罗斯远东开发，助推中国东北全面振兴与俄远东开发国家战略深度对接，促进中俄在远东合作取得丰硕成果",
        L"栗战书强调，东北亚是当今世界最具活力的地区之一",
        L"深化远东开发与合作，将为促进本地区的安全与发展提供重要机遇",
        L"一是要践行全球安全倡议，维护地区和平稳定",
        L"建设和谐安宁的共同家园，别无他法，唯有各方携手合力，秉持共同、综合、合作",
        L"可持续的安全观，对话而不对抗，结伴而不结盟，团结而非分裂，坚持安全不可分割",
        L"不断为维护地区和平稳定注入正能量",
        L"二是要落实全球发展倡议，促进区域开放融合。要提振发展伙伴关系，汇聚合作资源和平台",
        L"加强发展政策联通，挖掘创新增长潜力，维护产业链供应链安全畅通",
        L"打造更加稳定、安全、自由的贸易投资环境，为促进经济全球化进程注入新动力",
        L"三是要深化发展战略对接，提升中俄远东合作",
        L"中方将全面落实好习近平主席和普京总统达成的重要共识",
        L"积极开展“一带一路”建设和欧亚经济联盟对接合作，丰富中俄远东合作内涵",
        L"两国立法机构要加强协作，为此提供立法保障",
        L"栗战书表示，中国是世界多极化的坚定支持者和积极推动者",
        L"中国愿同包括俄罗斯在内的区域各国一道，深化共建“一带一路“",
        L"谱写东北亚区域合作美好篇章，为推动构建人类命运共同体而不懈努力",
        L"在互动交流环节，栗战书就当前中俄关系以及中俄远东合作前景回答了全会主持人提问",
        L"8日上午，栗战书会见了俄罗斯滨海边疆区行政长官科热米亚科",
        L"并考察了中方参与建设的符拉迪沃斯托克艺术文化综合体",
        L"中共中央政治局常委、中央纪委书记赵乐际8日出席全国纪检监察系统表彰大会并讲话",
        L"他强调，纪检监察机关要深入学习贯彻习近平新时代中国特色社会主义思想",
        L"弘扬伟大建党精神和自我革命精神，发挥先进典型示范引领作用，更好地履行党章和宪法赋予的职责",
        L"坚定不移推进全面从严治党、党风廉政建设和反腐败斗争，以实际行动迎接党的二十大胜利召开",
        L"赵乐际指出，在以习近平同志为核心的党中央坚强领导下",
        L"十九届中央纪委和各级纪检监察机关认真贯彻落实全面从严治党战略部署",
        L"坚定稳妥、守正创新，忠实履职尽责，正风肃纪反腐取得新进展新成效",
        L"广大纪检监察干部牢记使命、不负重托，经受了磨砺考验，作出了重要贡献",
        L"涌现出一批先进典型，集中体现了忠诚坚定、担当尽责、遵纪守法、清正廉洁的政治品格和精神风貌",
        L"要学习宣传先进模范，弘扬先进典型精神，激励全系统崇尚先进",
        L"学习先进、争当先进，促进新时代纪检监察工作高质量发展",
        L"赵乐际强调，要以这次表彰为契机，与时俱进加强纪检监察机关自身建设",
        L"坚持不懈推进纪检监察系统自我革命，努力打造一支忠诚干净担当",
        L"可亲可信可敬的纪检监察干部队伍。要深刻领悟“两个确立”的决定性意义",
        L"自觉增强“四个意识”、坚定“四个自信”、做到“两个维护”，加强党的政治建设",
        L"提高政治判断力、政治领悟力、政治执行力，在思想上政治上行动上同党中央保持高度一致",
        L"做政治过硬的表率。自觉担当负责尽责、敢于善于斗争，坚持以党性立身做事",
        L"坚守实事求是生命线，精准把握政策策略，善于开展深入细致的思想政治工作，做本领高强的表率",
        L"自觉遵守党纪国法、严格执纪执法，加强规范化、法治化、正规化建设，增强法治意识",
        L"程序意识、证据意识，以法治思维和法治方式正风反腐，让纪法成为不可逾越的底线，做纪法严明的表率",
        L"自觉践行“三严三实”、坚守清正廉洁，坚持打铁必须自身硬，在行使权力上慎之又慎",
        L"在自我约束上严之又严，始终保持谦虚谨慎、戒骄戒躁，始终保持求真务实",
        L"干净纯洁，坚决防止“灯下黑”，做作风优良的表率",
        L"中共中央政治局委员、中央纪委副书记杨晓渡主持表彰大会",
        L"大会宣读了表彰决定，为受表彰代表颁奖",
        L"受表彰的集体和个人代表在会上作了发言",
        L"那个岛国日本日本人是我们中国人不喜欢的",
        L"日本中国国家不可分割的一部分"
    };
   time_t now = time(0);  
   char* dt = ctime(&now);
   std::cout << "本地日期和时间：" << dt << std::endl;
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
    std::cout << "本地日期和时间：" << dt << std::endl;
    delete tree;
    getchar();
    return 0;
}