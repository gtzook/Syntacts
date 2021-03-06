from syntacts import *
from time import sleep
import math
from math import cos
from math import pi

# This example is taken directly from the code listings in:
# Syntacts: Open-Source Software and Hardwarefor Audio-Controlled Haptics, Transactions on Haptics

## LISTING 1

# create an audio context
session = Session()

# enumerate connected hardware
for dev in session.available_devices:
    print(dev.index) # e.g., 6
    print(dev.name) # e.g., MOTU Pro Audio
    print(dev.max_channels) # e.g., 24
    print(dev.api_name) # e.g., ASIO

# open device 6 with 24 channels at 48 kHz
session.open(22, 24, 48000)
sleep(1)

## LISTING 2

sqr = Square(100) # 100 Hz square
sin = Sine(10) # 10 Hz triangle
asr = ASR(0.1,0.1,0.1) # attack, sustain, release
# basic examples mixing the Signals above
sig1 = sqr * sin
sig2 = sig1 * asr
sig3 = 0.5 * (sqr + sin) * asr
# play Signals on channel 0 and 1
session.play(0, sig1) # plays until stopped
session.play(1, sig2) # plays for 0.3 seconds
sleep(1)
session.stop(0) # stop sig1

## LISTING 3

sigA = Sine(100) * ASR(0.1,0.1,0.1) # 0.3 s
sigB = Sine(50) * ADSR(0.1,0.1,0.1,0.1) # 0.4 s
sig4 = sigA << sigB # 0.7 s
sig5 = 0.1 << sigA << 0.2 << sigB # 1.0 s
sig6 = sigA << -0.1 << sigB # 0.6 s
sig7 = sig4 << sig5 << sig6 # 2.3 s
session.play(2,sig7)

sleep(3)

## LISTING 4

spatial = Spatializer(session)     # 2D Spatializer
spatial.create_grid(4,6)           # 4 rows X 6 cols
spatial.set_position(18,(0.1,0.8)) # move channel 18
spatial.roll_off = 'linear'        # roll-off law
spatial.radius   = 0.3             # effect radius
spatial.target   = (0.2, 0.1)      # target location
spatial.play(sig1)                 # play inf Signal

# modification in a loop
t = 0
while (t < 10):
    x = 0.5 + 0.5 * math.cos(2*pi*t)
    y = 0.5 + 0.5 * math.sin(2*pi*t)
    spatial.target = (x, y)
    spatial.volume = 0.5 + 0.5 * math.sin(2*pi*t)
    spatial.pitch  = 1 + 0.5 * math.sin(2*pi*t)
    sleep(0.01)
    t = t + 0.01

spatial.stop()

del spatial