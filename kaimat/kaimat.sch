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
P 9350 6300
F 0 "SW2" H 9350 6667 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9350 6576 50  0000 C CNN
F 2 "" H 9200 6460 50  0001 C CNN
F 3 "~" H 9350 6560 50  0001 C CNN
	1    9350 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5C5B60FE
P 9350 5600
F 0 "SW1" H 9350 5967 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 9350 5876 50  0000 C CNN
F 2 "" H 9200 5760 50  0001 C CNN
F 3 "~" H 9350 5860 50  0001 C CNN
	1    9350 5600
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground J1
U 1 1 5C5C6F4A
P 850 900
F 0 "J1" H 880 1225 50  0000 C CNN
F 1 "AudioJack2_Ground" H 880 1134 50  0000 C CNN
F 2 "" H 850 900 50  0001 C CNN
F 3 "~" H 850 900 50  0001 C CNN
	1    850  900 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C5C70ED
P 1200 1100
F 0 "R2" H 1270 1146 50  0000 L CNN
F 1 "R" H 1270 1055 50  0000 L CNN
F 2 "" V 1130 1100 50  0001 C CNN
F 3 "~" H 1200 1100 50  0001 C CNN
	1    1200 1100
	0    -1   1    0   
$EndComp
Text Notes 1100 1150 0    50   ~ 0
330
$Comp
L Device:R R1
U 1 1 5C5C72C2
P 1200 800
F 0 "R1" H 1270 846 50  0000 L CNN
F 1 "R" H 1270 755 50  0000 L CNN
F 2 "" V 1130 800 50  0001 C CNN
F 3 "~" H 1200 800 50  0001 C CNN
	1    1200 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	850  1100 1050 1100
Text Notes 1100 850  0    50   ~ 0
1000
Wire Wire Line
	1350 800  1550 800 
Wire Wire Line
	1350 1100 1550 1100
Wire Wire Line
	1550 1100 1550 800 
Wire Wire Line
	1550 800  1750 800 
Connection ~ 1550 800 
$Comp
L Connector:AudioJack2_Ground J2
U 1 1 5C5D9E79
P 850 1550
F 0 "J2" H 880 1875 50  0000 C CNN
F 1 "AudioJack2_Ground" H 880 1784 50  0000 C CNN
F 2 "" H 850 1550 50  0001 C CNN
F 3 "~" H 850 1550 50  0001 C CNN
	1    850  1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C5D9E80
P 1200 1750
F 0 "R4" H 1270 1796 50  0000 L CNN
F 1 "R" H 1270 1705 50  0000 L CNN
F 2 "" V 1130 1750 50  0001 C CNN
F 3 "~" H 1200 1750 50  0001 C CNN
	1    1200 1750
	0    -1   1    0   
$EndComp
Text Notes 1100 1800 0    50   ~ 0
330
$Comp
L Device:R R3
U 1 1 5C5D9E88
P 1200 1450
F 0 "R3" H 1270 1496 50  0000 L CNN
F 1 "R" H 1270 1405 50  0000 L CNN
F 2 "" V 1130 1450 50  0001 C CNN
F 3 "~" H 1200 1450 50  0001 C CNN
	1    1200 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	850  1750 1050 1750
Text Notes 1100 1500 0    50   ~ 0
1000
Wire Wire Line
	1350 1450 1550 1450
Wire Wire Line
	1350 1750 1550 1750
Wire Wire Line
	1550 1750 1550 1450
Wire Wire Line
	1550 1450 1750 1450
Connection ~ 1550 1450
$Comp
L pspice:DIODE D1
U 1 1 5C5DC9CE
P 1950 800
F 0 "D1" H 1950 1065 50  0000 C CNN
F 1 "DIODE" H 1950 974 50  0000 C CNN
F 2 "" H 1950 800 50  0001 C CNN
F 3 "~" H 1950 800 50  0001 C CNN
	1    1950 800 
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D2
U 1 1 5C5DCA79
P 1950 1450
F 0 "D2" H 1950 1715 50  0000 C CNN
F 1 "DIODE" H 1950 1624 50  0000 C CNN
F 2 "" H 1950 1450 50  0001 C CNN
F 3 "~" H 1950 1450 50  0001 C CNN
	1    1950 1450
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground J3
U 1 1 5C636B85
P 850 2200
F 0 "J3" H 880 2525 50  0000 C CNN
F 1 "AudioJack2_Ground" H 880 2434 50  0000 C CNN
F 2 "" H 850 2200 50  0001 C CNN
F 3 "~" H 850 2200 50  0001 C CNN
	1    850  2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C636B8C
