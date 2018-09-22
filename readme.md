# Advanced Metronome

Advanced Metronome is a small application in which you can set multiple measures with their own speed, time-signature and number of repeats.
This gives you the ability to practice songs that have multiple speeds and/or time-signatures.

## Screenshots

![Advanced Metronome mainwindow](data/screenshots/mainwindow.png)

## What can I do with it?

Advanced Metronome is created for musicians who want to practice songs which have multiple
speeds and/or time-durations. 'Cause regular metronomes only allow one constant tempo Advanced Metronome
steps in to solve this problem.

Advanced Metronome also gives you the ability to save and share your songs with others so this application will
suit many bands in their song-writing process.

## Required packages

### Building

- qt5-devel
- qt5-qtbase-devel
- qt5-qtmultimedia-devel

### Installing

- qt5
- qt5-multimedia

## How to build

### Linux

```
$ qmake
$ make install
```

And then run `advancedmetronome`

### Windows

This method assumes you're using the Microsoft build tools.

```
> qmake
> nmake release
```

To be able to run Advanced Metronome you need to copy all the
necessary Qt `.dll` files to the same location as `advancedmetronome.exe`
so the binary can find the required libraries.

## Packaging

### RPM package

```
$ cd data/packaging/RPM
$ spectool -g advancedmetronome.spec
$ fedpkg --release f28 local
```

This will create a RPM file which you can install using your package manager.

### Flatpak bundle

```
$ cd data/packaging/flatpak
$ flatpak-builder --repo=advancedmetronome_repo advancedmetronome net.bartkessels.advancedmetronome.json
$ flatpak build-bundle advancedmetronome_repo advancedmetronome.flatpak net.bartkessels.advancedmetronome
```

This will create a flatpak bundle called `advancedmetronome.flatpak`. To install the flatpak bundle
just run the command

```
$ flatpak install advancedmetronome.flatpak
```

Once installed you can run it from flatpak like this

```
$ flatpak run net.bartkessels.advancedmetronome
```

## Pre-build binaries

### RPM from COPR

If you're running Fedora you can easily install Advanced Metronome from [COPR](https://copr.fedorainfracloud.org/coprs/bartkessels/advancedmetronome/).

```
$ dnf copr enable bartkessels/advancedmetronome
$ dnf install advancedmetronome
```
