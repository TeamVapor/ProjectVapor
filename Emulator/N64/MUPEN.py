import argparse

## FILL IN EMULATOR PATH (Absolute)
EmulatorPath = "mupen64plus"
## FILL IN EMULATOR ARGUMENTS
Arguments = ""


def main():
    parser = argparse.ArgumentParser(description='ZSNES Emulator and Settings Interface')
    parser.add_argument('-c', metavar='command', dest='command', default='l',
                       help='Load or Save (l,s) (default is l)')
    parser.add_argument('-t', metavar='type',dest='type', default='l',
                       help='Launch or Settings (l,s) (default is l)')

    args = parser.parse_args()


    if(args.command[0] == 'l'): # if loading info
        if(args.type[0] == 'l'):
            print("$%$DUMP&LAUNCHERDATA")
            print("EMULATORPATH=" + "\"" + EmulatorPath + "\"")
            print("ARGUMENTS=" + "\""+ Arguments + "\"" )
            print("$&$")
        elif(args.type[0] == 's'):
            print("$%$DUMP&ALLSETTINGS")
            print("$&$")
        else:
            print("Invalid Type specified")

    elif(args.command[0] == 's'): #if loading settings info
        print("saving ", args.type) 
    else:
        print("Invalid command Specified!")



main()
