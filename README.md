# Admin System

This is the administration system that has a lot of opportunities and very simple and clear in use at the same time.

## Features
* Multi-level spectate system
* Panel for administrators when you click on a player in Tab
* General admin panel with items depending on the level
* Ability to specify several players in one command at once
* Messages of administration's actions are displayed only for administrators and the specified player
* Interaction with RCon (logged into RCon become administrators)
* Ability to cancel the last typed command
* Dynamic panel with suspected players

## Commands
Some commands allow you to enter keywords instead of parameters, for example, "/spec off" will do the same as the command "/specoff".  
Also you can omit the parameters in some commands, so then the command will work on the one who typed it.  
The commands will work on any cmd processor! (except rCmd).

`/report` *[text]* - send an question/complaint to administration

#### Level 1
`/achat` *[text]* - Admin chat  
`/ahelp` - Help with admin commands  
`/showstats` *[id]* - Show player's statistics  
`/answer` *[id]* *[text]* - Respond on player's report  
`/apanel` - Admin panel with all available commands  
`/admins` - List of administrators online  
`/eject` *[id]* - Remove player from vehicle

#### Level 2
`/spec` *[id]* - Begin spectate player  
`/spawnveh` *[vehicle id]* - Teleport vehicle to respawn  
`/(un)mute` *[id]* *[time]* *[reason]* - Mute/unmute player  
`/asay` *[text]* - Message: `Administrator: [text]`  
`/warn` *[id]* *[reason]* - Give warn to player  
`/kick` [id] *[reason]* - Kick player from the server  
`/(un)freeze` *[id]* - Freeze/unfreeze player  
`/slap` *[id]* *[reason]* - Slap player  
`/goto` *[id]* - Teleport to player

#### Level 3
`/suspectlist` - List of suspected players  
`/gethere` *[id]* - Teleport player to yourself  
`/gotoveh` *[vehicle id]* - Teleport to vehicle  
`/ban` *[id]* *[reason]*- Ban player's account  
`/gmtest` *[id]* - Check for infinite health  
`/spawn` *[id]* - Teleport player to respawn  
`/unwarn` *[id]* - Remove warn from player  
`/banip` *[IP]* - Block IP address  
`/cc` - Clear chat

#### Level 4
`/sethealth` *[id]* *[health]* - Set health to player  
`/setarmour` *[id]* *[armour]* - Set armour to player  
`/setmoney` *[id]* *[money]* - Set money to player  
`/setskin` *[id]* *[skin id]* - Set skin to player  
`/setint` *[id]* *[interior]* - Set interior to player  
`/setvw` *[id]* *[number]* - Set virtual world to player  
`/giveweapon` *[id]* *[weapon]* *[ammo]* - Give weapon to player  
`/repairveh` *[vehicle id]* - Repair vehicle  
`/unbanip` *[IP]* - Unblock IP address

#### Level 5
`/getall` - Teleport all to yourself  
`/setweather` *[number]* - Set weather  
`/settime` *[hour]* - Set time of day  
`/destroyveh` *[vehicle id]* - Destroy vehicle  
`/veh` *[vehicle id]* *[color 1]* *[color 2]* - Create vehicle  
`/sban` *[id]* - Silent ban  
`/skick` *[id]* - Silent kick

## How to install
Simply install to your project:
```bash
sampctl package install NexiusTailer/Admin-System
```

Include in your code and begin using the library:
```pawn
#include <admsys>
```

If you want to add admin rights saving after disconnection, use SetPlayerAdminLevel function (see "[Functions](README.md#functions)"), add it into your account load and GetPlayerAdminLevel function into account save.

If you want to add some actions when a player gets ban, kick or warn, add publics OnPlayerBan, OnPlayerKick and OnPlayerWarn in your gamemode.

If you want to see anyone in the panel with suspected players, use AddPlayerInSuspectList function to add the player to the list, and RemovePlayerFromSuspectList to remove.

## Functions
If you have an accounts system, some functions below will be useful.

#### public OnPlayerBan(playerid, gaveid, bool:sban)
```
Parameters:
playerid - The ID of the player who will be banned
gaveid - The ID of the player who gave a ban
sban - If the ban is silent (true) or not (false)

This callback does not return any values
```

#### public OnPlayerKick(playerid, gaveid, bool:skick)
```
Parameters:
playerid - The ID of the player who will be kicked
gaveid - The ID of the player who gave a kick
skick - If the kick is silent (true) or not (false)

This callback does not return any values
```

#### public OnPlayerWarn(playerid, gaveid, count)
```
Parameters:
playerid - The ID of the player who will be warned
gaveid - The ID of the player who gave a warn
count - The amount of warnings that 'playerid' have at the moment (including last given)

This callback does not return any values
```

#### IsPlayerAdminEx(playerid, lvl = 1)
```
Parameters:
playerid - The ID of the player whose admin level we want to check
lvl - Player's admin level we check (if not specified, will be equal to 1)

Returns 1 if the player have the admin level equal to or greater than specified in the 'lvl'
Returns 0 if the player does not have this admin level
```

#### GetPlayerAdminLevel(playerid)
```
Parameters:
playerid - The ID of the player whose admin level we want to get

Returns the admin level of the specified player
```

#### SetPlayerAdminLevel(playerid, lvl)
```
Parameters:
playerid - The ID of the player for which you need to set the admin level
lvl - The admin level you want to set to the player

Returns 1 if the function executed successfully
Returns 0 if the specified player is not connected
Returns -1 if the level is entered incorrectly
```

#### SendMessageToAdmins(lvl, color, const msg[])
```
Parameters:
lvl - The admin level required to receive this message
color - The color of the message which will be sent
msg - The string with the message

Always returns 1
```

#### GetPlayerMuteTime(playerid)
```
Parameters:
playerid - The ID of the player whose remaining mute time you want to know

Returns the remained time of mute for the specified player in seconds (0 - is not muted)
```

#### SetPlayerMuteTime(playerid, time)
```
Parameters:
playerid - The ID of the player for which you need to set the mute time
time - The mute time (in seconds) you need to set to the player

Returns 1 if the function executed successfully
Returns 0 if the specified player is not connected
Returns -1 if the time is entered incorrectly
```

#### AddPlayerInSuspectList(playerid)
```
Parameters:
playerid - The ID of the player which you want to add to the list of suspected

Returns 1 if the function executed successfully
Returns 0 if the specified player is not connected
```

#### RemovePlayerFromSuspectList(playerid)
```
Parameters:
playerid - The ID of the player which should be removed from the list of suspected

Returns 1 if the function executed successfully
Returns 0 if the specified player is not connected
```

#### UpdateSuspectList()
```
Returns the number of removed players from the list
```

## Thanks
DeimoS - ideas and suggestions  
Magic_York, Vitalik_Gonsor, RobertoYork, TheHero, Error4o4 - testing
