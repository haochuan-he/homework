// 以下程序来自罗荣鑫：
// 通过按位进行异或运算在同一变量res中进行，同一数两次进行会回复为0，最终剩下的1010...将会是落单的数（出现奇数次）
/*
#include<stdio.h>
#include<math.h>

int main(void){
    int n;
    scanf("%d",&n);
    int res=0;
    for(int i=1;i<=n*2-1;i++){
        int tmp;
        scanf("%d",&tmp);
        res^=tmp;
    }
    printf("%d\n",res);
    return 0;
}
*/

/*
// 23.10.8 18点41分
// for homework
// by HHC

#include <stdio.h>

int main()
{
    int num[1000012] = {0};
    int total = 0;
    scanf("%d ", &total);

    for (int i = 0; i < (2 * total - 1); i++)
    {
        int number = -1;
        scanf("%d", &number);
        if (num[number] == 0)
        {
            num[number] = number;
        }
        else
        {
            num[number] = 0;
        }
    }

    int single = -2;
    for (int i = 0; i < 1000012; i++)
    {
        if (num[i] >= 1)
        {
            single = num[i];
            break;
        }
    }

    printf("%d", single);

    return 0;
}

*/