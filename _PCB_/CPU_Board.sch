EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 56B219D5
P 5550 3850
F 0 "SHIELD1" H 5150 6350 60  0000 C CNN
F 1 "ARDUINO_MEGA_SHIELD" H 5450 1150 60  0000 C CNN
F 2 "Speeduino:ARDUINO MEGA SHIELD" H 5050 6250 60  0000 C CNN
F 3 "" H 5550 3850 60  0000 C CNN
	1    5550 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 56B1F3BE
P 3900 2250
F 0 "#PWR?" H 3900 2000 50  0001 C CNN
F 1 "GND" H 3900 2100 50  0000 C CNN
F 2 "" H 3900 2250 60  0000 C CNN
F 3 "" H 3900 2250 60  0000 C CNN
	1    3900 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 2200 4550 2200
Wire Wire Line
	4200 2200 4200 2300
Wire Wire Line
	4200 2300 4550 2300
Wire Wire Line
	4200 2250 3900 2250
Connection ~ 4200 2250
$EndSCHEMATC
