#include <iostream>
#include <string>
#include<vector>
using namespace std;



void Q1() {

    float n;
    float m;
    int k;
    scanf_s("%f %f %d", &n, &m, &k);



    for (int i = 0; i < k; i++) {

        n /= m;

    }


    printf("%0.4f", n);

}

void Q2() {

    int a;
    int b;
    int c;
    scanf_s("%d %d %d", &a, &b, &c);

    bool is_trian = false;
    
    if (a == b) {


        if (a != c) is_trian = true;

    }
    else if (b == c) {

        if (a != c) is_trian = true;
    }
    else if (a == c) {

        if (b != c) is_trian = true;

    }
    

    if(is_trian)printf("Yes");
    else printf("No");

}

void Q3() {

    int n;

    scanf_s("%d", &n);

    int price = n * 3 + 5;

    printf("%d", price);

}

void Q4() {

   int num=0;

    scanf_s("%d", &num);

    bool is_num = true;
    /*
    for (int i = 0; num[i] == '\0';i++) {

        if (!isdigit(str[i])) {
            //数字じゃなかったら
            is_num = false;

        }

    }
    */
    if (is_num) {



    }
    else printf("Error");

}

void Q5() {

    int a;

    scanf_s("%d", &a);

    bool is_uruu = false;

    if (a % 4==0) {
        //4で割り切れて
        if (a % 100 == 0) {

            if (a % 400 == 0) {

                is_uruu = true;

            }else is_uruu = false;


        }else is_uruu = true;
    }

    if (is_uruu) printf("%d年は閏年です", a);
    else printf("%d年は平年です", a);
}

void Q6() {

    char strong_map[6][20] = {
        "Error",
        "Very Weak"
        "Weak",
        "Good",
        "Strong",
        "Very Strong"
    };


    int securty_power=0;

    char str[256];

    scanf_s("%s", str,256);

    int str_lenght = 0;

    int str_kind[4] = { 0,0,0,0 };

    for (int i = 0; str[i] != '\0'; i++) {

        //もし文字が英語で
        if (isupper(str[i])) {

            str_kind[0] = 1;

        }
        else if (islower(str[i])) {
            

            str_kind[1] = 1;
        }
        else if (isdigit(str[i])) {

            str_kind[2] = 1;

        }
        else if (isprint(str[i])) {

            str_kind[3] = 1;

        }

        str_lenght++;
    }
    //もし文字列が8文字以上なら
    if (str_lenght >= 8) {
        securty_power++;
    }
    //もし文字列が114文字以上なら
    if (str_lenght >= 14) {
        securty_power++;
    }

    int kind = 0;
    for (int i = 0; i < 4; i++) {

        if (str_kind[i] == 1) {
            kind++;
        }

    }
    if (kind >= 2) {
        securty_power++;
    }
    if (kind >= 3) {
        securty_power++;
    }
    if (kind >= 4) {
        securty_power++;
    }

    printf("%s", strong_map[securty_power]);


}

struct Route {
    int s;
    int g;
    int t;
};


void SearchPass(int s, int g, vector<Route> route, int* score) {

    vector<Route> buff_route = route;

    //で受け取ったもののなかから最短経路を見つける
    //スタートと同じものを見つける
    for (int i = 0; i < buff_route.size(); i++) {

        if (buff_route[i].s == s) {

            //探索する
            //タイムを足す
            (*score) += buff_route[i].t;

            if (buff_route[i].g != g) {

                SearchPass(buff_route[i].g, g, route, score);

            }




        }


    }

}

void Q7() {

    int n;

    int s;

    int g;

    scanf_s("%d %d %d",&n,&s,&g);

    vector<Route> route;

    route.resize(n);

    for (int i = 0; i < n; i++) {
        //受け取る
        scanf_s("%d %d %d", &route[i].s, &route[i].g, &route[i].t);
        printf("%d %d %d\n", route[i].s, route[i].g, route[i].t);
    }

    //で受け取ったもののなかから最短経路を見つける
    int score = 120;
    //スタートと同じものを見つける

    //SearchPass(s,g,route,&score);
    for (int i = 0; i < n; i++) {
        
        int score_buff = 0;

        if (route[i].s == s) {

            score_buff += route[i].t;

            SearchPass(route[i].g,g, route,&score_buff);

            

        }

        if (score_buff >0&&score > score_buff) score = score_buff;

    }
    
    printf("%d", score);

}

