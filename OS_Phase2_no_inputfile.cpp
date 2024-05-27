#include <bits/stdc++.h>
using namespace std;

struct PCB
{
    int job_id;
    int TTL;
    int TLL;
    int TTC;
    int TLC;
};

struct PCB P;

int ptr;
int visited[30];
char M[300][4];
char IR[4];
char R[4];
int IC;
bool C;
int SI;
int VA;
int RA;
int PI;
int TI;
int EM;

unordered_map<int, string> errors = {{0, "No Error"},
        {1, "Out of Data"}, {2, "Line Limit Exceeded"},
        {3, "Time Limit Exceeded"},
        {4, "Operation Code Error"},
        {5, "Operand Error"}, {6, "Invalid Page Fault"}};

void init();
void LOAD();
void EXECUTE();
void MOS();
int ALLOCATE();
int ADDRESSMAP(int);
void TERMINATE(int);

void init()
{
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = ' ';
        }
    }

    for (int i = 0; i < 30; i++)
    {
        visited[i] = 0;
    }

    IR[4] = {'-'};
    R[4] = {'-'};
    IC = 0;
    C = false;
    ptr = 0;
    VA = 0;
    PI = 0;
    TI = 0;
    EM = 0;
}

int ALLOCATE()
{
    return (rand() % 30);
}

int ADDRESSMAP(int va)
{
    int pte = ptr * 10 + va / 10;

    string temp = "";

    if (M[pte][0] == '*')
    {
        cout << "Page Fault" << endl;
        return -1;
    }

    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (M[pte][i] != ' ')
                temp += M[pte][i];
        }

        return ((stoi(temp) * 10) + (va % 10));
    }
}

void TERMINATE(int Code)
{
    cout << "\n" << errors[Code] << endl;
    cout << "\nProgram Terminated abnormally" << "\t\t";
    cout << errors[Code] << endl;
}

void MOS()
{
    if (SI == 1)
    {
        string line;
        getline(cin, line);

        if (line[0] == '$' && line[1] == 'E' && line[2] == 'N' && line[3] == 'D')
        {
            EM = 1;
            TERMINATE(1);
            return;
        }

        int frame = ALLOCATE();

        while (visited[frame] != 0)
        {
            frame = ALLOCATE();
        }
        cout << "fr=" << frame << endl;
        visited[frame] = 1;

        int i = ptr;
        i = i * 10;
        cout << "\n\nPTR = " << ptr << endl;
        while (M[i][0] != '*')
        {
            i++;
        }

        int temp = frame / 10;

        M[i][0] = ' ';
        M[i][1] = ' ';
        M[i][2] = temp + 48;
        M[i][3] = frame % 10 + 48;

        int l = 0;
        frame = frame * 10;
        for (int i = 0; i < line.length() && line.length() < 40; i++)
        {
            M[frame][l++] = line[i];
            if (l == 4)
            {
                l = 0;
                frame += 1;
            }
        }
    }

    else if (SI == 2)
    {
        P.TLC += 1;
        if (P.TLC > P.TLL)
        {
            EM = 2;
            TERMINATE(2);
            return;
        }

        int add = IR[2] - 48;
        add = (add * 10);

        int ra = ADDRESSMAP(add);
        cout << "pdra=" << ra << endl;

        if (ra != -1)
        {
            string out;

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    out += M[ra][j];
                }
                ra += 1;
            }

            cout << out << "\n";
        }

        else
        {
            EM = 6;
            TERMINATE(6);
            PI = 3;
        }
    }

    else if (SI == 3)
    {
        cout << "\nProgram Terminated Successfully" << "\n";
        cout << "IC = " << IC << "\tToggle = " << C << "\tTLC = " << P.TLC << "\tTTC = " << P.TTC << "\tTTL = " << P.TTL << "\tTLL = " << P.TLL << "\tIR = ";

        for (int i = 0; i < 4; i++)
        {
            cout << IR[i];
        }

        cout << "\n\n";
    }
}

