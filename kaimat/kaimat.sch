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
P 10700 6300
F 0 "SW4" H 10700 6667 50  0000 C CNN
F 1 "SW_DIP_x02" H 10700 6576 50  0000 C CNN
F 2 "" H 10700 6300 50  0001 C CNN
F 3 "" H 10700 6300 50  0001 C CNN
	1    10700 6300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x02 SW3
U 1 1 5C49060B
P 10700 5600
F 0 "SW3" H 10700 5967 50  0000 C CNN
F 1 "SW_DIP_x02" H 10700 5876 50  0000 C CNN
F 2 "" H 10700 5600 50  0001 C CNN
F 3 "" H 10700 5600 50  0001 C CNN
	1    10700 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW2
U 1 1 5C5B4CB3
P 9200 6300
F 0 "SW2" H 9200 6667 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9200 6576 50  0000 C CNN
F 2 "" H 9050 6460 50  0001 C CNN
F 3 "~" H 9200 6560 50  0001 C CNN
	1    9200 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5C5B60FE
P 9200 5600
F 0 "SW1" H 9200 5967 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9200 5876 50  0000 C CNN
F 2 "" H 9050 5760 50  0001 C CNN
F 3 "~" H 9200 5860 50  0001 C CNN
	1    9200 5600
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground J1
U 1 1 5C5C6F4A
P 7400 900
F 0 "J1" H 7430 1225 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7430 1134 50  0000 C CNN
F 2 "" H 7400 900 50  0001 C CNN
F 3 "~" H 7400 900 50  0001 C CNN
	1    7400 900 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C5C70ED
P 7750 1100
F 0 "R2" H 7820 1146 50  0000 L CNN
F 1 "R" H 7820 1055 50  0000 L CNN
F 2 "" V 7680 1100 50  0001 C CNN
F 3 "~" H 7750 1100 50  0001 C CNN
	1    7750 1100
	0    -1   1    0   
$EndComp
Text Notes 7650 1150 0    50   ~ 0
330
$Comp
L Device:R R1
U 1 1 5C5C72C2
P 7750 800
F 0 "R1" H 7820 846 50  0000 L CNN
F 1 "R" H 7820 755 50  0000 L CNN
F 2 "" V 7680 800 50  0001 C CNN
F 3 "~" H 7750 800 50  0001 C CNN
	1    7750 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 1100 7600 1100
Text Notes 7650 850  0    50   ~ 0
1000
Wire Wire Line
	7900 800  8100 800 
Wire Wire Line
	7900 1100 8100 1100
Wire Wire Line
	8100 1100 8100 800 
Wire Wire Line
	8100 800  8300 800 
Connection ~ 8100 800 
$Comp
L Connector:AudioJack2_Ground J2
U 1 1 5C5D9E79
P 7400 1700
F 0 "J2" H 7430 2025 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7430 1934 50  0000 C CNN
F 2 "" H 7400 1700 50  0001 C CNN
F 3 "~" H 7400 1700 50  0001 C CNN
	1    7400 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C5D9E80
P 7750 1900
F 0 "R4" H 7820 1946 50  0000 L CNN
F 1 "R" H 7820 1855 50  0000 L CNN
F 2 "" V 7680 1900 50  0001 C CNN
F 3 "~" H 7750 1900 50  0001 C CNN
	1    7750 1900
	0    -1   1    0   
$EndComp
Text Notes 7650 1950 0    50   ~ 0
330
$Comp
L Device:R R3
U 1 1 5C5D9E88
P 7750 1600
F 0 "R3" H 7820 1646 50  0000 L CNN
F 1 "R" H 7820 1555 50  0000 L CNN
F 2 "" V 7680 1600 50  0001 C CNN
F 3 "~" H 7750 1600 50  0001 C CNN
	1    7750 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 1900 7600 1900
Text Notes 7650 1650 0    50   ~ 0
1000
Wire Wire Line
	7900 1600 8100 1600
