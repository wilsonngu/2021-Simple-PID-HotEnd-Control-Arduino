# 2021-Simple-PID-HotEnd-Control-Arduino
Simple PID HotEnd Control Arduino used to complete my Electrical Design and Analysis of a PID
control for a 3D Filament Recycler Heater


# Intro 
Everyday households to various consumer products are generally made with plastics to and
contributes to a huge factor of pollution waste. Amongst plastic usage, 3D printers use plastics to
prototype, create, and try out new things for industry or hobby use. As plastics are a heavily used
material, an oncoming issue is how to recycle plastic that has been purposed beyond its life
cycle. 3D printers are used now more than ever with advanced technology making it easier for
the consumer with minimal “3D printing” knowledge. The question remains for left over scrap
pieces, broken PLA plastic parts and out of use 3D plastic material that cannot be reused due to
its deformed state or end of life cycle. 

# Objective
The main objective of this project is to design and analyze a PID
control for a 3D filament recycler heater in aiding as a solution for a sub-part of the 3D filament
recycler. The PID heater system comes with many steps, the factors such as the type of plastic
properties vary, the forms in how plastics can be recycled (pellets, solids, and powder), the
feedback & output system and capacity of plastic that can be accommodated are just a few in
tackling this system. To reuse solid plastic, it must go through a heater system to change its form
into a malleable phase that is then molded or printed into the user’s desire. Finding an efficient
PID heat system and optimizing it will achieve feasibility for the specific implementation in a 3D
filament recycler heater

#  Electrical Circuit for PID Control Heat System
![image](https://user-images.githubusercontent.com/20295767/148154171-08cd32dd-cfa8-4ddf-8516-e034786d47de.png)

# PID Summation 
![image](https://user-images.githubusercontent.com/20295767/148154260-d1dfdfa2-1e10-4914-a9ff-bfb5812338d7.png)

# PWM Heat Cartridge Circuit
![image](https://user-images.githubusercontent.com/20295767/148154299-4e9a179c-d888-4d94-9b11-feaf61d20748.png)

# Physical PID Heater Cartridge Circuit
![image](https://user-images.githubusercontent.com/20295767/148154327-f8879176-43f2-4160-984d-637ec041a5ac.png)
![image](https://user-images.githubusercontent.com/20295767/148154356-2420be79-34ef-49d2-8013-96f339116822.png)

# Heat System State machine & Analysis of the PID Heat System
![image](https://user-images.githubusercontent.com/20295767/148154388-40537392-9024-488f-9daf-2562a55d3f02.png)

# Start (1), End (2), and Overshoot (3) test log extraction of PID solution
![image](https://user-images.githubusercontent.com/20295767/148154408-bb6aa13d-4663-4c1e-9dc1-fa3ec4b4142c.png)

#  Ramp-up Temperature trendlines within 2:30 Minute marker
![image](https://user-images.githubusercontent.com/20295767/148154431-0e2fee15-b743-45ef-9678-c942e9b6b39c.png)

# Steady State PID Solution with slight Over & Under – shooting
![image](https://user-images.githubusercontent.com/20295767/148154460-f940df78-a9de-4270-9811-614403eff2c6.png)

# Conclusion
For designing a PID control for a 3D filament recycler heater, cartridge, cast-in,
immersion, coil heater types were assessed based on feasibility of cost, accessibility, and
implementation for melting re-used PLA plastics. Due to accessibility and common use of
cartridge heaters in 3D printer applications, the cartridge heater was chosen with a low cost and
provides 12 V heaters that both fit below project costs and voltage draw.

Further analysis concludes a circuit prototype controlled by an Arduino Uno to integrate
the PID control logic, a power budget, a heat distribution environment assessment, and a stateflow diagram of the PID digital system implementation. The ideal heat environment was deemed to be a screw barrel system as its function allows the heat cartridges to be placed around
the barrel and shredded plastics are pushed through the volume while being heated. The max
voltage draw of the cartridge heater was 12.0V and is under 24V within the project requirements
with higher rated mosfet, BJTs, and diodes for safety. The working circuit also shows all
physical components used to perform a ramp-up test for comparison of similar hot-end
specifications producing valid temperature data.

With PID Control logic used in the Arduino, a state-flow analysis was conducted to
produce a closed loop system and is proven to reach steady-state at 210 ℃ with slight
oscillations of around +/- 2 to 4 ℃. The closed loop PID system also includes ramp-up bench
tests with the PID solution compared with two similar market hot-end PID systems used within
3D printers. The PID solution was able to ramp-up 4.35% faster to 210 ℃ than the time limit of
2 minutes and 30 seconds and a slightly steeper ramp-up slope than both ROSTOCK &
CREALITY PID hot-ends. The PID Control solution met all the project requirements and
reached a steady state of the rated melted PLA temperature making this project design and
analysis solution successful.

