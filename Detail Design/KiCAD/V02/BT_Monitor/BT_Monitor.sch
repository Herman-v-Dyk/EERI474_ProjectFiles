EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Body Temperature Monitor Wristband "
Date "2021-09-01"
Rev "rev02"
Comp "NWU"
Comment1 ""
Comment2 ""
Comment3 "Student No: 30254906"
Comment4 "Author: JH van Dyk"
$EndDescr
$Comp
L MCU_ST_STM32L0:STM32L071KBTx U1
U 1 1 61237953
P 6150 3450
F 0 "U1" H 6450 4300 50  0000 C CNN
F 1 "STM32L071KBT6" H 5650 2500 50  0000 C CNN
F 2 "Package_QFP:LQFP-32_7x7mm_P0.8mm" H 5650 2550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141136.pdf" H 6150 3450 50  0001 C CNN
	1    6150 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2550 6050 2400
Wire Wire Line
	6150 2550 6150 2400
Wire Wire Line
	6150 2400 6050 2400
$Comp
L Device:C C1
U 1 1 61238F1F
P 5650 1450
F 0 "C1" H 5765 1496 50  0000 L CNN
F 1 "100nF" H 5765 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5688 1300 50  0001 C CNN
F 3 "~" H 5650 1450 50  0001 C CNN
	1    5650 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 61239455
P 6100 1450
F 0 "C2" H 6215 1496 50  0000 L CNN
F 1 "100nF" H 6215 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6138 1300 50  0001 C CNN
F 3 "~" H 6100 1450 50  0001 C CNN
	1    6100 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 612396B4
P 6550 1450
F 0 "C3" H 6665 1496 50  0000 L CNN
F 1 "10uF" H 6665 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6588 1300 50  0001 C CNN
F 3 "~" H 6550 1450 50  0001 C CNN
	1    6550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1300 5650 1250
Wire Wire Line
	5650 1250 6100 1250
Wire Wire Line
	6550 1250 6550 1300
Wire Wire Line
	5650 1600 5650 1650
Wire Wire Line
	5650 1650 6100 1650
Wire Wire Line
	6550 1650 6550 1600
Wire Wire Line
	6100 1600 6100 1650
Connection ~ 6100 1650
Wire Wire Line
	6100 1650 6550 1650
Wire Wire Line
	6100 1300 6100 1250
Connection ~ 6100 1250
Wire Wire Line
	6100 1250 6550 1250
Connection ~ 5650 1650
$Comp
L power:GND #PWR014
U 1 1 61246F5C
P 6050 4600
F 0 "#PWR014" H 6050 4350 50  0001 C CNN
F 1 "GND" H 6055 4427 50  0000 C CNN
F 2 "" H 6050 4600 50  0001 C CNN
F 3 "" H 6050 4600 50  0001 C CNN
	1    6050 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4500 6150 4450
Wire Wire Line
	6150 4500 6050 4500
Wire Wire Line
	6050 4450 6050 4500
Connection ~ 6050 4500
Wire Wire Line
	6050 4500 6050 4600
Wire Wire Line
	6250 2550 6250 2400
Wire Wire Line
	6250 2400 6150 2400
Connection ~ 6150 2400
$Comp
L power:GND #PWR012
U 1 1 6124FD6A
P 9350 4400
F 0 "#PWR012" H 9350 4150 50  0001 C CNN
F 1 "GND" H 9355 4227 50  0000 C CNN
F 2 "" H 9350 4400 50  0001 C CNN
F 3 "" H 9350 4400 50  0001 C CNN
	1    9350 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 4650 9050 4650
Wire Wire Line
	9050 4650 9050 4550
Wire Wire Line
	9350 4400 9550 4400
Wire Wire Line
	9550 4400 9550 4550
$Comp
L MAX30205:MAX30205MTA+T U2
U 1 1 61259863
P 3850 6500
F 0 "U2" H 4650 6887 60  0000 C CNN
F 1 "MAX30205MTA+T" H 4650 6781 60  0000 C CNN
F 2 "Other_Components:MAX30205" H 4650 6740 60  0001 C CNN
F 3 "" H 3850 6500 60  0000 C CNN
	1    3850 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 6125B4E4
