+ACM-include +ADw-iostream+AD4-
+ACM-include +ADw-fstream+AD4-
+ACM-include +ADw-vector+AD4-

using namespace std+ADs-

ifstream fin(+ACI-date.in+ACI-)+ADs-
ofstream fout(+ACI-date.out+ACI-)+ADs-

const int LINE+AF8-MAX +AD0- 256+ADs-

int no+AF8-cycles+ADs-
vector+ADw-pair+ADw-string, int+AD4- +AD4- cycles+ADs-

long long strength+ADs-
string UI+ADs-

void read+AF8-cycle+AF8-value(char line+AFsAXQ-, int+ACY- value) +AHs-

    int index +AD0- 5+ADs-
    int sign +AD0- 1+ADs-

    if (line+AFs-5+AF0- +AD0APQ- '-')
        sign +AD0- -1,
        index+-+-+ADs-

    while (index +ADw- strlen(line) +ACYAJg- isdigit(line+AFs-index+AF0-))
        value +AD0- value +ACo- 10 +- (line+AFs-index+AF0- - '0'),
        index+-+-+ADs-

    value +ACoAPQ- sign+ADs-
+AH0-

void read() +AHs-

    char line+AFs-LINE+AF8-MAX+AF0AOw-

    string instruction+ADs-
    int cycle+AF8-value+ADs-


    while (fin.eof() +AD0APQ- false) +AHs-

        instruction +AD0- +ACIAIgA7-
        cycle+AF8-value +AD0- 0+ADs-

        fin.getline(line, LINE+AF8-MAX)+ADs-

        instruction +-+AD0- line+AFs-0+AF0AOw-
        instruction +-+AD0- line+AFs-1+AF0AOw-
        instruction +-+AD0- line+AFs-2+AF0AOw-
        instruction +-+AD0- line+AFs-3+AF0AOw-

        read+AF8-cycle+AF8-value(line, cycle+AF8-value)+ADs-

        cycles.push+AF8-back(make+AF8-pair(instruction, cycle+AF8-value))+ADs-
    +AH0-

    no+AF8-cycles +AD0- (int)cycles.size()+ADs-
+AH0-

void solve() +AHs-

    long long X +AD0- 1+ADs-
    int cycle +AD0- 1+ADs-
    int pixel +AD0- 0+ADs- 

    for (size+AF8-t i +AD0- 0+ADs- i +ADw- cycles.size()+ADs- i+-+-) +AHs-

        for (int j +AD0- 0+ADs- j +ADwAPQ- (cycles+AFs-i+AF0-.first +AD0APQ- +ACI-addx+ACI-) ? 1 : 0+ADs- j+-+-) +AHs-

            if (cycle +AD0APQ- 20 +AHwAfA- cycle +AD0APQ- 60 +AHwAfA- cycle +AD0APQ- 100 +AHwAfA-
                cycle +AD0APQ- 140 +AHwAfA- cycle +AD0APQ- 180 +AHwAfA- cycle +AD0APQ- 220)
                strength +-+AD0- X +ACo- cycle+ADs-

            if (abs(pixel - X) +ADwAPQ- 1)w
                UI +-+AD0- +ACIAIwAiADs-
            else
                UI +-+AD0- +ACI-.+ACIAOw-

            pixel+-+-+ADs-
            cycle+-+-+ADs-

            if (pixel +AD0APQ- 40)
                UI +-+AD0- +ACIAXA-n+ACI-,
                pixel +AD0- 0+ADs-
        +AH0-

        X +-+AD0- cycles+AFs-i+AF0-.second+ADs-
    +AH0-
+AH0-

void display() +AHs-

    fout +ADwAPA- UI+ADs-
+AH0-

int main()
+AHs-
    read()+ADs-
    solve()+ADs-
    display()+ADs-

    fin.close()+ADs-
    fout.close()+ADs-

    return 0+ADs-
+AH0-