P 1200 2400
F 0 "R6" H 1270 2446 50  0000 L CNN
F 1 "R" H 1270 2355 50  0000 L CNN
F 2 "" V 1130 2400 50  0001 C CNN
F 3 "~" H 1200 2400 50  0001 C CNN
	1    1200 2400
	0    -1   1    0   
$EndComp
Text Notes 1100 2450 0    50   ~ 0
330
$Comp
L Device:R R5
U 1 1 5C636B94
P 1200 2100
F 0 "R5" H 1270 2146 50  0000 L CNN
F 1 "R" H 1270 2055 50  0000 L CNN
F 2 "" V 1130 2100 50  0001 C CNN
F 3 "~" H 1200 2100 50  0001 C CNN
	1    1200 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	850  2400 1050 2400
Text Notes 1100 2150 0    50   ~ 0
1000
Wire Wire Line
	1350 2100 1550 2100
Wire Wire Line
	1350 2400 1550 2400
Wire Wire Line
	1550 2400 1550 2100
Wire Wire Line
	1550 2100 1750 2100
Connection ~ 1550 2100
$Comp
L pspice:DIODE D3
U 1 1 5C636BA2
P 1950 2100
F 0 "D3" H 1950 2365 50  0000 C CNN
F 1 "DIODE" H 1950 2274 50  0000 C CNN
F 2 "" H 1950 2100 50  0001 C CNN
F 3 "~" H 1950 2100 50  0001 C CNN
	1    1950 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground J4
U 1 1 5C638FDB
P 850 2850
F 0 "J4" H 880 3175 50  0000 C CNN
F 1 "AudioJack2_Ground" H 880 3084 50  0000 C CNN
F 2 "" H 850 2850 50  0001 C CNN
F 3 "~" H 850 2850 50  0001 C CNN
	1    850  2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5C638FE2
P 1200 3050
F 0 "R8" H 1270 3096 50  0000 L CNN
F 1 "R" H 1270 3005 50  0000 L CNN
F 2 "" V 1130 3050 50  0001 C CNN
F 3 "~" H 1200 3050 50  0001 C CNN
	1    1200 3050
	0    -1   1    0   
$EndComp
Text Notes 1100 3100 0    50   ~ 0
330
$Comp
L Device:R R7
U 1 1 5C638FEA
P 1200 2750
F 0 "R7" H 1270 2796 50  0000 L CNN
F 1 "R" H 1270 2705 50  0000 L CNN
F 2 "" V 1130 2750 50  0001 C CNN
F 3 "~" H 1200 2750 50  0001 C CNN
	1    1200 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	850  3050 1050 3050
Text Notes 1100 2800 0    50   ~ 0
1000
Wire Wire Line
	1350 2750 1550 2750
Wire Wire Line
	1350 3050 1550 3050
Wire Wire Line
	1550 3050 1550 2750
Wire Wire Line
	1550 2750 1750 2750
Connection ~ 1550 2750
$Comp
L pspice:DIODE D4
U 1 1 5C638FF8
P 1950 2750
F 0 "D4" H 1950 3015 50  0000 C CNN
F 1 "DIODE" H 1950 2924 50  0000 C CNN
F 2 "" H 1950 2750 50  0001 C CNN
F 3 "~" H 1950 2750 50  0001 C CNN
	1    1950 2750
	1    0    0    -1  
