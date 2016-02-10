EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
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
L TC4424AVOA U3
U 1 1 56B20C3A
P 5700 3700
F 0 "U3" H 5650 4250 50  0000 L CNN
F 1 "TC4424AVOA" H 5700 3050 50  0000 L CNN
F 2 "Speeduino:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5700 3700 50  0001 L CNN
F 3 "" H 5700 3700 60  0000 C CNN
	1    5700 3700
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 56B20C3B
P 4300 3350
F 0 "R21" V 4400 3350 50  0000 C CNN
F 1 "100K" V 4300 3350 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4230 3350 50  0001 C CNN
F 3 "" H 4300 3350 50  0000 C CNN
	1    4300 3350
	1    0    0    -1  
$EndComp
$Comp
L R R22
U 1 1 56B20C3C
P 4300 3950
F 0 "R22" V 4400 3950 50  0000 C CNN
F 1 "100K" V 4300 3950 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4230 3950 50  0001 C CNN
F 3 "" H 4300 3950 50  0000 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 56B9276F
P 4050 3700
F 0 "R20" V 4150 3700 50  0000 C CNN
F 1 "1K" V 4050 3700 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 3980 3700 50  0001 C CNN
F 3 "" H 4050 3700 50  0000 C CNN
	1    4050 3700
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 56B92761
P 4050 3600
F 0 "R19" V 3950 3600 50  0000 C CNN
F 1 "1K" V 4050 3600 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 3980 3600 50  0001 C CNN
F 3 "" H 4050 3600 50  0000 C CNN
	1    4050 3600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR018
U 1 1 56B92771
P 4800 4300
F 0 "#PWR018" H 4800 4050 50  0001 C CNN
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
L +5V #PWR019
U 1 1 56B92762
P 4200 1250
F 0 "#PWR019" H 4200 1100 50  0001 C CNN
F 1 "+5V" H 4200 1390 50  0000 C CNN
F 2 "" H 4200 1250 50  0000 C CNN
F 3 "" H 4200 1250 50  0000 C CNN
	1    4200 1250
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR020
U 1 1 56B92763
P 5100 1250
F 0 "#PWR020" H 5100 1100 50  0001 C CNN
F 1 "+12V" H 5100 1390 50  0000 C CNN
F 2 "" H 5100 1250 50  0000 C CNN
F 3 "" H 5100 1250 50  0000 C CNN
	1    5100 1250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR021
U 1 1 56B1FD67
P 4300 4300
F 0 "#PWR021" H 4300 4050 50  0001 C CNN
F 1 "GND" H 4300 4150 50  0000 C CNN
F 2 "" H 4300 4300 60  0000 C CNN
F 3 "" H 4300 4300 60  0000 C CNN
	1    4300 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 56B92773
P 4300 2950
F 0 "#PWR022" H 4300 2700 50  0001 C CNN
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
Text GLabel 4750 1550 2    60   Input ~ 0
VCC_INJECTOR
$Comp
L R R23
U 1 1 56B20449
P 4400 1250
F 0 "R23" V 4500 1250 50  0000 C CNN
F 1 "0" V 4400 1250 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4330 1250 50  0001 C CNN
F 3 "" H 4400 1250 50  0000 C CNN
	1    4400 1250
	0    1    1    0   
$EndComp
$Comp
L R R24
U 1 1 56B204C9
P 4900 1250
F 0 "R24" V 5000 1250 50  0000 C CNN
F 1 "0" V 4900 1250 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 4830 1250 50  0001 C CNN
F 3 "" H 4900 1250 50  0000 C CNN
	1    4900 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 1250 4250 1250
Wire Wire Line
	4550 1250 4750 1250
Wire Wire Line
	5100 1250 5050 1250
Wire Wire Line
	4750 1550 4650 1550
Wire Wire Line
	4650 1550 4650 1250
Connection ~ 4650 1250
Text GLabel 4650 3250 1    60   Input ~ 0
VCC_INJECTOR
Wire Wire Line
	4650 3400 4650 3250
Wire Wire Line
	3900 3600 3400 3600
Wire Wire Line
	3900 3700 3400 3700
