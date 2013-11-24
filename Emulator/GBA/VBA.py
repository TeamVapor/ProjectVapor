#!/usr/bin/python
import argparse
import os
## FILL IN EMULATOR PATH (Absolute)
EmulatorPath = "/usr/bin/VisualBoyAdvance"
## FILL IN EMULATOR ARGUMENTS
Arguments = "-c /etc/VisualBoyAdvance.cfg"
## FILL IN EMULATOR SETTINGS FILE PATH (Absolute)
SettingsFile = "/etc/VisualBoyAdvance.cfg"
 
## Define Settings to feed to the emulator when read from the file
AvailSettingsList = {
##Controller Settings
"Joy0_Left":## Name of the setting the file reader will find
	("Controller",## Category for the setting to be displayed in.
	"D-Pad Left",## Name for the gui to display.
	{"CTRL":"CTRL"}),## Controlmap input type
"Joy0_Right":("Controller","D-Pad Right",{"CTRL":"CTRL"}), 
"Joy0_Up":("Controller","D-Pad UP",{"CTRL":"CTRL"}), 
"Joy0_Down":("Controller","D-Pad Down",{"CTRL":"CTRL"}), 
"Joy0_A":("Controller","A Button",{"CTRL":"CTRL"}), 
"Joy0_B":("Controller","B Button",{"CTRL":"CTRL"}), 
"Joy0_L":("Controller","L Bumper",{"CTRL":"CTRL"}), 
"Joy0_R":("Controller","R Bumper",{"CTRL":"CTRL"}), 
"Joy0_Start":("Controller","Start Button",{"CTRL":"CTRL"}), 
"Joy0_Select":("Controller","Select Button",{"CTRL":"CTRL"},True), 
"Joy0_Speed":("Controller","Speed Button",{"CTRL":"CTRL"}), 
"Joy0_Capture":("Controller","Capture Button",{"CTRL":"CTRL"}),  
"Motion_Left":("Controller","Motion Left Direction",{"CTRL":"CTRL"}), 
"Motion_Right":("Controller","Motion Right Direction",{"CTRL":"CTRL"}), 
"Motion_Up":("Controller","Motion Up Direction",{"CTRL":"CTRL"}), 
"Motion_Down":("Controller","Motion Down Direction",{"CTRL":"CTRL"}),
 ##Video
"frameSkip":
	("Video",## Category Type
	"Frame Skip",##Regular expression to constrain setting to integer type
	{"INT 0-5x1":"INT 0-5x1"}),## Data btween 0 and five 
"gbFrameSkip":
	("Video","Gameboy Frame Skip",
	{"INT 0-5x1":"INT 0-5x1"}),
"video":
	("Video","Anti-Aliasing",
	{"1x":"0", 
	"2x":"1", 
	"3x":"2", 
	"4x":"3"}), 
"fullscreen":
	("Video","Fullscreen",
	{"Enabled":"1", 
	"Disabled":"0"}), 
"disableMMX":
	("Video","MMX Support",
	{"Enabled":"0", 
	"Disabled":"1"}), 
"useBios":(
	"Video","Use Bios",
	{"Enabled":"1", 
	"Disabled":"0"}), 
"biosFile":
	("Video","Bios File Path",
	{"DIR":"DIR"}),## Indicates the input is a directory type 
"filter":
	("Video", "video filter",
	{"No Filter"		:"0", 
	"TV Mode"		:"1", 
	"2xSaI"			:"2", 
	"Super 2xSaI"		:"3", 
	"Super Eagle"		:"4", 
	"Pixelate"		:"5", 
	"Motion Blur"		:"6",
	"AdvanceMAME Scale2x"	:"7", 
	"Simple 2x"		:"8", 
	"Bilinear"		:"9",
	"Bilinear Plus"		:"A", 
	"hq2x"			:"B", 
	"lq2x"			:"C"}), 
"disableStatus":
	("Emulator","Status messages",
	{"Enabled" : "1", 
	"Disabled" : "0"}), 
"borderOn":
	("Emulator","Gameboy Border",
	{"Enabled" : "1", 
	"Disabled" : "0"}), 
"emulatorType":
	("Emulator","Gameboy Type",
	{"Automatic"		:"0", 
	"Gameboy"		:"1",	
	"Super Gameboy"		:"2", 
	"Gameboy Color"		:"3",
	"Super Gameboy 2"	:"4",  
	"Gameboy Advance" 	:"5"}),
"colorOption":
	("Video",
	"Washed Colors",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}), 
"captureFormat":
	("Emulator","Save Screenshots as ",
	{"PNG" : "0",
	"BMP"  : "1"}),
"soundQuality":
	("Sound","Sound Quality",
	{"44Khz"	:"1",
	"22Khz"		:"2", 
	"11Khz"		:"4"}),
"soundEcho":
	("Sound","Sound Echo",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}),
