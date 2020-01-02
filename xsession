#!/bin/bash

export PATH=~/bin/:$PATH
export TERMINAL=termite

xset -dpms
xset s off
xset -b

[[ -f ~/.Xmodmap ]] && xmodmap ~/.Xmodmap

# capslock is additional escape
setxkbmap -option "caps:escape"

# sticky shift and ctrl
#xkbset sticky -twokey -latchlock

# compose key 
# exec --no-startup-id setxkbmap -option "setxkbmap -option compose:ralt"

## Enable zapping (C-A-<Bksp> kills X)
setxkbmap -option "terminate:ctrl_alt_bksp"

# disable touchpad
xinput -disable "Synaptics TM3075-002"

# make trackpoint more responsive
echo -n 220 > /sys/devices/platform/i8042/serio1/serio2/speed
echo -n 200 > /sys/devices/platform/i8042/serio1/serio2/sensitivity 
xinput set-prop "TPPS/2 IBM TrackPoint" "libinput Accel Speed" 0.85

# Fix BUG: Use XToolkit in java applications
export AWT_TOOLKIT=XToolkit

# Enable core dumps in case something goes wrong
ulimit -c unlimited

firefox &
thunderbird &
termite &
firefox --new-window http://mail.google.com --class="gmail" &
firefox --new-window http://chat.google.com --class="chat" &

$HOME/bin/dwm-status

while true; do
    xkbset sticky -twokey -latchlock
    $HOME/bin/dwm > .xsession-dwm.log
done
