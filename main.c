#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1000
#define BUFFER_LEN 1024000
#define INPUT "input.txt"

char instr[BUFFER_LEN];//输入符号串
int total_len;//输入符号串长度
int instr_index = 0;//当前输入符号读入字符的位置
char character[2];//全局变量字符，存放最新读入的字符
char token[LEN];//存放已读入的字符序列
char Reverse[LEN][10];//保留字表
char Boundary[LEN][10];//界符表
char Operator[LEN][10];//运算符表
int line = 1;//当前行数
int column = 1;//当前列数
int totalError = 0;//错误总数

// 类别编码依次是 保留字、标识符、常数
enum sign_type {
    RESERVE = 1, SYMBOL = 2, CONSTANT = 3
};

// 储存记号信息
typedef struct binary {
    int category;//类别编码
    int index;//表内位置
    char value[LEN];//记号内容
} Binary;

Binary Symbol[LEN];//标识符集
Binary Digit[LEN];//常数集
int symbol_len = 0;//标识符集当前元素个数
int digit_len = 0;//常数集当前元素个数

// 构造保留字表
void init_Reverse() {
    strcpy(Reverse[1], "auto");
    strcpy(Reverse[2], "break");
    strcpy(Reverse[3], "case");
    strcpy(Reverse[4], "char");
    strcpy(Reverse[5], "const");
    strcpy(Reverse[6], "continue");
    strcpy(Reverse[7], "default");
    strcpy(Reverse[8], "do");
    strcpy(Reverse[9], "double");
    strcpy(Reverse[10], "else");
    strcpy(Reverse[11], "enum");
    strcpy(Reverse[12], "extern");
    strcpy(Reverse[13], "float");
    strcpy(Reverse[14], "for");
    strcpy(Reverse[15], "goto");
    strcpy(Reverse[16], "if");
    strcpy(Reverse[17], "int");
    strcpy(Reverse[18], "long");
    strcpy(Reverse[19], "main");
    strcpy(Reverse[20], "register");
    strcpy(Reverse[21], "return");
    strcpy(Reverse[22], "short");
    strcpy(Reverse[23], "signed");
    strcpy(Reverse[24], "sizeof");
    strcpy(Reverse[25], "static");
    strcpy(Reverse[26], "struct");
    strcpy(Reverse[27], "switch");
    strcpy(Reverse[28], "typedef");
    strcpy(Reverse[29], "union");
    strcpy(Reverse[30], "unsigned");
    strcpy(Reverse[31], "void");
    strcpy(Reverse[32], "volatile");
    strcpy(Reverse[33], "while");
    strcpy(Reverse[34], "include");
    strcpy(Reverse[35], "define");
}

// 构造界符表
void init_Boundary() {
    strcpy(Boundary[4], "(");
    strcpy(Boundary[5], ")");
    strcpy(Boundary[6], "[");
    strcpy(Boundary[7], "]");
    strcpy(Boundary[8], "{");
    strcpy(Boundary[9], "}");
    strcpy(Boundary[10], "/*");
    strcpy(Boundary[11], "*/");
    strcpy(Boundary[12], "\"");
    strcpy(Boundary[13], "\'");
    strcpy(Boundary[14], ",");
    strcpy(Boundary[15], ";");
    strcpy(Boundary[16], "#");
}

