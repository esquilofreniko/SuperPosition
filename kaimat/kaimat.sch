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
L teensy:Teensy3.2 U?
U 1 1 5C48FCBF
P 3300 6150
F 0 "U?" H 3300 7737 60  0000 C CNN
F 1 "Teensy3.2" H 3300 7631 60  0000 C CNN
F 2 "" H 3300 5350 60  0000 C CNN
F 3 "" H 3300 5350 60  0000 C CNN
	1    3300 6150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x02 SW?
U 1 1 5C49054F
P 1100 4050
F 0 "SW?" H 1100 4417 50  0000 C CNN
F 1 "SW_DIP_x02" H 1100 4326 50  0000 C CNN
F 2 "" H 1100 4050 50  0001 C CNN
F 3 "" H 1100 4050 50  0001 C CNN
	1    1100 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x02 SW?
U 1 1 5C49060B
P 1100 3500
F 0 "SW?" H 1100 3867 50  0000 C CNN
F 1 "SW_DIP_x02" H 1100 3776 50  0000 C CNN
F 2 "" H 1100 3500 50  0001 C CNN
F 3 "" H 1100 3500 50  0001 C CNN
	1    1100 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  4050 800  4050
Wire Wire Line
	650  3500 800  3500
Wire Wire Line
	650  4850 650  4050
Wire Wire Line
	650  4050 650  3500
Connection ~ 650  4050
Wire Wire Line
	1400 3500 1550 3500
Wire Wire Line
	1550 3500 1550 5650
Wire Wire Line
	1400 4050 1400 6150
Wire Wire Line
	1550 5650 2300 5650
Wire Wire Line
	1400 6150 2300 6150
$Comp
L Device:Rotary_Encoder_Switch SW?
U 1 1 5C5B4CB3
P 2600 4200
F 0 "SW?" H 2600 4567 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 2600 4476 50  0000 C CNN
F 2 "" H 2450 4360 50  0001 C CNN
F 3 "~" H 2600 4460 50  0001 C CNN
	1    2600 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4200 2100 4200
Wire Wire Line
	2100 4200 2100 4600
Wire Wire Line
	650  4850 2100 4850
Connection ~ 2100 4850
Wire Wire Line
	2100 4850 2300 4850
Wire Wire Line
	3050 4600 3050 4300
Wire Wire Line
	3050 4300 2900 4300
Wire Wire Line
	2100 4600 3050 4600
Connection ~ 2100 4600
Wire Wire Line
	2100 4600 2100 4850
Wire Wire Line
	2900 4100 2950 4100
Wire Wire Line
	2950 4100 2950 4700
Wire Wire Line
	2950 4700 2250 4700
Wire Wire Line
	2250 4700 2250 4950
Wire Wire Line
	2250 4950 2300 4950
Wire Wire Line
	2300 5050 2200 5050
Wire Wire Line
	2200 5050 2200 4300
Wire Wire Line
	2200 4300 2300 4300
Wire Wire Line
	2300 4100 2150 4100
Wire Wire Line
	2150 5150 2300 5150
Wire Wire Line
	2150 4100 2150 5150
$Comp
L Device:Rotary_Encoder_Switch SW?
U 1 1 5C5B60FE
P 2600 3500
F 0 "SW?" H 2600 3867 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 2600 3776 50  0000 C CNN
F 2 "" H 2450 3660 50  0001 C CNN
F 3 "~" H 2600 3760 50  0001 C CNN
	1    2600 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 4200 2100 3500
Wire Wire Line
	2100 3500 2300 3500
Connection ~ 2100 4200
Wire Wire Line
	2900 3600 3050 3600
Wire Wire Line
	3050 3600 3050 4300
Connection ~ 3050 4300
Wire Wire Line
	2900 3400 3150 3400
Wire Wire Line
	3150 3400 3150 3050
Wire Wire Line
	3150 3050 1950 3050
Wire Wire Line
	1950 3050 1950 6850
Wire Wire Line
	1950 6850 2300 6850
Wire Wire Line
	2300 3400 2000 3400
Wire Wire Line
	2000 6950 2300 6950
Wire Wire Line
	2000 3400 2000 6950
Wire Wire Line
	2300 3600 1850 3600
Wire Wire Line
	1850 3600 1850 7050
Wire Wire Line
	1850 7050 2300 7050
$EndSCHEMATC
