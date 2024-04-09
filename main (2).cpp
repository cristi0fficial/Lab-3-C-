#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Base class for file information
class FileInfo {
protected:
    string filename;
    string extension;
    time_t createdTime;
    time_t updatedTime;

public:
    FileInfo(const string& name, const string& ext, time_t created, time_t updated)
        : filename(name), extension(ext), createdTime(created), updatedTime(updated) {}

    virtual void printInfo() const {
        cout << "Filename: " << filename << endl;
        cout << "Extension: " << extension << endl;
        cout << "Created: " << ctime(&createdTime);
        cout << "Updated: " << ctime(&updatedTime);
    }

    virtual void printSpecificInfo() const = 0; // Virtual function for specific file types

    // Check if the file has been changed since the snapshot time
    bool isChangedSince(time_t snapshotTime) const {
        return updatedTime > snapshotTime;
    }
};

// Text file class
class TextFile : public FileInfo {
public:
    TextFile(const string& name, const string& ext, time_t created, time_t updated)
        : FileInfo(name, ext, created, updated) {}

    void printSpecificInfo() const override {}
};

// Image file class
class ImageFile : public FileInfo {
public:
    ImageFile(const string& name, const string& ext, time_t created, time_t updated)
        : FileInfo(name, ext, created, updated) {}

    void printSpecificInfo() const override {}
};

// Program file class
class ProgramFile : public FileInfo {
public:
    ProgramFile(const string& name, const string& ext, time_t created, time_t updated)
        : FileInfo(name, ext, created, updated) {}

    void printSpecificInfo() const override {}
};

// File Change Detector class
class FileChangeDetector {
private:
    string folderPath;
    time_t snapshotTime;

public:
    FileChangeDetector(const string& path) : folderPath(path), snapshotTime(0) {}

    // Update snapshot time
    void commit() {
        snapshotTime = time(nullptr);
        cout << "Snapshot time updated to: " << ctime(&snapshotTime);
    }

    // Print general information about the file
    void info(const string& filename) {
        // Dummy implementation for demonstration
        cout << "Printing information for file: " << filename << endl;
    }

    // Check file change status since snapshot time
    void status() {
        // Dummy implementation for demonstration
        cout << "Checking file change status since snapshot time..." << endl;
    }
};

int main() {
    FileChangeDetector detector("C:/Users/Cristi/OneDrive/Desktop"); // Specify your folder path here

    // Sample usage
    detector.commit(); // Initial snapshot
    detector.status(); // Check status after initial snapshot

    // Sample loop for interactive command line
    bool running = true;
    while (running) {
        string command;
        cout << "Enter command (commit, info <filename>, status, quit): ";
        getline(cin, command);

        if (command == "commit") {
            detector.commit();
        }
        else if (command.substr(0, 4) == "info") {
            string filename = command.substr(5);
            detector.info(filename);
        }
        else if (command == "status") {
            detector.status();
        }
        else if (command == "quit") {
            running = false;
        }
        else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
