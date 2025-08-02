param (
    [string]$Arg
)

if (-not $Arg) {
    Write-Host "Usage: .\run.ps1 <project_folder|clean_all>"
    exit 1
}

if ($Arg -eq "clean_all") {
    # clean all projects
    $projects = Get-ChildItem -Directory
    foreach ($proj in $projects) {
        Write-Host "Cleaning $($proj.Name)..."
        Push-Location $proj.FullName
        if (Test-Path Makefile) {
            & make clean
        }
        Pop-Location
    }
    exit 0
}

if (-not (Test-Path $Arg -PathType Container)) {
    Write-Host "Error: Folder '$Arg' not found."
    exit 1
}

Set-Location $Arg

gcc -Wall -Wextra -o main *.c

if ($LASTEXITCODE -eq 0) {
    Write-Host "Running ${Arg}:"
    ./main.exe
} else {
    Write-Host "Compilation failed."
}
