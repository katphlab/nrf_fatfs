# nrf_fatfs
FATFS Library for NRF devices using elm-chan<br>
All credit goes to [ELM-chan](http://elm-chan.org/fsw/ff/00index_e.html)

## Setting up:
1. Change the pins in diskio.c<br>
2. sd_card.c is written by me, modify them according to your requirement.

## Problems:
1. For some reason my sd card is not detected by default. Workaround: initialize first time with a random miso pin, then use the actual miso pin. Works flawlessly after that.
2. Time taken to open and close file is huge, like 30ms or something, and without closing the file, nothing is written on it.

I am unable to resolve the issues on my own so any suggestions on improving the library are more than welcome.

Under DO-ANYTHING BUT CONTRIBUTE LICENSE
