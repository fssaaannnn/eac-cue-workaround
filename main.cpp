#include <iostream>
#include <vector>

void printUsage() {
    std::cout << "Usage: eac-cue-workaround [cue-file] [clipboard-file]"
              << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{&argv[1], &argv[argc]};

    if (argc != 3) {
        printUsage();
        return 0;
    }

    return 0;
}