P 3550 6100
F 0 "R7" H 3550 6250 50  0000 L CNN
F 1 "4.7k" H 3550 5950 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3480 6100 50  0001 C CNN
F 3 "~" H 3550 6100 50  0001 C CNN
	1    3550 6100
	1    0    0    -1  
$EndComp
$Comp
L power:+3V0 #PWR03
U 1 1 6125C5F7
P 5650 1250
F 0 "#PWR03" H 5650 1100 50  0001 C CNN
F 1 "+3V0" H 5665 1423 50  0000 C CNN
F 2 "" H 5650 1250 50  0001 C CNN
F 3 "" H 5650 1250 50  0001 C CNN
	1    5650 1250
	1    0    0    -1  
$EndComp
Connection ~ 5650 1250
$Comp
L power:+3V0 #PWR08
U 1 1 6125C9F6
P 6050 2400
F 0 "#PWR08" H 6050 2250 50  0001 C CNN
F 1 "+3V0" H 6065 2573 50  0000 C CNN
F 2 "" H 6050 2400 50  0001 C CNN
F 3 "" H 6050 2400 50  0001 C CNN
	1    6050 2400
	1    0    0    -1  
$EndComp
Connection ~ 6050 2400
$Comp
L power:+3V0 #PWR013
U 1 1 6125CEA4
P 9050 4550
F 0 "#PWR013" H 9050 4400 50  0001 C CNN
F 1 "+3V0" H 9065 4723 50  0000 C CNN
F 2 "" H 9050 4550 50  0001 C CNN
F 3 "" H 9050 4550 50  0001 C CNN
	1    9050 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 6125D79F
P 3700 6100
F 0 "R8" H 3770 6146 50  0000 L CNN
F 1 "4.7k" H 3770 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3630 6100 50  0001 C CNN
F 3 "~" H 3700 6100 50  0001 C CNN
	1    3700 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 6125DB1F
P 3400 6100
F 0 "R6" H 3330 6054 50  0000 R CNN
F 1 "4.7k" H 3330 6145 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3330 6100 50  0001 C CNN
F 3 "~" H 3400 6100 50  0001 C CNN
	1    3400 6100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 6125DF85
P 3700 6950
F 0 "#PWR019" H 3700 6700 50  0001 C CNN
F 1 "GND" H 3705 6777 50  0000 C CNN
F 2 "" H 3700 6950 50  0001 C CNN
F 3 "" H 3700 6950 50  0001 C CNN
	1    3700 6950
	1    0    0    -1  
$EndComp
$Comp
L power:+3V0 #PWR017
U 1 1 612643FC
P 4700 5750
F 0 "#PWR017" H 4700 5600 50  0001 C CNN
F 1 "+3V0" H 4715 5923 50  0000 C CNN
F 2 "" H 4700 5750 50  0001 C CNN
F 3 "" H 4700 5750 50  0001 C CNN
	1    4700 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5950 3400 5800
Wire Wire Line
	3400 5800 3550 5800
Wire Wire Line
	4700 5800 4700 5750
Connection ~ 3550 5800
Wire Wire Line
	3550 5800 3700 5800
Wire Wire Line
	3550 5800 3550 5950
Wire Wire Line
	3700 5950 3700 5800
Connection ~ 3700 5800
Wire Wire Line
	3700 5800 4700 5800
Wire Wire Line
	3700 6250 3700 6700
Wire Wire Line
	3700 6700 3850 6700
Wire Wire Line
	3550 6600 3550 6250
Wire Wire Line
	3850 6500 3400 6500
Wire Wire Line
	3400 6500 3400 6250
$Comp
L Device:C C8
U 1 1 6126894E
P 5800 6750
F 0 "C8" H 5915 6796 50  0000 L CNN
F 1 "100nF" H 5915 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5838 6600 50  0001 C CNN
F 3 "~" H 5800 6750 50  0001 C CNN
	1    5800 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 6600 5650 6600
Wire Wire Line
	5650 6600 5650 5800
Wire Wire Line
	5650 5800 4700 5800
Connection ~ 5650 6600
Wire Wire Line
	5650 6600 5800 6600
