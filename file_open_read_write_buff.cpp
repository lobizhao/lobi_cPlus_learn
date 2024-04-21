#include <fcntl.h> // about open something packate
#include <iostream>
#include <unistd.h> // for read



// this file 2024/04/20
// I review something about file open read write
// and little bit about buff
// just back up

using namespace std;

int main() {

    // create file descriptor
    int input_fd;
    int output_fd;

    string fileName = "hello.txt";
    string outFile = "output.txt";

    input_fd = open(fileName.c_str(), O_RDONLY);
    if(input_fd == -1){ //some error exist
        cerr << "Can not open this file ";
        return 1;
    }

    output_fd = open(outFile.c_str(), O_WRONLY | O_CREAT);
    if(output_fd == -1){
        cerr << outFile <<" can not open " << endl;
    }

    //create buffer
    const int BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];
    ssize_t inByte;
    ssize_t outByte;

    while ((inByte = read(input_fd, buffer, BUFF_SIZE))>0){
        cout << buffer << endl; // print what buff get

        outByte = write(output_fd, buffer, inByte);
        if(outByte != inByte){
            cerr << "different byte between read and write "<< endl;
            close(input_fd);
            close(output_fd);
            return -1;
        }
    }

    if(inByte == -1){
        cerr << "can not read file " << endl;
        return -1;
    }

    //ask user input something
    cout << "say something: " << endl;
    string typeChar;
    getline(cin, typeChar);

    outByte = write(output_fd, typeChar.c_str(), typeChar.size());
    if(outByte != static_cast<ssize_t>(typeChar.size())){
        close(input_fd);
        close(input_fd);
        return -1;
    }
    close(output_fd);

    int final_fd;
    final_fd = open(outFile.c_str(), O_RDONLY);

    if(final_fd == -1){
        close(output_fd);
        close(input_fd);
        return -1;
    }

    ssize_t getFinal;
    getFinal = read(final_fd, buffer, BUFF_SIZE);
    cout.write(buffer, getFinal);

    close(output_fd);
    close(input_fd);

    std::cout << "Good job" << std::endl;
    return 0;
}
