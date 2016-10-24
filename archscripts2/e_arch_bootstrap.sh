#!/bin/bash
# -*- coding: utf-8 -*-
# Take an arch install from zero to ready for Enlightenment

sudo pacman --noconfirm -S git screen sudo
sudo pacman --noconfirm -S check libjpeg-turbo fribidi libx11 libxext valgrind libxrender libgles giflib libtiff libraw librsvg poppler

sudo pacman --noconfirm -S libpulse libxcursor libxcomposite libxinerama libxp libxrandr libxss lua
sudo pacman --noconfirm -S gstreamer gst-plugins-base gst-plugins-good bullet luajit

sudo pacman --noconfirm -S xcb-util-keysyms xorg-sessreg vlc

sudo pacman --noconfirm -S base-devel gdb cmake

