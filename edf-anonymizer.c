#include "edf-anonymizer.h"
#include "commandline.h"
#include "messages.h"

int main() {
    char* filename = NULL;
    FILE* file = NULL;
    printWelcome();

    // main loop: print options, process input, call handler
    while(1) {
        printMain(filename);
        printPrompt();
        char* response = getInput();

        // process the response to be sure it is a number
        char** check = &response;
        int selection = strtol(response, check, 10);
        if (*response != '\0' && **check == '\0') {
            printNotNumber(response);
            continue;
        }
        if (selection == 0 && check == &response) {
            printNotNumber(response);
            continue;
        }

        // handle the input
        switch (selection) {
            case EXIT_VAL:
                printf("Bye bye!");
                exit(0);
            case LOAD_VAL:
                printf("case 2: load file\n");
                break;
            case MODIFY_VAL:
                if (filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("case 3: modify header\n");
                break;
            case SAVE_VAL:
                if (filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("case 4: write file\n");
                break;
            default:
                printUnknownOption(selection);
                break;
        }
    }
}