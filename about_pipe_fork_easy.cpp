#include <iostream>
#include <unistd.h> // package for fork
#include <fcntl.h>
#include <cstring>

using namespace std;

int main() {
    // I like this simple program
    // This program tell me that, what is pipe ~ and what is fork()
    // And how to transform information with pipe
    // ok let us begin

    //create a pipe
    int pipefd[2];
    char buffer;

    if (pipe(pipefd) == -1) {
        cerr << "Pipe cration failed" << endl;
        return -1;
    }

    //create child process
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed " << endl;
        return -1;
    } else if (pid > 0) {
        // this is parent working
        cout << " this is parent working now" << endl;
        // close pipe read, so parent just write
        close(pipefd[0]);
        cout << "parent first run this " << endl;
        write(pipefd[1], "a", 1);
        close(pipefd[1]);
        // what is wait means?
        wait(NULL);
    } else {
        //child process just read something from pipe
        close(pipefd[1]);
        read(pipefd[0], &buffer, 1);
        cout << "show what child read from parent: " << buffer << endl;
        cout << "child runs after parent" << endl;
        close(pipefd[0]);

    }

    return 0;
}
