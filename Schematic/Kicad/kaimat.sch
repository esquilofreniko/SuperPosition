EESchema Schematic File Version 4
LIBS:kaimat-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_DIP_x02 SW4
U 1 1 5C49054F
P 10650 6350
F 0 "SW4" H 10650 6717 50  0000 C CNN
F 1 "SW_DIP_x02" H 10650 6626 50  0000 C CNN
F 2 "" H 10650 6350 50  0001 C CNN
F 3 "" H 10650 6350 50  0001 C CNN
	1    10650 6350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x02 SW3
U 1 1 5C49060B
P 10650 5800
F 0 "SW3" H 10650 6167 50  0000 C CNN
F 1 "SW_DIP_x02" H 10650 6076 50  0000 C CNN
F 2 "" H 10650 5800 50  0001 C CNN
F 3 "" H 10650 5800 50  0001 C CNN
	1    10650 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW2
U 1 1 5C5B4CB3
P 9200 6250
F 0 "SW2" H 9200 6617 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9200 6526 50  0000 C CNN
F 2 "" H 9050 6410 50  0001 C CNN
F 3 "~" H 9200 6510 50  0001 C CNN
	1    9200 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5C5B60FE
P 9200 5550
F 0 "SW1" H 9200 5917 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9200 5826 50  0000 C CNN
F 2 "" H 9050 5710 50  0001 C CNN
F 3 "~" H 9200 5810 50  0001 C CNN
	1    9200 5550
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground J1
U 1 1 5C5C6F4A
P 7350 2000
F 0 "J1" H 7380 2325 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7380 2234 50  0000 C CNN
F 2 "" H 7350 2000 50  0001 C CNN
F 3 "~" H 7350 2000 50  0001 C CNN
	1    7350 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C5C70ED
P 7700 2200
F 0 "R2" H 7770 2246 50  0000 L CNN
F 1 "R" H 7770 2155 50  0000 L CNN
F 2 "" V 7630 2200 50  0001 C CNN
F 3 "~" H 7700 2200 50  0001 C CNN
	1    7700 2200
	0    -1   1    0   
$EndComp
Text Notes 7600 2250 0    50   ~ 0
330
$Comp
L Device:R R1
U 1 1 5C5C72C2
P 7700 1900
F 0 "R1" H 7770 1946 50  0000 L CNN
F 1 "R" H 7770 1855 50  0000 L CNN
F 2 "" V 7630 1900 50  0001 C CNN
F 3 "~" H 7700 1900 50  0001 C CNN
	1    7700 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 2200 7550 2200
Text Notes 7600 1950 0    50   ~ 0
1000
Wire Wire Line
	7850 1900 8050 1900
Wire Wire Line
	7850 2200 8050 2200
Wire Wire Line
	8050 2200 8050 1900
Wire Wire Line
	8050 1900 8250 1900
Connection ~ 8050 1900
$Comp
L Connector:AudioJack2_Ground J2
U 1 1 5C5D9E79
P 7350 2800
F 0 "J2" H 7380 3125 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7380 3034 50  0000 C CNN
F 2 "" H 7350 2800 50  0001 C CNN
F 3 "~" H 7350 2800 50  0001 C CNN
	1    7350 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C5D9E80
P 7700 3000
F 0 "R4" H 7770 3046 50  0000 L CNN
F 1 "R" H 7770 2955 50  0000 L CNN
F 2 "" V 7630 3000 50  0001 C CNN
F 3 "~" H 7700 3000 50  0001 C CNN
	1    7700 3000
	0    -1   1    0   
$EndComp
Text Notes 7600 3050 0    50   ~ 0
330
$Comp
L Device:R R3
U 1 1 5C5D9E88
P 7700 2700
F 0 "R3" H 7770 2746 50  0000 L CNN
F 1 "R" H 7770 2655 50  0000 L CNN
F 2 "" V 7630 2700 50  0001 C CNN
F 3 "~" H 7700 2700 50  0001 C CNN
	1    7700 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3000 7550 3000
Text Notes 7600 2750 0    50   ~ 0
1000
Wire Wire Line
	7850 2700 8050 2700
Wire Wire Line
	7850 3000 8050 3000
Wire Wire Line
	8050 3000 8050 2700
Wire Wire Line
	8050 2700 8250 2700
Connection ~ 8050 2700
$Comp
L Connector:AudioJack2_Ground J3
U 1 1 5C636B85
P 7350 3600
F 0 "J3" H 7380 3925 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7380 3834 50  0000 C CNN
F 2 "" H 7350 3600 50  0001 C CNN
F 3 "~" H 7350 3600 50  0001 C CNN
	1    7350 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C636B8C
