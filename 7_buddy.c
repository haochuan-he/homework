// 23.11.18
// for homework
// by HHC

#include <stdio.h>
#include <math.h>
#define MAX 112

int memory[MAX][4];
//[0][0]保留最大节点序号,即节点总数
//
//[][0]节点序号
//[][1]为此节点空间取log2
//[][2]为此节点id
//[][3]为下一个节点的下标
void question(void);
int allot(int id, int space);
int division(int space);

int main()
{
    for (int i = 0; i < MAX; i++)
    {
        memory[i][1] = -1;
    }
    int n = 0, q = 0;
    scanf("%d%d", &n, &q);
    getchar();
    memory[1][1] = n;
    memory[0][0] = 1; // 初始最大号为1
    memory[1][0] = 1; // 第一位序号为1
    memory[1][3] = 0; // 末尾指针指向0
    // loop for q times
    for (int i = 0; i < q; i++)
    {
        char order = getchar();
        if (order == 'Q')
        {
            question();
        }
        else if (order == 'A')
        {
            int id = 0, space = 0;
            scanf("%d%d", &id, &space);
            int real_space = 0;
            while (space > pow(2, real_space))
            {
                real_space++;
            }
            // printf("%d", real_space);//FOR TEST
            allot(id, real_space);
        }
        else
        {
            printf("--WRONG--");
        }
        getchar();
    }
    return 0;
}

/*******************************************************************
 * queation:respond to the find request
 *
 *
 */
void question(void)
{
    printf("%d\n", memory[0][0]);
    int i = 1;
    for (; memory[i][3] != i; i = memory[i][3]) // 借用指针
    {
        printf("%d ", memory[i][2]);
    }
    // printf("%d", memory[i][2]); // for the end node
    printf("\n");
    return;
}

/*******************************************************************
 * allot: allot the space step by step
 *
 *
 */

int allot(int id, int space)
{
    // printf("-%d-", space);
    // find the space just suitable and the index-first to allot
    int i = 1;
    for (; memory[i][3] != i; i = memory[i][3]) // 借用指针
    {
        if (memory[i][2] == 0 && memory[i][1] == space)
        {
            memory[i][1] = space;
            memory[i][2] = id;
            return 0;
        }
    }

    division(space);
    return allot(id, space);
}

/*******************************************************************
 * division: divide the space into two parts
 *
 */
int division(int space)
{
    int i = 1;
    for (; memory[i][3] != i; i = memory[i][3]) // 借用指针
    {
        if (memory[i][2] == 0 && memory[i][1] > space)
        {

            // 中间节点分裂，原后续节点序号++，此节点置于数组末尾空位
            memory[0][0]++;                         // 总数+1
            memory[i][1]--;                         // 源节点空间减少
            memory[memory[0][0]][1] = memory[i][1]; // 新节点空间

            // 节点插入
            memory[memory[0][0]][3] = memory[i][3];
            memory[i][3] = memory[0][0];

            return 0;
        }
    }

    return 0;
}

/*if (memory[j][2] == 0 && memory[j][1] > space)
        {

            if (j <= memory[0][0])
            { // 中间节点分裂，原后续节点序号++，此节点置于数组末尾空位
                memory[0][0]++;
                memory[j][1]--;
                memory[memory[0][0]][1] = memory[j][1];
                memory[memory[0][0]][0] = memory[j][0] + 1;

                for (int begin = memory[j][0] + 1; begin < memory[0][0]; begin++) // 遍历所有后续序号
                {
                    int start = 1;
                    for (; memory[start][0] != begin; start++) // 确实找到所需序号
                        ;
                    memory[start][0]++;
                }
                return 0;
            }
            else
            {
                printf("WRONG HERE");
            }*/
// // 23.11.17
// // for homework
// // by HHC

// #include <stdio.h>
// #include <math.h>
// #define MAX 10012

