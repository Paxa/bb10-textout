## TextOut app

My first app for blackberry 10 using cascades framework, it prints text to screen. (as simple as that)

I make it as `printf`-replacement for my experiments.

### Build and install

1. First make sure you have installed Momentics SDK
2. Then you need to have debug token installed
3. Open `deploy.yml` and put your info

Then run:

    rake build deploy

Done! If you see `result::success` - this app already installed to your device.

### Build without Rake

    cd build
    cmake -DCMAKE_TOOLCHAIN_FILE="./cmake/Toolchain-QNX-8.0.0.cmake" .
    make


*note: all development tested only in OS X 10.9*