P 7700 3800
F 0 "R6" H 7770 3846 50  0000 L CNN
F 1 "R" H 7770 3755 50  0000 L CNN
F 2 "" V 7630 3800 50  0001 C CNN
F 3 "~" H 7700 3800 50  0001 C CNN
	1    7700 3800
	0    -1   1    0   
$EndComp
Text Notes 7600 3850 0    50   ~ 0
330
$Comp
L Device:R R5
U 1 1 5C636B94
P 7700 3500
F 0 "R5" H 7770 3546 50  0000 L CNN
F 1 "R" H 7770 3455 50  0000 L CNN
F 2 "" V 7630 3500 50  0001 C CNN
F 3 "~" H 7700 3500 50  0001 C CNN
	1    7700 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3800 7550 3800
Text Notes 7600 3550 0    50   ~ 0
1000
Wire Wire Line
	7850 3500 8050 3500
Wire Wire Line
	7850 3800 8050 3800
Wire Wire Line
	8050 3800 8050 3500
Wire Wire Line
	8050 3500 8250 3500
Connection ~ 8050 3500
$Comp
L Connector:AudioJack2_Ground J4
U 1 1 5C638FDB
P 7350 4400
F 0 "J4" H 7380 4725 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7380 4634 50  0000 C CNN
F 2 "" H 7350 4400 50  0001 C CNN
F 3 "~" H 7350 4400 50  0001 C CNN
	1    7350 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5C638FE2
P 7700 4600
F 0 "R8" H 7770 4646 50  0000 L CNN
F 1 "R" H 7770 4555 50  0000 L CNN
F 2 "" V 7630 4600 50  0001 C CNN
F 3 "~" H 7700 4600 50  0001 C CNN
	1    7700 4600
	0    -1   1    0   
$EndComp
Text Notes 7600 4650 0    50   ~ 0
330
$Comp
L Device:R R7
U 1 1 5C638FEA
P 7700 4300
F 0 "R7" H 7770 4346 50  0000 L CNN
F 1 "R" H 7770 4255 50  0000 L CNN
F 2 "" V 7630 4300 50  0001 C CNN
F 3 "~" H 7700 4300 50  0001 C CNN
	1    7700 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 4600 7550 4600
Text Notes 7600 4350 0    50   ~ 0
1000
Wire Wire Line
	7850 4300 8050 4300
Wire Wire Line
	7850 4600 8050 4600
Wire Wire Line
	8050 4600 8050 4300
Wire Wire Line
	8050 4300 8250 4300