// 构造运算符表
void init_Operator() {
    strcpy(Operator[17], "+");
    strcpy(Operator[18], "-");
    strcpy(Operator[19], "*");
    strcpy(Operator[20], "/");
    strcpy(Operator[21], "%");
    strcpy(Operator[22], "!");
    strcpy(Operator[23], "&&");
    strcpy(Operator[24], "||");
    strcpy(Operator[25], "++");
    strcpy(Operator[26], "--");
    strcpy(Operator[27], "&");
    strcpy(Operator[28], "|");
    strcpy(Operator[29], "^");
    strcpy(Operator[30], "~");
    strcpy(Operator[31], "<<");
    strcpy(Operator[32], ">>");
    strcpy(Operator[33], "<");
    strcpy(Operator[34], "<=");
    strcpy(Operator[35], ">");
    strcpy(Operator[36], ">=");
    strcpy(Operator[37], "!=");
    strcpy(Operator[38], "==");
    strcpy(Operator[39], "=");
    strcpy(Operator[40], "+=");
    strcpy(Operator[41], "-=");
    strcpy(Operator[42], "*=");
    strcpy(Operator[43], "/=");
    strcpy(Operator[44], "%=");
    strcpy(Operator[45], "<<=");
    strcpy(Operator[46], ">>=");
    strcpy(Operator[47], "&=");
    strcpy(Operator[48], "|=");
    strcpy(Operator[49], "^=");
    strcpy(Operator[50], ".");
    strcpy(Operator[51], "->");
    strcpy(Operator[52], "?");
    strcpy(Operator[53], ":");
}

// 连接字符串 token 和 character
void concat() {
    strcat(token, character);
}

// 回退字符
void retract() {
    character[0] = ' ';
    instr_index--;
    column--;
}

// 判断是否为字母，是返回 1，否则返回 0
int isLetter() {
    if (character[0] >= 'A' && character[0] <= 'Z' || character[0] >= 'a' && character[0] <= 'z')
        return 1;
    return 0;
}

// 判断是否为数字，是返回 1，否则返回 0
int isDigit() {
    if (character[0] >= '0' && character[0] <= '9')
        return 1;
    return 0;
}

// 读入一个字符
void getChar() {
    character[0] = instr[instr_index++];
    column++;
}

// 检查 character 中的字符是否为空白字符，若是，则调用 getchar 读入下一个字符，直到 character 中的字符是非空白字符为止
void getNBC() {
    int flag = 0;
    while (character[0] == ' ' || character[0] == '\n' || character[0] == '\t') {
        if (character[0] == '\n') {
            line++;
            column = 1;
        }
        getChar();
        flag = 1;
    }
    if (flag == 1)
        retract();
}

// 匹配保留字符，并返回下标
int reverse() {
    for (int i = 0; i < LEN; i++) {
        if (strcmp(Reverse[i], token) == 0)
            return i;
    }
    return -1;
}

// 处理标识符：对 token 中的字符串查标识符表，若查到，返回它在表中的位置下标，否则，把 token 添加到表尾并返回下标
int symbol() {
    for (int i = 0; i < symbol_len; i++) {
        if (strcmp(token, Symbol[i].value) == 0)
            return i;
    }
    strcpy(Symbol[symbol_len].value, token);
    Symbol[symbol_len].category = SYMBOL;
    Symbol[symbol_len].index = symbol_len;
    symbol_len++;
    return symbol_len - 1;
}

// 处理常数：对 token 中的字符串查常数表，若查到，返回它在表中的位置下标，否则，把 token 添加到表尾并返回下标
int constant() {
    for (int i = 0; i < digit_len; i++) {
        if (strcmp(token, Digit[i].value) == 0)
            return i;
    }
    strcpy(Digit[digit_len].value, token);
    Digit[digit_len].category = CONSTANT;
    Digit[digit_len].index = digit_len;
    digit_len++;
    return digit_len - 1;
}

// 打印错误位置信息
Binary error() {
    Binary error = {0, 0, "-"};
    totalError++;
    printf("An error was found in Line %d, Column %d\n", line, column);
    return error;
}

