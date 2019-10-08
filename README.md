<img src="https://raw.githubusercontent.com/mahilab/Syntacts/master/logo/logo_text.png" width="500">

## Building from Source

### Requirements

- [git](https://git-scm.com/)
- [CMake](https://cmake.org/)
- [MSVC Compiler](https://visualstudio.microsoft.com/vs/)

### Dependencies

- [portaudio](http://www.portaudio.com/)
- [Steinberg ASIO SDK](https://www.steinberg.net/en/company/developers.html)

### Building portaudio with ASIO support

1. Open PowerShell **as an administrator** in a directory of your choice and run the following commands:

```shell
> wget https://www.steinberg.net/asiosdk -outfile "asiosdk.zip"
> Expand-Archive -Path asiosdk.zip -DestinationPath ./
> git clone https://git.assembla.com/portaudio.git 
> cd portaudio
> mkdir build
> cd build
> cmake .. -A x64 -DPA_USE_ASIO=ON -DPA_DLL_LINK_WITH_STATIC_RUNTIME=OFF -DCMAKE_DEBUG_POSTFIX=-d
> cmake --build . --target install --config Release
> cmake --build . --target install --config Debug
```

2. This will build Release and Debug variants of `portaudio` with `ASIO` enabled and install them in `C:/Program Files/portaudio`.

### Building Syntacts

1. Open PowerShell **as an administrator** in a directory of your choice and run the following commands:

```shell
> git clone https://github.com/mahilab/Syntacts
> mkdir build
> cd build
> cmake .. -A x64
> cmake --build . --target install --config Release
> cmake --build . --target install --config Debug
```

2. This will build Release and Debug variants of `Syntacts` and install them in `C:/Program Files/Syntacts`.

### Building Syntacts GUI

1. Compile and install the [carnot](https://github.com/epezent/carnot) engine using its README instructions.
2. Recompile and install Syntacts. CMake will detect the presence of `carnot` and build the GUI automatically.