Connection ~ 8050 4300
Text GLabel 8900 5450 0    50   Input ~ 0
enc1pinA
Text GLabel 8900 5650 0    50   Input ~ 0
enc1pinB
Text GLabel 9500 5450 2    50   Input ~ 0
enc1button
Text GLabel 9500 6150 2    50   Input ~ 0
enc2button
Text GLabel 8900 6150 0    50   Input ~ 0
enc2pinA
Text GLabel 8900 6350 0    50   Input ~ 0
enc2pinB
Text GLabel 11000 5700 2    50   Input ~ 0
b1
Text GLabel 11000 6250 2    50   Input ~ 0
b2
Text GLabel 8550 1900 2    50   Input ~ 0
cvIn1
Text GLabel 8550 2700 2    50   Input ~ 0
cvIn2
Text GLabel 8550 3500 2    50   Input ~ 0
cvIn3
Text GLabel 8550 4300 2    50   Input ~ 0
cvIn4
Text GLabel 7850 5750 2    50   Input ~ 0
DACdataout
Text GLabel 7850 5650 2    50   Input ~ 0
DACspiclk
Text GLabel 6850 5750 0    50   Input ~ 0
DACslaveSelect
Text GLabel 6850 5650 0    50   Input ~ 0
DACldac
Text GLabel 7850 6350 2    50   Input ~ 0
DACclr
Text GLabel 10700 4900 2    50   Input ~ 0
trellisSCL
Text GLabel 10700 4800 2    50   Input ~ 0
trellisSDA
Text GLabel 10700 4000 2    50   Input ~ 0
OLEDclock
Text GLabel 10700 4300 2    50   Input ~ 0
OLEDreset
Text GLabel 10700 4200 2    50   Input ~ 0
OLEDdc
Text GLabel 10700 4100 2    50   Input ~ 0
OLEDcs
Text GLabel 10700 3900 2    50   Input ~ 0
OLEDdata
Text GLabel 9700 900  0    50   Input ~ 0
enc1button
Text GLabel 9700 1000 0    50   Input ~ 0
enc1pinA
Text GLabel 9700 1100 0    50   Input ~ 0
enc1pinB
Text GLabel 9700 2100 0    50   Input ~ 0
b2
Text GLabel 9700 1700 0    50   Input ~ 0
OLEDreset
Text GLabel 9700 1800 0    50   Input ~ 0
OLEDdc
Text GLabel 9700 1900 0    50   Input ~ 0
OLEDcs
Text GLabel 9700 2000 0    50   Input ~ 0
OLEDdata
Text GLabel 9700 1200 0    50   Input ~ 0
DACdataout
Text GLabel 9700 1300 0    50   Input ~ 0
DACspiclk
Text GLabel 9700 1500 0    50   Input ~ 0
DACldac
Text GLabel 9700 1600 0    50   Input ~ 0
DACclr
Text GLabel 10700 1100 2    50   Input ~ 0
cvIn1
Text GLabel 10700 1200 2    50   Input ~ 0
cvIn2
Text GLabel 10700 1300 2    50   Input ~ 0
cvIn3
Text GLabel 10700 2000 2    50   Input ~ 0
enc2button
Text GLabel 10700 1900 2    50   Input ~ 0
enc2pinA
Text GLabel 10700 1800 2    50   Input ~ 0
enc2pinB
Text GLabel 10700 2100 2    50   Input ~ 0
OLEDclock
Text GLabel 10700 1700 2    50   Input ~ 0
b1
Text GLabel 10700 1600 2    50   Input ~ 0
trellisSDA
Text GLabel 10700 1500 2    50   Input ~ 0
trellisSCL
Text GLabel 10700 1400 2    50   Input ~ 0
cvIn4
$Comp
L KaimatKicadLib:Teensy3.6 MCU2
U 1 1 5C6810D8
P 10200 650
F 0 "MCU2" H 10200 765 50  0000 C CNN
F 1 "Teensy3.6" H 10200 674 50  0000 C CNN
F 2 "" H 10200 800 50  0001 C CNN
F 3 "" H 10200 800 50  0001 C CNN
	1    10200 650 
	1    0    0    -1  
$EndComp
$Comp
L KaimatKicadLib:TI_DAC8568_ICPW DAC1
U 1 1 5C68358D
P 7350 5500
F 0 "DAC1" H 7350 5615 50  0000 C CNN
F 1 "TI_DAC8568_ICPW" H 7350 5524 50  0000 C CNN
F 2 "" H 7350 5650 50  0001 C CNN
F 3 "" H 7350 5650 50  0001 C CNN
	1    7350 5500
	1    0    0    -1  
$EndComp
$Comp
L KaimatKicadLib:Adafruit_NeoTrellis U2
U 1 1 5C6926FB
P 10400 4650
F 0 "U2" H 10400 4765 50  0000 C CNN
F 1 "Adafruit_NeoTrellis" H 10400 4674 50  0000 C CNN
F 2 "" H 10400 4800 50  0001 C CNN
F 3 "" H 10400 4800 50  0001 C CNN
	1    10400 4650
	1    0    0    -1  
$EndComp
NoConn ~ 10100 4800
NoConn ~ 10100 4900
NoConn ~ 10100 5000
NoConn ~ 10100 5100
NoConn ~ 10100 5200
NoConn ~ 10700 5200
$Comp
L KaimatKicadLib:Waveshare_128x128_OLED_SSD1327 U1
U 1 1 5C69EE51
P 10400 3550
F 0 "U1" H 10436 3665 50  0000 C CNN
F 1 "Waveshare_128x128_OLED_SSD1327" H 10436 3574 50  0000 C CNN
F 2 "" H 10400 3700 50  0001 C CNN
F 3 "" H 10400 3700 50  0001 C CNN
	1    10400 3550
	1    0    0    -1  
$EndComp
Text Notes 7600 2150 0    50   ~ 0
550
Wire Wire Line
	7950 1100 8100 1100
Wire Wire Line
	8100 1100 8100 1000
Wire Wire Line
	8100 1000 7950 1000
Wire Wire Line
	8100 1000 8100 900 
Wire Wire Line
	8100 900  7950 900 