"soundLowPass":
	("Sound","Low Pass Filter",
	{"Enabled"	:"1", 	
	"Disabled"	:"0"}), 
"soundReverse":
	("Sound","Reverse Stereo",
	{"Enabled"	:"1",
	 "Disabled"	:"2"}),
"saveType":
	("Emulator","Save Type",
	{"automatic"	:"0",
	"EEPROM"	:"1", 
	"SRAM"		:"2", 
	"Flash"		:"3", 
	"EEPROM+Sensor"	:"4", 
	"None"		:"5"}),
"flashSize":
	("Emulator","Flash Size",
	{"64K" 	:"0", 
	"128K" 	:"1"}),
"soundVolume":
	("Sound","Sound Volume",
	{"1x"	:"0", 
	"2x"	:"1", 	
	"3x"	:"2", 
	"4x"	:"3"}),
"ifbType":("Video","Interframe Blending",
	{"None"		:"0", 
	"Motion Blur"	:"1", 
	"Smart"		:"2"}),
"showSpeed":
	("Emulator","Show emulation speed",
	{"None"		:"0", 
	"Percent"	:"1", 
	"Detailed"	:"2"}),
"showSpeedTransparent":
	("Emulator" ,"Show speed in transparent mode",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}),
"autoFrameSkip":
	("Video","Auto-Frameskip",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}),
"throttle":
	("Emulator","Throttle",
	{"NUMERIC 0-1000x5":"NUMERIC 0-1000x5"}),
"pauseWhenInactive":
	("Emulator","Pause Emulator when window is inactive",
	{"Enabled"	:"1",
	"Disabled"	:"0"}),
"agbPrint":
	("Emulator","AGBPrint support",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}),
"rtcEnabled":
	("Emulator","GBA RTC support",
	{"Enabled"	:"1", 
	"Disabled"	:"0"}),
"soundOff":
	("Sound","Sound",
	{"Enabled" : "0", 
	"Disabled" : "1"}),
"borderAutomatic":
	("Emulator","automatic Super Gameboy border",
	{"Enabled"	:"1", 
	"Disabled"	:"0"})
}
## Emulator Settings Hash table
settingsHash = dict({})
################################################################################
## AddSetting
## INPUT ##
##  Take a string of the category name, a string of the name of the setting, a
## string of the current value, and a string list of available Settings, and a 
## 1 or 0 to indicate the Input Type Modifier.
## Process ##
##  Add a setting to the emulator settings hash if the setting name does not
## already exist in the emulator settings hash table.
################################################################################
def AddSetting(Category, Name, CurrentSetting, AvailableSettings):
    if Category not in settingsHash:
        settingsHash[Category] = {}
    if Name not in settingsHash[Category]:
        settingsHash[Category][Name] = (CurrentSetting, AvailableSettings)
################################################################################
## UpdateSetting
## INPUT ##
##  Take a string of the category name, a string of the name of the setting, and
## a string of the new current value.
## Process ##
##  Updates the current value of a specific setting in category.
################################################################################
def UpdateSetting (Category, Name, NewValue):
    if Category in settingsHash:
        if Name in settingsHash[Category]:
            settingsHash[Category][Name] = (NewValue, settingsHash[Category][Name][1])


def main():
    parser = argparse.ArgumentParser(description='VBA Emulator and Settings Interface')
    parser.add_argument('-c', metavar='command', dest='command', default='l',## Defaults to load
                       help='Load or Save (l,s) (default is l)')
    parser.add_argument('-t', metavar='type',dest='type', default='l',## Defaults to Launcher
                       help='Launch or Settings (l,s) (default is l)')

    args = parser.parse_args()


    if(args.command[0] == 'l'): # if loading Settings info
        if(args.type[0] == 'l'):
            print("$%$DUMP&LAUNCHERDATA")
            print("EMULATORPATH=" + "\"" + EmulatorPath + "\"")
            print("ARGUMENTS=" +  Arguments )
            print("$&$")
        elif(args.type[0] == 's'):## load settings
            print("$%$DUMP&ALLSETTINGS")
            with open(SettingsFile, 'r') as fin:## Open File For Read
		data = ""
	    	for line in fin:
			if(line.startswith("#")):
				data+=line
			elif (len(line) > 2):
				index = line.replace("\n","").split('=')[0]
				cValue = line.replace("\n","").split('=')[1]
				if index in AvailSettingsList:
					category = AvailSettingsList[index][0]
					name = AvailSettingsList[index][1]
					avail = AvailSettingsList[index][2]
					AddSetting(category, name, cValue, avail)
					data = ""			
	    fin.closed
	    fin.close()
            print(settingsHash)
            print("$&$")
        else:
            print("Invalid Type specified")

    elif(args.command[0] == 's'): #If Saving Settings
        
        print("saving ", args.type) 
    else:
        print("Invalid command Specified!")
main()
