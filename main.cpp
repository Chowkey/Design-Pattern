#include <iostream>
#include <string>

class CloudStorage {
public:
    virtual void uploadFile(const std::string& fileName) = 0;
    virtual void downloadFile(const std::string& fileName) = 0;
    virtual ~CloudStorage() = default;
};

class GoogleDriveAPI {
public:
    void uploadFile(const std::string& fileName) {
        std::cout << "Uploading " << fileName << " to Google Drive.\n";
    }

    void downloadFile(const std::string& fileName) {
        std::cout << "Downloading " << fileName << " from Google Drive.\n";
    }
};
class DropboxAPI {
public:
    void upload(const std::string& fileName) {
        std::cout << "Uploading " << fileName << " to Dropbox.\n";
    }

    void fetch(const std::string& fileName) {
        std::cout << "Fetching " << fileName << " from Dropbox.\n";
    }
};

class OneDriveAPI {
public:
    void uploadDocument(const std::string& fileName) {
        std::cout << "Uploading " << fileName << " to OneDrive.\n";
    }

    void getDocument(const std::string& fileName) {
        std::cout << "Getting " << fileName << " from OneDrive.\n";
    }
};

class GoogleDriveAdapter : public CloudStorage {
private:
    GoogleDriveAPI* googleDrive;
public:
    GoogleDriveAdapter() : googleDrive(new GoogleDriveAPI()) {}
    ~GoogleDriveAdapter() { delete googleDrive; }

    void uploadFile(const std::string& fileName) override {
        googleDrive->uploadFile(fileName);
    }

    void downloadFile(const std::string& fileName) override {
        googleDrive->downloadFile(fileName);
    }
};

class DropboxAdapter : public CloudStorage {
private:
    DropboxAPI* dropbox;
public:
    DropboxAdapter() : dropbox(new DropboxAPI()) {}
    ~DropboxAdapter() { delete dropbox; }

    void uploadFile(const std::string& fileName) override {
        dropbox->upload(fileName);
    }

    void downloadFile(const std::string& fileName) override {
        dropbox->fetch(fileName);
    }
};

class OneDriveAdapter : public CloudStorage {
private:
    OneDriveAPI* oneDrive;
public:
    OneDriveAdapter() : oneDrive(new OneDriveAPI()) {}
    ~OneDriveAdapter() { delete oneDrive; }

    void uploadFile(const std::string& fileName) override {
        oneDrive->uploadDocument(fileName);
    }

    void downloadFile(const std::string& fileName) override {
        oneDrive->getDocument(fileName);
    }
};

class FileManager {
private:
    CloudStorage* cloudStorage;
public:
    FileManager() : cloudStorage(nullptr) {}
    ~FileManager() { delete cloudStorage; }

    void setCloudStorage(CloudStorage* storage) {
        if (cloudStorage) delete cloudStorage;
        cloudStorage = storage;
    }

    void uploadFile(const std::string& fileName) {
        if (cloudStorage) {
            cloudStorage->uploadFile(fileName);
        } else {
            std::cout << "No cloud storage selected.\n";
        }
    }

    void downloadFile(const std::string& fileName) {
        if (cloudStorage) {
            cloudStorage->downloadFile(fileName);
        } else {
            std::cout << "No cloud storage selected.\n";
        }
    }
};

int main() {
    FileManager fileManager;

    fileManager.setCloudStorage(new GoogleDriveAdapter());
    fileManager.uploadFile("example1.txt");
    fileManager.downloadFile("example1.txt");

    fileManager.setCloudStorage(new DropboxAdapter());
    fileManager.uploadFile("example2.txt");
    fileManager.downloadFile("example2.txt");

    fileManager.setCloudStorage(new OneDriveAdapter());
    fileManager.uploadFile("example3.txt");
    fileManager.downloadFile("example3.txt");

    return 0;
}
