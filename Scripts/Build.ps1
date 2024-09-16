$VerbosePreference = 'SilentlyContinue'

Set-Location ..

#Remove-Item -Recurse -Force ./Build

#$CMAKE_ARGS = ""
#Get-Content "./Scripts/Common.txt" | ForEach-Object {
#    $CMAKE_ARGS += "$_ "
#}
#Write-Host "CMAKE_ARGS: $CMAKE_ARGS"

cmake -G "Ninja" -B Build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_BINARY_DIR=.


cmake --build Build

Set-Location Build/compiled


