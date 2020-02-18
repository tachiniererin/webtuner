# WebTuner

![Fully Automated WebTuner logo](https://raw.githubusercontent.com/tachiniererin/webtuner/master/webtuner_logo.png "Fully Automated WebTuner")

Has this ever happened to you? Do you just have too many tabs to scroll through with your mouse?
Would you like to have a better option and fine-grained control about your scroll speed?

Look no further!

3D-print yourself a nice knob for your rotary encoder, upload the sketch to an Arduino and get scrolling.

Watch the WebTuner in action:   
[![Watch the WebTuner in action on YouTube!](https://img.youtube.com/vi/nNiJmV_KFPg/0.jpg)](https://www.youtube.com/watch?v=nNiJmV_KFPg) \
or on [diode.zone](https://diode.zone/videos/watch/89fa7e87-2f07-4148-9009-f70ae06c8d03)

## How to run

- Print the encoder knob and the ThinkPad holder
- Upload the Arduino sketch
- run the the installer `sh installer.sh` or install manually:
  - Adjust the path in pypoti.json to match where the repo is
  - `mkdir -p ~/.mozilla/native-messaging-hosts/`
  - `ln -s /path/to/repo/ext/pypoti.json ~/.mozilla/native-messaging-hosts/` or copy it
  - Load the extension in Firefox about:debugging -> Load temporary add-on
