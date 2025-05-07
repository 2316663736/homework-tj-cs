#include<iostream>
#include <string> 

using namespace std;
class all_ {
public:
    int fro_next[2] = { 0,0 };
    //int fro = 0;
    string color = "";
    int bianhao = 10;
    //int next = 0;
};

void cuowu(string a)
{
    for (int i = 0; i < 100; i++)
    {
        cout << "错误" << endl;
        cout << a << endl;
        getchar();
        i--;
    }
}int nnn = 0;
int bianhao_(string hao)
{
    hao[0] = (hao[0] >= 'a' && hao[0] <= 'z') ? (hao[0] - 'a' + 'A') : hao[0];

    if (hao[0] == '1')
        return 10;
    for (int i = 2; i < 10; i++)
        if (hao[0] == (i + '0'))
            return i;
    if (hao[0] == 'A')
        return 1;
    else if (hao[0] == 'J')
        return  11;
    else if (hao[0] == 'Q')
        return 12;
    else if (hao[0] == 'K')
        return 13;

    return 0;
}
void output(all_ the)
{
    cout << the.color << " ";
    if (the.bianhao == 1)
        cout << "A";
    else if (the.bianhao >= 2 && the.bianhao <= 10)
        cout << the.bianhao;
    else if (the.bianhao == 11)
        cout << "J";
    else if (the.bianhao == 12)
        cout << "Q";
    else
        cout << "K";
    cout << endl;
}
int main()
{
    /*第0个位置不存放任何东西*/
    all_ puke[1000];
    string chose, hao, tem_color;
    //first代表排队顶，last代表牌堆底，now_num代表现在的牌的数量
    int first = 1, last = 1, now_num = 0, chose_num, have_num = 0;
    int revert = 0;
    cin >> chose_num;
    for (int i = 0; i < chose_num; i++)
    {
        cin >> chose;
        if (chose == "Append")
        {
            now_num++;
            have_num++;
            cin >> puke[have_num].color >> hao;
            puke[have_num].bianhao = bianhao_(hao);
            if (now_num != 1)
            {
                puke[have_num].fro_next[revert] = last;
                puke[last].fro_next[1 - revert] = have_num;
            }
            else
            {
                puke[have_num].fro_next[revert] =NULL;
                first = have_num;
            }
            puke[have_num].fro_next[1 - revert] = NULL;
            last = have_num;
        }
        else if (chose == "Extract")
        {
            cin >> tem_color;
            int extract_num = 0;
            int tem_last = last, tem_first, tem_num = 1,tem_tt=0;

            while (tem_last != first && tem_num < now_num)
            {
                tem_num++;
                tem_tt++;
                if (tem_tt > 1000)
                    break;
                int tem_last_tem = puke[tem_last].fro_next[revert];
                if (puke[tem_last].color == tem_color)
                {

                    tem_first = first;
                    while (puke[tem_first].color == puke[tem_last].color && puke[tem_first].bianhao < puke[tem_last].bianhao)
                    {
                        tem_first = puke[tem_first].fro_next[1 - revert];
                     
                    }
                    if (tem_last == tem_first||tem_first==0)
                        goto lab;

                    puke[puke[tem_last].fro_next[revert]].fro_next[1 - revert] = puke[tem_last].fro_next[1 - revert];
                    if (tem_last != last)
                        puke[puke[tem_last].fro_next[1 - revert]].fro_next[revert] = puke[tem_last].fro_next[revert];
                    else
                    {
                        last = puke[tem_last].fro_next[revert];
                        puke[last].fro_next[1-revert] = NULL;

                    }

                    puke[tem_last].fro_next[1 - revert] = tem_first;
                    puke[tem_last].fro_next[revert] = puke[tem_first].fro_next[revert];
                    if (tem_first != first)
                    {
                        puke[puke[tem_first].fro_next[revert]].fro_next[1 - revert] = tem_last;
                        tem_num--;
                    }
                    else
                    {
                        first = tem_last;
                        puke[first].fro_next[revert] = NULL;
                    }
                    puke[tem_first].fro_next[revert] = tem_last;
                  
                }
                lab:
                if (tem_last_tem != NULL)
                    tem_last = tem_last_tem;
                else
                    break;
            }
        }
        else if (chose == "Revert")
        {
            revert = (revert + 1) % 2;
            int tem = last;
            last = first;
            first = tem;
        }
        else if (chose == "Pop")
        {
            if (now_num == 0)
                cout << "NULL" << endl;
            else
            {
                now_num--;
                output(puke[first]);
                if (puke[first].fro_next[1 - revert] != NULL)
                    puke[puke[first].fro_next[1 - revert]].fro_next[revert] = NULL;

                first = puke[first].fro_next[1 - revert];
            }
        }

    }
    int tem = first;
    if (now_num != 0)
        for (int i = 0; i < now_num; i++)
        {
            if (tem != NULL)
                output(puke[tem]);

            tem = puke[tem].fro_next[1 - revert];

        }
    else
        cout << "NULL";
}