// 词法分析函数，逐个识别单词
Binary LexAnalyze() {
    memset(token, 0, LEN);
    character[0] = ' ';
    getNBC();
    getChar();
    int flag = 0;
    int table_index = 0;
    int num = 0;
    switch (character[0]) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
            while (isLetter() == 1 || isDigit() == 1 || character[0] == '_') {
                concat();
                getChar();
            }
            retract();
            num = reverse();
            if (num != -1) {
                Binary res = {RESERVE, num};
                strcpy(res.value, token);
                return res;
            }
            else {
                table_index = symbol();
                return Symbol[table_index];
            }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while (isDigit() == 1 || (character[0] == '.' && !flag)) {
                if (character[0] == '.')
                    flag = 1;
                concat();
                getChar();
            }
            // 若是科学计数法
            if (character[0] == 'E' || character[0] == 'e') {
                concat();
                getChar();
                flag = 0;
                if (character[0] == '+' || character[0] == '-') {
                    concat();
                    getChar();
                }
                while (isDigit() == 1 || (character[0] == '.' && !flag)) {
                    if (character[0] == '.')
                        flag = 1;
                    concat();
                    getChar();
                }
            }
            int legal_flag = 0;
            // 若是非法标识符或非法数字，报错
            while (isLetter() == 1 || isDigit() == 1 || character[0] == '_' || character[0] == '.') {
                concat();
                getChar();
                legal_flag = 1;
            }
            retract();
            if (legal_flag == 1)
                return error();
            table_index = constant();
            return Digit[table_index];
        case '<':
            getChar();
            if (character[0] == '=') {
                Binary res = {34, 0, "<="};
                return res;
            }
            else if (character[0] == '<') {
                getChar();
                if (character[0] == '=') {
                    Binary res = {45, 0, "<<="};
                    return res;
                }
                else {
                    retract();
                    Binary res = {31, 0, "<<"};
                    return res;
                }
            }
            else {
                retract();
                Binary res = {33, 0, "<"};
                return res;
            }
        case '>':
            getChar();
            if (character[0] == '=') {
                Binary res = {36, 0, ">="};
                return res;
            }
            else if (character[0] == '>') {
                getChar();
                if (character[0] == '=') {
                    Binary res = {46, 0, ">>="};
                    return res;
                }
                else {
                    retract();
                    Binary res = {32, 0, ">>"};
                    return res;
                }
            }
            else {
                retract();
                Binary res = {35, 0, ">"};
                return res;
            }
        case '=':
            getChar();
            if (character[0] == '=') {
                Binary res = {38, 0, "=="};
                return res;
            }
            else {
                retract();
                Binary res = {39, 0, "="};
                return res;
            }
        case '!':
            getChar();
            if (character[0] == '=') {
                Binary res = {37, 0, "!="};
                return res;
            }
            else {
                retract();
                Binary res = {22, 0, "!"};
                return res;
            }
        case '+':
            getChar();
            if (character[0] == '=') {
                Binary res = {40, 0, "+="};
                return res;
            }
            else if (character[0] == '+') {
                Binary res = {25, 0, "++"};
                return res;
            }
            else {
                retract();
                Binary res = {17, 0, "+"};
                return res;
            }
        case '-':
            getChar();
            if (character[0] == '=') {
                Binary res = {41, 0, "-="};
                return res;
            }
            else if (character[0] == '-') {
                Binary res = {26, 0, "--"};
                return res;
            }
            else if (character[0] == '>') {
                Binary res = {51, 0, "->"};
                return res;
            }
            else {
                retract();
                Binary res = {18, 0, "-"};
                return res;
            }
        case '*':
            getChar();
            if (character[0] == '=') {
                Binary res = {42, 0, "*="};
                return res;
            }
            else {
                retract();
                Binary res = {19, 0, "*"};
                return res;
            }
        case '/':
            getChar();
            if (character[0] == '=') {
                Binary res = {43, 0, "/="};
                return res;
            }
                // 跳过 "//" 注释
            else if (character[0] == '/') {
                while (character[0] != '\n') {
                    getChar();
                }
                retract();
                Binary res = {0, 0, "-"};
                return res;
            }
                // 跳过 "/**/" 注释
            else if (character[0] == '*') {
                while (instr_index <= total_len) {
                    getChar();
                    if (character[0] == '*') {
                        getChar();
                        if (character[0] == '/')
                            break;
                        else
                            retract();
                    }
                    else if (character[0] == '\n') {
                        line++;
                        column = 1;
                    }
                }
                if (character[0] == '\0')
                    return error();
                Binary res = {0, 0, "-"};
                return res;
            }
            else {
                retract();
                Binary res = {20, 0, "/"};
                return res;
            }

        case '%':
            getChar();
            if (character[0] == '=') {
                Binary res = {44, 0, "%="};
                return res;
            }
            else {
                retract();
                Binary res = {21, 0, "%"};
                return res;
            }
        case '&':
            getChar();
            if (character[0] == '=') {
                Binary res = {47, 0, "&="};
                return res;
            }
            else if (character[0] == '&') {
                Binary res = {23, 0, "&&"};
                return res;
            }
            else {
                retract();
                Binary res = {27, 0, "&"};
                return res;
            }
        case '|':
            getChar();
            if (character[0] == '=') {
                Binary res = {48, 0, "|="};
                return res;
            }
            else if (character[0] == '|') {
                Binary res = {24, 0, "||"};
                return res;
            }
            else {
                retract();
                Binary res = {28, 0, "|"};
                return res;
            }
        case '^':
            getChar();
            if (character[0] == '=') {
                Binary res = {49, 0, "^="};
                return res;
            }
            else {
                retract();
                Binary res = {29, 0, "^"};
                return res;
            }
        case '~':
            if (character[0] == '~') {
                Binary res = {30, 0, "~"};
                return res;
            }
        case '.':
            if (character[0] == '.') {
                Binary res = {50, 0, "."};
                return res;
            }
        case '?':
            if (character[0] == '?') {
                Binary res = {52, 0, "?"};
                return res;
            }
        case ':':
            if (character[0] == ':') {
                Binary res = {53, 0, ":"};
                return res;
            }
        case '(':
            if (character[0] == '(') {
                Binary res = {4, 0, "("};
                return res;
            }
        case ')':
            if (character[0] == ')') {
                Binary res = {5, 0, ")"};
                return res;
            }
        case '[':
            if (character[0] == '[') {
                Binary res = {6, 0, "["};
                return res;
            }
        case ']':
            if (character[0] == ']') {
                Binary res = {7, 0, "]"};
                return res;
            }
        case '{':
            if (character[0] == '{') {
                Binary res = {8, 0, "{"};
                return res;
            }
        case '}':
            if (character[0] == '}') {
                Binary res = {9, 0, "}"};
                return res;
            }
        case ',':
            if (character[0] == ',') {
                Binary res = {14, 0, ","};
                return res;
            }
        case ';':
            if (character[0] == ';') {
                Binary res = {15, 0, ";"};
                return res;
            }
        case '#':
            if (character[0] == '#') {
                Binary res = {16, 0, "#"};
                return res;
            }
        case '\"':
            concat();
            getChar();
            while (character[0] != '\"' && instr_index <= total_len) {
                if (character[0] == '\\') {
                    concat();
                    getChar();
                    if (character[0] == '\"' || character[0] == '\'' || character[0] == '\\') {
                        concat();
                        getChar();
                    }
                }
                else if (character[0] == '\n') {
                    line++;
                    column = 1;
                }
                else {
                    concat();
                    getChar();
                }
            }
            if (character[0] == '\0') {
                return error();
            }
            concat();
            num = reverse();
            if (num != -1) {
                Binary res = {RESERVE, num};
                strcpy(res.value, token);
                return res;
            }
            else {
                table_index = symbol();
                return Symbol[table_index];
            }
        case '\'':
            concat();
            getChar();
            while (character[0] != '\'' && instr_index < total_len) {
                if (character[0] == '\\') {
                    concat();
                    getChar();
                    if (character[0] == '\'' || character[0] == '\"' || character[0] == '\\') {
                        concat();
                        getChar();
                    }
                }
                else {
                    concat();
                    getChar();
                }
            }
            if (character[0] == '\n') {
                line++;
                column = 1;
                return error();
            }
            concat();
            num = reverse();
            if (num != -1) {
                Binary res = {RESERVE, num};
                strcpy(res.value, token);
                return res;
            }
            else {
                table_index = symbol();
                return Symbol[table_index];
            }
        case '\0':
            if (1) {
                Binary res = {0, 0, "EOF"};
                return res;
            }
        default:
            return error();
    }
}

