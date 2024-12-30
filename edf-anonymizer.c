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
                loadFile(fileManager);
                break;
            case VIEW_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                miniHexDump(fileManager->filename, HEADER_ROWS);
                break;
            case MODIFY_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("modify header unimplemented\n");
                break;
            case SAVE_VAL:
                if (fileManager->filename == NULL) {
                    printNoOpenFile();
                    break;
                }
                printf("write file unimplemented\n");
                break;
            default:
                printUnknownOption(selection);
                break;
        }
    }
}