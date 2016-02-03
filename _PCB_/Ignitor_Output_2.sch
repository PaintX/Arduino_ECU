EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L TC4424AVOA U2
U 1 1 56B1F235
P 5700 3700
F 0 "U2" H 5650 4250 50  0000 L CNN
F 1 "TC4424AVOA" H 5700 3050 50  0000 L CNN
F 2 "Speeduino:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5700 3700 50  0001 L CNN
F 3 "" H 5700 3700 60  0000 C CNN
	1    5700 3700
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 56B1F284
P 4300 3350
F 0 "R9" V 4400 3350 50  0000 C CNN
F 1 "100K" V 4300 3350 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4230 3350 50  0001 C CNN
F 3 "" H 4300 3350 50  0000 C CNN
	1    4300 3350
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 56B1F2FB
P 4300 3950
F 0 "R10" V 4400 3950 50  0000 C CNN
F 1 "100K" V 4300 3950 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4230 3950 50  0001 C CNN
F 3 "" H 4300 3950 50  0000 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 56B1F338
P 4050 3700
F 0 "R8" V 4150 3700 50  0000 C CNN
F 1 "1K" V 4050 3700 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 3980 3700 50  0001 C CNN
F 3 "" H 4050 3700 50  0000 C CNN
	1    4050 3700
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 56B20C3E
P 4050 3600
F 0 "R7" V 3950 3600 50  0000 C CNN
F 1 "1K" V 4050 3600 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 3980 3600 50  0001 C CNN
F 3 "" H 4050 3600 50  0000 C CNN
	1    4050 3600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 56B1F3DA
P 4800 4300
F 0 "#PWR09" H 4800 4050 50  0001 C CNN
F 1 "GND" H 4800 4150 50  0000 C CNN
F 2 "" H 4800 4300 60  0000 C CNN
F 3 "" H 4800 4300 60  0000 C CNN
	1    4800 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3600 4200 3600
Wire Wire Line
	5000 3700 4200 3700
Wire Wire Line
	4300 3500 4300 3600
Connection ~ 4300 3600
Wire Wire Line
	4300 3700 4300 3800
Connection ~ 4300 3700
Wire Wire Line
	5000 4200 4800 4200
Wire Wire Line
	4800 4200 4800 4300
Wire Wire Line
	4650 3400 5000 3400
$Comp
L GND #PWR010
U 1 1 56B20C40
P 4300 4300
F 0 "#PWR010" H 4300 4050 50  0001 C CNN
F 1 "GND" H 4300 4150 50  0000 C CNN
F 2 "" H 4300 4300 60  0000 C CNN
F 3 "" H 4300 4300 60  0000 C CNN
	1    4300 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 56B1FE3E
P 4300 2950
F 0 "#PWR011" H 4300 2700 50  0001 C CNN
F 1 "GND" H 4300 2800 50  0000 C CNN
F 2 "" H 4300 2950 60  0000 C CNN
F 3 "" H 4300 2950 60  0000 C CNN
	1    4300 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 3200 4300 2950
Wire Wire Line
	4300 4300 4300 4100
Text GLabel 4650 3250 1    59   Input ~ 0
VCC_IGNITION
Wire Wire Line
	4650 3400 4650 3250
Wire Wire Line
	3900 3600 3450 3600
Wire Wire Line
	3900 3700 3450 3700
Text GLabel 3450 3600 0    59   Input ~ 0
IGN3_CPU_D52
Text GLabel 3450 3700 0    59   Input ~ 0
IGN4_CPU_D50
$Comp
L R R15
U 1 1 56B259B8
P 6650 3400
F 0 "R15" V 6730 3400 50  0000 C CNN
F 1 "R" V 6650 3400 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6580 3400 50  0001 C CNN
F 3 "" H 6650 3400 50  0000 C CNN
	1    6650 3400
	0    1    1    0   
