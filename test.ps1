$ErrorActionPreference = 'Stop'

& .\isProcessRunning.exe 1 2
if ($LastExitCode -eq 0) {
  Write-Host "[ ] fails with multiple arguments"
  exit 1
}
if ($LastExitCode -eq 1) {
  Write-Host "[x] fails with multiple arguments"
}

& .\isProcessRunning.exe 'abc'
if ($LastExitCode -eq 0) {
  Write-Host "[ ] fails with non-numeric argument"
  exit 1
}
if ($LastExitCode -eq 1) {
  Write-Host "[x] fails with non-numeric argument"
}

$NonExistent = 9999999
$Res = .\isProcessRunning.exe $NonExistent
if ($Res -eq 'false') {
  Write-Host "[x] $NonExistent returns false"
}
if ($Res -eq 'true') {
  Write-Host "[ ] $NonExistent process returns false"
  exit 1
}

tasklist.exe /fo csv |
  ConvertFrom-Csv |
  Select-Object -SkipLast 10 |
  Select-Object -First 30 |
  ForEach-Object {

  $ProcessId = $_.PID
  $Res = .\isProcessRunning.exe $ProcessId
  if ($Res -eq 'false') {
    Write-Host "[ ] $ProcessId returns false"
    exit 1
  }
  if ($Res -eq 'true') {
    Write-Host "[x] $ProcessId returns true"
  }
}