// 打印所有词汇表
void show_table() {
    printf("\n==================Reserve==================\n");
    printf("Reverse\t\tCategory\tIndex\n");
    for (int i = 0; i < LEN; i++) {
        if (Reverse[i][0] != '\0') {
            if (strlen(Reverse[i]) >= 8)
                printf("%s\t%d\t\t%d\n", Reverse[i], RESERVE, i);
            else
                printf("%s\t\t%d\t\t%d\n", Reverse[i], RESERVE, i);
        }
    }
    printf("\n==================Boundary==================\n");
    printf("Boundary\tCategory\n");
    for (int i = 0; i < LEN; i++) {
        if (Boundary[i][0] != '\0')
            printf("%s\t\t%d\n", Boundary[i], i);
    }
    printf("\n==================Operator==================\n");
    printf("Operator\tCategory\n");
    for (int i = 0; i < LEN; i++) {
        if (Operator[i][0] != '\0')
            printf("%s\t\t%d\n", Operator[i], i);
    }
    printf("\n==================Symbol==================\n");
    printf("Symbol\t\tCategory\tIndex\n");
    for (int i = 0; i < symbol_len; i++) {
        if (strlen(Symbol[i].value) >= 8)
            printf("%s\t%d\t\t%d\n", Symbol[i].value, SYMBOL, Symbol[i].index);
        else
            printf("%s\t\t%d\t\t%d\n", Symbol[i].value, SYMBOL, Symbol[i].index);
    }
    printf("\n==================Constant==================\n");
    printf("Constant\tCategory\tIndex\n");
    for (int i = 0; i < digit_len; i++) {
        if (strlen(Digit[i].value) >= 8)
            printf("%s\t%d\t\t%d\n", Digit[i].value, CONSTANT, Digit[i].index);
        else
            printf("%s\t\t%d\t\t%d\n", Digit[i].value, CONSTANT, Digit[i].index);
    }
}

