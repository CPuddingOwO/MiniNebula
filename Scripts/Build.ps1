$VerbosePreference = 'SilentlyContinue'

Set-Location ..

$CMAKE_ARGS = ""

Get-Content "./Scripts/Common.txt" | ForEach-Object {
    $CMAKE_ARGS += " $_"
}

cmake -G "Ninja" -B Build $CMAKE_ARGS

cmake --build Build

Set-Location Build

if (-Not (Test-Path -Path "compiled")) {
    New-Item -ItemType Directory -Path "compiled"
}