$EndComp
$Comp
L R R16
U 1 1 56B25A0B
P 6650 3500
F 0 "R16" V 6730 3500 50  0000 C CNN
F 1 "R" V 6650 3500 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6580 3500 50  0001 C CNN
F 3 "" H 6650 3500 50  0000 C CNN
	1    6650 3500
	0    1    1    0   
$EndComp
$Comp
L R R17
U 1 1 56B25A30
P 7050 3250
F 0 "R17" V 7130 3250 50  0000 C CNN
F 1 "R" V 7050 3250 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6980 3250 50  0001 C CNN
F 3 "" H 7050 3250 50  0000 C CNN
	1    7050 3250
	0    1    1    0   
$EndComp
$Comp
L R R18
U 1 1 56B25A76
P 7050 3650
F 0 "R18" V 7130 3650 50  0000 C CNN
F 1 "R" V 7050 3650 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6980 3650 50  0001 C CNN
F 3 "" H 7050 3650 50  0000 C CNN
	1    7050 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 3400 6500 3400
Wire Wire Line
	6400 3500 6500 3500
Wire Wire Line
	6800 3400 8050 3400
Wire Wire Line
	6800 3500 8050 3500
$Comp
L LED D3
U 1 1 56B25B8B
P 7500 3250
F 0 "D3" H 7500 3350 50  0000 C CNN
F 1 "LED" H 7500 3150 50  0000 C CNN
F 2 "Speeduino:LED_0603" H 7500 3050 60  0001 C CNN
F 3 "" H 7500 3250 60  0000 C CNN
	1    7500 3250
	-1   0    0    1   
$EndComp
$Comp
L LED D4
U 1 1 56B25C56
P 7500 3650
F 0 "D4" H 7500 3750 50  0000 C CNN
F 1 "LED" H 7500 3550 50  0000 C CNN
F 2 "Speeduino:LED_0603" H 7500 3450 60  0001 C CNN
F 3 "" H 7500 3650 60  0000 C CNN
	1    7500 3650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR012
U 1 1 56B25DCD
P 7800 3250
F 0 "#PWR012" H 7800 3000 50  0001 C CNN
F 1 "GND" H 7800 3100 50  0000 C CNN
F 2 "" H 7800 3250 60  0000 C CNN
F 3 "" H 7800 3250 60  0000 C CNN
	1    7800 3250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR013
U 1 1 56B25DF7
P 7800 3650
F 0 "#PWR013" H 7800 3400 50  0001 C CNN
F 1 "GND" H 7800 3500 50  0000 C CNN
F 2 "" H 7800 3650 60  0000 C CNN
F 3 "" H 7800 3650 60  0000 C CNN
	1    7800 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7200 3250 7300 3250
Wire Wire Line
	7200 3650 7300 3650
Wire Wire Line
	7700 3250 7800 3250
Wire Wire Line
	7700 3650 7800 3650
Text GLabel 8050 3500 2    59   Input ~ 0
IGN-3-OUT
Text GLabel 8050 3400 2    59   Input ~ 0
IGN-4-OUT
$Comp
L C C2
U 1 1 56B26800
P 4900 3050
F 0 "C2" H 4925 3150 50  0000 L CNN
F 1 "C" H 4925 2950 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 4938 2900 50  0001 C CNN
F 3 "" H 4900 3050 50  0000 C CNN
	1    4900 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 56B26907
P 4900 2750
F 0 "#PWR014" H 4900 2500 50  0001 C CNN
F 1 "GND" H 4900 2600 50  0000 C CNN
F 2 "" H 4900 2750 60  0000 C CNN
F 3 "" H 4900 2750 60  0000 C CNN
	1    4900 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3400 4900 3200
Connection ~ 4900 3400
Wire Wire Line
	4900 2900 4900 2750
Wire Wire Line
	6850 3250 6850 3400
Connection ~ 6850 3400
Connection ~ 6850 3500
Wire Wire Line
	6850 3500 6850 3650
Wire Wire Line
	6850 3650 6900 3650
Wire Wire Line
	6900 3250 6850 3250
$EndSCHEMATC
