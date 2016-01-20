### osmium-meets-coroutines

Pairing libosmium's visitor and coroutines; concept.


## Building

Grab latest libosmium:

    ./getDeps.sh

Compile and link it:

    mkdir build
    pushd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

## Usage

See it in action:

    ./core in.osm.pbf


## License

Copyright © 2016 Daniel J. Hofmann

Distributed under the MIT License (MIT).