$EndComp
Text GLabel 9050 5500 0    50   Input ~ 0
enc1pinA
Text GLabel 9050 5700 0    50   Input ~ 0
enc1pinB
Text GLabel 9650 5500 2    50   Input ~ 0
enc1button
Text GLabel 9650 5700 2    50   Input ~ 0
GND
Text GLabel 9650 6200 2    50   Input ~ 0
enc2button
Text GLabel 9650 6400 2    50   Input ~ 0
GND
Text GLabel 9050 6200 0    50   Input ~ 0
enc2pinA
Text GLabel 9050 6400 0    50   Input ~ 0
enc2pinB
Text GLabel 9050 5600 0    50   Input ~ 0
GND
Text GLabel 9050 6300 0    50   Input ~ 0
GND
Text GLabel 10400 5500 0    50   Input ~ 0
GND
Text GLabel 11000 5500 2    50   Input ~ 0
b1
Text GLabel 10400 6200 0    50   Input ~ 0
GND
Text GLabel 11000 6200 2    50   Input ~ 0
b2
Text GLabel 2150 800  2    50   Input ~ 0
cvIn1
Text GLabel 2150 1450 2    50   Input ~ 0
cvIn2
Text GLabel 2150 2100 2    50   Input ~ 0
cvIn3
Text GLabel 2150 2750 2    50   Input ~ 0
cvIn4
Text GLabel 8100 5700 2    50   Input ~ 0
DACdataout
Text GLabel 8100 5600 2    50   Input ~ 0
DACspiclk
Text GLabel 7100 5700 0    50   Input ~ 0
DACslaveSelect
Text GLabel 7100 5600 0    50   Input ~ 0
DACldac
Text GLabel 8100 6300 2    50   Input ~ 0
DACclr
Text GLabel 7100 5800 0    50   Input ~ 0
3.3v
Text GLabel 8100 5800 2    50   Input ~ 0
GND
Text GLabel 10750 4500 2    50   Input ~ 0
trellisSCL
Text GLabel 10750 4400 2    50   Input ~ 0
trellisSDA
Text GLabel 10750 4600 2    50   Input ~ 0
GND
Text GLabel 10750 4700 2    50   Input ~ 0
3.3V
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
Text GLabel 9600 4400 2    50   Input ~ 0
3.3V
Text GLabel 9600 4500 2    50   Input ~ 0
GND
Text GLabel 9700 850  0    50   Input ~ 0
GND
Text GLabel 9700 950  0    50   Input ~ 0
enc1button
Text GLabel 9700 1050 0    50   Input ~ 0
enc1pinA
Text GLabel 9700 1150 0    50   Input ~ 0
enc1pinB
Text GLabel 9700 2150 0    50   Input ~ 0
b2
Text GLabel 9700 1750 0    50   Input ~ 0
OLEDreset
Text GLabel 9700 1850 0    50   Input ~ 0
OLEDdc
Text GLabel 9700 1950 0    50   Input ~ 0
OLEDcs
Text GLabel 9700 2050 0    50   Input ~ 0
OLEDdata
Text GLabel 9700 1250 0    50   Input ~ 0
DACdataout
Text GLabel 9700 1350 0    50   Input ~ 0
DACspiclk
Text GLabel 9700 1450 0    50   Input ~ 0
DACslaveSelect
Text GLabel 9700 1550 0    50   Input ~ 0
DACldac
Text GLabel 9700 1650 0    50   Input ~ 0
DACclr
Text GLabel 10700 1150 2    50   Input ~ 0
cvIn1
Text GLabel 10700 1250 2    50   Input ~ 0
cvIn2
Text GLabel 10700 1350 2    50   Input ~ 0
cvIn3
Text GLabel 10700 2050 2    50   Input ~ 0
enc2button
Text GLabel 10700 1950 2    50   Input ~ 0
enc2pinA
Text GLabel 10700 1850 2    50   Input ~ 0
enc2pinB
Text GLabel 10700 2150 2    50   Input ~ 0
OLEDclock
Text GLabel 10700 1750 2    50   Input ~ 0
b1
Text GLabel 10700 1650 2    50   Input ~ 0
trellisSDA
Text GLabel 10700 1550 2    50   Input ~ 0
trellisSCL
Text GLabel 10700 1450 2    50   Input ~ 0
cvIn4
$Comp
L KaimatKicadLib:Teensy3.6 MCU2
U 1 1 5C6810D8
P 10200 700
F 0 "MCU2" H 10200 815 50  0000 C CNN
F 1 "Teensy3.6" H 10200 724 50  0000 C CNN
F 2 "" H 10200 850 50  0001 C CNN
F 3 "" H 10200 850 50  0001 C CNN
	1    10200 700 
	1    0    0    -1  
$EndComp
$Comp
L KaimatKicadLib:TI_DAC8568_ICPW DAC1
U 1 1 5C68358D
P 7600 5450
F 0 "DAC1" H 7600 5565 50  0000 C CNN
F 1 "TI_DAC8568_ICPW" H 7600 5474 50  0000 C CNN
F 2 "" H 7600 5600 50  0001 C CNN
F 3 "" H 7600 5600 50  0001 C CNN
	1    7600 5450
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
$EndSCHEMATC
