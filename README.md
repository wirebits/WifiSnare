# WifiSnare
It capture 2.4GHz wifi passwords using Evil-Twin attack.

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
1. Download Arduino IDE from <a href="https://www.arduino.cc/en/software">here</a> according to your Operating System.<br>
2. Install it.<br>
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
1. Download or Clone the Repository.
2. Open the folder and just double click on `WifiSnare.ino` file.
3. It opens in Arduino IDE.
4. Compile the code.
5. Select the correct board from the `Tools` then `Board` and then `ESP8266 Boards`.
6. It is generally `NodeMCU 1.0 (ESP-12E Module)`.
7. Select the port number of that board.
8. Upload the code.
9. After 1-2 minutes, an Access Point is created named `WifiSnare` whose password is `wifisnare`.
10. Connect to it.
11. After few seconds, a page automatically opens where ask to enter the exact SSID name to start attack on it.
12. Click on `Start Capture` button.
13. After that, it disconnects the access point and as well as an open access point created with the same SSID name.
14. Connect to that open wifi.
15. It show a page where it ask for password.
16. If password is right, then led of the board blink `3` times and after `2` seconds it close that open access point and restart the `WifiSnare` access point.
17. If password is wrong, then led of the board blink `2` times and back to the password page to enter password again.
18. Connnct again to that `WifiSnare` access point.
19. At the bottom, it shows the password of that SSID and a download button to save the password to the Phone/PC/Laptop in a `.txt` file.
20. Also, to attack on some other SSID, type the exact name and click on `Start Capture` button.
