#include "cachelab.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
// 打印-h参数
void print_h() {
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h        Print this help message.\n");
    printf("  -v        Optional verbose flag.\n");
    printf("  -s <num>  Number of set index bits.\n");
    printf("  -E <num>  Number of lines per set.\n");
    printf("  -b <num>  Number of block offset bits.\n");
    printf("  -t <file> Trace file.\n\n");
    printf("Examples:\n");
    printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}
// 快速幂
int fpow(int base, int exp) {
    int res = 1;
    while(exp) {
        if(exp & 1)res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}
// 字符串转int
int stoi(char* str) {                          
    int len = strlen(str);
    int sum = 0,i = 0;
    for(i = 0; i < len; ++i) {
        sum *= 10;
        if(str[i] >= '0' && str[i] <= '9') {
            sum += str[i] - '0';
        } else {
            return -1;
        }
    }
    return sum;
}
// 缓存行
typedef struct Line {
    int valid_bit;
    int tag_bits;
    int left_block;
    int right_block;
    int store_time;
}Line;
// 记录载入时间的链表，方便evict
typedef struct Node {
    int value;
    struct Node* next;
}Node;
// 缓存组
typedef struct Group {
    Line* line;
    Node* access_list_head;
    Node* access_list_tail;
}Group;
// 缓存
typedef struct Cache {
    Group* group;
    int group_bits;
    int block_bits;
    int group_number;
    int line_number;
    int block_number;
}Cache;

typedef struct HandleResult {
    int hits;
    int misses;
    int evictions;
}HandleResult;

void cache_constructor(Cache* cache) {
    cache->group = (Group*) malloc(cache->group_number * sizeof(Group));
    int i = 0,j = 0;
    for(i = 0;i < cache->group_number; ++i) {
        cache->group[i].line = (Line*) malloc(cache->line_number * sizeof(Line));
        cache->group[i].access_list_tail = cache->group[i].access_list_head;
        for(j = 0;j < cache->line_number; ++j) {
            cache->group[i].line[j].valid_bit = 0;
            cache->group[i].line[j].tag_bits = 0;
            cache->group[i].line[j].left_block = 0;
            cache->group[i].line[j].right_block = 0;
            cache->group[i].line[j].store_time = 0;
        }
    }
}

void cache_destructor(Cache* cache) {
    int i = 0;
    for(i = 0;i < cache->group_number; ++i) {
        free(cache->group[i].line);
    }
    free(cache->group);
}

long parse_address(char* command) {
    int i = 0;
    long res = 0;
    for(i = 3;command[i] != ','; ++i) {
        res *= 16;
        if(command[i] >= '0' && command[i] <= '9') {
            res += command[i] - '0';
        }else {
            res += 10 + command[i] - 'a';
        }
    }
    return res;
}

void handle_operations(Cache* cache, char* file_path, bool verbose, HandleResult* res) {
    FILE* file;
    char command[40];
    
    file = fopen(file_path, "r");
    if( file == NULL ) {
        printf("open file %s error\n", file_path);
    }
    int time = 1;
    while(fgets(command, sizeof(command), file)) {
        if(command[0] == 'I'){continue;}
        int i = 0,len = strlen(command);
        for(i = 1;i < len-1;++i) {
            printf("%c",command[i]);
        }
        long address = parse_address(command);
        // printf("%ld\n",address);
        long block_id = address & ((1 << cache->block_bits) - 1);
        long group_id = (address >> cache->block_bits) & ((1 << cache->group_bits) - 1);
        long tag = address >> (cache->block_bits + cache->group_bits);
        // printf("%ld*****%ld*****%ld\n", tag, group_id, block_id);
        int hit_flag = -1,empty_line = -1,min_time = 0x3f3f3f3f,min_line = 0;
        for(i = 0;i < cache->line_number;++i) {
            int valid_bit = cache->group[group_id].line[i].valid_bit;
            int left_block = cache->group[group_id].line[i].left_block;
            int right_block = cache->group[group_id].line[i].right_block;
            int tag_bits = cache->group[group_id].line[i].tag_bits;
            int store_time = cache->group[group_id].line[i].store_time;
            if(valid_bit && tag == tag_bits && block_id >= left_block && block_id <= right_block) {
                hit_flag = 1;
                cache->group[group_id].line[i].store_time = time;
                break;
            }
            if(!valid_bit){
                empty_line = i;
            }
            if(store_time < min_time) {
                min_time = store_time;
                min_line = i;
            }
        }
        if(hit_flag != -1) {
            if(verbose){printf(" hit");}
            ++res->hits;
        } else if(empty_line != -1) {
            if(verbose){printf(" miss");}
            cache->group[group_id].line[empty_line].valid_bit = 1;
            cache->group[group_id].line[empty_line].tag_bits = tag;
            cache->group[group_id].line[empty_line].store_time = time;
            cache->group[group_id].line[empty_line].left_block = 0;
            cache->group[group_id].line[empty_line].right_block = (1 << cache->block_bits) - 1;
            ++res->misses;
        } else {
            if(verbose){printf(" miss eviction");}
            cache->group[group_id].line[min_line].valid_bit = 1;
            cache->group[group_id].line[min_line].tag_bits = tag;
            cache->group[group_id].line[min_line].store_time = time;
            cache->group[group_id].line[min_line].left_block = 0;
            cache->group[group_id].line[min_line].right_block = (1 << cache->block_bits) - 1;
            ++res->misses;
            ++res->evictions;
        }
        if(command[1] == 'M'){
            if(verbose){printf(" hit\n");}
            ++res->hits;
        } else {
            if(verbose){printf("\n");}
        }
        ++time;
    }
}

void cache_handle(int group_bits, int line_number, int block_bits, 
                    char* file_path, bool verbose, HandleResult* res) {
    Cache* cache = (Cache*) malloc(sizeof(Cache));
    cache->group_bits = group_bits;
    cache->block_bits = block_bits;
    cache->group_number = fpow(2, group_bits);
    cache->line_number = line_number;
    cache->block_number = fpow(2, block_bits);
    cache_constructor(cache);

    handle_operations(cache, file_path, verbose, res);

    cache_destructor(cache);
}

int main(int argc, char *argv[]) {
    int i = 0;
    bool help = false, verbose = false;
    int group_bits = -1, block_bits = -1, line_number = -1;
    char* file_path = NULL;
    for(i = 0;i < argc; ++i) {
        if( !strcmp(argv[i], "-h") ) {
            help = true;
        }
        if( !strcmp(argv[i], "-v") ) {
            verbose = true;
        }
        if( !strcmp(argv[i], "-s") ) {
            group_bits = stoi(argv[i+1]);
        }
        if( !strcmp(argv[i], "-b") ) {
            block_bits = stoi(argv[i+1]);

        }
        if( !strcmp(argv[i], "-E")) {
            line_number = stoi(argv[i+1]);

        }
        if( !strcmp(argv[i], "-t")) {
            file_path = argv[i+1];
        }
    }
    if(help || group_bits == -1 || block_bits == -1 || line_number == -1 || file_path == NULL){
        print_h();
        return 0;
    }

    HandleResult res;
    res.hits = 0;
    res.misses = 0;
    res.evictions = 0;
    cache_handle(group_bits, line_number, block_bits, file_path, verbose, &res);

    printSummary(res.hits, res.misses, res.evictions);
    return 0;
}