Connection ~ 4700 5800
Wire Wire Line
	3700 6950 3700 6800
Wire Wire Line
	3700 6800 3850 6800
$Comp
L power:GND #PWR021
U 1 1 6126EF2F
P 5800 7000
F 0 "#PWR021" H 5800 6750 50  0001 C CNN
F 1 "GND" H 5805 6827 50  0000 C CNN
F 2 "" H 5800 7000 50  0001 C CNN
F 3 "" H 5800 7000 50  0001 C CNN
	1    5800 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 7000 5800 6900
Wire Wire Line
	5450 6700 5550 6700
Wire Wire Line
	5550 6700 5550 6800
Wire Wire Line
	5450 6800 5550 6800
Connection ~ 5550 6800
Wire Wire Line
	5550 6800 5550 6900
Wire Wire Line
	5450 6900 5550 6900
Connection ~ 5550 6900
Wire Wire Line
	5550 6900 5550 7000
Wire Wire Line
	5450 6500 5550 6500
Wire Wire Line
	5550 6500 5550 6700
Connection ~ 5550 6700
$Comp
L power:GND #PWR020
U 1 1 6127332A
P 5550 7000
F 0 "#PWR020" H 5550 6750 50  0001 C CNN
F 1 "GND" H 5555 6827 50  0000 C CNN
F 2 "" H 5550 7000 50  0001 C CNN
F 3 "" H 5550 7000 50  0001 C CNN
	1    5550 7000
	1    0    0    -1  
$EndComp
Text GLabel 3250 6500 0    50   Input ~ 0
SDA_T
Text GLabel 3250 6600 0    50   Input ~ 0
SCL_T
Wire Wire Line
	3250 6500 3400 6500
Connection ~ 3400 6500
Wire Wire Line
	3250 6600 3550 6600
Connection ~ 3550 6600
Wire Wire Line
	3550 6600 3850 6600
Text GLabel 6750 3550 2    50   Input ~ 0
SCL_T
Text GLabel 5450 3950 0    50   Input ~ 0
SDA_T
Wire Wire Line
	5450 3950 5550 3950
Wire Wire Line
	6750 3550 6650 3550
$Comp
L Device:Battery_Cell BT1
U 1 1 612801D7
P 1100 1600
F 0 "BT1" H 1218 1696 50  0000 L CNN
F 1 "3V - Coin Cell Battery " H 1218 1605 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_3002_1x2032" V 1100 1660 50  0001 C CNN
F 3 "~" V 1100 1660 50  0001 C CNN
	1    1100 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 61246642
P 5650 1650
F 0 "#PWR04" H 5650 1400 50  0001 C CNN
F 1 "GND" H 5655 1477 50  0000 C CNN
F 2 "" H 5650 1650 50  0001 C CNN
F 3 "" H 5650 1650 50  0001 C CNN
	1    5650 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 61281EDA
P 1100 1750
F 0 "#PWR06" H 1100 1500 50  0001 C CNN
F 1 "GND" H 1105 1577 50  0000 C CNN
F 2 "" H 1100 1750 50  0001 C CNN
F 3 "" H 1100 1750 50  0001 C CNN
	1    1100 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1750 1100 1700
Wire Wire Line
	1100 1400 1100 1150
$Comp
L power:+3V0 #PWR01
U 1 1 61284897
P 1100 1150
F 0 "#PWR01" H 1100 1000 50  0001 C CNN
F 1 "+3V0" H 1115 1323 50  0000 C CNN
F 2 "" H 1100 1150 50  0001 C CNN
F 3 "" H 1100 1150 50  0001 C CNN
	1    1100 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3V0 #PWR02
U 1 1 6128D070
P 9700 1150
F 0 "#PWR02" H 9700 1000 50  0001 C CNN
F 1 "+3V0" H 9715 1323 50  0000 C CNN
F 2 "" H 9700 1150 50  0001 C CNN
F 3 "" H 9700 1150 50  0001 C CNN
	1    9700 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6128EC10
P 9700 1900
F 0 "R3" H 9770 1946 50  0000 L CNN
F 1 "10k" H 9770 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9630 1900 50  0001 C CNN
F 3 "~" H 9700 1900 50  0001 C CNN
	1    9700 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 61292012
