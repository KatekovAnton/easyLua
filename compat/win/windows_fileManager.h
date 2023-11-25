#pragma once
#include "FileManger.h"

std::wstring utf8_to_wstring(const std::string& str);

class windowsFile : public IFile {
	std::string GetFileNameForFopen();
public:
    
    windowsFile(const std::string &filename);
    ~windowsFile();
    
    virtual std::string GetContentAsString();
    
    virtual void SaveString(const std::string &content);
    virtual void SaveBuffer(const char *buffer, unsigned long length);
    
};

class windows_fileManager :
	public FileManager
{
	friend class  windowsFile;

	std::string appPath;
	std::wstring wAppPath;
	std::wstring GetFilePathFromDir(std::wstring filename, std::wstring dir);
	
public:
	windows_fileManager(void);
	~windows_fileManager(void);
	
	bool IsFileExists(std::string path);
    
    virtual std::shared_ptr<IFile> LoadFile(std::string name);
    virtual std::shared_ptr<IFile> SaveFile(std::string name, const char *data, long dataLength, bool forceOverride, FileManagerStorageType storage);

	virtual std::string GetFilePath(std::string filename);
	virtual std::string GetContent(std::string filename);

};

