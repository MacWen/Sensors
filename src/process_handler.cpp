#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <string>
#include <algorithm>

class process
{
public:

    static PROCESS_INFORMATION launchProcess(std::string app, std::string arg)
    {

        // Prepare handles.
        STARTUPINFO si;
        PROCESS_INFORMATION pi; // The function returns this
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        //Prepare CreateProcess args
        std::string app_w(app.length(), ' '); // Make room for characters
        std::copy(app.begin(), app.end(), app_w.begin()); // Copy string to wstring.

        std::string arg_w(arg.length(), ' '); // Make room for characters
        std::copy(arg.begin(), arg.end(), arg_w.begin()); // Copy string to wstring.

        std::string input = app_w + " " + arg_w;
        char* arg_concat = const_cast<char*>( input.c_str() );
        const char* app_const = const_cast<char*>( app_w.c_str());

        // Start the child process.
        if( !CreateProcessA(
            app_const,      // app path
            arg_concat,     // Command line (needs to include app path as first argument. args seperated by whitepace)
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory
            &si,            // Pointer to STARTUPINFO structure
            &pi )           // Pointer to PROCESS_INFORMATION structure
        )
        {
            printf( "CreateProcess failed (%d).\n", GetLastError() );
            throw std::exception("Could not create child process");
        }
        else
        {
            std::cout << "[          ] Successfully launched child process" << std::endl;
        }

        // Return process handle
        return pi;
    }

    static bool checkIfProcessIsActive(PROCESS_INFORMATION pi)
    {
        // Check if handle is closed
            if ( pi.hProcess == NULL )
            {
                printf( "Process handle is closed or invalid (%d).\n", GetLastError());
                return FALSE;
            }

        // If handle open, check if process is active
        DWORD lpExitCode = 0;
        if( GetExitCodeProcess(pi.hProcess, &lpExitCode) == 0)
        {
            printf( "Cannot return exit code (%d).\n", GetLastError() );
            throw std::exception("Cannot return exit code");
        }
        else
        {
            if (lpExitCode == STILL_ACTIVE)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }

    static bool stopProcess( PROCESS_INFORMATION &pi)
    {
        // Check if handle is invalid or has allready been closed
            if ( pi.hProcess == NULL )
            {
                printf( "Process handle invalid. Possibly allready been closed (%d).\n", GetLastError());
                return 0;
            }

        // Terminate Process
            if( !TerminateProcess(pi.hProcess,1))
            {
                printf( "ExitProcess failed (%d).\n", GetLastError() );
                return 0;
            }

        // Wait until child process exits.
            if( WaitForSingleObject( pi.hProcess, INFINITE ) == WAIT_FAILED)
            {
                printf( "Wait for exit process failed(%d).\n", GetLastError() );
                return 0;
            }

        // Close process and thread handles.
            if( !CloseHandle( pi.hProcess ))
            {
                printf( "Cannot close process handle(%d).\n", GetLastError() );
                return 0;
            }
            else
            {
                pi.hProcess = NULL;
            }

            if( !CloseHandle( pi.hThread ))
            {
                printf( "Cannot close thread handle (%d).\n", GetLastError() );
                return 0;
            }
            else
            {
                 pi.hProcess = NULL;
            }
            return 1;
    }
};//class process
#endif //win32