P 9700 2150
F 0 "#PWR07" H 9700 1900 50  0001 C CNN
F 1 "GND" H 9705 1977 50  0000 C CNN
F 2 "" H 9700 2150 50  0001 C CNN
F 3 "" H 9700 2150 50  0001 C CNN
	1    9700 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61292E2F
P 9350 1700
F 0 "R2" V 9143 1700 50  0000 C CNN
F 1 "470" V 9234 1700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 9280 1700 50  0001 C CNN
F 3 "~" H 9350 1700 50  0001 C CNN
	1    9350 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	9700 1250 9700 1200
Wire Wire Line
	9700 1750 9700 1700
Wire Wire Line
	9700 2050 9700 2150
Wire Wire Line
	9500 1700 9700 1700
Connection ~ 9700 1700
Wire Wire Line
	9700 1700 9700 1650
Wire Wire Line
	9200 1700 9100 1700
$Comp
L Device:C C4
U 1 1 6129EADF
P 9100 1400
F 0 "C4" H 8986 1354 50  0000 R CNN
F 1 "10uF" H 8986 1445 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9138 1250 50  0001 C CNN
F 3 "~" H 9100 1400 50  0001 C CNN
	1    9100 1400
	1    0    0    1   
$EndComp
Wire Wire Line
	9100 1550 9100 1700
Connection ~ 9100 1700
Wire Wire Line
	9100 1700 8950 1700
Wire Wire Line
	9100 1250 9100 1200
Wire Wire Line
	9100 1200 9700 1200
Connection ~ 9700 1200
Wire Wire Line
	9700 1200 9700 1150
$Comp
L power:GND #PWR010
U 1 1 612A5798
P 9700 3650
F 0 "#PWR010" H 9700 3400 50  0001 C CNN
F 1 "GND" H 9705 3477 50  0000 C CNN
F 2 "" H 9700 3650 50  0001 C CNN
F 3 "" H 9700 3650 50  0001 C CNN
	1    9700 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3650 9700 3600
Wire Wire Line
	9700 3150 9700 3100
$Comp
L Device:R R4
U 1 1 612A8C3D
P 9700 2850
F 0 "R4" H 9770 2896 50  0000 L CNN
F 1 "10k" H 9770 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9630 2850 50  0001 C CNN
F 3 "~" H 9700 2850 50  0001 C CNN
	1    9700 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V0 #PWR09
U 1 1 612A901F
P 9700 2650
F 0 "#PWR09" H 9700 2500 50  0001 C CNN
F 1 "+3V0" H 9715 2823 50  0000 C CNN
F 2 "" H 9700 2650 50  0001 C CNN
F 3 "" H 9700 2650 50  0001 C CNN
	1    9700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2650 9700 2700
Wire Wire Line
	9700 3100 9500 3100
Connection ~ 9700 3100
Wire Wire Line
	9700 3100 9700 3000
$Comp
L Device:R R5
U 1 1 612ACA61
P 9350 3100
F 0 "R5" V 9143 3100 50  0000 C CNN
F 1 "470" V 9234 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 9280 3100 50  0001 C CNN
F 3 "~" H 9350 3100 50  0001 C CNN
	1    9350 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 3100 9100 3100
$Comp
L Device:C C7
U 1 1 612AE847
P 9100 3350
F 0 "C7" H 8986 3304 50  0000 R CNN
F 1 "10uF" H 8986 3395 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9138 3200 50  0001 C CNN
F 3 "~" H 9100 3350 50  0001 C CNN
	1    9100 3350
	1    0    0    1   
$EndComp
Wire Wire Line
	9100 3200 9100 3100
Connection ~ 9100 3100
Wire Wire Line
	9100 3100 8850 3100
Wire Wire Line
	9100 3500 9100 3600
Wire Wire Line
	9100 3600 9700 3600
Connection ~ 9700 3600
Wire Wire Line
	9700 3600 9700 3550
Text GLabel 8950 1700 0    50   Input ~ 0
PA0
Text GLabel 6750 2750 2    50   Input ~ 0
PA0
Wire Wire Line
	6750 2750 6650 2750