int main() {
    init_Reverse();
    init_Boundary();
    init_Operator();
    instr_index = 0;
    character[0] = ' ';
    memset(token, 0, LEN);
    memset(instr, 0, BUFFER_LEN);

    // 把文本文件读入到字符数组缓冲区中
    FILE *fp;
    if ((fp = fopen(INPUT, "r")) == NULL) {
        printf("Fail to open %s !\n", INPUT);
        exit(1);
    }
    char ch[2];
    ch[0] = fgetc(fp);
    while (ch[0] != EOF) {
        strcat(instr, ch);
        ch[0] = fgetc(fp);
    }
    total_len = strlen(instr);
    fclose(fp);

    Binary word = {0, 0, "-"};
    printf("\nTips : Category of Reserve is 1, Symbol is 2, Constant is 3\n");
    printf("\n------------------------Results------------------------\n");
    while (instr_index < total_len) {
        word = LexAnalyze();
        if (word.category != 0) {
            printf("word\t\t(%d, %s)\n", word.category, word.value);
        }
    }
    if (totalError >= 2) {
        printf("%d errors were found!\n", totalError);
    }
    else {
        printf("%d error was found!\n", totalError);
    }

    printf("\n------------------------Vocabulary------------------------\n");
    show_table();

//    system("pause");
    return 0;
}
