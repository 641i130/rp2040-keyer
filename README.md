# rp2040-ctf
Embedded hardware CTF challenge daemoncon 2024

Began building this in November 2023.

Very unsure how it'll turn out! Let me know what you think on [matrix](https://matrix.to/#/@caret:m.sif.moe)!

---

## Development Setup
(This was primarily taken from [Drewol/rp2040-gamecon](https://github.com/Drewol/rp2040-gamecon), so feel free to check that source out!)

### Build instructions
Insturctions based on Ubuntu 20.04.1 LTS tested under WSL2

1. Install CMake (at least version 3.13), and GCC cross compiler
```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
```

2. Download the pico-sdk and set the `PICO_SDK_PATH` environment variable. Also set the variable in your `.bashrc` for future use.
```
git clone https://github.com/raspberrypi/pico-sdk
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=$PWD
cd ..
```

3. Clone and build this repository
```
git clone https://github.com/641i130/rp2040-ctf
cd rp2040-ctf
mkdir build
cd build
cmake ..
make
```

4. Upload the `ctf.uf2` that was created in your build directory.


---
If you're using linux and you want to mount the pico easily, try these commands out:
`sudo mkdir /mnt/pico`
`sudo mount (sudo fdisk -l | grep 'W95 FAT16' | awk '{print $1}') /mnt/pico`
`sudo cp ctf.uf2 /mnt/pico`
---

Then you can serial into the device. 