Text GLabel 8850 3100 0    50   Input ~ 0
PA1
Text GLabel 6750 2850 2    50   Input ~ 0
PA1
Wire Wire Line
	6750 2850 6650 2850
Text GLabel 5450 2750 0    50   Input ~ 0
NRST
Wire Wire Line
	5450 2750 5550 2750
Text GLabel 6750 4050 2    50   Input ~ 0
SYS_SWDIO
Text GLabel 6750 4150 2    50   Input ~ 0
SYS_SWCLK
Wire Wire Line
	6750 4150 6650 4150
Wire Wire Line
	6750 4050 6650 4050
Wire Wire Line
	5450 2950 5550 2950
Text GLabel 5450 2950 0    50   Input ~ 0
BOOT0
Text GLabel 5150 1200 1    50   Input ~ 0
BOOT0
$Comp
L Device:R R1
U 1 1 612CF07A
P 5150 1450
F 0 "R1" H 5080 1404 50  0000 R CNN
F 1 "10K" H 5080 1495 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5080 1450 50  0001 C CNN
F 3 "~" H 5150 1450 50  0001 C CNN
	1    5150 1450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 612CF689
P 5150 1700
F 0 "#PWR05" H 5150 1450 50  0001 C CNN
F 1 "GND" H 5155 1527 50  0000 C CNN
F 2 "" H 5150 1700 50  0001 C CNN
F 3 "" H 5150 1700 50  0001 C CNN
	1    5150 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1700 5150 1600
Wire Wire Line
	5150 1300 5150 1200
$Comp
L power:+3V0 #PWR016
U 1 1 612D5ABF
P 9500 5650
F 0 "#PWR016" H 9500 5500 50  0001 C CNN
F 1 "+3V0" H 9515 5823 50  0000 C CNN
F 2 "" H 9500 5650 50  0001 C CNN
F 3 "" H 9500 5650 50  0001 C CNN
	1    9500 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5700 9500 5700
Wire Wire Line
	9500 5700 9500 5650
Text GLabel 9400 5800 0    50   Input ~ 0
SYS_SWCLK
Wire Wire Line
	9400 5800 9600 5800
Wire Wire Line
	9600 5900 8850 5900
Wire Wire Line
	8850 5900 8850 6050
$Comp
L power:GND #PWR018
U 1 1 612DD33E
P 8850 6050
F 0 "#PWR018" H 8850 5800 50  0001 C CNN
F 1 "GND" H 8855 5877 50  0000 C CNN
F 2 "" H 8850 6050 50  0001 C CNN
F 3 "" H 8850 6050 50  0001 C CNN
	1    8850 6050
	1    0    0    -1  
$EndComp
Text GLabel 9400 6000 0    50   Input ~ 0
SYS_SWDIO
Wire Wire Line
	9400 6000 9600 6000
Text GLabel 9400 6100 0    50   Input ~ 0
NRST
Wire Wire Line
	9400 6100 9600 6100
Text GLabel 5450 3350 0    50   Input ~ 0
RCC_OSC32_IN
Wire Wire Line
	5450 3350 5550 3350
Text GLabel 5450 3450 0    50   Input ~ 0
RCC_OSC32_OUT
Wire Wire Line
	5450 3450 5550 3450
$Comp
L Device:Crystal_GND23 Y1
U 1 1 612FB2C3
P 3750 3100
F 0 "Y1" H 3550 3000 50  0000 L CNN
F 1 "QANTEK 32.768kHz" H 3800 3300 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_SeikoEpson_MC146-4Pin_6.7x1.5mm_HandSoldering" H 3750 3100 50  0001 C CNN
F 3 "~" H 3750 3100 50  0001 C CNN
	1    3750 3100
	1    0    0    -1  
$EndComp
NoConn ~ 3750 2900
NoConn ~ 3750 3300
Text GLabel 3450 3100 0    50   Input ~ 0
RCC_OSC32_IN
Text GLabel 4050 3100 2    50   Input ~ 0
RCC_OSC32_OUT
Wire Wire Line
	3900 3100 4000 3100
Wire Wire Line
	3450 3100 3500 3100
