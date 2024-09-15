@echo false

cd ..

if not exist Build mkdir Build
cd Build

cmake -G "Ninja" -B W64 @../Scripts/Common.txt

cd W64

ninja