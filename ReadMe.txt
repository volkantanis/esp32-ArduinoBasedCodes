Read Me:

Kindly note to let the board to get autoconnect and fetch previous settings upon restart of the ESP32 board,
All the configuration settings are saved in "Congfig.txt" file in SPIFFS .

Work-flow ;

Upon start of board, 
-> pinMode configuration for button pinMode
-> attach interrupt for button pinMode
-> initialise serial at baudrate 115200 (as per your requirement you can do these settings)
-> initialise SPIFFS 
-> read Config.txt file to fetch if some previous configuration are present

-> If previous configurations are ok, and button is not pressed , be in STA mode using previous configuration.
-> If user wants to do some configuration changes, then button is pressed and ISR makes buttonState = 1.
-> If buttonState=1, switch to AP Mode -

-> After switching to AP Mode user can access webpage using 192.168.4.1
-> The configuration menu is displayed, user can select any configuration as per requirement
-> User is then forwarded to respective configuration page on which he can do settings and click save configuration
-> After doing save configurations , required Strings are updated into code 
-> Then user has option to either return to configuration menu page to do other settings 
    or to close the page if all required settings are done.
	#Kindly note to save settings to file, user must click close button after doing all the required changes
	
-> At any stage on webpage if user want to getback to STA mode, he should click the close button on webpage


-> Thus even if board restarts , the configuration settings are remained sabed in Config.txt File.

-> Again in STA Mode , if user wants to do some settings, the button is pressed and board comes into AP Mode
   where user can do respective settings as mentioned above. Until these settings are done successfully by clicking close button,
   board remains in AP Mode.
   Also if settings are done and close button is clicked with clicking save configuration button , then these settings are not saved.
   So, to save the settings click save configuration button. Then if all settings are done and you want to get back to STA Mode,
   click close button.
 
