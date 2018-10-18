#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fputs("Usage: isProcessRunning.exe <pid>\n", stderr);
    return 1;
  }

  // Make sure that the first argument, the PID, is numeric.
  for (char *c = argv[1]; *c; ++c)
  {
    if (!isdigit(*c))
    {
      fputs("Usage: isProcessRunning.exe <pid>\n", stderr);
      return 1;
    }
  }

  DWORD pid = atoi(argv[1]);

  // If the specified process is the System Process (0x00000000),
  // OpenProcess will fail, but that process is running, of course.
  if (pid == 0)
  {
    puts("true");
    return 0;
  }

  HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
  if (proc == NULL)
  {
    // If the specified process is the Idle process or one of the CSRSS processes,
    // OpenProcess fails and the last error code is ERROR_ACCESS_DENIED, but those
    // process are running, of course, too.
    DWORD lastError = GetLastError();
    if (lastError == ERROR_ACCESS_DENIED)
    {
      puts("true");
      return 0;
    }
    // INVALID_PARAMETER in this case means that the process cannot be opened
    // because it is not running.
    else if (lastError == ERROR_INVALID_PARAMETER)
    {
      puts("false");
      return 0;
    }
    else
    {
      fprintf(stderr, "Unexpected error occured: OpenProcess: %d\n", lastError);
      return 1;
    }
  }

  // A process that has just exited may still be opened so we need to check the
  // exit code of the process.
  DWORD exitCode;
  BOOL success = GetExitCodeProcess(proc, &exitCode);
  if (!success)
  {
    fprintf(stderr, "Unexpected error occured: GetExitCodeProcess: %d\n", GetLastError());
    CloseHandle(proc);
    return 1;
  }

  // If the exit code of the process is STILL_ACTIVE, then it hasn't actually exited
  // yet. Otherwise, we can safely report that the process isn't running anymore.
  puts(exitCode == STILL_ACTIVE ? "true" : "false");
  CloseHandle(proc);
  return 0;
}
