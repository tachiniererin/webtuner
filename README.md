# webtuner

Has this ever happened to you? Do you just have too many tabs to scroll through with your mouse?
Would you like to have a better option and fine-grained control about your scroll speed?

Look no further!

3D-print yourself a nice knob for your rotary encoder, upload the sketch to an Arduino and get scrolling.

## How to run

- Print the encoder knob and the ThinkPad holder
- Upload the Arduino sketch
- Adjust the path in pypoti.json to the repo
- `mkdir -p ~/.mozilla/native-messaging-hosts/`
- `ln -s /path/to/repo/ext/pypoti.json ~/.mozilla/native-messaging-hosts/`
- Load the extension in Firefox about:debugging -> Load temporary add-on
