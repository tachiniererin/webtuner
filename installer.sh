#!/bin/bash
sed -ibak "s?/path/to/repo?$PWD?" ext/pypoti.json
mkdir -p ~/.mozilla/native-messaging-hosts/
ln -sf $PWD/ext/pypoti.json ~/.mozilla/native-messaging-hosts/
rm -f webtuner.xpi
cd ext
zip -r -FS ../webtuner.zip *
cd ..
mv webtuner.zip webtuner.xpi
echo "Please install webtuner.xpi from Firefox; go to Settings -> Extensions."
echo "You must enable debug mode, as the xpi file is not signed."

