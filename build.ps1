# NOTE : g++.exe (MSYS2 mingw64) plante silencieusement (cc1plus.exe ne
# produit ni sortie ni exe, juste un exit code 1) quand il est lance
# directement depuis PowerShell/cmd. On delegue donc la compilation a
# Git Bash, qui l'invoque correctement.
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root

$bash = "C:\Program Files\Git\bin\bash.exe"
if (-not (Test-Path $bash)) { $bash = "C:\Program Files\Git\usr\bin\bash.exe" }
if (-not (Test-Path $bash)) { Write-Error "Git Bash introuvable (installe Git for Windows)." }

New-Item -ItemType Directory -Force -Path "$root\build" | Out-Null

$rootUnix = "/" + $root.Substring(0, 1).ToLower() + $root.Substring(2).Replace('\', '/')

$buildScript = @'
set -e
ROOT="$1"
GPP="/c/msys64/mingw64/bin/g++.exe"
"$GPP" -std=c++17 -g -Wall -Wextra "$ROOT/main.cpp" "$ROOT"/cpp/*.cpp \
    -I "/c/msys64/mingw64/include" -L "/c/msys64/mingw64/lib" \
    -lraylib -lopengl32 -lgdi32 -lwinmm \
    -o "$ROOT/build/uneviedefourmi.exe"
for dll in libraylib.dll glfw3.dll libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll; do
    cp "/c/msys64/mingw64/bin/$dll" "$ROOT/build/$dll"
done
'@

$scriptPath = Join-Path $env:TEMP "uneviedefourmi_build.sh"
Set-Content -Path $scriptPath -Value $buildScript -NoNewline -Encoding ASCII

$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $bash
$psi.Arguments = "`"$scriptPath`" `"$rootUnix`""
$psi.RedirectStandardOutput = $true
$psi.RedirectStandardError = $true
$psi.UseShellExecute = $false
$p = [System.Diagnostics.Process]::Start($psi)
$stdout = $p.StandardOutput.ReadToEnd()
$stderr = $p.StandardError.ReadToEnd()
$p.WaitForExit()

if ($stdout) { Write-Host $stdout }
if ($stderr) { Write-Host $stderr }

if ($p.ExitCode -ne 0) { exit $p.ExitCode }

Write-Host "Build OK -> build\uneviedefourmi.exe"