$Comp
L Device:C C5
U 1 1 6130CF10
P 3500 3450
F 0 "C5" H 3615 3496 50  0000 L CNN
F 1 "18pF" H 3615 3405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3538 3300 50  0001 C CNN
F 3 "~" H 3500 3450 50  0001 C CNN
	1    3500 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 6130D3EE
P 4000 3450
F 0 "C6" H 4115 3496 50  0000 L CNN
F 1 "18pF" H 4115 3405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4038 3300 50  0001 C CNN
F 3 "~" H 4000 3450 50  0001 C CNN
	1    4000 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3300 3500 3100
Connection ~ 3500 3100
Wire Wire Line
	3500 3100 3600 3100
Wire Wire Line
	4000 3300 4000 3100
Connection ~ 4000 3100
Wire Wire Line
	4000 3100 4050 3100
Wire Wire Line
	3500 3600 3500 3650
Wire Wire Line
	3500 3650 3750 3650
Wire Wire Line
	4000 3650 4000 3600
Wire Wire Line
	3750 3700 3750 3650
Connection ~ 3750 3650
Wire Wire Line
	3750 3650 4000 3650
$Comp
L power:GND #PWR011
U 1 1 61319C5C
P 3750 3700
F 0 "#PWR011" H 3750 3450 50  0001 C CNN
F 1 "GND" H 3755 3527 50  0000 C CNN
F 2 "" H 3750 3700 50  0001 C CNN
F 3 "" H 3750 3700 50  0001 C CNN
	1    3750 3700
	1    0    0    -1  
$EndComp
Text Notes 2950 2650 0    50   ~ 0
C_LOAD = 2 * (C_LOAD_CRYSTAL - C_STRAY)
Text Notes 2950 2750 0    50   ~ 0
C_LOAD = 2 * (12.5pF - 3pF)
NoConn ~ 6650 2950
NoConn ~ 6650 3050
NoConn ~ 6650 3150
NoConn ~ 6650 3250
NoConn ~ 6650 3350
NoConn ~ 6650 3450
NoConn ~ 6650 3850
NoConn ~ 6650 3950
NoConn ~ 6650 4250
NoConn ~ 5550 4250
NoConn ~ 5550 4150
NoConn ~ 5550 4050
NoConn ~ 5550 3850
NoConn ~ 5550 3750
NoConn ~ 5550 3650
$Comp
L Switch:SW_SPST SW1
U 1 1 61357F81
P 9700 1450
F 0 "SW1" V 9746 1548 50  0000 L CNN
F 1 "SW_SPST" V 9655 1548 50  0000 L CNN
F 2 "Other_Components:Tactile-Switch-SPST-SMD" H 9700 1450 50  0001 C CNN
F 3 "~" H 9700 1450 50  0001 C CNN
	1    9700 1450
	0    1    -1   0   
$EndComp
$Comp
L Switch:SW_SPST SW2
U 1 1 61358906
P 9700 3350
F 0 "SW2" V 9746 3448 50  0000 L CNN
F 1 "SW_SPST" V 9655 3448 50  0000 L CNN
F 2 "Other_Components:Tactile-Switch-SPST-SMD" H 9700 3350 50  0001 C CNN
F 3 "~" H 9700 3350 50  0001 C CNN
	1    9700 3350
	0    1    -1   0   
$EndComp
Text GLabel 9400 4850 0    50   Input ~ 0
SDA_D
Text GLabel 9400 4750 0    50   Input ~ 0
SCL_D
Wire Wire Line
	9400 4750 9550 4750
Wire Wire Line
	9550 4850 9400 4850
Text GLabel 6750 3650 2    50   Input ~ 0
SCL_D
Text GLabel 6750 3750 2    50   Input ~ 0
SDA_D
Wire Wire Line
	6750 3650 6650 3650
Wire Wire Line
	6750 3750 6650 3750
Wire Notes Line
	2700 850  7500 850 
Wire Notes Line
	7500 850  7500 4900
Wire Notes Line
	7500 4900 2700 4900
Wire Notes Line
	2700 4900 2700 850 
Wire Notes Line
	6200 5450 6200 7400
Wire Notes Line
	6200 7400 2700 7400
Wire Notes Line
	2700 7400 2700 5450