// int memory[MAX][3];
// //[0][0]保留最大节点序号,即节点总数
// //
// //[][0]节点序号
// //[][1]为此节点空间取log2
// //[][2]为此节点id
// void question(void);
// int allot(int id, int space);
// int division(int space);

// int main()
// {
//     for (int i = 0; i < MAX; i++)
//     {
//         memory[i][1] = -1;
//     }
//     int n = 0, q = 0;
//     scanf("%d%d", &n, &q);
//     getchar();
//     memory[1][1] = n;
//     memory[0][0] = 1; // 初始最大号为1
//     memory[1][0] = 1; // 第一位序号为1
//     // loop for q times
//     for (int i = 0; i < q; i++)
//     {
//         char order = getchar();
//         if (order == 'Q')
//         {
//             question();
//         }
//         else if (order == 'A')
//         {
//             int id = 0, space = 0;
//             scanf("%d%d", &id, &space);
//             int real_space = 0;
//             while (space > pow(2, real_space))
//             {
//                 real_space++;
//             }
//             // printf("%d", real_space);//FOR TEST
//             allot(id, real_space);
//         }
//         else
//         {
//             printf("--WRONG--");
//         }
//         getchar();
//     }
//     return 0;
// }

// /*******************************************************************
//  * queation:respond to the find request
//  *
//  * tested
//  */
// void question(void)
// {
//     printf("%d\n", memory[0][0]);
//     for (int i = 1; i <= memory[0][0]; i++) // 遍历所有序号
//     {
//         int j = 1;
//         for (; memory[j][0] != i; j++)
//         {
//             if (memory[memory[0][0] + 1 - j][0] == i)
//             {
//                 j = memory[0][0] + 1 - j;
//                 break;
//             }
//         } // 确实找到所需序号
//         ;
//         printf("%d ", memory[j][2]);
//         // printf("id%d-space%d-index%d ", memory[j][2], memory[j][1], memory[j][0]); // FOR TEST
//     }
//     printf("\n");
//     return;
// }

// /*******************************************************************
//  * allot: allot the space step by step
//  *
//  * tested
//  */

// int allot(int id, int space)
// {
//     // printf("-%d-", space);
//     // find the space just suitable and the index-first to allot
//     for (int i = 1; i <= memory[0][0]; i++)
//     {
//         int j = 1;
//         for (; memory[j][0] != i; j++)
//         {
//             if (memory[memory[0][0] + 1 - j][0] == i)
//             {
//                 j = memory[0][0] + 1 - j;
//                 break;
//             }
//         }
//         if (memory[j][2] == 0 && memory[j][1] == space)
//         {
//             memory[j][1] = space;
//             memory[j][2] = id;
//             return 0;
//         }
//     }

//     division(space);
//     return allot(id, space);
// }

// /*******************************************************************
//  * division: divide the space into two parts
//  *
//  */
// int division(int space)
// {
//     for (int i = 1; i <= memory[0][0]; i++)
//     {
//         int j = 1;
//         for (; memory[j][0] != i; j++)
//         {
//             if (memory[memory[0][0] + 1 - j][0] == i)
//             {
//                 j = memory[0][0] + 1 - j;
//                 break;
//             }
//         }
//         if (memory[j][2] == 0 && memory[j][1] > space)
//         {

//             if (j <= memory[0][0])
//             { // 中间节点分裂，原后续节点序号++，此节点置于数组末尾空位
//                 memory[0][0]++;
//                 memory[j][1]--;
//                 memory[memory[0][0]][1] = memory[j][1];
//                 memory[memory[0][0]][0] = memory[j][0] + 1;

//                 for (int begin = memory[j][0] + 1; begin < memory[0][0]; begin++) // 遍历所有后续序号
//                 {
//                     int start = 1;
//                     for (; memory[start][0] != begin; start++) // 确实找到所需序号
//                         ;
//                     memory[start][0]++;
//                 }
//                 return 0;
//             }
//             else
//             {
//                 printf("WRONG HERE");
//             }
//         }
//     }
//     return 0;
// }