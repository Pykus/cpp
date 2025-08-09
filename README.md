# cpp

✅ Jak używać (z VS Code lub ręcznie)
📦 1. Zbuduj projekt z mini-frameworkiem (domyślnie):

cmake -S . -B build
cmake --build build
./build/test_mini.exe
🧪 2. Zbuduj projekt z GoogleTest:

cmake -S . -B build -DUSE_GTEST=ON
cmake --build build
./build/test_gtest.exe
