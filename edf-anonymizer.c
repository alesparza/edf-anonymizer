#include "edf-anonymizer.h"
#include "file-manager.h"
#include "commandline.h"
#include "messages.h"

int main() {
    FileManager* fileManager = initialiseFileManager();
    printWelcome();

    // main loop: print options, process input, call handler
    while(1) {
        printMain(fileManager->filename);
        printPrompt();
        char* response = getInput();

        // process the response to be sure it is a number
        int selection = validateNumericInput(response);
        if (selection == 0) {
            printNotNumber(response);
            continue;
        }

        // handle the input
        switch (selection) {
            case EXIT_VAL:
                printf("Bye bye!\n");
                freeFileManager(fileManager);
                exit(0);
            case LOAD_VAL:
                printf("case 2: load file\n");
                loadFile(fileManager);
                break;
            case MODIFY_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("case 3: modify header\n");
                break;
            case SAVE_VAL:
                if (fileManager->filename == NULL) {
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