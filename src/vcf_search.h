#ifndef VCFSEARCH_H_
#define VCFSEARCH_H_

#include <vector>

#include "structs.h"
#include "pattern.h"

#define HASHSIZE 19997

//VCFSearch
typedef struct _node
{
    pos_t p1;
    pos_t p2;
    int pre, next;
}node_t;

typedef struct _listnode
{
    int pos;
    int score;
    int dist;
}ListNode;

typedef struct _hashnode
{
    int dep;
    unsigned long hash;
    int pre;
    move_t move;
    bool res;
    char color;
}HashNode;

class CVCFSearch {
    public:
        CVCFSearch();
        CVCFSearch(char* ptr_board[GRID_NUM], char* ptr_chess_type);

        //判断是否需要VCF搜索；
        bool vcf_judge(move_t * preMove);

        int init();

        void init_game();

        void before_search(char board[][GRID_NUM], char color);

        //VCF的实现；bestMove:返回最佳招法；preMove:传入上一步招法;
        bool vcf_search(int depth,char ourColor,move_t * bestMove,move_t * preMove, int preNode, int prePos);

        //反向VCF的实现；bestMove:返回最佳招法；preMove:传入上一步招法;
        bool anti_vcf_search(int depth,char ourColor,move_t * bestMove,move_t * preMove, int preNode, int prePos);

        //获取VCF招法；a_d:当前是进攻还是防守；canUse:传入可选择的点；moveList:返回招法序列和序列长度；
        int vcf_get_move_list( char ourColor,char a_d, pos_t * canUse, int n_Pos, move_t * moveList, move_t* pretMove);

    private:
        //判断是否结束；ourColor:当前棋的颜色；preMove:传入上一步的棋文件名；
        //bool IsWin(char ourColor, SMove * preMove);

        //判断该走法是否具有威胁
        int is_attack(char board[][GRID_NUM],char Color, move_t * Move);

        //判断该走法是否构成活四
        int is_dlb_attack(char board[][GRID_NUM],char Color, move_t * Move);
        void vcf_make_move(char Color, move_t * move);            //下棋
        void vcf_unmake_move(char Color, move_t * move);        //撤消招法
        int vcf_hash_check(HashNode node);
        unsigned long vcf_hash_board(char board[GRID_NUM][GRID_NUM]);

        int is_three(char position[GRID_NUM][GRID_NUM],char Color, pos_t * Pos);
        void sort(move_t * moveList, int n_moveList, move_t * preMove);
        inline int vcf_abs(int a);
        inline int dist(pos_t p1, pos_t p2, pos_t pt);
        inline int vcf_min(int a, int b);

    public:
        int                 m_vcf_node;

    private:
        CDFA                m_dfa;

        char                m_board[GRID_NUM][GRID_NUM];
        char                m_chess_type;
        char                m_has_win;

        char                m_org_board[GRID_NUM][GRID_NUM];
        ListNode            m_list_node[10000];
        move_t              m_tmp_move_list[10000];
        move_t              m_vcf_move_list[VCFDEPTH+1][10000];                        //生成的招法序列
        std::vector<int>    m_hash_map[VCFDEPTH+1][HASHSIZE];
        HashNode            m_hash_que[1000000];

        node_t              m_vcf_move_table[100000];
        int                 m_vcf_total_node;
        int                 m_vcf_now_pos;
        int                 m_dy[4];
        int                 m_dx[4];        //定义方向数组
        char                m_vcf_use[GRID_NUM][GRID_NUM][4];                    //评价标记数组
        char                m_vcf_mark[GRID_NUM][GRID_NUM];

};

#endif

