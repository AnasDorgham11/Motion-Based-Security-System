# Motion-Based Security System
Motion-Based Security System (ATmega32A)


## System Overview
The Motion-Based Security System is designed to detect and log motion events using passive infrared (PIR) sensors. The system aims to provide:
- Reliable motion detection
- Redundancy for enhanced reliability
- User-friendly interface for viewing logged events

## System Components

1. **PIR Sensors (2)**
   - Detect motion within their respective fields of view by sensing infrared radiation changes
   - Two sensors provide redundancy, ensuring motion detection even if one sensor fails

2. **LED Indicator**
   - Blinks to provide a visual alert when motion is detected by either sensor

3. **Button for Data Retrieval**
   - Allows management to retrieve and display stored motion detection data

4. **LCD Display**
   - Displays:
     - Number of motion detections
     - Time each detection occurred

5. **ATmega32A Microcontroller**
   - System's central processing unit that:
     - Handles sensor inputs
     - Manages data storage
     - Controls output to the display

## System Operation

### Motion Detection
- When either PIR sensor detects motion:
  - Microcontroller activates blinking LED (visual alert)
  - Current time is recorded and stored in EEPROM

### Data Retrieval
- Pressing the button triggers:
  - Display of total motion detection count
  - Display of corresponding detection times on LCD
- Provides easy review of intrusion history

### Redundancy for Reliability
- Dual PIR sensors ensure continuous operation:
  - If one sensor fails, the other remains operational
  - Enhances overall system reliability
