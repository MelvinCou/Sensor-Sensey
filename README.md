# Sensor-Sensey

Original repository: https://github.com/MelvinCou/Sensor-Sensey  
Documentation: https://github.com/MelvinCou/Sensor-Sensey/wiki

## Getting started

Needed tool

- [PlatformIO](https://platformio.org)
- [Clang](https://clang.llvm.org/) (optionnal)
- protobuf and grpcio-tools (`pip install --upgrade protobuf grpcio-tools`)

```sh
# Run sensors project
cd sensors
platformio run --target upload --upload-port $PORT
# Run sensors project
cd gateway
platformio run --target upload --upload-port $PORT

# lint, format code (clang needed)
./scripts/format.sh
./scripts/lint.sh
```
