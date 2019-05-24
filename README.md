# LilleFP #15 - Build native mobile apps with reason-react-native

## Setup

### Using Homebrew

```
$ ~ > brew install node yarn watchman
$ ~ > yarn global add reason-cli@latest-macos react-native-cli
```

## Crawling and serving data

```
$ ~/Code/lillefp15-demo/server > yarn
$ ~/Code/lillefp15-demo/server > yarn crawl
$ ~/Code/lillefp15-demo/server > yarn serve
```

## Starting mobile app

```
$ ~/Code/lillefp15-demo/mobile > yarn
$ ~/Code/lillefp15-demo/mobile > yarn bs:start
$ ~/Code/lillefp15-demo/mobile > yarn rn:start
```

Then launch the app in the iOS / android simulator.

_⚠️ Don't forget to update the url contained in the `Pools.re` file with your computer IP instead of localhost if your choose to run the app on your device instead._