void EXECUTE()
{
    while (true)
    {
        if (PI != 0 || TI != 0 || EM != 0)
        {
            cout << "IC = " << IC << "\tToggle = " << C << "\tTLC = " << P.TLC << "\tTTC = " << P.TTC << "\tTTL = " << P.TTL << "\tTLL = " << P.TLL << "\tIR = ";

            for (int i = 0; i < 4; i++)
            {
                cout << IR[i];
            }
            cout << "\n\n";
            break;
        }

        RA = ADDRESSMAP(IC);

        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[RA][i];
        }
        IC++;

        if (M[RA][0] != 'H' && (!isdigit(M[RA][2]) || !isdigit(M[RA][3])))
        {
            EM = 5;
            TERMINATE(EM);
            cout << "IC = " << IC << "\tToggle = " << C << "\tTLC = " << P.TLC << "\tTTC = " << P.TTC << "\tTTL = " << P.TTL << "\tTLL = " << P.TLL << "\tIR = ";

            for (int i = 0; i < 4; i++)
            {
                cout << IR[i];
            }
            cout << "\n\n";
            break;
        }

        int add = IR[2] - 48;
        add = (add * 10) + (IR[3] - 48);

        if ((IR[0] == 'G' && IR[1] == 'D') || (IR[0] == 'S' && IR[1] == 'R'))
            P.TTC += 2;
        else
            P.TTC += 1;

        if (P.TTC > P.TTL)
        {
            EM = 3;
            TI = 2;
            if (IR[0] == 'P' && IR[1] == 'D' && (isdigit(M[RA][2]) && isdigit(M[RA][3])))
            {
                SI = 2;
                MOS();
            }
            if (IR[0] == 'H')
            {
                EM = 0;
                SI = 3;
                MOS();
                break;
            }
            TERMINATE(EM);
            cout << "IC = " << IC << "\tToggle = " << C << "\tTLC = " << P.TLC << "\tTTC = " << P.TTC << "\tTTL = " << P.TTL << "\tTLL = " << P.TLL << "\tIR = ";

            for (int i = 0; i < 4; i++)
            {
                cout << IR[i];
            }
            cout << "\n\n";
            break;
        }

        if (IR[0] == 'L' && IR[1] == 'R')
        {
            int ra = ADDRESSMAP(add);
            cout << "ra=" << ra << endl;
            if (ra == -1)
            {
                EM = 6;
                TERMINATE(6);
            }
            else
            {
                for (int i = 0; i < 4; i++)
                    R[i] = M[ra][i];
            }
        }

        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int ra = ADDRESSMAP(add);

            if (ra != -1)
            {
                for (int i = 0; i < 4; i++)
                    M[ra][i] = R[i];
            }

            else
            {
                int frame = ALLOCATE();
                while (visited[frame] != 0)
                {
                    frame = ALLOCATE();
                }

                visited[frame] = 1;

                int i = ptr;
                i = i * 10;
                while (M[i][0] != '*')
                {
                    i++;
                }

                int temp = frame / 10;

                M[i][0] = ' ';
                M[i][1] = ' ';
                M[i][2] = temp + 48;
                M[i][3] = frame % 10 + 48;

                frame = frame * 10;
                for (int i = 0; i < 4; i++)
                    M[frame][i] = R[i];
            }
        }

        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int flag = 0;

            int ra = ADDRESSMAP(add);
            cout << "RACR=" << ra << endl;

            if (ra == -1)
            {
                EM = 6;
                TERMINATE(6);
            }

            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (R[i] != M[ra][i])
                        flag = 1;
                }

                if (flag == 1)
                    C = false;
                else
                    C = true;
            }
        }

        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
                IC = add;
        }

        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }

        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }

        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();

            break;
        }

        else
        {
            EM = 4;
            TERMINATE(EM);
            cout << "IC = " << IC << "\tToggle = " << C << "\tTLC = " << P.TLC << "\tTTC = " << P.TTC << "\tTTL = " << P.TTL << "\tTLL = " << P.TLL << "\tIR = ";

            for (int i = 0; i < 4; i++)
            {
                cout << IR[i];
            }
            cout << "\n\n";
            break;
        }
    }
}

