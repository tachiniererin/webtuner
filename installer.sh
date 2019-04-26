#!/bin/bash
sed -ibak "s?/path/to/repo?$PWD?" ext/pypoti.json
mkdir -p ~/.mozilla/native-messaging-hosts/
ln -s $PWD/ext/pypoti.json ~/.mozilla/native-messaging-hosts/
cd ext
zip -r -FS ../webtuner.zip *
cd ..
mv webtuner.zip webtuner.xpi
echo "Please install webtuner.xpi from Firefox"