void Q8() {

    char str[256];

    scanf_s("%s",str,256);

    int num_num[10];

    for (int i = 0; i < 10; i++) {
        num_num[i] = 0;
    }
   
    for (int i = 0; str[i]!='\0'; i++) {

        const char c = str[i];
        int num = atoi(&c);

        num_num[num]++;

    }

    for (int i = 0; i < 10;i++) {

       printf("'%d':",i);
       for (int j = 0; j < num_num[i]; j++) {

                printf("*");

       }
       printf("\n");

    }


}

void Q9() {

    char buff_str[1000];

    scanf_s("%s", buff_str, 1000);


    char old_str;

    for (int i = 0; buff_str[i] != '\0'; i++) {

        if (buff_str[i] == '*') {
            //開業する
            printf("\n");

        }
        if (buff_str[i] == '+') {

        }
        if (isalpha(buff_str[i])) {

            old_str = buff_str[i];

        }
        if (isdigit(buff_str[i])) {

            int j = atoi(&buff_str[i]);
            for (int n=0; n < j; n++) {
                printf("%c", old_str);
            }
            
        }
    }

    

}

void Q10() {


    //お菓子袋
    int m;

    //人数
    int n;


    struct Snack {
        int cander;
        int num;
    };

    Snack snack[2];

    scanf_s("%d %d",&n,&m);

    for (int i = 0; i < 2; i++) {
        scanf_s("%d %d", &snack[i].cander, &snack[i].num);
    }
    /*
    どのお菓子袋も未開封の状態でちょうど一人の子供に分配される
        全員が貰えるキャンディーの数は同数
        全員が貰えるお菓子袋の数も同数
        お菓子袋に入っているキャンディー以外のお菓子の数は必ずしも同数でなくてもよい
    */


    //できるときは"YATTA!"
        //できないときは"ZANNEN"
}


void Q11() {


    //お金
    int n;

    //預金の種類
    int b;

    float yokin_kind[4] = {
        0.1f,
        0.2f,
        0.5f,
        0.2f,
    };

    scanf_s("%d %d", &n, &b);

    const int max_time = 72;

    float buff = n;

    for (int i = 0; i < max_time; i++) {

        buff = buff + (buff * yokin_kind[b]);


        if (i == 23) {

            
            float z = buff - b;
            z--;

            printf("%.f\n", z);
        }
        if (i == 47) {
            float z = buff - b;
            z--;
            printf("%.f\n", z);
        }
        if (i == 71) {
            float z = buff - b;
            z--;
            printf("%.f\n", z);
        }
    }
    


}


class BIGINT {
public:
    char m_v[2000];
    int lenght;
    BIGINT() {
        m_v[0] = '1';
        lenght = 1;
    }

    BIGINT operator *= (int i) {

        for (int j = 0; j < lenght; j++) {
           
        }
    }
};


void Q12() {

    char str;

    int n;

    scanf_s("%d", &n);

    int buff=1;

    for (int i = n; i > 0; i--) {


        buff *= i;



    }

    printf("%d", buff);
}

void Q13() {

    int n;

    char str[256];

    scanf_s("%d\n", &n);

    gets_s(str, 256);

    char* buff = new char[n];

    int l = 0;
    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] != ' ') {

            buff[l] = atoi(&str[i]);
            l++;
        }

    }

    for (int i = 0; i < l; i++) {
        printf("%d\n",buff[i]);
    }

    char y = buff[0];

     y = y ^ (y - 1);

    printf("%d", y);
}

int main()
{
    Q13();
   
}