# Project Description
Build a client demo with freeopcua sdk.

# Build x86 Demo
```bash
cd demo
mkdir build
cd build
cmake ..
make -j8
```

# Build arm Demo
```bash
cd demo
mkdir build
cd build
cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
