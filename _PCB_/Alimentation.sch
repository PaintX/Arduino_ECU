EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 8
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
L D D13
U 1 1 56B393F8
P 2100 1950
F 0 "D13" H 2100 2050 50  0000 C CNN
F 1 "FM5818" H 2100 1850 50  0000 C CNN
F 2 "Speeduino:SMA_Handsoldering" H 2100 1950 60  0001 C CNN
F 3 "" H 2100 1950 60  0000 C CNN
	1    2100 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 1950 1650 1950
$Comp
L CP C3
U 1 1 56B3A760
P 2400 2250
F 0 "C3" H 2425 2350 50  0000 L CNN
F 1 "CP" H 2425 2150 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 2438 2100 50  0001 C CNN
F 3 "" H 2400 2250 50  0000 C CNN
	1    2400 2250
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 56B3A7A3
P 2750 2250
F 0 "C4" H 2775 2350 50  0000 L CNN
F 1 "C" H 2775 2150 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 2788 2100 50  0001 C CNN
F 3 "" H 2750 2250 50  0000 C CNN
	1    2750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1950 3500 1950
Wire Wire Line
	2400 1950 2400 2100
Wire Wire Line
	2750 1450 2750 2100
Connection ~ 2400 1950
$Comp
L GND #PWR031
U 1 1 56B3A7DF
P 2400 2650
F 0 "#PWR031" H 2400 2400 50  0001 C CNN
F 1 "GND" H 2400 2500 50  0000 C CNN
F 2 "" H 2400 2650 60  0000 C CNN
F 3 "" H 2400 2650 60  0000 C CNN
	1    2400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2400 2400 2650
$Comp
L GND #PWR032
U 1 1 56B3A804
P 2750 2650
F 0 "#PWR032" H 2750 2400 50  0001 C CNN
F 1 "GND" H 2750 2500 50  0000 C CNN
F 2 "" H 2750 2650 60  0000 C CNN
F 3 "" H 2750 2650 60  0000 C CNN
	1    2750 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2400 2750 2650
$Comp
L LM2940CS-5.0 U3
U 1 1 56B3C47A
P 4200 1950
F 0 "U3" H 3970 2201 50  0000 L CNN
F 1 "LM2940CS-5.0" H 4027 1341 50  0000 L CNN
F 2 "Speeduino:TO-263-3Lead" H 4200 1950 50  0001 L CNN
F 3 "" H 4200 1950 60  0000 C CNN
	1    4200 1950
	1    0    0    -1  
$EndComp
Connection ~ 2750 1950
$Comp
L GND #PWR033
U 1 1 56B3C4E3
P 3250 2650
F 0 "#PWR033" H 3250 2400 50  0001 C CNN
F 1 "GND" H 3250 2500 50  0000 C CNN
F 2 "" H 3250 2650 60  0000 C CNN
F 3 "" H 3250 2650 60  0000 C CNN
	1    3250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2150 3250 2150
Wire Wire Line
	3250 2150 3250 2650
Wire Wire Line
	3500 2250 3250 2250
Connection ~ 3250 2250
$Comp
L CP C6
U 1 1 56B3C6FF
P 5100 2250
F 0 "C6" H 5125 2350 50  0000 L CNN
F 1 "CP" H 5125 2150 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 5138 2100 50  0001 C CNN
F 3 "" H 5100 2250 50  0000 C CNN
	1    5100 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 56B3C74C
P 5100 2650
F 0 "#PWR034" H 5100 2400 50  0001 C CNN
F 1 "GND" H 5100 2500 50  0000 C CNN
F 2 "" H 5100 2650 60  0000 C CNN
F 3 "" H 5100 2650 60  0000 C CNN
	1    5100 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1950 5950 1950
Wire Wire Line
	5100 2100 5100 1950
Connection ~ 5100 1950
Wire Wire Line
	5100 2650 5100 2400
$Comp
L C C7
U 1 1 56B3C7AD
P 5450 2250
F 0 "C7" H 5475 2350 50  0000 L CNN
F 1 "C" H 5475 2150 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 5488 2100 50  0001 C CNN
F 3 "" H 5450 2250 50  0000 C CNN
	1    5450 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 56B3C815
P 5450 2650
F 0 "#PWR035" H 5450 2400 50  0001 C CNN
F 1 "GND" H 5450 2500 50  0000 C CNN
F 2 "" H 5450 2650 60  0000 C CNN
F 3 "" H 5450 2650 60  0000 C CNN
	1    5450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1950 5450 2100
Connection ~ 5450 1950
Wire Wire Line
	5450 2400 5450 2650
$Comp
L +5V #PWR036
U 1 1 56B3C95A
P 5950 1950
F 0 "#PWR036" H 5950 1800 50  0001 C CNN
F 1 "+5V" H 5950 2090 50  0000 C CNN
F 2 "" H 5950 1950 50  0000 C CNN
F 3 "" H 5950 1950 50  0000 C CNN
	1    5950 1950
	0    1    1    0   
$EndComp
$Comp
L +12V #PWR037
U 1 1 56B3C9C8
P 5950 1450
F 0 "#PWR037" H 5950 1300 50  0001 C CNN
F 1 "+12V" H 5950 1590 50  0000 C CNN
F 2 "" H 5950 1450 50  0000 C CNN
F 3 "" H 5950 1450 50  0000 C CNN
	1    5950 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 1450 2750 1450
$EndSCHEMATC