Wire Wire Line
	7900 1900 8100 1900
Wire Wire Line
	8100 1900 8100 1600
Wire Wire Line
	8100 1600 8300 1600
Connection ~ 8100 1600
$Comp
L Connector:AudioJack2_Ground J3
U 1 1 5C636B85
P 7400 2500
F 0 "J3" H 7430 2825 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7430 2734 50  0000 C CNN
F 2 "" H 7400 2500 50  0001 C CNN
F 3 "~" H 7400 2500 50  0001 C CNN
	1    7400 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C636B8C
P 7750 2700
F 0 "R6" H 7820 2746 50  0000 L CNN
F 1 "R" H 7820 2655 50  0000 L CNN
F 2 "" V 7680 2700 50  0001 C CNN
F 3 "~" H 7750 2700 50  0001 C CNN
	1    7750 2700
	0    -1   1    0   
$EndComp
Text Notes 7650 2750 0    50   ~ 0
330
$Comp
L Device:R R5
U 1 1 5C636B94
P 7750 2400
F 0 "R5" H 7820 2446 50  0000 L CNN
F 1 "R" H 7820 2355 50  0000 L CNN
F 2 "" V 7680 2400 50  0001 C CNN
F 3 "~" H 7750 2400 50  0001 C CNN
	1    7750 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 2700 7600 2700
Text Notes 7650 2450 0    50   ~ 0
1000
Wire Wire Line
	7900 2400 8100 2400
Wire Wire Line
	7900 2700 8100 2700
Wire Wire Line
	8100 2700 8100 2400
Wire Wire Line
	8100 2400 8300 2400
Connection ~ 8100 2400
$Comp
L Connector:AudioJack2_Ground J4
U 1 1 5C638FDB
P 7400 3300
F 0 "J4" H 7430 3625 50  0000 C CNN
F 1 "AudioJack2_Ground" H 7430 3534 50  0000 C CNN
F 2 "" H 7400 3300 50  0001 C CNN
F 3 "~" H 7400 3300 50  0001 C CNN
	1    7400 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5C638FE2
P 7750 3500
F 0 "R8" H 7820 3546 50  0000 L CNN
F 1 "R" H 7820 3455 50  0000 L CNN
F 2 "" V 7680 3500 50  0001 C CNN
F 3 "~" H 7750 3500 50  0001 C CNN
	1    7750 3500
	0    -1   1    0   
$EndComp
Text Notes 7650 3550 0    50   ~ 0
330
$Comp
L Device:R R7
U 1 1 5C638FEA
P 7750 3200
F 0 "R7" H 7820 3246 50  0000 L CNN
F 1 "R" H 7820 3155 50  0000 L CNN
F 2 "" V 7680 3200 50  0001 C CNN
F 3 "~" H 7750 3200 50  0001 C CNN
	1    7750 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 3500 7600 3500
Text Notes 7650 3250 0    50   ~ 0
1000
Wire Wire Line
	7900 3200 8100 3200
Wire Wire Line
	7900 3500 8100 3500
Wire Wire Line
	8100 3500 8100 3200
Wire Wire Line
	8100 3200 8300 3200