Wire Notes Line
	2700 5450 6200 5450
Wire Notes Line
	10600 4200 10600 5100
Wire Notes Line
	10600 5100 8450 5100
Wire Notes Line
	8450 5100 8450 4200
Wire Notes Line
	8450 4200 10600 4200
Wire Notes Line
	8450 5400 10600 5400
Wire Notes Line
	10600 5400 10600 6300
Wire Notes Line
	10600 6300 8450 6300
Wire Notes Line
	8450 6300 8450 5400
Wire Notes Line
	10250 900  10250 3900
Wire Notes Line
	10250 3900 8500 3900
Wire Notes Line
	8500 3900 8500 900 
Wire Notes Line
	8500 900  10250 900 
Wire Notes Line
	2200 850  2200 2100
Wire Notes Line
	2200 2100 800  2100
Wire Notes Line
	800  2100 800  850 
Wire Notes Line
	800  850  2200 850 
Text Notes 4950 850  0    79   ~ 0
MCU
Text Notes 1250 850  0    79   ~ 0
Power In
Text Notes 3950 5400 0    79   ~ 0
Temperature Sensor
Text Notes 9050 900  0    79   ~ 0
Input Buttons
Text Notes 9100 4200 0    79   ~ 0
OLED Connector
Text Notes 9150 5400 0    79   ~ 0
SWD Connector
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 612E7717
P 1250 4650
F 0 "H1" V 1204 4800 50  0000 L CNN
F 1 "MountingHole_Pad" V 1295 4800 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 1250 4650 50  0001 C CNN
F 3 "~" H 1250 4650 50  0001 C CNN
	1    1250 4650
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 612E8292
P 1250 4900
F 0 "H2" V 1204 5050 50  0000 L CNN
F 1 "MountingHole_Pad" V 1295 5050 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 1250 4900 50  0001 C CNN
F 3 "~" H 1250 4900 50  0001 C CNN
	1    1250 4900
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 612E8464
P 1250 5150
F 0 "H3" V 1204 5300 50  0000 L CNN
F 1 "MountingHole_Pad" V 1295 5300 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 1250 5150 50  0001 C CNN
F 3 "~" H 1250 5150 50  0001 C CNN
	1    1250 5150
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 612E87AB
P 1250 5400
F 0 "H4" V 1204 5550 50  0000 L CNN
F 1 "MountingHole_Pad" V 1295 5550 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 1250 5400 50  0001 C CNN
F 3 "~" H 1250 5400 50  0001 C CNN
	1    1250 5400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 612E8A35
P 950 5450
F 0 "#PWR015" H 950 5200 50  0001 C CNN
F 1 "GND" H 955 5277 50  0000 C CNN
F 2 "" H 950 5450 50  0001 C CNN
F 3 "" H 950 5450 50  0001 C CNN
	1    950  5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  5450 950  5400
Wire Wire Line
	950  4650 1150 4650
Connection ~ 950  4900
Wire Wire Line
	950  4900 950  4650
Wire Wire Line
	950  4900 1150 4900
Wire Wire Line
	1150 5150 950  5150
Connection ~ 950  5150
Wire Wire Line
	950  5150 950  4900
Wire Wire Line
	1150 5400 950  5400
Connection ~ 950  5400
Wire Wire Line
	950  5400 950  5150
Wire Notes Line
	2150 4500 2150 5700
Wire Notes Line
	2150 5700 750  5700
Wire Notes Line
	750  5700 750  4500
Wire Notes Line
	750  4500 2150 4500
Text Notes 900  4500 0    79   ~ 0
Mounting Holes
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 6133173F
P 9750 4650
F 0 "J1" H 9778 4626 50  0000 L CNN
F 1 "Conn_01x04_Female" H 9778 4535 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9750 4650 50  0001 C CNN
F 3 "~" H 9750 4650 50  0001 C CNN
	1    9750 4650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Female J2
U 1 1 61332348
P 9800 5900
F 0 "J2" H 9828 5926 50  0000 L CNN
F 1 "Conn_01x05_Female" H 9828 5835 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 9800 5900 50  0001 C CNN
F 3 "~" H 9800 5900 50  0001 C CNN
	1    9800 5900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