Connection ~ 8100 1000
$Comp
L eurocad:Pin_Header_2x5 U?
U 1 1 5C665CEE
P 7500 700
F 0 "U?" H 7500 825 50  0000 C CNN
F 1 "Pin_Header_2x5" H 7500 734 50  0000 C CNN
F 2 "" H 7500 800 50  0001 C CNN
F 3 "" H 7500 800 50  0001 C CNN
	1    7500 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1000 8200 1000
NoConn ~ 7050 800 
NoConn ~ 7050 900 
NoConn ~ 7050 1000
NoConn ~ 7050 1100
NoConn ~ 7950 1200
$Comp
L power:GND #PWR?
U 1 1 5C66E52C
P 10700 5000
F 0 "#PWR?" H 10700 4750 50  0001 C CNN
F 1 "GND" V 10705 4872 50  0000 R CNN
F 2 "" H 10700 5000 50  0001 C CNN
F 3 "" H 10700 5000 50  0001 C CNN
	1    10700 5000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C66EE8E
P 10700 3800
F 0 "#PWR?" H 10700 3550 50  0001 C CNN
F 1 "GND" V 10705 3672 50  0000 R CNN
F 2 "" H 10700 3800 50  0001 C CNN
F 3 "" H 10700 3800 50  0001 C CNN
	1    10700 3800
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C66F22E
P 10700 1000
F 0 "#PWR?" H 10700 850 50  0001 C CNN
F 1 "+3.3V" V 10715 1128 50  0000 L CNN
F 2 "" H 10700 1000 50  0001 C CNN
F 3 "" H 10700 1000 50  0001 C CNN
	1    10700 1000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C66F58A
P 9700 800
F 0 "#PWR?" H 9700 550 50  0001 C CNN
F 1 "GND" V 9705 672 50  0000 R CNN
F 2 "" H 9700 800 50  0001 C CNN
F 3 "" H 9700 800 50  0001 C CNN
	1    9700 800 
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C66F616
P 10700 800
F 0 "#PWR?" H 10700 650 50  0001 C CNN
F 1 "+5V" V 10715 928 50  0000 L CNN
F 2 "" H 10700 800 50  0001 C CNN
F 3 "" H 10700 800 50  0001 C CNN
	1    10700 800 
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C67268D
P 7350 3000
F 0 "#PWR?" H 7350 2750 50  0001 C CNN
F 1 "GND" H 7355 2827 50  0000 C CNN
F 2 "" H 7350 3000 50  0001 C CNN
F 3 "" H 7350 3000 50  0001 C CNN
	1    7350 3000
	1    0    0    -1  
$EndComp
Connection ~ 7350 3000
$Comp
L power:GND #PWR?
U 1 1 5C6726EA
P 7350 3800
F 0 "#PWR?" H 7350 3550 50  0001 C CNN
F 1 "GND" H 7355 3627 50  0000 C CNN
F 2 "" H 7350 3800 50  0001 C CNN
F 3 "" H 7350 3800 50  0001 C CNN
	1    7350 3800
	1    0    0    -1  
$EndComp
Connection ~ 7350 3800
$Comp
L power:GND #PWR?
U 1 1 5C672747
P 7350 4600
F 0 "#PWR?" H 7350 4350 50  0001 C CNN
F 1 "GND" H 7355 4427 50  0000 C CNN
F 2 "" H 7350 4600 50  0001 C CNN
F 3 "" H 7350 4600 50  0001 C CNN
	1    7350 4600
	1    0    0    -1  
$EndComp
Connection ~ 7350 4600
$Comp
L power:GND #PWR?
U 1 1 5C673CB5
P 7850 5850
F 0 "#PWR?" H 7850 5600 50  0001 C CNN
F 1 "GND" V 7855 5722 50  0000 R CNN
F 2 "" H 7850 5850 50  0001 C CNN
F 3 "" H 7850 5850 50  0001 C CNN
	1    7850 5850
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C67417B
P 9500 5650
F 0 "#PWR?" H 9500 5400 50  0001 C CNN
F 1 "GND" V 9505 5522 50  0000 R CNN
F 2 "" H 9500 5650 50  0001 C CNN
F 3 "" H 9500 5650 50  0001 C CNN
	1    9500 5650
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C6744F1
P 8900 5550
F 0 "#PWR?" H 8900 5300 50  0001 C CNN
F 1 "GND" V 8905 5422 50  0000 R CNN
F 2 "" H 8900 5550 50  0001 C CNN
F 3 "" H 8900 5550 50  0001 C CNN
	1    8900 5550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674BC5