Connection ~ 8100 3200
Text GLabel 8900 5500 0    50   Input ~ 0
enc1pinA
Text GLabel 8900 5700 0    50   Input ~ 0
enc1pinB
Text GLabel 9500 5500 2    50   Input ~ 0
enc1button
Text GLabel 9500 6200 2    50   Input ~ 0
enc2button
Text GLabel 8900 6200 0    50   Input ~ 0
enc2pinA
Text GLabel 8900 6400 0    50   Input ~ 0
enc2pinB
Text GLabel 11000 5500 2    50   Input ~ 0
b1
Text GLabel 11000 6200 2    50   Input ~ 0
b2
Text GLabel 8600 800  2    50   Input ~ 0
cvIn1
Text GLabel 8600 1600 2    50   Input ~ 0
cvIn2
Text GLabel 8600 2400 2    50   Input ~ 0
cvIn3
Text GLabel 8600 3200 2    50   Input ~ 0
cvIn4
Text GLabel 7900 5700 2    50   Input ~ 0
DACdataout
Text GLabel 7900 5600 2    50   Input ~ 0
DACspiclk
Text GLabel 6900 5700 0    50   Input ~ 0
DACslaveSelect
Text GLabel 6900 5600 0    50   Input ~ 0
DACldac
Text GLabel 7900 6300 2    50   Input ~ 0
DACclr
Text GLabel 10750 4500 2    50   Input ~ 0
trellisSCL
Text GLabel 10750 4400 2    50   Input ~ 0
trellisSDA
Text GLabel 9600 4700 2    50   Input ~ 0
OLEDclock
Text GLabel 9600 5000 2    50   Input ~ 0
OLEDreset
Text GLabel 9600 4900 2    50   Input ~ 0
OLEDdc
Text GLabel 9600 4800 2    50   Input ~ 0
OLEDcs
Text GLabel 9600 4600 2    50   Input ~ 0
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
P 7400 5450
F 0 "DAC1" H 7400 5565 50  0000 C CNN
F 1 "TI_DAC8568_ICPW" H 7400 5474 50  0000 C CNN
F 2 "" H 7400 5600 50  0001 C CNN
F 3 "" H 7400 5600 50  0001 C CNN
	1    7400 5450
	1    0    0    -1  
$EndComp
$Comp
L KaimatKicadLib:Adafruit_NeoTrellis U2
U 1 1 5C6926FB
P 10450 4250
F 0 "U2" H 10450 4365 50  0000 C CNN
F 1 "Adafruit_NeoTrellis" H 10450 4274 50  0000 C CNN
F 2 "" H 10450 4400 50  0001 C CNN
F 3 "" H 10450 4400 50  0001 C CNN
	1    10450 4250
	1    0    0    -1  
$EndComp
NoConn ~ 10150 4400
NoConn ~ 10150 4500
NoConn ~ 10150 4600
NoConn ~ 10150 4700
NoConn ~ 10150 4800
NoConn ~ 10750 4800
$Comp
L KaimatKicadLib:Waveshare_128x128_OLED_SSD1327 U1
U 1 1 5C69EE51
P 9300 4250
F 0 "U1" H 9336 4365 50  0000 C CNN
F 1 "Waveshare_128x128_OLED_SSD1327" H 9336 4274 50  0000 C CNN
F 2 "" H 9300 4400 50  0001 C CNN
F 3 "" H 9300 4400 50  0001 C CNN
	1    9300 4250
	1    0    0    -1  
$EndComp
Text Notes 7650 1050 0    50   ~ 0
550
Wire Wire Line
	8000 4950 8150 4950
Wire Wire Line
	8150 4950 8150 4850
Wire Wire Line
	8150 4850 8000 4850
Wire Wire Line
	8150 4850 8150 4750
Wire Wire Line
	8150 4750 8000 4750
Connection ~ 8150 4850
$Comp
L eurocad:Pin_Header_2x5 U?
U 1 1 5C665CEE
P 7550 4550
F 0 "U?" H 7550 4675 50  0000 C CNN
F 1 "Pin_Header_2x5" H 7550 4584 50  0000 C CNN
F 2 "" H 7550 4650 50  0001 C CNN
F 3 "" H 7550 4650 50  0001 C CNN
	1    7550 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 4850 8250 4850
NoConn ~ 7100 4650
NoConn ~ 7100 4750
NoConn ~ 7100 4850
NoConn ~ 7100 4950
NoConn ~ 8000 5050
$Comp
L power:GND #PWR?
U 1 1 5C66E3B8
P 8250 4850
F 0 "#PWR?" H 8250 4600 50  0001 C CNN
F 1 "GND" V 8255 4722 50  0000 R CNN
F 2 "" H 8250 4850 50  0001 C CNN
F 3 "" H 8250 4850 50  0001 C CNN
	1    8250 4850
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C66E52C
P 10750 4600
F 0 "#PWR?" H 10750 4350 50  0001 C CNN
F 1 "GND" V 10755 4472 50  0000 R CNN
F 2 "" H 10750 4600 50  0001 C CNN
F 3 "" H 10750 4600 50  0001 C CNN
	1    10750 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C66EE8E
