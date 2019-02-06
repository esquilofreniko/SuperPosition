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
L Device:Rotary_Encoder SW?
U 1 1 5C4900BD
P 2500 3450
F 0 "SW?" H 2729 3496 50  0000 L CNN
F 1 "Rotary_Encoder" H 2729 3405 50  0000 L CNN
F 2 "" H 2350 3610 50  0001 C CNN
F 3 "~" H 2500 3710 50  0001 C CNN
	1    2500 3450
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
Wire Wire Line
	650  4850 2300 4850
Wire Wire Line
	1800 3550 1800 4950
Wire Wire Line
	1800 4950 2300 4950
Wire Wire Line
	1750 3450 1750 5050
Wire Wire Line
	1750 5050 2300 5050
Wire Wire Line
	1700 3350 1700 5150
Wire Wire Line
	1700 5150 2300 5150
Wire Wire Line
	1800 3550 2200 3550
Wire Wire Line
	1750 3450 2200 3450
Wire Wire Line
	1700 3350 2200 3350
$EndSCHEMATC
