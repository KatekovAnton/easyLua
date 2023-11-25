#include "windows_fileManager.h"
#include <string>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iosfwd>



#include <codecvt>
#include <windows.h>



// convert UTF-8 string to wstring
std::wstring utf8_to_wstring (const std::string& str)
{
    // Convert an ASCII string to a Unicode String
    std::wstring wstrTo;
    wchar_t *wszTo = new wchar_t[str.length() + 1];
    wszTo[str.size()] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());
    wstrTo = wszTo;
    delete[] wszTo;
    return wstrTo;
}

// convert wstring to UTF-8 string
std::string wstring_to_utf8 (const std::wstring& wstr)
{
	// Convert a Unicode string to an ASCII string
    std::string strTo;
    char *szTo = new char[wstr.length() + 1];
    szTo[wstr.size()] = '\0';
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
    strTo = szTo;
    delete[] szTo;
    return strTo;
}

BOOL FileExists(std::wstring szPath)
{
	DWORD dwAttrib = GetFileAttributesW(szPath.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

char* GetRawContent(const std::string &destination)
{
	FILE* file = fopen(destination.c_str(), "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		long filesize = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* memblock = new char[filesize + 1];
		memblock[filesize] = '\0';
		fread(memblock, sizeof(char), filesize, file);
		fclose(file);
		return memblock;
	}

	return NULL;
}


windowsFile::windowsFile(const std::string &filename)
	:IFile(filename)
{}

windowsFile::~windowsFile()
{}
    
std::string windowsFile::GetContentAsString()
{
	char *chars = GetRawContent(GetFileNameForFopen());
	if (!chars)
		return "";
	std::string result(chars);

	return chars;
	
}

std::string windowsFile::GetFileNameForFopen()
{
	windows_fileManager *manager = reinterpret_cast<windows_fileManager*>(FileManager::SharedManager());
	std::string destination = "." + _filename.substr(manager->appPath.length(), _filename.length() - manager->appPath.length());
	return destination;
}

std::string GetFileNameFromPath(std::string filename)
{
	// Remove directory if present.
	// Do this before extension removal incase directory has a period character.
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx) {
		filename.erase(0, last_slash_idx + 1);
	}

	return filename;
}
    
void windowsFile::SaveString(const std::string &content)
{
	SaveBuffer(content.c_str(), content.length());
}

void windowsFile::SaveBuffer(const char *buffer, unsigned long length)
{
	std::string destination = GetFileNameForFopen();
	FILE* file = fopen(destination.c_str(), "wb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		
		size_t num = length;
		fwrite(buffer, sizeof(char), length, file);
		fflush(file);
		fclose(file);

	}
}

windows_fileManager::windows_fileManager(void)
{
	const unsigned len = GetCurrentDirectory(0, 0);
	std::wstring str(len,'\0');
	GetCurrentDirectoryW(len, &str[0]);
	appPath = wstring_to_utf8(str);
	wAppPath = str;

	auto save = wAppPath.substr(0, wAppPath.length() - 1) + L"\\Save";
	CreateDirectoryW(save.c_str(), NULL);
}

windows_fileManager::~windows_fileManager(void)
{
}

bool windows_fileManager::IsFileExists(std::string path)
{
	FILE* file = fopen(path.c_str(), "rb");
	bool exists = file != NULL;
	if (file)
		fclose(file);
	return exists;
}

std::string windows_fileManager::GetContent(std::string filename)
{
	//string path = GetFilePath(filename);
	FILE* f = fopen(filename.c_str(), "r");

	// Determine file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f) + 1;

	char* where1 = new char[size];
	memset(where1, 0, size);
    rewind(f);
    fread(where1, sizeof(char), size - 1, f);
	where1[size - 1] = 0;
   
	std::string result = std::string(where1);
	delete[] where1;
    fclose(f);
    return result;
}


std::string windows_fileManager::GetFilePath(std::string filename)
{
	std::string filenameWin = filename;
	std::replace(filenameWin.begin(), filenameWin.end(), '/', '\\');
	std::string fullPath = ".\\Resources\\" + filenameWin;
	std::wstring fFullPath(fullPath.begin(), fullPath.end());
	
	if (FileExists(fFullPath))
	{
		return fullPath;
	}

	std::string filename1 = GetFileNameFromPath(filename);
	
	//wstring path (appPath.begin(), appPath.end());
	std::wstring path = L".\\";
	std::wstring fName (filename1.begin(), filename1.end());

	if (FileExists(L".\\" + fName)) {
		return ".\\" + filename1; // only shaders
	}
	return "";
}
    
std::shared_ptr<IFile>windows_fileManager:: LoadFile(std::string name)
{
	//string path (appPath.begin(), appPath.end() - 1);
	std::string fullName = "Save\\" + name;

	if (!IsFileExists(fullName)) {
		std::string filepath = GetFilePath(name);
		if (filepath.length() > 1)
		{
			return std::shared_ptr<IFile>(new windowsFile(appPath + filepath.substr(1, filepath.length() - 1)));
		}
		return nullptr;
	}
	
	return std::shared_ptr<IFile>(new windowsFile(appPath + "\\" + fullName));
}

std::shared_ptr<IFile> windows_fileManager::SaveFile(std::string name, const char *data, long dataLength, bool forceOverride, FileManagerStorageType storage)
{
	std::shared_ptr<IFile> saveFile = LoadFile(name);
	if (!saveFile) {
		std::string fullName = appPath + "\\Save\\" + name;
		saveFile = std::shared_ptr<IFile>(new windowsFile(fullName));
	}
	
	saveFile->SaveBuffer(data, dataLength);
    return saveFile;
}