P 9600 4500
F 0 "#PWR?" H 9600 4250 50  0001 C CNN
F 1 "GND" V 9605 4372 50  0000 R CNN
F 2 "" H 9600 4500 50  0001 C CNN
F 3 "" H 9600 4500 50  0001 C CNN
	1    9600 4500
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
P 7400 1900
F 0 "#PWR?" H 7400 1650 50  0001 C CNN
F 1 "GND" H 7405 1727 50  0000 C CNN
F 2 "" H 7400 1900 50  0001 C CNN
F 3 "" H 7400 1900 50  0001 C CNN
	1    7400 1900
	1    0    0    -1  
$EndComp
Connection ~ 7400 1900
$Comp
L power:GND #PWR?
U 1 1 5C6726EA
P 7400 2700
F 0 "#PWR?" H 7400 2450 50  0001 C CNN
F 1 "GND" H 7405 2527 50  0000 C CNN
F 2 "" H 7400 2700 50  0001 C CNN
F 3 "" H 7400 2700 50  0001 C CNN
	1    7400 2700
	1    0    0    -1  
$EndComp
Connection ~ 7400 2700
$Comp
L power:GND #PWR?
U 1 1 5C672747
P 7400 3500
F 0 "#PWR?" H 7400 3250 50  0001 C CNN
F 1 "GND" H 7405 3327 50  0000 C CNN
F 2 "" H 7400 3500 50  0001 C CNN
F 3 "" H 7400 3500 50  0001 C CNN
	1    7400 3500
	1    0    0    -1  
$EndComp
Connection ~ 7400 3500
$Comp
L power:GND #PWR?
U 1 1 5C673CB5
P 7900 5800
F 0 "#PWR?" H 7900 5550 50  0001 C CNN
F 1 "GND" V 7905 5672 50  0000 R CNN
F 2 "" H 7900 5800 50  0001 C CNN
F 3 "" H 7900 5800 50  0001 C CNN
	1    7900 5800
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C67417B
P 9500 5700
F 0 "#PWR?" H 9500 5450 50  0001 C CNN
F 1 "GND" V 9505 5572 50  0000 R CNN
F 2 "" H 9500 5700 50  0001 C CNN
F 3 "" H 9500 5700 50  0001 C CNN
	1    9500 5700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C6744F1
P 8900 5600
F 0 "#PWR?" H 8900 5350 50  0001 C CNN
F 1 "GND" V 8905 5472 50  0000 R CNN
F 2 "" H 8900 5600 50  0001 C CNN
F 3 "" H 8900 5600 50  0001 C CNN
	1    8900 5600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674BC5
P 8900 6300
F 0 "#PWR?" H 8900 6050 50  0001 C CNN
F 1 "GND" V 8905 6172 50  0000 R CNN
F 2 "" H 8900 6300 50  0001 C CNN
F 3 "" H 8900 6300 50  0001 C CNN
	1    8900 6300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674C3C
P 9500 6400
F 0 "#PWR?" H 9500 6150 50  0001 C CNN
F 1 "GND" V 9505 6272 50  0000 R CNN
F 2 "" H 9500 6400 50  0001 C CNN
F 3 "" H 9500 6400 50  0001 C CNN
	1    9500 6400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C674FB9
P 10400 6200
F 0 "#PWR?" H 10400 5950 50  0001 C CNN
F 1 "GND" V 10405 6072 50  0000 R CNN
F 2 "" H 10400 6200 50  0001 C CNN
F 3 "" H 10400 6200 50  0001 C CNN
	1    10400 6200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C675C10
