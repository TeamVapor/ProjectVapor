#!/usr/bin/python
import argparse
import os
## FILL IN EMULATOR PATH (Absolute)
EmulatorPath = "VBA"
## FILL IN EMULATOR ARGUMENTS
Arguments = "-c VisualBoyAdvance.cfg"
## FILL IN EMULATOR SETTINGS FILE PATH (Absolute)
SettingsFile = "Emlulator/GBA/VisualBoyAdvance.cfg"

def main():
    parser = argparse.ArgumentParser(description='VBA Emulator and Settings Interface')
    parser.add_argument('-c', metavar='command', dest='command', default='l',## Defsuls to load
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
            f = open(SettingsFile, "r", encoding="utf-8")## Open File
	    
            
            open.close()
            print("$&$")
        else:
            print("Invalid Type specified")

    elif(args.command[0] == 's'): #If Saving Settings
        
        print("saving ", args.type) 
    else:
        print("Invalid command Specified!")



main()
