EESchema Schematic File Version 2
LIBS:Speeduino
LIBS:Speeduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 600  6600 2150 1050
U 56B1F212
F0 "Ignitor_Output_1" 60
F1 "Ignitor_Output_1.sch" 60
$EndSheet
$Sheet
S 2900 6600 2050 1050
U 56B20A5E
F0 "Ignitor_Output_2" 60
F1 "Ignitor_Output_2.sch" 60
$EndSheet
$Sheet
S 700  700  3250 1700
U 56B219CA
F0 "CPU_Board" 60
F1 "CPU_Board.sch" 60
$EndSheet
$Sheet
S 600  5200 2150 1150
U 56B270A0
F0 "Injector" 59
F1 "Injector.sch" 59
$EndSheet
$Comp
L BSP149 Q5
U 1 1 56B47F9F
P 4750 5700
F 0 "Q5" H 4950 5775 50  0000 L CNN
F 1 "BSP149" H 4950 5700 50  0000 L CNN
F 2 "Speeduino:SOT-223" H 4950 5625 50  0001 L CIN
F 3 "" H 4750 5700 50  0000 L CNN
	1    4750 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5450 4800 5400
Wire Wire Line
	4800 5400 4950 5400
Wire Wire Line
	4950 5400 4950 5450
$EndSCHEMATC