void LOAD()
{
    cout << "\nReading Data..." << endl;
    int m = 0;
    string line;
    while (getline(cin, line))
    {
        string str = "";
        for (int i = 0; i < 4; i++)
        {
            str += line[i];
        }

        if (str == "$AMJ")
        {
            init();
            ptr = ALLOCATE();
            cout << ptr << endl;
            for (int i = ptr * 10; i < ptr * 10 + 10; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[i][j] = '*';
                }
            }
            visited[ptr] = 1;

            // Initialize PCB

            string jobid_str = "";
            string TTL_str = "";
            string TLL_str = "";
            for (int i = 0; i < 4; i++)
            {
                jobid_str += line[i + 4];
                TTL_str += line[i + 8];
                TLL_str += line[i + 12];
            }
            P.job_id = stoi(jobid_str);
            P.TTL = stoi(TTL_str);
            P.TLL = stoi(TLL_str);
            P.TLC = 0;
            P.TTC = 0;
        }
        else if (str == "$DTA")
        {
            EXECUTE();
        }
        else if (str == "$END")
        {
            for (int i = 0; i < 300; i++)
            {
                cout << "M[" << i << "] - ";
                for (int j = 0; j < 4; j++)
                {
                    cout << M[i][j] << " ";
                }
                // cout << "\t\tM[" << i + 150 << "] - ";
                // for (int j = 0; j < 4; j++)
                // {
                //     cout << M[i + 150][j] << " ";
                // }

                cout << endl;
            }
            cout << "\n**************   END/HALT   **************\n\n" << endl;
        }
        else
        {
            int frameNo = ALLOCATE();
            cout << "f=" << frameNo << endl;
            while (visited[frameNo] != 0)
            {
                frameNo = ALLOCATE(); // 17
            }

            visited[frameNo] = 1;

            int i = ptr;
            while (M[i][0] != '*')
            {
                i++;
            }

            int temp = frameNo / 10; // 17/10 = 1

            M[i][0] = ' ';
            M[i][1] = ' ';
            M[i][2] = temp + 48;
            M[i][3] = frameNo % 10 + 48;

            int len = 0;
            for (int i = frameNo * 10; i < frameNo * 10 + 10 && len < line.length(); i++)
            {
                for (int j = 0; j < 4 && len < line.length(); j++)
                {
                    if (line[len] == 'H')
                    {
                        M[i][j] = line[len++];
                        break;
                    }

                    else
                    {
                        M[i][j] = line[len++];
                    }
                }
            }

            line.clear();
        }
    }
}

int main()
{
    LOAD();
    return 0;
  //Sample input in input section
  /*$AMJ000200160004
GD20LR20SR50LR21SR53LR22SR52LR23SR51PD50H
$DTA
$END0002
$AMJ001700200001
GD10GD20GD30GD40LR20CR30BT09PD40PD30H
$DTA
12
13
EQUAL
NOT
$END0017
$AMJ000100010001
GD10PD10H
$DTA
HELLO CLASS
$END0001
$AMJ000300100003
GD10GD20GD30PD30PD20PD10H
$DTA
6
7
8
$END0003
$AMJ001700100002
GC20GD30GD40GD50LR20CR30BT09PD50PD40H
$DTA
12
15
EQUAL
NOT
$END0017
$AMJ001800100002
GD2oLR22SR30LR23SR40LR20CR21BT10PD30HPD40H
$DTA
HELLWELLNOT SAME
$END0017
$AMJ000100200003
GD10LR52SR20LR53SR30LR50CR51BT09PD20PD10H
$DTA
A   b   NOT SAME
$END0001*/
}