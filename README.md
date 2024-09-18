![WifiSnare](https://github.com/user-attachments/assets/19673186-c069-45de-b324-15bd16aaa3aa)

# WifiSnare
It capture 2.4GHz WiFi passwords using Evil-Twin attack.

# Key Features
- Simple Setup.
- Set SSID easily for attack.
- LED Status for Right and Wrong Passwords.
- Download captured password on the system in a `.txt` file.

# Supported Board
- It supports NodeMCU ESP8266 Boards only.
- It supports 2.4GHz frequency only.
- If possible, use those NodeMCU ESP8266 boards which contain `CP2102` driver chipset.

# Setup
1. Download Arduino IDE from [here](https://www.arduino.cc/en/software) according to your Operating System.
2. Install it.
3. Go to `File` → `Preferences` → `Additional Boards Manager URLs`.
4. Paste the following link :
   
   ```
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
5. Click on `OK`.
6. Go to `Tools` → `Board` → `Board Manager`.
7. Wait for sometimes and search `esp8266` by `ESP8266 Community`.
8. Simply install it.
9. Wait for sometime and after that it is installed.
10. Restart the Arduino IDE.
11. Done!

# Install and Run
## Via Arduino IDE
1. Download or Clone the Repository.
2. Open the folder and just double click on `WifiSnare.ino` file.
3. It opens in Arduino IDE.
4. Compile the code.
5. Select the correct board from the `Tools` → `Board` → `ESP8266 Boards`.
   - It is generally `NodeMCU 1.0 (ESP-12E Module)`.
6. Select the correct port number of that board.
7. Upload the code.
8. After 1-2 minutes, an Access Point is created named `WiFiSnare` whose password is `wifisnare`.
9. Connect to it.
10. After few seconds, a page automatically opens where ask to enter the exact SSID name to start attack on it.
11. Click on `Start Capture` button.
12. After that, it disconnects the access point and as well as an open access point created with the same SSID name.
13. Connect to that open WiFi.
14. It show a page where it ask for password.
15. Enter the password and click on `Sign Up` button.
    - If password is wrong, then led of the board blink `2` times and back to the password page to enter password again.
    - If password is right, then led of the board blink `3` times and after `2` seconds it close that open access point and restart the `WiFiSnare` access point.
16. Connnct again to that `WiFiSnare` access point.
17. At the bottom, it shows the password of that SSID and a download button to save the password to the Phone/PC/Laptop in a `.txt` file.
18. Also, to attack on some other SSID, type the exact name and click on `Start Capture` button.