Text GLabel 3400 3600 0    59   Input ~ 0
INJ1_CPU_D8
Text GLabel 3400 3700 0    59   Input ~ 0
INJ2_CPU_D9
$Comp
L LED D5
U 1 1 56B92774
P 7600 3200
F 0 "D5" H 7600 3300 50  0000 C CNN
F 1 "LED" H 7600 3100 50  0000 C CNN
F 2 "Speeduino:LED_0603" H 7600 3000 60  0001 C CNN
F 3 "" H 7600 3200 60  0000 C CNN
	1    7600 3200
	-1   0    0    1   
$EndComp
$Comp
L LED D6
U 1 1 56B92776
P 7600 3700
F 0 "D6" H 7600 3800 50  0000 C CNN
F 1 "LED" H 7600 3600 50  0000 C CNN
F 2 "Speeduino:LED_0603" H 7600 3500 60  0001 C CNN
F 3 "" H 7600 3700 60  0000 C CNN
	1    7600 3700
	-1   0    0    1   
$EndComp
$Comp
L R R25
U 1 1 56B92778
P 6700 3400
F 0 "R25" V 6780 3400 50  0000 C CNN
F 1 "R" V 6700 3400 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6630 3400 50  0001 C CNN
F 3 "" H 6700 3400 50  0000 C CNN
	1    6700 3400
	0    1    1    0   
$EndComp
$Comp
L R R26
U 1 1 56B9277A
P 6700 3500
F 0 "R26" V 6780 3500 50  0000 C CNN
F 1 "R" V 6700 3500 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 6630 3500 50  0001 C CNN
F 3 "" H 6700 3500 50  0000 C CNN
	1    6700 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 3400 6550 3400
Wire Wire Line
	6550 3500 6400 3500
Wire Wire Line
	6850 3400 8000 3400
Wire Wire Line
	6850 3500 8000 3500
Wire Wire Line
	6900 3400 6900 3200
Wire Wire Line
	6900 3200 7000 3200
Connection ~ 6900 3400
Wire Wire Line
	6900 3500 6900 3700
Connection ~ 6900 3500
Wire Wire Line
	6900 3700 7000 3700
$Comp
L R R27
U 1 1 56B9277C
P 7150 3200
F 0 "R27" V 7230 3200 50  0000 C CNN
F 1 "R" V 7150 3200 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 7080 3200 50  0001 C CNN
F 3 "" H 7150 3200 50  0000 C CNN
	1    7150 3200
	0    1    1    0   
$EndComp
$Comp
L R R28
U 1 1 56B9277F
P 7150 3700
F 0 "R28" V 7230 3700 50  0000 C CNN
F 1 "R" V 7150 3700 50  0000 C CNN
F 2 "Speeduino:R_0603_HandSoldering" V 7080 3700 50  0001 C CNN
F 3 "" H 7150 3700 50  0000 C CNN
	1    7150 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	7300 3200 7400 3200
Wire Wire Line
	7300 3700 7400 3700
$Comp
L GND #PWR023
U 1 1 56B25EE6
P 7850 3200
F 0 "#PWR023" H 7850 2950 50  0001 C CNN
F 1 "GND" H 7850 3050 50  0000 C CNN
F 2 "" H 7850 3200 60  0000 C CNN
F 3 "" H 7850 3200 60  0000 C CNN
	1    7850 3200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR024
U 1 1 56B2616E
P 7850 3700
F 0 "#PWR024" H 7850 3450 50  0001 C CNN
F 1 "GND" H 7850 3550 50  0000 C CNN
F 2 "" H 7850 3700 60  0000 C CNN
F 3 "" H 7850 3700 60  0000 C CNN
	1    7850 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7800 3200 7850 3200
Wire Wire Line
	7800 3700 7850 3700
Text GLabel 8000 3500 2    59   Input ~ 0
INJ-1-OUT
Text GLabel 8000 3400 2    59   Input ~ 0
INJ-2-OUT
$Comp
L C C3
U 1 1 56B92785
P 4900 3050
F 0 "C3" H 4925 3150 50  0000 L CNN
F 1 "C" H 4925 2950 50  0000 L CNN
F 2 "Speeduino:C_0603_HandSoldering" H 4938 2900 50  0001 C CNN
F 3 "" H 4900 3050 50  0000 C CNN
	1    4900 3050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR025
U 1 1 56B92787
P 4900 2750
F 0 "#PWR025" H 4900 2500 50  0001 C CNN
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
$EndSCHEMATC
