#include <fcntl.h>
#include <iostream>
#include <unistd.h> //package for STDOUT/STDIN/STDERR


using namespace std;

int main() {
    int stdout_copy = dup(STDOUT_FILENO);
    if (stdout_copy == -1) {
        cerr << "failed copy stdout descriptor" << endl;
        close(stdout_copy);
        return EXIT_FAILURE;
    }

    int file_ed = open("output.txt", O_WRONLY | O_CREAT, 0666);
    if (file_ed < -1) {
        cerr << "failed crate a new file " << endl;
        close(file_ed);
        return EXIT_FAILURE;
    }

    if (dup2(file_ed, STDOUT_FILENO) < 0) {
        cerr << " failed copy files" << endl;
        close(file_ed);
        return EXIT_FAILURE;
    }

    cout << "now, all out print words will recall in the output.txt file" << endl;

    //ok, resotre STDOUT back
    if (dup2(stdout_copy, STDOUT_FILENO) < 0) {
        cerr << " failed restore stdout descriptor, you have to try again" << endl;
        close(stdout_copy);
        return EXIT_FAILURE;
    }

    cout << "now you restored, now you can print anything on screen" << endl;

    close(file_ed);
    close(stdout_copy);

    return 0;
}