P 8900 6250
F 0 "#PWR?" H 8900 6000 50  0001 C CNN
F 1 "GND" V 8905 6122 50  0000 R CNN
F 2 "" H 8900 6250 50  0001 C CNN
F 3 "" H 8900 6250 50  0001 C CNN
	1    8900 6250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674C3C
P 9500 6350
F 0 "#PWR?" H 9500 6100 50  0001 C CNN
F 1 "GND" V 9505 6222 50  0000 R CNN
F 2 "" H 9500 6350 50  0001 C CNN
F 3 "" H 9500 6350 50  0001 C CNN
	1    9500 6350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674FB9
P 10300 6250
F 0 "#PWR?" H 10300 6000 50  0001 C CNN
F 1 "GND" V 10305 6122 50  0000 R CNN
F 2 "" H 10300 6250 50  0001 C CNN
F 3 "" H 10300 6250 50  0001 C CNN
	1    10300 6250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C675C10
P 10300 5700
F 0 "#PWR?" H 10300 5450 50  0001 C CNN
F 1 "GND" V 10305 5572 50  0000 R CNN
F 2 "" H 10300 5700 50  0001 C CNN
F 3 "" H 10300 5700 50  0001 C CNN
	1    10300 5700
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C679A0F
P 10700 5100
F 0 "#PWR?" H 10700 4950 50  0001 C CNN
F 1 "+3.3V" V 10715 5228 50  0000 L CNN
F 2 "" H 10700 5100 50  0001 C CNN
F 3 "" H 10700 5100 50  0001 C CNN
	1    10700 5100
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C679E70
P 10700 3700
F 0 "#PWR?" H 10700 3550 50  0001 C CNN
F 1 "+3.3V" V 10715 3828 50  0000 L CNN
F 2 "" H 10700 3700 50  0001 C CNN
F 3 "" H 10700 3700 50  0001 C CNN
	1    10700 3700
	0    1    1    0   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C682E98
P 8100 800
F 0 "D?" H 8100 584 50  0000 C CNN
F 1 "D_ALT" H 8100 675 50  0000 C CNN
F 2 "" H 8100 800 50  0001 C CNN
F 3 "~" H 8100 800 50  0001 C CNN
	1    8100 800 
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68B931
P 8400 4300
F 0 "D?" H 8400 4084 50  0000 C CNN
F 1 "D_ALT" H 8400 4175 50  0000 C CNN
F 2 "" H 8400 4300 50  0001 C CNN
F 3 "~" H 8400 4300 50  0001 C CNN
	1    8400 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68BCC8
P 8400 3500
F 0 "D?" H 8400 3284 50  0000 C CNN
F 1 "D_ALT" H 8400 3375 50  0000 C CNN
F 2 "" H 8400 3500 50  0001 C CNN
F 3 "~" H 8400 3500 50  0001 C CNN
	1    8400 3500
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68C690
P 8400 2700
F 0 "D?" H 8400 2484 50  0000 C CNN
F 1 "D_ALT" H 8400 2575 50  0000 C CNN
F 2 "" H 8400 2700 50  0001 C CNN
F 3 "~" H 8400 2700 50  0001 C CNN
	1    8400 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68CD2E
P 8400 1900
F 0 "D?" H 8400 1684 50  0000 C CNN
F 1 "D_ALT" H 8400 1775 50  0000 C CNN
F 2 "" H 8400 1900 50  0001 C CNN
F 3 "~" H 8400 1900 50  0001 C CNN
	1    8400 1900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C68E121
P 7350 2200
F 0 "#PWR?" H 7350 1950 50  0001 C CNN
F 1 "GND" H 7355 2027 50  0000 C CNN
F 2 "" H 7350 2200 50  0001 C CNN
F 3 "" H 7350 2200 50  0001 C CNN
	1    7350 2200
	1    0    0    -1  
$EndComp
Connection ~ 7350 2200
Text GLabel 9700 1400 0    50   Input ~ 0
DACslaveSelect
NoConn ~ 7550 2000
NoConn ~ 7550 2800
NoConn ~ 7550 3600
NoConn ~ 7550 4400
NoConn ~ 7050 1200
$Comp
L power:GND #PWR?
U 1 1 5C692728
P 10700 900
F 0 "#PWR?" H 10700 650 50  0001 C CNN
F 1 "GND" V 10705 772 50  0000 R CNN
F 2 "" H 10700 900 50  0001 C CNN
F 3 "" H 10700 900 50  0001 C CNN
	1    10700 900 
	0    -1   -1   0   
