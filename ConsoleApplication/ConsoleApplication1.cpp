#include <iostream>
#include <windows.h>
#include <iostream>

// parametrai
const long long STUDENT_ID = 2412927;
const double X_START = -(STUDENT_ID % 19);
const double X_END = (STUDENT_ID % 25);
const double DX = STUDENT_ID / 1000000000000.0;

// DLL funkciju tipai
typedef int (*SetUserTimeRestrictionType)(const char*, const char*);
typedef int (*CreateWorkFoldersType)();
typedef int (*DeleteWorkFoldersType)();
typedef int (*CreateWorkFilesType)();
typedef void (*StartTimerType)();
typedef void (*StopTimerType)();
typedef double (*GetElapsedSecondsType)();
typedef int (*ClearWorkFilesType)();
typedef long long (*CalculateTschirnhausenAndWriteType)(double, double, double, double);
typedef int (*MergeFilesForFType)(double);

int main()
{
    HMODULE hDll = LoadLibraryA("Dll1.dll");

    if (hDll == NULL)
    {
        std::cout << "Nepavyko uzkrauti DLL" << std::endl;
        return 1;
    }

    SetUserTimeRestrictionType SetUserTimeRestriction =
        (SetUserTimeRestrictionType)GetProcAddress(hDll, "SetUserTimeRestriction");
    if (SetUserTimeRestriction == NULL)
    {
        std::cout << "Nepavyko rasti SetUserTimeRestriction funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    CreateWorkFoldersType CreateWorkFolders =
        (CreateWorkFoldersType)GetProcAddress(hDll, "CreateWorkFolders");
    if (CreateWorkFolders == NULL)
    {
        std::cout << "Nepavyko rasti CreateWorkFolders funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    CreateWorkFilesType CreateWorkFiles =
        (CreateWorkFilesType)GetProcAddress(hDll, "CreateWorkFiles");
    if (CreateWorkFiles == NULL)
    {
        std::cout << "Nepavyko rasti CreateWorkFiles funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    DeleteWorkFoldersType DeleteWorkFolders =
        (DeleteWorkFoldersType)GetProcAddress(hDll, "DeleteWorkFolders");
    if (DeleteWorkFolders == NULL)
    {
        std::cout << "Nepavyko rasti DeleteWorkFolders funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    StartTimerType StartTimer = (StartTimerType)GetProcAddress(hDll, "StartTimer");
    StopTimerType StopTimer = (StopTimerType)GetProcAddress(hDll, "StopTimer");
    GetElapsedSecondsType GetElapsedSeconds = (GetElapsedSecondsType)GetProcAddress(hDll, "GetElapsedSeconds");
    if (!StartTimer || !StopTimer || !GetElapsedSeconds)
    {
        std::cout << "Nepavyko rasti laiko matavimo funkciju" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    ClearWorkFilesType ClearWorkFiles =
        (ClearWorkFilesType)GetProcAddress(hDll, "ClearWorkFiles");
    if (ClearWorkFiles == NULL)
    {
        std::cout << "Nepavyko rasti ClearWorkFiles funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    CalculateTschirnhausenAndWriteType CalculateTschirnhausenAndWrite =
        (CalculateTschirnhausenAndWriteType)GetProcAddress(hDll, "CalculateTschirnhausenAndWrite");
    if (CalculateTschirnhausenAndWrite == NULL)
    {
        std::cout << "Nepavyko rasti CalculateTschirnhausenAndWrite funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    MergeFilesForFType MergeFilesForF =
        (MergeFilesForFType)GetProcAddress(hDll, "MergeFilesForF");
    if (MergeFilesForF == NULL)
    {
        std::cout << "Nepavyko rasti MergeFilesForF funkcijos" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    int result1 = SetUserTimeRestriction("user01", "M-F,18:00-20:00");
    std::cout << "Laiko ribojimo rezultatas: " << result1 << std::endl;

    // VISAS programos veikimo laikas
    StartTimer();

    int result2 = CreateWorkFolders();
    std::cout << "Aplanku kurimo rezultatas: " << result2 << std::endl;

    int result3 = CreateWorkFiles();
    std::cout << "Failu kurimo rezultatas: " << result3 << std::endl;

    // uztikrina, kad failai butu visiskai isvalyti pries pirma F iteracija
    ClearWorkFiles();

    // ciklas skirtingoms F reiksmems (-2, -1, 0, 1, 2)
    double f_values[] = { -2.0, -1.0, 0.0, 1.0, 2.0 };

    for (int i = 0; i < 5; ++i)
    {
        double F = f_values[i];

        long long points = CalculateTschirnhausenAndWrite(
            F,
            X_START,
            X_END,
            DX
        );

        int merged = MergeFilesForF(F);

        std::cout << "--- Skaiciavimai F = " << F << " atlikti ---" << std::endl;
        std::cout << "   Tasku sugeneruota: " << points << std::endl;
        std::cout << "   Tasku po sujungimo: " << merged << std::endl;
    }

    int result4 = DeleteWorkFolders();
    std::cout << "Aplanku trynimo rezultatas: " << result4 << std::endl;

    // programa baigta
    StopTimer();
    double totalElapsed = GetElapsedSeconds();
    std::cout << "\n============================================\n";
    std::cout << "Bendras operaciju vykdymo laikas: " << totalElapsed << " s" << std::endl;
    std::cout << "============================================\n";

    FreeLibrary(hDll);
    return 0;
}
