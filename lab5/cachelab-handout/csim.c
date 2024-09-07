#include "cachelab.h"
#include <stdbool.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ul unsigned long 
int s, S, E, b, B, count, val, result[3];
ul address;
FILE *f;
bool display;
char tp, *word[3] = {" hit", " miss", " eviction"}, out[20];
struct line
{
    int count;
    ul tag;
};
struct line **cache;

void init()
{
    cache = (struct line **)malloc(sizeof(struct line *) * S);
    for (int i = 0; i < S; i++)
    {
        cache[i] = (struct line *)malloc(sizeof(struct line) * E);
        for (int j = 0; j < E; j++)
            cache[i][j].count = 0;
    }
}

void destory()
{
    for (int i = 0; i < S; i++)
        free(cache[i]);
    free(cache);
    fclose(f);
}

int getGroup(ul address) // 第b位开始取s位
{
    return address << (64 - b - s) >> (64 - s);
}

ul getTag(int address)
{
    return address >> (s + b);
}

void modify(int c, int r, ul tag, int op)
{
    ++result[op];
    if (display)
        strcat(out, word[op]);
    if (r == -1)
        return;
    cache[c][r].tag = tag;
    cache[c][r].count = count;
}

void work()
{
    int pos = getGroup(address);
    ul tag = getTag(address);
   // printf("%d %lld\n",pos,tag);
    int minPos = 0, isEmpty = -1;
    for (int i = 0; i < E; i++)
    {
        if (!cache[pos][i].count)
        {
            isEmpty = i;
        }
        else
        {
            if (cache[pos][i].tag == tag)
            {
                modify(pos, i, tag, 0); // hit
                return;
            }
            if (cache[pos][i].count < cache[pos][minPos].count)
                minPos = i;
        }
    }
    modify(pos, isEmpty, tag, 1); // miss;
    if (isEmpty == -1)
        modify(pos, minPos, tag, 2); // eviction
}

void command(int argc, char **argv)
{
    char op;
    while ((op=getopt(argc, argv, "hvsEbt"))!=EOF)
    {
        switch (op)
        {
        case 'h':
            break;
        case 'v':
            display = 1;
            break;
        case 's':
            s = atoi(argv[optind]);
            S = 1 << s;
            break;
        case 'E':
            E = atoi(argv[optind]);
        case 'b':
            b = atoi(argv[optind]);
            B = 1 << b;
            break;
        case 't':
            f = fopen(argv[optind], "r");
            break;
        }
    }
}

int main(int argc, char **argv)
{
    command(argc, argv);
    init();
    while (fscanf(f, " %c %lx,%d", &tp, &address, &val)==3)
    {
        if(tp=='I') continue;
        ++count;
        memset(out, 0, sizeof(out));
        work();
        if (tp == 'M')
        {
            ++result[0];
            if (display)
                strcat(out, word[0]);
        }
        if (display)
            fprintf(stdout, "%c %lx,%d%s\n", tp, address, val, out);
    }
    destory();
    printSummary(result[0], result[1], result[2]);
    return 0;
}