$EndComp
Entry Wire Line
	12100 400  12200 500 
$Comp
L power:+5V #PWR?
U 1 1 5C6937C9
P 6850 5850
F 0 "#PWR?" H 6850 5700 50  0001 C CNN
F 1 "+5V" V 6865 5978 50  0000 L CNN
F 2 "" H 6850 5850 50  0001 C CNN
F 3 "" H 6850 5850 50  0001 C CNN
	1    6850 5850
	0    -1   -1   0   
$EndComp
Text GLabel 6850 5950 0    50   Input ~ 0
CVout1
Text GLabel 7850 5950 2    50   Input ~ 0
CVout2
Text GLabel 6850 6050 0    50   Input ~ 0
CVout3
Text GLabel 7850 6050 2    50   Input ~ 0
CVout4
Text GLabel 6850 6150 0    50   Input ~ 0
TRout1
Text GLabel 7850 6150 2    50   Input ~ 0
TRout2
Text GLabel 6850 6250 0    50   Input ~ 0
TRout3
Text GLabel 7850 6250 2    50   Input ~ 0
TRout4
Text GLabel 4850 900  0    50   Input ~ 0
CVout1
Text GLabel 4850 1300 0    50   Input ~ 0
CVout3
Text GLabel 4850 1700 0    50   Input ~ 0
TRout1
Text GLabel 4850 2100 0    50   Input ~ 0
TRout3
Text GLabel 4850 1100 0    50   Input ~ 0
CVout2
Text GLabel 4850 1500 0    50   Input ~ 0
CVout4
Text GLabel 4850 1900 0    50   Input ~ 0
TRout2
Text GLabel 4850 2300 0    50   Input ~ 0
TRout4
NoConn ~ 6850 6350
Wire Wire Line
	10300 5700 10350 5700
Wire Wire Line
	10350 5700 10350 5800
Connection ~ 10350 5700
Wire Wire Line
	10950 5800 10950 5700
Wire Wire Line
	10950 5700 11000 5700
Connection ~ 10950 5700
Wire Wire Line
	10300 6250 10350 6250
Wire Wire Line
	10350 6350 10350 6250
Connection ~ 10350 6250
Wire Wire Line
	10950 6350 10950 6250
Wire Wire Line
	10950 6250 11000 6250
Connection ~ 10950 6250
$Comp
L power:GND #PWR?
U 1 1 5C6A2054
P 8200 1100
F 0 "#PWR?" H 8200 850 50  0001 C CNN
F 1 "GND" H 8205 927 50  0000 C CNN
F 2 "" H 8200 1100 50  0001 C CNN
F 3 "" H 8200 1100 50  0001 C CNN
	1    8200 1100
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM1117-5.0 U?
U 1 1 5C6AFFEC
P 8550 800
F 0 "U?" H 8550 1042 50  0000 C CNN
F 1 "LM1117-5.0" H 8550 951 50  0000 C CNN
F 2 "" H 8550 800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 8550 800 50  0001 C CNN
	1    8550 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C6B0D3B
P 8550 1100
F 0 "#PWR?" H 8550 850 50  0001 C CNN
F 1 "GND" H 8555 927 50  0000 C CNN
F 2 "" H 8550 1100 50  0001 C CNN
F 3 "" H 8550 1100 50  0001 C CNN
	1    8550 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1000 8200 1100
$Comp
L power:+5V #PWR?
U 1 1 5C6B1A2F
P 8850 800
F 0 "#PWR?" H 8850 650 50  0001 C CNN
F 1 "+5V" V 8865 928 50  0000 L CNN
F 2 "" H 8850 800 50  0001 C CNN
F 3 "" H 8850 800 50  0001 C CNN
	1    8850 800 
	0    1    1    0   
$EndComp
NoConn ~ 9700 2200
NoConn ~ 9700 2300
NoConn ~ 9700 2400
NoConn ~ 9700 2500
NoConn ~ 9700 2600
NoConn ~ 9700 2700
NoConn ~ 9700 2800
NoConn ~ 9700 2900
NoConn ~ 9700 3000
NoConn ~ 9700 3100
NoConn ~ 10700 3100
NoConn ~ 10700 3000
NoConn ~ 10700 2900
NoConn ~ 10700 2800
NoConn ~ 10700 2700
NoConn ~ 10700 2600
NoConn ~ 10700 2500
NoConn ~ 10700 2400
NoConn ~ 10700 2300
NoConn ~ 10700 2200
$EndSCHEMATC
