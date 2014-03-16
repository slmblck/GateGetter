#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{

    FILE *faults;
    FILE *circuit;
    char fault[20];
    //char gate[20];
    bool printed = false;
    char gate_number[20];
    int i = 0;
    int j = 0;
    char *fault_line = NULL;
    size_t fault_linelen = 0;
    ssize_t fault_reallen = 0;
    char *gate_line = NULL;
    size_t gate_linelen = 0;
    ssize_t gate_reallen = 0;

    if( argc != 3 ) {
        printf("Invalid number of arguments. Try again.\n");
        exit(-1);
    }

    //open circuit file
    if ( ( circuit = fopen( argv[1], "r" )) == NULL )
    {
        puts( "Can't open circuit file. Try again.\n" );
        exit(1);
    }

    //open fault file
    if ( ( faults = fopen( argv[2], "r")) == NULL )
    {
        puts( "Can't open ufaults file. Try again. \n" );
        exit(2);
    }

    //Get ufault in order
    while((fault_reallen = getline(&fault_line, &fault_linelen, faults)) != -1){
        i = 0;
        printed = false;
        //Put the line number into an array
	memset(fault,'\0',sizeof(fault));
        while (fault_line[i] != ' ' && fault_line[i] != '-' && fault_line[i] != '\n'){
            fault[i] = fault_line[i];
            i++;
        }
	//cout << fault << endl;
        //Get gate from circuit
	rewind(circuit);
        while((gate_reallen = getline(&gate_line, &gate_linelen, circuit)) != -1){
            //Put the gate line number into an array
            j = 0;
	    memset(gate_number,'\0',sizeof(gate_number));
            while (gate_line[j] != ' ' && gate_line[j] != '-' && gate_line[j] != '\n'){
                gate_number[j] = gate_line[j];
                j++;
            }
	    //cout << gate_number << endl;
            //Compare to see if the fault line number and fault line number
            if(strcmp(fault, gate_number) == 0){
                //Print out the gate
                cout << "For fault: " << fault_line << " gate is: " << gate_line << endl;
                printed = true;
            }
            //Clear gate_line
            free(gate_line);
            gate_linelen = 0;
        }
        if(printed == false){
            cout << "No gate for: " << fault_line << endl;
        }
        free(fault_line);
        fault_linelen = 0;
    }




    return 0;
}