P 10400 5500
F 0 "#PWR?" H 10400 5250 50  0001 C CNN
F 1 "GND" V 10405 5372 50  0000 R CNN
F 2 "" H 10400 5500 50  0001 C CNN
F 3 "" H 10400 5500 50  0001 C CNN
	1    10400 5500
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C6760CC
P 6900 5800
F 0 "#PWR?" H 6900 5650 50  0001 C CNN
F 1 "+3.3V" V 6915 5928 50  0000 L CNN
F 2 "" H 6900 5800 50  0001 C CNN
F 3 "" H 6900 5800 50  0001 C CNN
	1    6900 5800
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C679A0F
P 10750 4700
F 0 "#PWR?" H 10750 4550 50  0001 C CNN
F 1 "+3.3V" V 10765 4828 50  0000 L CNN
F 2 "" H 10750 4700 50  0001 C CNN
F 3 "" H 10750 4700 50  0001 C CNN
	1    10750 4700
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C679E70
P 9600 4400
F 0 "#PWR?" H 9600 4250 50  0001 C CNN
F 1 "+3.3V" V 9615 4528 50  0000 L CNN
F 2 "" H 9600 4400 50  0001 C CNN
F 3 "" H 9600 4400 50  0001 C CNN
	1    9600 4400
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C679F6B
P 8300 4650
F 0 "#PWR?" H 8300 4500 50  0001 C CNN
F 1 "VCC" V 8317 4778 50  0000 L CNN
F 2 "" H 8300 4650 50  0001 C CNN
F 3 "" H 8300 4650 50  0001 C CNN
	1    8300 4650
	0    1    1    0   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C682E98
P 8150 4650
F 0 "D?" H 8150 4434 50  0000 C CNN
F 1 "D_ALT" H 8150 4525 50  0000 C CNN
F 2 "" H 8150 4650 50  0001 C CNN
F 3 "~" H 8150 4650 50  0001 C CNN
	1    8150 4650
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68B931
P 8450 3200
F 0 "D?" H 8450 2984 50  0000 C CNN
F 1 "D_ALT" H 8450 3075 50  0000 C CNN
F 2 "" H 8450 3200 50  0001 C CNN
F 3 "~" H 8450 3200 50  0001 C CNN
	1    8450 3200
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68BCC8
P 8450 2400
F 0 "D?" H 8450 2184 50  0000 C CNN
F 1 "D_ALT" H 8450 2275 50  0000 C CNN
F 2 "" H 8450 2400 50  0001 C CNN
F 3 "~" H 8450 2400 50  0001 C CNN
	1    8450 2400
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68C690
P 8450 1600
F 0 "D?" H 8450 1384 50  0000 C CNN
F 1 "D_ALT" H 8450 1475 50  0000 C CNN
F 2 "" H 8450 1600 50  0001 C CNN
F 3 "~" H 8450 1600 50  0001 C CNN
	1    8450 1600
	-1   0    0    1   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C68CD2E
P 8450 800
F 0 "D?" H 8450 584 50  0000 C CNN
F 1 "D_ALT" H 8450 675 50  0000 C CNN
F 2 "" H 8450 800 50  0001 C CNN
F 3 "~" H 8450 800 50  0001 C CNN
	1    8450 800 
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C68E121
P 7400 1100
F 0 "#PWR?" H 7400 850 50  0001 C CNN
F 1 "GND" H 7405 927 50  0000 C CNN
F 2 "" H 7400 1100 50  0001 C CNN
F 3 "" H 7400 1100 50  0001 C CNN
	1    7400 1100
	1    0    0    -1  
$EndComp
Connection ~ 7400 1100
Text GLabel 9700 1400 0    50   Input ~ 0
DACslaveSelect
NoConn ~ 7600 900 
NoConn ~ 7600 1700
NoConn ~ 7600 2500
NoConn ~ 7600 3300
NoConn ~ 7100 5050
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
$EndSCHEMATC
