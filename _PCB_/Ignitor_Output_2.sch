EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L GND #PWR06
U 1 1 56B1F3DA
P 4800 4300
F 0 "#PWR06" H 4800 4050 50  0001 C CNN
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
L GND #PWR07
U 1 1 56B20C40
P 4300 4300
F 0 "#PWR07" H 4300 4050 50  0001 C CNN
F 1 "GND" H 4300 4150 50  0000 C CNN
F 2 "" H 4300 4300 60  0000 C CNN
F 3 "" H 4300 4300 60  0000 C CNN
	1    4300 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 56B1FE3E
P 4300 2950
F 0 "#PWR08" H 4300 2700 50  0001 C CNN
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
$EndSCHEMATC