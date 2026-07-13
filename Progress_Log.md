# Progress Log

This log documents the development of the project, including each major stage, the decisions I made, the challenges I encountered, and the thought process behind my solutions.

## Stage 1 (Where I am at before recording into the progression log)

#### What I have:

- ESP32 Microcontroller (Mind of hardware)
- RGB LED (Indicates mode)
- 2 Buttons (Used for Changing LED colour and another used for Dealing with clock functions)
- Potentiometer (Used as a dial for controlling Time set and brightness of LED)
- Passive buzzer (For feedback loop when buttons pressed and for alarm sounds)

#### Code: 
https://github.com/NormalSoul/ESP32-Desk-Companion/commit/ea43b75de5dbdddb6e390ee3b9066d2f14af8a38

#### Initial functionality Video:
<details>
<summary>Video Demonstration of Stage 1</summary>
https://github.com/user-attachments/assets/960af775-9e7a-4d3d-9713-fba8393d7be6
</details>

#### Problems Faced and Next steps:
- Potentiometer is connected to both Led brightness and Timer duration so when one is modified the other is effected and preset Eg when brightness is set to max timer is set to max when timer is set to 5 mins brightness is also diminished 

- Need to allow for stop watch to be implemented and for Alarm clock to bet set 

- Buttons are hard to access need to find a work around such as implementing a keypad 
