//Admin System by Nexius v2.8

#if defined _admsys_included
	#endinput
#endif
#define _admsys_included

#include <a_samp>

#define	ADMSYS_VERSION						"2.8"

#if !defined ADMSYS_SHOW_KILL_LIST_FOR_ADM
	#define ADMSYS_SHOW_KILL_LIST_FOR_ADM		true
#endif

#if !defined ADMSYS_SEND_ACTION_MSGS_TO_ALL
	#define ADMSYS_SEND_ACTION_MSGS_TO_ALL		false
#endif

#if !defined ADMSYS_SEND_CONNECT_MSGS_TO_ADM
	#define ADMSYS_SEND_CONNECT_MSGS_TO_ADM		false
#endif

#if ADMSYS_SEND_CONNECT_MSGS_TO_ADM
	#if !defined ADMSYS_CONNECT_MSG_COLOR
		#define ADMSYS_CONNECT_MSG_COLOR	0xA9C4E4FF
	#endif
#endif

#if !defined ADMSYS_DEFAULT_COLOR
	#define ADMSYS_DEFAULT_COLOR			0xFFFFFFFF
#endif

#if !defined ADMSYS_ADM_CHAT_COLOR
	#define ADMSYS_ADM_CHAT_COLOR			0x88AA62FF
#endif

#if !defined ADMSYS_ADM_ACTION_COLOR
	#define ADMSYS_ADM_ACTION_COLOR			0x2587CEFF
#endif

#if !defined ADMSYS_REPORT_COLOR
	#define ADMSYS_REPORT_COLOR				0xB9C9BFFF
#endif

#if !defined ADMSYS_CMD_HELPER_COLOR
	#define ADMSYS_CMD_HELPER_COLOR			0xD2D2D2FF
#endif

#if !defined ADMSYS_ERROR_COLOR
	#define ADMSYS_ERROR_COLOR				0xBB9999FF
#endif

#if !defined ADMSYS_MAX_WARNS
	#define ADMSYS_MAX_WARNS				2
#endif

#if !defined ADMSYS_MAX_TAB_INPUT
	#define ADMSYS_MAX_TAB_INPUT			8
#endif

#if !defined ADMSYS_MAX_SUSPECTS_IN_TABLE
	#define ADMSYS_MAX_SUSPECTS_IN_TABLE		8
#endif

#if !defined ADMSYS_MAX_GIVE_PLAYERS_IN_CMD
	#define ADMSYS_MAX_GIVE_PLAYERS_IN_CMD		3
#endif

#define admsys_isnull(%0) ((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
#define admsys_fpublic%0(%1) forward %0(%1); public %0(%1)

#if !defined CMD
	#define CMD:%0(%1) forward cmd_%0(%1); public cmd_%0(%1)
#endif

static const AdmSys1LvlCmds[][] =
{
	"Level 1:\n",
	"/achat [text] - Admin chat\n",
	"/ahelp - Help with admin commands\n",
	"/showstats [id] - Show player's statistics\n",
	"/answer [id] [text] - Respond on player's report\n",
	"/apanel - Admin panel with all available commands\n",
	"/admins - List of administrators online\n",
	"/eject [id] - Remove player from vehicle"
},

AdmSys2LvlCmds[][] =
{
	"Level 2:\n",
	"/spec [id] - Start spectate player\n",
	"/spawnveh [vehicle id] - Teleport vehicle to respawn\n",
	"/(un)mute [id] [time] [reason] - Mute/unmute player\n",
	"/asay [text] - Message: 'Administrator: [text]'\n",
	"/warn [id] [reason] - Give warn to player\n",
	"/kick [id] [reason] - Kick player from the server\n",
	"/(un)freeze [id] - Freeze/unfreeze player\n",
	"/slap [id] [reason] - Slap player\n",
	"/goto [id] - Teleport to player"
},

AdmSys3LvlCmds[][] =
{
	"Level 3:\n",
	"/suspectlist - List of suspected players\n",
	"/gethere [id] - Teleport player to yourself\n",
	"/gotoveh [vehicle id] - Teleport to vehicle\n",
	"/gotopos [x] [y] [z] - Teleport to position\n",
	"/ban [id] [reason] - Ban player's account\n",
	"/gmtest [id] - Check for infinite health\n",
	"/spawn [id] - Teleport player to respawn\n",
	"/unwarn [id] - Remove warn from player\n",
	"/banip [IP] - Block IP address\n",
	"/cc - Clear chat"
},

AdmSys4LvlCmds[][] =
{
	"Level 4:\n",
	"/sethealth [id] [health] - Set health to player\n",
	"/setarmour [id] [armour] - Set armour to player\n",
	"/setmoney [id] [money] - Set money to player\n",
	"/givemoney [id] [money] - Give money to player\n",
	"/setscore [id] [score] - Set score to player\n",
	"/setskin [id] [skin id] - Set skin to player\n",
	"/setint [id] [interior] - Set interior to player\n",
	"/setvw [id] [vw] - Set virtual world to player\n",
	"/giveweapon [id] [weapon] [ammo] - Give weapon to player\n",
	"/repairveh [vehicle id] - Repair vehicle\n",
	"/unbanip [IP] - Unblock IP address"
},

AdmSys5LvlCmds[][] =
{
	"Level 5:\n",
	"/getall - Teleport all to yourself\n",
	"/setweather [number] - Set weather\n",
	"/settime [hour] - Set time of day\n",
	"/destroyveh [vehicle id] - Destroy vehicle\n",
	"/veh [vehicle id] [color 1] [color 2] - Create vehicle\n",
	"/sban [id] - Silent ban\n",
	"/skick [id] - Silent kick"
};

enum
{
	ADMSYS_DIALOG_TAB_PANEL = 8192,
	ADMSYS_DIALOG_ANSWER,
	ADMSYS_DIALOG_MUTE_TIME,
	ADMSYS_DIALOG_MUTE,
	ADMSYS_DIALOG_WARN,
	ADMSYS_DIALOG_KICK,
	ADMSYS_DIALOG_SLAP,
	ADMSYS_DIALOG_BAN,
	ADMSYS_DIALOG_SET_HEALTH,
	ADMSYS_DIALOG_SET_ARMOUR,
	ADMSYS_DIALOG_SET_MONEY,
	ADMSYS_DIALOG_GIVE_MONEY,
	ADMSYS_DIALOG_SET_SCORE,
	ADMSYS_DIALOG_CHANGE_SKIN,
	ADMSYS_DIALOG_SET_INT,
	ADMSYS_DIALOG_SET_VW,
	ADMSYS_DIALOG_GIVE_WEAPON,
	ADMSYS_DIALOG_GIVE_WEAPON_AMMO,
	ADMSYS_DIALOG_AHELP_LVL_1,
	ADMSYS_DIALOG_AHELP_LVL_2,
	ADMSYS_DIALOG_AHELP_LVL_3,
	ADMSYS_DIALOG_AHELP_LVL_4,
	ADMSYS_DIALOG_AHELP_LVL_5,
	ADMSYS_DIALOG_STATS,
	ADMSYS_DIALOG_APANEL,
	ADMSYS_DIALOG_ACHAT,
	ADMSYS_DIALOG_SPAWN_VEH,
	ADMSYS_DIALOG_ASAY,
	ADMSYS_DIALOG_GOTO_VEH,
	ADMSYS_DIALOG_GOTO_POS,
	ADMSYS_DIALOG_BAN_IP,
	ADMSYS_DIALOG_REPAIR_VEH,
	ADMSYS_DIALOG_UNBAN_IP,
	ADMSYS_DIALOG_SET_WEATHER,
	ADMSYS_DIALOG_SET_TIME,
	ADMSYS_DIALOG_DESTROY_VEH,
	ADMSYS_DIALOG_CREATE_VEH,
	ADMSYS_DIALOG_CREATE_VEH_COL_1,
	ADMSYS_DIALOG_CREATE_VEH_COL_2,
	ADMSYS_DIALOG_ADMINS,
	ADMSYS_DIALOG_SUSPECT_LIST,
	ADMSYS_DIALOG_GMTEST
}

enum asInfo
{
	Float:asGmTestHP,
	Float:asGmTestAR,
	Float:asLastAngle,
	Float:asLastPos[3],
	Float:asLastFloatData,
	asInput[ADMSYS_MAX_TAB_INPUT],
	asInput2[ADMSYS_MAX_TAB_INPUT],
	asLastWeapon[13],
	asLastIntData[2],
	asLastAmmo[13],
	asLastActionID,
	asLastAction,
	asLastSpecID,
	asGmTestID,
	asAdminLvl,
	asTabPanel,
	asMuteTime,
	asWarns,
	asSpecID,
	asLastVW,
	asLastInt,
	asUpdTimer,
	bool:asLastSpec,
	bool:asIsSpawned,
	bool:asIsDead,
	bool:asGmTest
}

static
	AdmSysInfo[MAX_PLAYERS][asInfo],
	SuspectList[ADMSYS_MAX_SUSPECTS_IN_TABLE] = {INVALID_PLAYER_ID, ...},

	AdmSys1LvlCmdsStr[293],
	AdmSys2LvlCmdsStr[398],
	AdmSys3LvlCmdsStr[393],
	AdmSys4LvlCmdsStr[516],
	AdmSys5LvlCmdsStr[262];

forward OnPlayerBan(playerid, gaveid, bool:sban);
forward OnPlayerKick(playerid, gaveid, bool:skick);
forward OnPlayerWarn(playerid, gaveid, count);

public OnGameModeInit()
{
	print(" ");
	print(" Admin System by Nexius loaded!");
	printf(" Version: %s", ADMSYS_VERSION);
	print(" ");
	for(new i; i < sizeof AdmSys1LvlCmds; i++) strcat(AdmSys1LvlCmdsStr, AdmSys1LvlCmds[i]);
	for(new i; i < sizeof AdmSys2LvlCmds; i++) strcat(AdmSys2LvlCmdsStr, AdmSys2LvlCmds[i]);
	for(new i; i < sizeof AdmSys3LvlCmds; i++) strcat(AdmSys3LvlCmdsStr, AdmSys3LvlCmds[i]);
	for(new i; i < sizeof AdmSys4LvlCmds; i++) strcat(AdmSys4LvlCmdsStr, AdmSys4LvlCmds[i]);
	for(new i; i < sizeof AdmSys5LvlCmds; i++) strcat(AdmSys5LvlCmdsStr, AdmSys5LvlCmds[i]);
	SetTimer("UpdateMuteTime", 1000, 1);
	#if defined admsys_OnGameModeInit
		return admsys_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit admsys_OnGameModeInit
#if defined admsys_OnGameModeInit
	forward admsys_OnGameModeInit();
#endif

public OnGameModeExit()
{
	print(" ");
	print(" Admin System by Nexius unloaded!");
	print(" ");
	#if defined admsys_OnGameModeExit
		return admsys_OnGameModeExit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit admsys_OnGameModeExit
#if defined admsys_OnGameModeExit
	forward admsys_OnGameModeExit();
#endif

public OnPlayerConnect(playerid)
{
	AdmSysInfo[playerid][asWarns] = 0;
	AdmSysInfo[playerid][asMuteTime] = 0;
	AdmSysInfo[playerid][asAdminLvl] = 0;
	AdmSysInfo[playerid][asUpdTimer] = -1;
	AdmSysInfo[playerid][asSpecID] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asLastSpecID] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asGmTestID] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asIsSpawned] = false;
	AdmSysInfo[playerid][asIsDead] = false;
	AdmSysInfo[playerid][asGmTest] = false;
	#if ADMSYS_SEND_CONNECT_MSGS_TO_ADM
		new strtmp[78], sname[MAX_PLAYER_NAME + 1], sip[16];
		GetPlayerName(playerid, sname, sizeof sname);
		GetPlayerIp(playerid, sip, sizeof sip);
		format(strtmp, sizeof strtmp, "[IP: %s] %s[%d] has joined the server", sip, sname, playerid);
		SendMessageToAdmins(1, ADMSYS_CONNECT_MSG_COLOR, strtmp);
	#endif
	#if defined admsys_OnPlayerConnect
		return admsys_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect admsys_OnPlayerConnect
#if defined admsys_OnPlayerConnect
	forward admsys_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	AdmSysInfo[playerid][asLastAction] = 0;
	KillTimer(AdmSysInfo[playerid][asUpdTimer]);
	#if defined foreach
		foreach(new i : Player)
		{
	#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		{
			if(!IsPlayerConnected(i)) continue;
	#endif
		if(AdmSysInfo[i][asSpecID] == playerid)
		{
			SendClientMessage(i, ADMSYS_ERROR_COLOR, "Player has disconnected");
			StopSpectating(i);
		}
	}
	#if defined admsys_OnPlayerDisconnect
		return admsys_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect admsys_OnPlayerDisconnect
#if defined admsys_OnPlayerDisconnect
	forward admsys_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerSpawn(playerid)
{
	if(IsPlayerSpectating(playerid))
	{
		for(new i = 12; i >= 0; --i)
			GivePlayerWeapon(playerid, AdmSysInfo[playerid][asLastWeapon][i], AdmSysInfo[playerid][asLastAmmo][i]);
		SetPlayerPos(playerid, AdmSysInfo[playerid][asLastPos][0],
		AdmSysInfo[playerid][asLastPos][1], AdmSysInfo[playerid][asLastPos][2]);
		SetPlayerFacingAngle(playerid, AdmSysInfo[playerid][asLastAngle]);
		SetPlayerVirtualWorld(playerid, AdmSysInfo[playerid][asLastVW]);
		SetPlayerInterior(playerid, AdmSysInfo[playerid][asLastInt]);
	}
	AdmSysInfo[playerid][asSpecID] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asLastSpecID] = INVALID_PLAYER_ID;
	AdmSysInfo[playerid][asIsSpawned] = true;
	AdmSysInfo[playerid][asLastSpec] = false;
	AdmSysInfo[playerid][asIsDead] = false;
	#if defined foreach
		foreach(new i : Player)
		{
	#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		{
			if(!IsPlayerConnected(i)) continue;
	#endif
		if(AdmSysInfo[i][asSpecID] == playerid) UpdateSpectating(i);
	}
	#if defined admsys_OnPlayerSpawn
		return admsys_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn admsys_OnPlayerSpawn
#if defined admsys_OnPlayerSpawn
	forward admsys_OnPlayerSpawn(playerid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	new interior, vw;
	interior = GetPlayerInterior(playerid);
	vw = GetPlayerVirtualWorld(playerid);
	#if defined foreach
	foreach(new i : Player)
	{
	#else
	for(new i = GetPlayerPoolSize(); i >= 0; --i)
	{
		if(!IsPlayerConnected(i)) continue;
	#endif
		if(AdmSysInfo[i][asSpecID] == playerid)
		{
			SendClientMessage(i, ADMSYS_ERROR_COLOR, "Player has died");
			SetPlayerInterior(i, interior);
			SetPlayerVirtualWorld(i, vw);
		}
		#if ADMSYS_SHOW_KILL_LIST_FOR_ADM
			if(IsPlayerAdminEx(i)) SendDeathMessageToPlayer(i, killerid, playerid, reason);
		#endif
	}
	AdmSysInfo[playerid][asIsSpawned] = false;
	AdmSysInfo[playerid][asIsDead] = true;
	#if defined admsys_OnPlayerDeath
		return admsys_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath admsys_OnPlayerDeath
#if defined admsys_OnPlayerDeath
	forward admsys_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerText(playerid, text[])
{
	static strtmp[59];
	if(AdmSysInfo[playerid][asMuteTime] > 0)
	{
		format(strtmp, sizeof strtmp, "You are muted. Remaining mute time: %d minutes %d seconds",
		floatround(AdmSysInfo[playerid][asMuteTime] / 60, floatround_tozero), AdmSysInfo[playerid][asMuteTime] % 60);
		SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
		return 0;
	}
	#if defined admsys_OnPlayerText
		return admsys_OnPlayerText(playerid, text);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText admsys_OnPlayerText
#if defined admsys_OnPlayerText
	forward admsys_OnPlayerText(playerid, text[]);
#endif

#if !defined YCMD && !defined _I_ZCMD_INCLUDED
	public OnPlayerCommandText(playerid, cmdtext[])
	{
		new cmd[32], pos;
		static params[126];
		params[0] = EOS;
		while(cmdtext[pos] > ' ')
		{
			cmd[pos] = cmdtext[pos];
			pos++;
		}
		while(cmdtext[pos] == ' ')
		{
			pos++;
			if(cmdtext[pos] == '\0')
			{
				params = "\1";
				break;
			}
		}
		strcat(params, cmdtext[pos]);
		if(!strcmp(cmd, "/report", true)) return admsys_cmd_report(playerid, params);
		if(!strcmp(cmd, "/achat", true) || !strcmp(cmd, "/admchat", true) || !strcmp(cmd, "/adminchat", true)) return admsys_cmd_achat(playerid, params);
		if(!strcmp(cmd, "/ahelp", true) || !strcmp(cmd, "/admhelp", true) || !strcmp(cmd, "/adminhelp", true)) return admsys_cmd_ahelp(playerid, params);
		if(!strcmp(cmd, "/showstats", true)) return admsys_cmd_showstats(playerid, params);
		if(!strcmp(cmd, "/answer", true)) return admsys_cmd_answer(playerid, params);
		if(!strcmp(cmd, "/apanel", true) || !strcmp(cmd, "/admpanel", true) || !strcmp(cmd, "/adminpanel", true)) return admsys_cmd_apanel(playerid, params);
		if(!strcmp(cmd, "/admins", true)) return admsys_cmd_admins(playerid, params);
		if(!strcmp(cmd, "/eject", true)) return admsys_cmd_eject(playerid, params);

		if(!strcmp(cmd, "/spec", true)) return admsys_cmd_spec(playerid, params);
		if(!strcmp(cmd, "/specupdate", true)) return admsys_cmd_specupdate(playerid, params);
		if(!strcmp(cmd, "/specoff", true)) return admsys_cmd_specoff(playerid, params);
		if(!strcmp(cmd, "/spawnveh", true) || !strcmp(cmd, "/spawnvehicle", true)) return admsys_cmd_spawnveh(playerid, params);
		if(!strcmp(cmd, "/mute", true)) return admsys_cmd_mute(playerid, params);
		if(!strcmp(cmd, "/unmute", true)) return admsys_cmd_unmute(playerid, params);
		if(!strcmp(cmd, "/asay", true) || !strcmp(cmd, "/admsay", true) || !strcmp(cmd, "/adminsay", true)) return admsys_cmd_asay(playerid, params);
		if(!strcmp(cmd, "/warn", true)) return admsys_cmd_warn(playerid, params);
		if(!strcmp(cmd, "/kick", true)) return admsys_cmd_kick(playerid, params);
		if(!strcmp(cmd, "/freeze", true)) return admsys_cmd_freeze(playerid, params);
		if(!strcmp(cmd, "/unfreeze", true)) return admsys_cmd_unfreeze(playerid, params);
		if(!strcmp(cmd, "/slap", true)) return admsys_cmd_slap(playerid, params);
		if(!strcmp(cmd, "/goto", true)) return admsys_cmd_goto(playerid, params);

		if(!strcmp(cmd, "/suspectlist", true)) return admsys_cmd_suspectlist(playerid, params);
		if(!strcmp(cmd, "/gethere", true) || !strcmp(cmd, "/get", true)) return admsys_cmd_gethere(playerid, params);
		if(!strcmp(cmd, "/gotoveh", true) || !strcmp(cmd, "/gotovehicle", true)) return admsys_cmd_gotoveh(playerid, params);
		if(!strcmp(cmd, "/gotopos", true) || !strcmp(cmd, "/gotoposition", true)) return admsys_cmd_gotopos(playerid, params);
		if(!strcmp(cmd, "/ban", true)) return admsys_cmd_ban(playerid, params);
		if(!strcmp(cmd, "/gmtest", true)) return admsys_cmd_gmtest(playerid, params);
		if(!strcmp(cmd, "/spawn", true)) return admsys_cmd_spawn(playerid, params);
		if(!strcmp(cmd, "/unwarn", true)) return admsys_cmd_unwarn(playerid, params);
		if(!strcmp(cmd, "/banip", true) || !strcmp(cmd, "/blockip", true)) return admsys_cmd_banip(playerid, params);
		if(!strcmp(cmd, "/cc", true) || !strcmp(cmd, "/clearchat", true)) return admsys_cmd_cc(playerid, params);

		if(!strcmp(cmd, "/sethealth", true)) return admsys_cmd_sethealth(playerid, params);
		if(!strcmp(cmd, "/setarmour", true)) return admsys_cmd_setarmour(playerid, params);
		if(!strcmp(cmd, "/setmoney", true)) return admsys_cmd_setmoney(playerid, params);
		if(!strcmp(cmd, "/givemoney", true)) return admsys_cmd_givemoney(playerid, params);
		if(!strcmp(cmd, "/setscore", true)) return admsys_cmd_setscore(playerid, params);
		if(!strcmp(cmd, "/setskin", true)) return admsys_cmd_setskin(playerid, params);
		if(!strcmp(cmd, "/setint", true) || !strcmp(cmd, "/setinterior", true)) return admsys_cmd_setint(playerid, params);
		if(!strcmp(cmd, "/setvw", true) || !strcmp(cmd, "/setvirtualworld", true)) return admsys_cmd_setvw(playerid, params);
		if(!strcmp(cmd, "/giveweapon", true)) return admsys_cmd_giveweapon(playerid, params);
		if(!strcmp(cmd, "/repairveh", true) || !strcmp(cmd, "/repairvehicle", true)) return admsys_cmd_repairveh(playerid, params);
		if(!strcmp(cmd, "/unbanip", true) || !strcmp(cmd, "/unblockip", true)) return admsys_cmd_unbanip(playerid, params);

		if(!strcmp(cmd, "/setweather", true)) return admsys_cmd_setweather(playerid, params);
		if(!strcmp(cmd, "/getall", true)) return admsys_cmd_getall(playerid, params);
		if(!strcmp(cmd, "/settime", true)) return admsys_cmd_settime(playerid, params);
		if(!strcmp(cmd, "/destroyveh", true) || !strcmp(cmd, "/destroyvehicle", true)) return admsys_cmd_destroyveh(playerid, params);
		if(!strcmp(cmd, "/veh", true) || !strcmp(cmd, "/vehicle", true)) return admsys_cmd_veh(playerid, params);
		if(!strcmp(cmd, "/sban", true) || !strcmp(cmd, "/silentban", true)) return admsys_cmd_sban(playerid, params);
		if(!strcmp(cmd, "/skick", true) || !strcmp(cmd, "/silentkick", true)) return admsys_cmd_skick(playerid, params);
		#if defined admsys_OnPlayerCommandText
			return admsys_OnPlayerCommandText(playerid, cmdtext);
		#else
			return 0;
		#endif
	}

	#if defined _ALS_OnPlayerCommandText
		#undef OnPlayerCommandText
	#else
		#define _ALS_OnPlayerCommandText
	#endif
	#define OnPlayerCommandText admsys_OnPlayerCommandText
	#if defined admsys_OnPlayerCommandText
		forward admsys_OnPlayerCommandText(playerid, cmdtext[]);
	#endif
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING)
	{
		#if defined foreach
			foreach(new i : Player)
			{
		#else
			for(new i = GetPlayerPoolSize(); i >= 0; --i)
			{
				if(!IsPlayerConnected(i)) continue;
		#endif
			if(AdmSysInfo[i][asSpecID] == playerid)
			{
				SendClientMessage(i, ADMSYS_ERROR_COLOR, "Player is in spectator mode");
				StopSpectating(i);
			}
		}
	}
	else if(PLAYER_STATE_DRIVER <= newstate <= PLAYER_STATE_PASSENGER || PLAYER_STATE_DRIVER <= oldstate <= PLAYER_STATE_PASSENGER)
	{
		#if defined foreach
			foreach(new i : Player)
			{
		#else
			for(new i = GetPlayerPoolSize(); i >= 0; --i)
			{
				if(!IsPlayerConnected(i)) continue;
		#endif
			if(AdmSysInfo[i][asSpecID] == playerid) UpdateSpectating(i);
		}
	}
	#if defined admsys_OnPlayerStateChange
		return admsys_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange admsys_OnPlayerStateChange
#if defined admsys_OnPlayerStateChange
	forward admsys_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING &&
	AdmSysInfo[playerid][asSpecID] != INVALID_PLAYER_ID && AdmSysInfo[AdmSysInfo[playerid][asSpecID]][asIsDead])
	{
		new Float:pX, Float:pY, Float:pZ, Float:cX, Float:cY, Float:cZ;
		GetPlayerCameraPos(AdmSysInfo[playerid][asSpecID], cX, cY, cZ);
		GetPlayerPos(AdmSysInfo[playerid][asSpecID], pX, pY, pZ);
		SetPlayerCameraPos(playerid, cX, cY, cZ);
		SetPlayerCameraLookAt(playerid, pX, pY, pZ);
	}
	#if defined admsys_OnPlayerUpdate
		return admsys_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate admsys_OnPlayerUpdate
#if defined admsys_OnPlayerUpdate
	forward admsys_OnPlayerUpdate(playerid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case ADMSYS_DIALOG_TAB_PANEL:
		{
			if(response)
			{
				static strtmp[3];
				format(strtmp, sizeof strtmp, "%d", AdmSysInfo[playerid][asTabPanel]);
				switch(listitem)
				{
					case 0: admsys_cmd_showstats(playerid, strtmp);
					case 1:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ANSWER, DIALOG_STYLE_INPUT, "Respond on report", "Enter the answer to the report:", "Ok", "Close");
					case 2: admsys_cmd_eject(playerid, strtmp);
					case 3: admsys_cmd_spec(playerid, strtmp);
					case 4:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Mute", "Enter mute time:", "Ok", "Close");
					case 5: admsys_cmd_unmute(playerid, strtmp);
					case 6:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_WARN, DIALOG_STYLE_INPUT, "Give warn", "Enter the reason of the warn:", "Ok", "Close");
					case 7:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_KICK, DIALOG_STYLE_INPUT, "Kick", "Enter the reason of kick:", "Ok", "Close");
					case 8: admsys_cmd_freeze(playerid, strtmp);
					case 9: admsys_cmd_unfreeze(playerid, strtmp);
					case 10:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SLAP, DIALOG_STYLE_INPUT, "Slap", "Enter the reason of slap:", "Ok", "Close");
					case 11: admsys_cmd_goto(playerid, strtmp);
					case 12: admsys_cmd_gethere(playerid, strtmp);
					case 13:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN, DIALOG_STYLE_INPUT, "Ban", "Enter the reason of ban:", "Ok", "Close");
					case 14: admsys_cmd_gmtest(playerid, strtmp);
					case 15: admsys_cmd_spawn(playerid, strtmp);
					case 16: admsys_cmd_unwarn(playerid, strtmp);
					case 17:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_HEALTH, DIALOG_STYLE_INPUT, "Set health", "Enter the amount of health you want to set:", "Ok", "Close");
					case 18:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_ARMOUR, DIALOG_STYLE_INPUT, "Set armour", "Enter the amount of armour you want to set:", "Ok", "Close");
					case 19:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_MONEY, DIALOG_STYLE_INPUT, "Set money", "Enter the amount of money you want to set:", "Ok", "Close");
					case 20:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_MONEY, DIALOG_STYLE_INPUT, "Give money", "Enter the amount of money you want to give:", "Ok", "Close");
					case 21:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_SCORE, DIALOG_STYLE_INPUT, "Set score", "Enter the amount of score you want to set:", "Ok", "Close");
					case 22:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_CHANGE_SKIN, DIALOG_STYLE_INPUT, "Set skin", "Enter the ID of the skin you want to set:", "Ok", "Close");
					case 23:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_INT, DIALOG_STYLE_INPUT, "Set interior", "Enter the ID of the interior you want to set:", "Ok", "Close");
					case 24:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_VW, DIALOG_STYLE_INPUT, "Set virtual world", "Enter the ID of the virtual world you want to set:", "Ok", "Close");
					case 25:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Give weapon", "Enter the ID of the weapon you want to give:", "Ok", "Close");
					case 26: admsys_cmd_sban(playerid, strtmp);
					case 27: admsys_cmd_skick(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_ANSWER:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ANSWER, DIALOG_STYLE_INPUT, "Respond on report", "Enter the answer to the report:", "Ok", "Close");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_answer(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_MUTE_TIME:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Mute", "Enter mute time:", "Ok", "Close");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE, DIALOG_STYLE_INPUT, "Mute", "Enter the reason of mute:", "Ok", "Back");
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_MUTE:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE, DIALOG_STYLE_INPUT, "Mute", "Enter the reason of mute:", "Ok", "Back");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s %s", AdmSysInfo[playerid][asTabPanel], AdmSysInfo[playerid][asInput], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_mute(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Mute", "Enter the time of mute:", "Ok", "Close");
			return 1;
		}
		case ADMSYS_DIALOG_WARN:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_WARN, DIALOG_STYLE_INPUT, "Give warn", "Enter the reason of the warn:", "Ok", "Close");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_warn(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_KICK:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_KICK, DIALOG_STYLE_INPUT, "Kick", "Enter the reason of kick:", "Ok", "Close");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_kick(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SLAP:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SLAP, DIALOG_STYLE_INPUT, "Slap", "Enter the reason of slap:", "Ok", "Close");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_slap(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_BAN:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN, DIALOG_STYLE_INPUT, "Ban", "Enter the reason of ban:", "Ok", "Close");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_ban(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_HEALTH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_HEALTH, DIALOG_STYLE_INPUT, "Set health", "Enter the amount of health you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_sethealth(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_ARMOUR:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_ARMOUR, DIALOG_STYLE_INPUT, "Set armour", "Enter the amount of armour you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setarmour(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_MONEY:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_MONEY, DIALOG_STYLE_INPUT, "Set money", "Enter the amount of money you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setmoney(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_GIVE_MONEY:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_MONEY, DIALOG_STYLE_INPUT, "Give money", "Enter the amount of money you want to give:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_givemoney(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_SCORE:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_SCORE, DIALOG_STYLE_INPUT, "Set score", "Enter the amount of score you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setscore(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_CHANGE_SKIN:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CHANGE_SKIN, DIALOG_STYLE_INPUT, "Set skin", "Enter the ID of the skin you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setskin(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_INT:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_INT, DIALOG_STYLE_INPUT, "Set interior", "Enter the ID of the interior you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setint(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_VW:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_VW, DIALOG_STYLE_INPUT, "Set virtual world", "Enter the ID of the virtual world you want to set:", "Ok", "Close");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s", AdmSysInfo[playerid][asTabPanel], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_setvw(playerid, strtmp);
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_GIVE_WEAPON:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Give weapon", "Enter the ID of the weapon you want to give:", "Ok", "Close");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Give weapon", "Enter the number of ammo you want to give:", "Ok", "Back");
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_GIVE_WEAPON_AMMO:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Give weapon", "Enter the number of ammo you want to give:", "Ok", "Back");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s %s", AdmSysInfo[playerid][asTabPanel], AdmSysInfo[playerid][asInput], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_giveweapon(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Give weapon", "Enter the ID of the weapon you want to give:", "Ok", "Close");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_1:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_2, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys2LvlCmdsStr, "Next", "Back");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_2:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_3, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys3LvlCmdsStr, "Next", "Back");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_1, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys1LvlCmdsStr, "Next", "Close");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_3:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_4, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys4LvlCmdsStr, "Next", "Back");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_2, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys2LvlCmdsStr, "Next", "Back");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_4:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_5, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys5LvlCmdsStr, "Ok", "Back");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_3, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys3LvlCmdsStr, "Next", "Back");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_5:
		{
			if(!response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_4, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys4LvlCmdsStr, "Next", "Back");
			return 1;
		}
		case ADMSYS_DIALOG_APANEL:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ACHAT, DIALOG_STYLE_INPUT, "Admin chat", "Write your message:", "Ok", "Close");
					case 1: admsys_cmd_ahelp(playerid, "\1");
					case 2: admsys_cmd_admins(playerid, "\1");
					case 3:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SPAWN_VEH, DIALOG_STYLE_INPUT, "Teleport vehicle to respawn", "Enter the ID of vehicle you want to spawn:", "Ok", "Close");
					case 4:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ASAY, DIALOG_STYLE_INPUT, "Message from admin", "Write your message:", "Ok", "Close");
					case 5: admsys_cmd_suspectlist(playerid, "\1");
					case 6:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_VEH, DIALOG_STYLE_INPUT, "Teleport to vehicle", "Enter the ID of vehicle you want to teleport to:", "Ok", "Close");
					case 7:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_POS, DIALOG_STYLE_INPUT, "Teleport to position", "Enter the coordinates separated by a space, to which you want to teleport:", "Ok", "Close");
					case 8:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN_IP, DIALOG_STYLE_INPUT, "Block IP address", "Enter the IP address you want to block:", "Ok", "Close");
					case 9: admsys_cmd_cc(playerid, "\1");
					case 10:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_REPAIR_VEH, DIALOG_STYLE_INPUT, "Repair vehicle", "Enter the ID of vehicle you want to repair:", "Ok", "Close");
					case 11:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_UNBAN_IP, DIALOG_STYLE_INPUT, "Unblock IP address", "Enter the IP address you want to unblock:", "Ok", "Close");
					case 12: admsys_cmd_getall(playerid, "\1");
					case 13:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_WEATHER, DIALOG_STYLE_INPUT, "Set weather", "Enter the ID of the weather you want to set:", "Ok", "Close");
					case 14:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_TIME, DIALOG_STYLE_INPUT, "Set the time of day", "Enter the hour you want to set:", "Ok", "Close");
					case 15:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_DESTROY_VEH, DIALOG_STYLE_INPUT, "Destroy vehicle", "Enter the ID of vehicle you want to destroy:", "Ok", "Close");
					case 16:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Create vehicle", "Enter vehicle model you want to create:", "Ok", "Close");
					case 17:
					{
						if(IsPlayerAdminEx(playerid) && AdmSysInfo[playerid][asLastAction])
						{
							switch(AdmSysInfo[playerid][asLastAction])
							{
								case 1: SetPlayerHealth(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastFloatData]);
								case 2: SetPlayerArmour(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastFloatData]);
								case 3:
								{
									ResetPlayerMoney(AdmSysInfo[playerid][asLastActionID]);
									GivePlayerMoney(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0]);
								}
								case 4: GivePlayerMoney(AdmSysInfo[playerid][asLastActionID], -AdmSysInfo[playerid][asLastIntData][0]);
								case 5: SetPlayerScore(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0]);
								case 6: SetPlayerSkin(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0]);
								case 7: SetPlayerInterior(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0]);
								case 8: SetPlayerVirtualWorld(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0]);
								case 9:
									GivePlayerWeapon(AdmSysInfo[playerid][asLastActionID], AdmSysInfo[playerid][asLastIntData][0], -AdmSysInfo[playerid][asLastIntData][1]);
							}
							AdmSysInfo[playerid][asLastAction] = 0;
							SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, "Command canceled");
						}
					}
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_ACHAT:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ACHAT, DIALOG_STYLE_INPUT, "Admin chat", "Write your message:", "Ok", "Close");
				else admsys_cmd_achat(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_SPAWN_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext)) admsys_cmd_spawnveh(playerid, "\1");
				else admsys_cmd_spawnveh(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_ASAY:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ASAY, DIALOG_STYLE_INPUT, "Message from admin", "Write your message:", "Ok", "Close");
				else admsys_cmd_asay(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_GOTO_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_VEH, DIALOG_STYLE_INPUT, "Teleport to vehicle", "Enter the ID of vehicle you want to teleport to:", "Ok", "Close");
				else admsys_cmd_gotoveh(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_GOTO_POS:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_POS, DIALOG_STYLE_INPUT, "Teleport to position", "Enter the coordinates separated by a space, to which you want to teleport:", "Ok", "Close");
				else admsys_cmd_gotopos(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_BAN_IP:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN_IP, DIALOG_STYLE_INPUT, "Block IP address", "Enter the IP address you want to block:", "Ok", "Close");
				else admsys_cmd_banip(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_REPAIR_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext)) admsys_cmd_repairveh(playerid, "\1");
				else admsys_cmd_repairveh(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_UNBAN_IP:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_UNBAN_IP, DIALOG_STYLE_INPUT, "Unblock IP address", "Enter the IP address you want to unblock:", "Ok", "Close");
				else admsys_cmd_unbanip(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_WEATHER:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_WEATHER, DIALOG_STYLE_INPUT, "Set weather", "Enter the ID of the weather you want to set:", "Ok", "Close");
				else admsys_cmd_setweather(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_TIME:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_TIME, DIALOG_STYLE_INPUT, "Set the time of day", "Enter the hour you want to set:", "Ok", "Close");
				else admsys_cmd_settime(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_DESTROY_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext)) admsys_cmd_destroyveh(playerid, "\1");
				else admsys_cmd_destroyveh(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_CREATE_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Create vehicle", "Enter vehicle model you want to create:", "Ok", "Close");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_1, DIALOG_STYLE_INPUT, "Create vehicle", "Enter the color 1 for vehicle you want to create:", "Ok", "Back");
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_CREATE_VEH_COL_1:
		{
			if(response)
			{
				if(admsys_isnull(inputtext)) admsys_cmd_veh(playerid, AdmSysInfo[playerid][asInput]);
				else
				{
					format(AdmSysInfo[playerid][asInput2], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_2, DIALOG_STYLE_INPUT, "Create vehicle", "Enter the color 2 for vehicle you want to create:", "Ok", "Back");
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Create vehicle", "Enter vehicle model you want to create:", "Ok", "Close");
			return 1;
		}
		case ADMSYS_DIALOG_CREATE_VEH_COL_2:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_2, DIALOG_STYLE_INPUT, "Create vehicle", "Enter the color 2 for vehicle you want to create:", "Ok", "Back");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%s %s %s", AdmSysInfo[playerid][asInput], AdmSysInfo[playerid][asInput2], inputtext);
					admsys_cmd_veh(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_1, DIALOG_STYLE_INPUT, "Create vehicle", "Enter the color 1 for vehicle you want to create:", "Ok", "Back");
			return 1;
		}
		case ADMSYS_DIALOG_SUSPECT_LIST:
		{
			if(response && IsPlayerAdminEx(playerid, 3) && 0 <= listitem < sizeof SuspectList)
			{
				if(!StartSpectating(playerid, SuspectList[listitem]))
				{
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player has disconnected");
					admsys_cmd_suspectlist(playerid, "\1");
				}
				else if(AdmSysInfo[playerid][asSpecID] == SuspectList[listitem]) RemovePlayerFromSuspectList(SuspectList[listitem]);
				else admsys_cmd_suspectlist(playerid, "\1");
			}
			return 1;
		}
	}
	#if defined admsys_OnDialogResponse
		return admsys_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 0;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse admsys_OnDialogResponse
#if defined admsys_OnDialogResponse
	forward admsys_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	#if defined foreach
		foreach(new i : Player)
		{
	#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		{
			if(!IsPlayerConnected(i)) continue;
	#endif
		if(AdmSysInfo[i][asSpecID] == playerid) UpdateSpectating(i);
	}
	#if defined admsys_OnPlayerInteriorChange
		return admsys_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange admsys_OnPlayerInteriorChange
#if defined admsys_OnPlayerInteriorChange
	forward admsys_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && AdmSysInfo[playerid][asSpecID] != INVALID_PLAYER_ID)
	{
		if(newkeys & KEY_ANALOG_LEFT)
		{
			new ud = AdmSysInfo[playerid][asSpecID];
			AdmSysInfo[playerid][asSpecID]--;
			while(!IsPlayerConnected(AdmSysInfo[playerid][asSpecID]) || IsPlayerSpectating(AdmSysInfo[playerid][asSpecID]) || AdmSysInfo[playerid][asSpecID] == playerid)
			{
				AdmSysInfo[playerid][asSpecID]--;
				if(AdmSysInfo[playerid][asSpecID] < 0) AdmSysInfo[playerid][asSpecID] = GetPlayerPoolSize();
				if(AdmSysInfo[playerid][asSpecID] == ud) break;
			}
			if(AdmSysInfo[playerid][asSpecID] != ud) UpdateSpectating(playerid);
		}
		else if(newkeys & KEY_ANALOG_RIGHT)
		{
			new ud = AdmSysInfo[playerid][asSpecID];
			AdmSysInfo[playerid][asSpecID]++;
			while(!IsPlayerConnected(AdmSysInfo[playerid][asSpecID]) || IsPlayerSpectating(AdmSysInfo[playerid][asSpecID]) || AdmSysInfo[playerid][asSpecID] == playerid)
			{
				AdmSysInfo[playerid][asSpecID]++;
				if(AdmSysInfo[playerid][asSpecID] > GetPlayerPoolSize()) AdmSysInfo[playerid][asSpecID] = 0;
				if(AdmSysInfo[playerid][asSpecID] == ud) break;
			}
			if(AdmSysInfo[playerid][asSpecID] != ud) UpdateSpectating(playerid);
		}
	}
	#if defined admsys_OnPlayerKeyStateChange
		return admsys_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange admsys_OnPlayerKeyStateChange
#if defined admsys_OnPlayerKeyStateChange
	forward admsys_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(IsPlayerAdminEx(playerid))
	{
		static strtmp[373], strtmp2[43], strname[MAX_PLAYER_NAME + 1];
		strtmp[0] = EOS;
		AdmSysInfo[playerid][asTabPanel] = clickedplayerid;
		GetPlayerName(clickedplayerid, strname, sizeof strname);
		format(strtmp2, sizeof strtmp2, "Admin panel for %s", strname);
		strcat(strtmp, "Show statistics\nRespond on report\nRemove from vehicle");
		if(IsPlayerAdminEx(playerid, 2)) strcat(strtmp, "\nStart spectate\n\
		Mute\nUnmute\nGive warn\nKick\nFreeze\nUnfreeze\nSlap\nTeleport to player");
		if(IsPlayerAdminEx(playerid, 3)) strcat(strtmp, "\nTeleport to yourself\nBan\n\
		Check for infinite health\nTeleport to respawn\nRemove warn");
		if(IsPlayerAdminEx(playerid, 4)) strcat(strtmp, "\nSet health\nSet armour\nSet money\n\
		Give money\nSet score\nSet skin\nSet interior\nSet virtual world\nGive weapon");
		if(IsPlayerAdminEx(playerid, 5)) strcat(strtmp, "\nSilent ban\nSilent kick");
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_TAB_PANEL, DIALOG_STYLE_LIST, strtmp2, strtmp, "Ok", "Close");
	}
	#if defined admsys_OnPlayerClickPlayer
		return admsys_OnPlayerClickPlayer(playerid, clickedplayerid, source);
	#else
		return 0;
	#endif
}

#if defined _ALS_OnPlayerClickPlayer
	#undef OnPlayerClickPlayer
#else
	#define _ALS_OnPlayerClickPlayer
#endif
#define OnPlayerClickPlayer admsys_OnPlayerClickPlayer
#if defined admsys_OnPlayerClickPlayer
	forward admsys_OnPlayerClickPlayer(playerid, clickedplayerid, source);
#endif

admsys_fpublic BanWithDelay(playerid) return Ban(playerid);

admsys_fpublic KickWithDelay(playerid) return Kick(playerid);

admsys_fpublic UpdateMuteTime()
{
	#if defined foreach
	foreach(new i : Player)
	{
	#else
	for(new i = GetPlayerPoolSize(); i >= 0; --i)
	{
		if(!IsPlayerConnected(i)) continue;
	#endif
		if(AdmSysInfo[i][asMuteTime] > 0)
		{
			AdmSysInfo[i][asMuteTime]--;
			if(AdmSysInfo[i][asMuteTime] < 1)
				SendClientMessage(i, ADMSYS_DEFAULT_COLOR, "Mute time has expired");
		}
	}
	return 1;
}

admsys_fpublic UpdateSpecInfo(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && AdmSysInfo[playerid][asSpecID] != INVALID_PLAYER_ID)
	{
		static strtmp[100], sname[MAX_PLAYER_NAME + 1], sip[16];
		GetPlayerIp(AdmSysInfo[playerid][asSpecID], sip, sizeof sip);
		GetPlayerName(AdmSysInfo[playerid][asSpecID], sname, sizeof sname);
		format(strtmp, sizeof strtmp, "~w~~n~~n~~n~~n~~n~~n~Nick: %s~n~ID: %d~n~IP: %s~n~Ping: %d",
		sname, AdmSysInfo[playerid][asSpecID], sip, GetPlayerPing(AdmSysInfo[playerid][asSpecID]));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(AdmSysInfo[playerid][asSpecID]));
		AdmSysInfo[playerid][asUpdTimer] = SetTimerEx("UpdateSpecInfo", 1000, false, "d", playerid);
		GameTextForPlayer(playerid, strtmp, 1500, 3);
		return 1;
	}
	return 0;
}

admsys_fpublic GmTest(playerid)
{
	if(AdmSysInfo[playerid][asGmTestID] != INVALID_PLAYER_ID)
	{
		if(AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTest])
		{
			static strtmp[182];
			new vehid, Float:nowhp, Float:nowar, Float:hpdiff, Float:ardiff;
			vehid = GetPlayerVehicleID(AdmSysInfo[playerid][asGmTestID]);
			if(vehid) GetVehicleHealth(vehid, nowhp);
			else
			{
				GetPlayerHealth(AdmSysInfo[playerid][asGmTestID], nowhp);
				GetPlayerArmour(AdmSysInfo[playerid][asGmTestID], nowar);
			}
			hpdiff = AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP] - nowhp;
			ardiff = AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR] - nowar;
			if(hpdiff == 0.0 && ardiff == 0.0)
			{
				format(strtmp, sizeof strtmp, "Before:\t%.1f health, %.1f armour\nAfter:\t%.1f health, %.1f armour\nHealth and armour hasn't decreased\n\nPerhaps the player uses GodMode.",
				AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR], nowhp, nowar);
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_GMTEST, DIALOG_STYLE_MSGBOX, "Check for GodMode", strtmp, "Close", "");
			}
			else
			{
				format(strtmp, sizeof strtmp, "Before:\t%.1f health, %.1f armour\nAfter:\t%.1f health, %.1f armour\n\
				Health decreased by:\t%.1f\nArmour decreased by:\t%.1f\n\nGodMode isn't detected.\nHealth and armor restored.",
				AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR], nowhp, nowar, hpdiff, ardiff);
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_GMTEST, DIALOG_STYLE_MSGBOX, "Check for GodMode", strtmp, "Close", "");
				if(vehid) SetVehicleHealth(vehid, AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP]);
				else
				{
					SetPlayerHealth(AdmSysInfo[playerid][asGmTestID], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP]);
					SetPlayerArmour(AdmSysInfo[playerid][asGmTestID], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR]);
				}
			}
		}
		AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTest] = false;
		AdmSysInfo[playerid][asGmTestID] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:report(playerid, const params[]) return admsys_cmd_report(playerid, params);
admsys_cmd_report(playerid, const params[])
{
	static strtmp[145];
	if(AdmSysInfo[playerid][asMuteTime] > 0)
	{
		format(strtmp, sizeof strtmp, "You are muted. Remaining mute time: %d minutes %d seconds",
		floatround(AdmSysInfo[playerid][asMuteTime] / 60, floatround_tozero), AdmSysInfo[playerid][asMuteTime] % 60);
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
	}
	if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /report [text]");
	static strname[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, strname, sizeof strname);
	format(strtmp, sizeof strtmp, "[Report] %s[%d]: %s", strname, playerid, params);
	if(!IsPlayerAdminEx(playerid)) SendClientMessage(playerid, ADMSYS_REPORT_COLOR, strtmp);
	SendMessageToAdmins(1, ADMSYS_REPORT_COLOR, strtmp);
	return 1;
}

CMD:achat(playerid, const params[]) return admsys_cmd_achat(playerid, params);
CMD:admchat(playerid, const params[]) return admsys_cmd_achat(playerid, params);
CMD:adminchat(playerid, const params[]) return admsys_cmd_achat(playerid, params);
admsys_cmd_achat(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /achat [text]");
		static strtmp[145], strname[MAX_PLAYER_NAME + 1];
		strtmp = "[Admin chat] ";
		GetPlayerName(playerid, strname, sizeof strname);
		strcat(strtmp, strname);
		strcat(strtmp, ": ");
		strcat(strtmp, params);
		SendMessageToAdmins(1, ADMSYS_ADM_CHAT_COLOR, strtmp);
	}
	return 1;
}

CMD:ahelp(playerid, const params[]) return admsys_cmd_ahelp(playerid, params);
CMD:admhelp(playerid, const params[]) return admsys_cmd_ahelp(playerid, params);
CMD:adminhelp(playerid, const params[]) return admsys_cmd_ahelp(playerid, params);
admsys_cmd_ahelp(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid))
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_1, DIALOG_STYLE_MSGBOX, "Help with admin commands", AdmSys1LvlCmdsStr, "Next", "Close");
	return 1;
}

CMD:showstats(playerid, params[]) return admsys_cmd_showstats(playerid, params);
admsys_cmd_showstats(playerid, params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		if(admsys_isnull(params)) params[0] = playerid;
		else
		{
			if(!admsys_IsNumeric(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /showstats [id]");
			params[0] = strval(params);
			if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		}
		new Float:ghealth, Float:garmour;
		static strtmp[38], strtmp2[192], strname[MAX_PLAYER_NAME + 1], gip[16];
		GetPlayerName(params[0], strname, sizeof strname);
		GetPlayerHealth(params[0], ghealth);
		GetPlayerArmour(params[0], garmour);
		GetPlayerIp(params[0], gip, sizeof gip);
		format(strtmp, sizeof strtmp, "Info about %s", strname);
		format(strtmp2, sizeof strtmp2, "Health: %.1f\nArmour: %.1f\nMoney: %d\nInterior: %d\nVirtual world: %d\nWanted level: %d\nIP address: %s\nPing: %d\nWeapon: %d\nAmmo: %d\nScore: %d\nSkin: %d",
		ghealth, garmour, GetPlayerMoney(params[0]), GetPlayerInterior(params[0]), GetPlayerVirtualWorld(params[0]), GetPlayerWantedLevel(params[0]), gip, GetPlayerPing(params[0]),
		GetPlayerWeapon(params[0]), GetPlayerAmmo(params[0]), GetPlayerScore(params[0]), GetPlayerSkin(params[0]));
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_STATS, DIALOG_STYLE_MSGBOX, strtmp, strtmp2, "Ok", "");
	}
	return 1;
}

CMD:answer(playerid, const params[]) return admsys_cmd_answer(playerid, params);
admsys_cmd_answer(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /answer [id] [text]");
		new pos;
		static strtmp[145];
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /answer [id] [text]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /answer [id] [text]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "[Response to report %s] %s: %s", strname2, strname, params[pos]);
		SendMessageToAdmins(1, ADMSYS_REPORT_COLOR, strtmp);
		if(!IsPlayerAdminEx(giveid))
		{
			strtmp = "[Response to report]: ";
			strcat(strtmp, params[pos]);
			SendClientMessage(giveid, ADMSYS_REPORT_COLOR, strtmp);
		}
	}
	return 1;
}

CMD:apanel(playerid, const params[]) return admsys_cmd_apanel(playerid, params);
CMD:admpanel(playerid, const params[]) return admsys_cmd_apanel(playerid, params);
CMD:adminpanel(playerid, const params[]) return admsys_cmd_apanel(playerid, params);
admsys_cmd_apanel(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid))
	{
		static strtmp[382];
		strtmp[0] = EOS;
		strcat(strtmp, "Admin chat\nHelp with admin commands\nList of administrators online");
		if(IsPlayerAdminEx(playerid, 2)) strcat(strtmp, "\nTeleport vehicle to respawn\n\
		Message: 'Administrator: [text]'");
		if(IsPlayerAdminEx(playerid, 3)) strcat(strtmp, "\nList of suspected players\n\
		Teleport to vehicle\nTeleport to position\nBlock IP address\nClear chat");
		if(IsPlayerAdminEx(playerid, 4)) strcat(strtmp, "\nRepair vehicle\nUnblock IP address");
		if(IsPlayerAdminEx(playerid, 5)) strcat(strtmp, "\nTeleport all to yourself\nSet weather\n\
		Set the time of day\nDestroy vehicle\nCreate vehicle");
		strcat(strtmp, "\nUndo the last command");
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_APANEL, DIALOG_STYLE_LIST, "Admin panel", strtmp, "Ok", "Close");
	}
	return 1;
}

CMD:admins(playerid, const params[]) return admsys_cmd_admins(playerid, params);
admsys_cmd_admins(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid))
	{
		static strtmp[296];
		strtmp[0] = EOS;
		static strtmp2[59], strtmp3[MAX_PLAYER_NAME + 1];
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			if(IsPlayerAdminEx(i))
			{
				GetPlayerName(i, strtmp3, sizeof strtmp3);
				format(strtmp2, sizeof strtmp2, "Administrator %s[%d] [Level %d]\n", strtmp3, i, GetPlayerAdminLevel(i));
				strcat(strtmp, strtmp2);
			}
		}
		if(strtmp[0] == '\0') strtmp = "Right now no administrators online";
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_ADMINS, DIALOG_STYLE_MSGBOX, "Administrators online", strtmp, "Ok", "");
	}
	return 1;
}

CMD:eject(playerid, const params[]) return admsys_cmd_eject(playerid, params);
admsys_cmd_eject(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		new strtmp[66];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_eject(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /eject [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(!IsPlayerInAnyVehicle(giveid))
				{
					if(i == 1)
					{
						if(giveid == playerid) strtmp = "You are not in vehicle";
						else strtmp = "Player is not in vehicle";
					}
					else format(strtmp, sizeof strtmp, "Player %d is not in vehicle", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					RemovePlayerFromVehicle(giveid);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "You removed %s[%d] from vehicle", strname2, giveid);
					SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
					format(strtmp, sizeof strtmp, "Administrator %s removed you from vehicle", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:spec(playerid, params[]) return admsys_cmd_spec(playerid, params);
admsys_cmd_spec(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /spec [id]");
		if(!strcmp(params, "off", true)) return admsys_cmd_specoff(playerid, "\1");
		if(!strcmp(params, "update", true)) return admsys_cmd_specupdate(playerid, "\1");
		if(!admsys_IsNumeric(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /spec [id]");
		params[0] = strval(params);
		if(!StartSpectating(playerid, params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
	}
	return 1;
}

CMD:specupdate(playerid, const params[]) return admsys_cmd_specupdate(playerid, params);
admsys_cmd_specupdate(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid, 2)) UpdateSpectating(playerid);
	return 1;
}

CMD:specoff(playerid, const params[]) return admsys_cmd_specoff(playerid, params);
admsys_cmd_specoff(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid, 2)) StopSpectating(playerid);
	return 1;
}

CMD:spawnveh(playerid, params[]) return admsys_cmd_spawnveh(playerid, params);
CMD:spawnvehicle(playerid, params[]) return admsys_cmd_spawnveh(playerid, params);
admsys_cmd_spawnveh(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params))
		{
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are not in vehicle");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /spawnveh [vehicle id]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Vehicle is not found");
		}
		static strtmp[24];
		SetVehicleToRespawn(params[0]);
		format(strtmp, sizeof strtmp, "Vehicle id %d spawned", params[0]);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:mute(playerid, const params[]) return admsys_cmd_mute(playerid, params);
admsys_cmd_mute(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /mute [id] [time] [reason]");
		static strtmp[145];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /mute [id] [time] [reason]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(AdmSysInfo[giveid][asMuteTime] > 0) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is already muted");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't apply this action to the administrator");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /mute [id] [time] [reason]");
		new gtime = strval(strtmp);
		if(!(1 <= gtime <= 60)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "The time must be from 1 to 60 minutes");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /mute [id] [time] [reason]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		AdmSysInfo[giveid][asMuteTime] = gtime * 60;
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Administrator %s muted %s[%d] on %d minutes. Reason: %s", strname, strname2, giveid, gtime, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Administrator %s muted you on %d minutes. Reason: %s", strname, gtime, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:unmute(playerid, const params[]) return admsys_cmd_unmute(playerid, params);
admsys_cmd_unmute(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		new strtmp[92];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_unmute(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /unmute [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(AdmSysInfo[giveid][asMuteTime] < 1)
				{
					if(i == 1) strtmp = "Player is not muted";
					else format(strtmp, sizeof strtmp, "Player %d is not muted", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					AdmSysInfo[giveid][asMuteTime] = 0;
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Administrator %s unmuted %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Administrator %s unmuted you", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:asay(playerid, const params[]) return admsys_cmd_asay(playerid, params);
CMD:admsay(playerid, const params[]) return admsys_cmd_asay(playerid, params);
CMD:adminsay(playerid, const params[]) return admsys_cmd_asay(playerid, params);
admsys_cmd_asay(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /asay [text]");
		static strtmp[145], strname[MAX_PLAYER_NAME + 1];
		strtmp = "Administrator ";
		GetPlayerName(playerid, strname, sizeof strname);
		strcat(strtmp, strname);
		strcat(strtmp, ": ");
		strcat(strtmp, params);
		SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:warn(playerid, const params[]) return admsys_cmd_warn(playerid, params);
admsys_cmd_warn(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /warn [id] [reason]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /warn [id] [reason]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't apply this action to the administrator");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /warn [id] [reason]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		AdmSysInfo[giveid][asWarns]++;
		CallRemoteFunction("OnPlayerWarn", "iii", giveid, playerid, AdmSysInfo[giveid][asWarns]);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Administrator %s has given %s[%d] a warn. Reason: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Administrator %s has given you a warn. Reason: %s", strname, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
		if(AdmSysInfo[giveid][asWarns] > ADMSYS_MAX_WARNS) return admsys_cmd_ban(playerid, params);
	}
	return 1;
}

CMD:kick(playerid, const params[]) return admsys_cmd_kick(playerid, params);
admsys_cmd_kick(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /kick [id] [reason]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /kick [id] [reason]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't apply this action to the administrator");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /kick [id] [reason]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		CallRemoteFunction("OnPlayerKick", "iii", giveid, playerid, false);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Administrator %s has kicked %s[%d]. Reason: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Administrator %s has kicked you. Reason: %s", strname, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
		SetTimerEx("KickWithDelay", 500, 0, "i", giveid);
	}
	return 1;
}

CMD:freeze(playerid, const params[]) return admsys_cmd_freeze(playerid, params);
admsys_cmd_freeze(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		new strtmp[90];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_freeze(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /freeze [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					TogglePlayerControllable(giveid, 0);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Administrator %s froze %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Administrator %s froze you", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:unfreeze(playerid, const params[]) return admsys_cmd_unfreeze(playerid, params);
admsys_cmd_unfreeze(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		new strtmp[92];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_unfreeze(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /unfreeze [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					TogglePlayerControllable(giveid, 1);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Administrator %s unfroze %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Administrator %s unfroze you", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:slap(playerid, const params[]) return admsys_cmd_slap(playerid, params);
admsys_cmd_slap(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /slap [id] [reason]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /slap [id] [reason]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't apply this action to the administrator");
		if(IsPlayerSpectating(giveid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is in spectator mode");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /slap [id] [reason]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(giveid, pX, pY, pZ);
		SetPlayerPos(giveid, pX, pY, pZ + 8.0);
		PlayerPlaySound(giveid, 1130, 0.0, 0.0, 0.0);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Administrator %s slapped %s[%d]. Reason: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Administrator %s slapped you. Reason: %s", strname, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:goto(playerid, params[]) return admsys_cmd_goto(playerid, params);
admsys_cmd_goto(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		if(IsPlayerSpectating(playerid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are in spectator mode");
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /goto [id]");
		params[0] = strval(params);
		if(params[0] == playerid) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't specify your id");
		if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		static strtmp[54], strname[MAX_PLAYER_NAME + 1];
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(params[0], pX, pY, pZ);
		SetPlayerPos(playerid, pX + 1.0, pY + 1.0, pZ);
		SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
		GetPlayerName(params[0], strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You are teleported to %s[%d]", strname, params[0]);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:suspectlist(playerid, const params[]) return admsys_cmd_suspectlist(playerid, params);
admsys_cmd_suspectlist(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid, 3))
	{
		UpdateSuspectList();
		new c;
		static strtmp[337], strtmp2[43], iname[MAX_PLAYER_NAME + 1];
		strtmp[0] = EOS;
		for(new i; i < sizeof SuspectList; ++i)
		{
			if(SuspectList[i] != INVALID_PLAYER_ID)
			{
				GetPlayerName(SuspectList[i], iname, sizeof iname);
				format(strtmp2, sizeof strtmp2, "%d. %s [ID: %d]\n", i + 1, iname, SuspectList[i]);
				strcat(strtmp, strtmp2);
				c++;
			}
		}
		if(c) ShowPlayerDialog(playerid, ADMSYS_DIALOG_SUSPECT_LIST, DIALOG_STYLE_LIST, "Waiting for checking", strtmp, "Ok", "Close");
		else SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, "List is empty");
	}
	return 1;
}

CMD:gethere(playerid, const params[]) return admsys_cmd_gethere(playerid, params);
CMD:get(playerid, const params[]) return admsys_cmd_gethere(playerid, params);
admsys_cmd_gethere(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gethere [id]");
		if(!strcmp(params, "all", true)) return admsys_cmd_getall(playerid, "\1");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		new strtmp[67], interior, vw, Float:pX, Float:pY, Float:pZ;
		GetPlayerName(playerid, strname, sizeof strname);
		interior = GetPlayerInterior(playerid);
		vw = GetPlayerVirtualWorld(playerid);
		GetPlayerPos(playerid, pX, pY, pZ);
		pX += 1.0;
		pY += 1.0;
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /gethere [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(giveid == playerid) SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't specify your id");
				else if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					SetPlayerPos(giveid, pX, pY, pZ);
					SetPlayerVirtualWorld(giveid, vw);
					SetPlayerInterior(giveid, interior);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "You teleported %s[%d] to himself", strname2, giveid);
					SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
					format(strtmp, sizeof strtmp, "Administrator %s teleported you to himself", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:gotoveh(playerid, params[]) return admsys_cmd_gotoveh(playerid, params);
CMD:gotovehicle(playerid, params[]) return admsys_cmd_gotoveh(playerid, params);
admsys_cmd_gotoveh(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(IsPlayerSpectating(playerid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are in spectator mode");
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gotoveh [vehicle id]");
		params[0] = strval(params);
		if(GetVehicleModel(params[0]) <= 0) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Vehicle is not found");
		static strtmp[50];
		new Float:vX, Float:vY, Float:vZ;
		GetVehiclePos(params[0], vX, vY, vZ);
		SetPlayerPos(playerid, vX, vY, vZ + 2.5);
		SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(params[0]));
		format(strtmp, sizeof strtmp, "You are teleported to vehicle id %d", params[0]);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:gotopos(playerid, params[]) return admsys_cmd_gotopos(playerid, params);
CMD:gotoposition(playerid, params[]) return admsys_cmd_gotopos(playerid, params);
admsys_cmd_gotopos(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(IsPlayerSpectating(playerid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are in spectator mode");
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gotopos [x] [y] [z]");
		static strtmp[76];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gotopos [x] [y] [z]");
		new Float:cX = floatstr(strtmp);
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gotopos [x] [y] [z]");
		new Float:cY = floatstr(strtmp);
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gotopos [x] [y] [z]");
		new Float:cZ = floatstr(strtmp);
		SetPlayerPos(playerid, cX, cY, cZ);
		format(strtmp, sizeof strtmp, "You are teleported to coordinates %.4f, %.4f, %.4f", cX, cY, cZ);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:ban(playerid, const params[]) return admsys_cmd_ban(playerid, params);
admsys_cmd_ban(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /ban [id] [reason]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /ban [id] [reason]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't apply this action to the administrator");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /ban [id] [reason]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		CallRemoteFunction("OnPlayerBan", "iii", giveid, playerid, false);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Administrator %s has banned %s[%d]. Reason: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Administrator %s has banned you. Reason: %s", strname, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
		SetTimerEx("BanWithDelay", 500, 0, "i", giveid);
	}
	return 1;
}

CMD:gmtest(playerid, params[]) return admsys_cmd_gmtest(playerid, params);
admsys_cmd_gmtest(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /gmtest [id]");
		params[0] = strval(params);
		if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		if(AdmSysInfo[playerid][asGmTestID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are already checking someone for GodMode");
		if(AdmSysInfo[params[0]][asGmTest])
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is already being checked for GodMode");
		if(!AdmSysInfo[params[0]][asIsSpawned])
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not spawned");
		if(IsPlayerSpectating(params[0]))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is in spectator mode");
		new Float:bx, Float:by, Float:bz;
		GetPlayerPos(params[0], bx, by, bz);
		if(!IsPlayerInAnyVehicle(params[0]))
		{
			GetPlayerHealth(params[0], AdmSysInfo[params[0]][asGmTestHP]);
			GetPlayerArmour(params[0], AdmSysInfo[params[0]][asGmTestAR]);
		}
		else GetVehicleHealth(GetPlayerVehicleID(params[0]), AdmSysInfo[params[0]][asGmTestHP]);
		AdmSysInfo[params[0]][asGmTest] = true;
		AdmSysInfo[playerid][asGmTestID] = params[0];
		CreateExplosionForPlayer(params[0], bx, by, bz + 7.5, 5, 0.5);
		SetTimerEx("GmTest", 1000, 0, "d", playerid);
	}
	return 1;
}

CMD:spawn(playerid, const params[]) return admsys_cmd_spawn(playerid, params);
admsys_cmd_spawn(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		new strtmp[102];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_spawn(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /spawn [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					if(IsPlayerSpectating(giveid)) TogglePlayerSpectating(giveid, 0);
					else SpawnPlayer(giveid);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Administrator %s has spawned %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Administrator %s has spawned you", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:unwarn(playerid, const params[]) return admsys_cmd_unwarn(playerid, params);
admsys_cmd_unwarn(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		new strtmp[108];
		if(admsys_isnull(params))
		{
			format(strtmp, sizeof strtmp, "%d", playerid);
			return admsys_cmd_unwarn(playerid, strtmp);
		}
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		for(new i = 1, pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /unwarn [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strname2, sizeof strname2, " [id %d]", j);
							strcat(strtmp, strname2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(AdmSysInfo[giveid][asWarns] < 1)
				{
					if(i == 1) strtmp = "Player has no warns";
					else format(strtmp, sizeof strtmp, "Player %d has no warns", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					AdmSysInfo[giveid][asWarns]--;
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Administrator %s has removed a warn from %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Administrator %s has removed a warn from you", strname);
					SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
				}
			}
		}
	}
	return 1;
}

CMD:banip(playerid, const params[]) return admsys_cmd_banip(playerid, params);
CMD:blockip(playerid, const params[]) return admsys_cmd_banip(playerid, params);
admsys_cmd_banip(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /banip [IP]");
		for(new i, c, j = strlen(params); i < j; i++)
		{
			switch(params[i])
			{
				case '*':
				{
					if(c < 2) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP address entered incorrectly");
				}
				case '.': c++;
				case '0'..'9':{}
				default: return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP address entered incorrectly");
			}
		}
		static strtmp[74], strname[MAX_PLAYER_NAME + 1];
		format(strtmp, sizeof strtmp, "banip %s", params);
		SendRconCommand(strtmp);
		SendRconCommand("reloadbans");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has blocked IP %s", strname, params);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
	}
	return 1;
}

CMD:cc(playerid, const params[]) return admsys_cmd_cc(playerid, params);
CMD:clearchat(playerid, const params[]) return admsys_cmd_cc(playerid, params);
admsys_cmd_cc(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid, 3))
	{
		static strtmp[62], strname[MAX_PLAYER_NAME + 1];
		for(new i = 30; i >= 0; --i) SendClientMessageToAll(-1, " ");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has cleared the chat", strname);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
	}
	return 1;
}

CMD:sethealth(playerid, const params[]) return admsys_cmd_sethealth(playerid, params);
admsys_cmd_sethealth(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /sethealth [id] [health]");
		static strtmp[72];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /sethealth [id] [health]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /sethealth [id] [health]");
		static strname[MAX_PLAYER_NAME + 1];
		new Float:ghealth = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 1;
		GetPlayerHealth(giveid, AdmSysInfo[playerid][asLastFloatData]);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerHealth(giveid, ghealth);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set health to %.1f to %s[%d]", ghealth, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set your health to %.1f", strname, ghealth);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setarmour(playerid, const params[]) return admsys_cmd_setarmour(playerid, params);
admsys_cmd_setarmour(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setarmour [id] [armour]");
		static strtmp[72];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setarmour [id] [armour]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setarmour [id] [armour]");
		static strname[MAX_PLAYER_NAME + 1];
		new Float:garmour = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 2;
		GetPlayerArmour(giveid, AdmSysInfo[playerid][asLastFloatData]);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerArmour(giveid, garmour);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set armour to %.1f to %s[%d]", garmour, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set your armour to %.1f", strname, garmour);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setmoney(playerid, const params[]) return admsys_cmd_setmoney(playerid, params);
admsys_cmd_setmoney(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setmoney [id] [money]");
		static strtmp[64];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setmoney [id] [money]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setmoney [id] [money]");
		static strname[MAX_PLAYER_NAME + 1];
		new gmoney = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 3;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerMoney(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		ResetPlayerMoney(giveid);
		GivePlayerMoney(giveid, gmoney);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set $%d to %s[%d]", gmoney, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set you $%d", strname, gmoney);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:givemoney(playerid, const params[]) return admsys_cmd_givemoney(playerid, params);
admsys_cmd_givemoney(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /givemoney [id] [money]");
		static strtmp[62];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /givemoney [id] [money]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /givemoney [id] [money]");
		static strname[MAX_PLAYER_NAME + 1];
		new gmoney = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 4;
		AdmSysInfo[playerid][asLastIntData][0] = gmoney;
		AdmSysInfo[playerid][asLastActionID] = giveid;
		GivePlayerMoney(giveid, gmoney);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You gave $%d to %s[%d]", gmoney, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s gave you $%d", strname, gmoney);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setscore(playerid, const params[]) return admsys_cmd_setscore(playerid, params);
admsys_cmd_setscore(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setscore [id] [score]");
		static strtmp[66];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setscore [id] [score]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setscore [id] [score]");
		static strname[MAX_PLAYER_NAME + 1];
		new gscore = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 5;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerScore(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerScore(giveid, gscore);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set score to %d to %s[%d]", gscore, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set your score to %d", strname, gscore);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setskin(playerid, const params[]) return admsys_cmd_setskin(playerid, params);
admsys_cmd_setskin(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setskin [id] [skin]");
		static strtmp[66];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setskin [id] [skin]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setskin [id] [skin]");
		new skinid = strval(strtmp);
		if(!(0 <= skinid <= 311)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Skin ID must be from 0 to 311");
		static strname[MAX_PLAYER_NAME + 1];
		AdmSysInfo[playerid][asLastAction] = 6;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerSkin(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerSkin(giveid, skinid);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have changed the skin to %d to %s[%d]", skinid, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has changed your skin to %d", strname, skinid);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setint(playerid, const params[]) return admsys_cmd_setint(playerid, params);
CMD:setinterior(playerid, const params[]) return admsys_cmd_setint(playerid, params);
admsys_cmd_setint(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setint [id] [interior]");
		static strtmp[70];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setint [id] [interior]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setint [id] [interior]");
		static strname[MAX_PLAYER_NAME + 1];
		new gint = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 7;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerInterior(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerInterior(giveid, gint);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set the interior to %d to %s[%d]", gint, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set your interior to %d", strname, gint);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setvw(playerid, const params[]) return admsys_cmd_setvw(playerid, params);
CMD:setvirtualworld(playerid, const params[]) return admsys_cmd_setvw(playerid, params);
admsys_cmd_setvw(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setvw [id] [vw]");
		static strtmp[82];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setvw [id] [vw]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setvw [id] [vw]");
		static strname[MAX_PLAYER_NAME + 1];
		new gvw = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 8;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerVirtualWorld(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerVirtualWorld(giveid, gvw);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You have set the virtual world to %d to %s[%d]", gvw, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s has set your virtual world to %d", strname, gvw);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:giveweapon(playerid, const params[]) return admsys_cmd_giveweapon(playerid, params);
admsys_cmd_giveweapon(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /giveweapon [id] [weapon] [ammo]");
		static strtmp[77];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /giveweapon [id] [weapon] [ammo]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not found");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /giveweapon [id] [weapon] [ammo]");
		new gweapon = strval(strtmp);
		if(!(0 <= gweapon <= 46)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Weapon ID must be from 0 to 46");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /giveweapon [id] [weapon] [ammo]");
		static strname[MAX_PLAYER_NAME + 1];
		new gammo = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 9;
		AdmSysInfo[playerid][asLastIntData][0] = gweapon;
		AdmSysInfo[playerid][asLastIntData][1] = gammo;
		AdmSysInfo[playerid][asLastActionID] = giveid;
		GivePlayerWeapon(giveid, gweapon, gammo);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "You gave the weapon %d with %d ammo to %s[%d]", gweapon, gammo, strname, giveid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s gave you weapon %d with %d ammo", strname, gweapon, gammo);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:repairveh(playerid, params[]) return admsys_cmd_repairveh(playerid, params);
CMD:repairvehicle(playerid, params[]) return admsys_cmd_repairveh(playerid, params);
admsys_cmd_repairveh(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params))
		{
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are not in vehicle");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /repairveh [vehicle id]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Vehicle is not found");
		}
		static strtmp[25];
		RepairVehicle(params[0]);
		format(strtmp, sizeof strtmp, "Vehicle id %d repaired", params[0]);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:unbanip(playerid, const params[]) return admsys_cmd_unbanip(playerid, params);
CMD:unblockip(playerid, const params[]) return admsys_cmd_unbanip(playerid, params);
admsys_cmd_unbanip(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /unbanip [IP]");
		for(new i, j = strlen(params); i < j; i++)
		{
			switch(params[i])
			{
				case '*', '.', '0'..'9':{}
				default: return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP address entered incorrectly");
			}
		}
		static strtmp[76], strname[MAX_PLAYER_NAME + 1];
		format(strtmp, sizeof strtmp, "unbanip %s", params);
		SendRconCommand(strtmp);
		SendRconCommand("reloadbans");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s unblocked the IP %s", strname, params);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(4, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
	}
	return 1;
}

CMD:setweather(playerid, params[]) return admsys_cmd_setweather(playerid, params);
admsys_cmd_setweather(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /setweather [weather]");
		params[0] = strval(params);
		if(!(0 <= params[0] <= 20)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Weather ID must be from 0 to 20");
		SetWeather(params[0]);
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			SetPlayerWeather(i, params[0]);
		}
		static strtmp[66], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s changed the weather to %d", strname, params[0]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(5, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
	}
	return 1;
}

CMD:getall(playerid, const params[]) return admsys_cmd_getall(playerid, params);
admsys_cmd_getall(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid, 5))
	{
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(playerid, pX, pY, pZ);
		pX += 1.0;
		pY += 1.0;
		new interior = GetPlayerInterior(playerid), vw = GetPlayerVirtualWorld(playerid);
		#if defined foreach
		foreach(new i : Player)
		{
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		{
			if(!IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
		#endif
			if(i != playerid)
			{
				SetPlayerVirtualWorld(i, vw);
				SetPlayerInterior(i, interior);
				SetPlayerPos(i, pX, pY, pZ);
			}
		}
		static strtmp[67], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s teleported all to himself", strname);
		SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:settime(playerid, params[]) return admsys_cmd_settime(playerid, params);
admsys_cmd_settime(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /settime [hour]");
		params[0] = strval(params);
		if(!(0 <= params[0] <= 23)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "The hour must be between 0 and 23");
		SetWorldTime(params[0]);
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			SetPlayerTime(i, params[0], 0);
		}
		static strtmp[70], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Administrator %s changed the time to %d hours", strname, params[0]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(5, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
	}
	return 1;
}

CMD:destroyveh(playerid, params[]) return admsys_cmd_destroyveh(playerid, params);
CMD:destroyvehicle(playerid, params[]) return admsys_cmd_destroyveh(playerid, params);
admsys_cmd_destroyveh(playerid, params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(admsys_isnull(params))
		{
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are not in vehicle");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /destroyveh [vehicle id]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Vehicle is not found");
		}
		static strtmp[26];
		DestroyVehicle(params[0]);
		format(strtmp, sizeof strtmp, "Vehicle id %d destroyed", params[0]);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:veh(playerid, const params[]) return admsys_cmd_veh(playerid, params);
CMD:vehicle(playerid, const params[]) return admsys_cmd_veh(playerid, params);
admsys_cmd_veh(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(IsPlayerSpectating(playerid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are in spectator mode");
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /veh [vehicle id] [color 1] [color 2]");
		static strtmp[48];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /veh [vehicle id] [color 1] [color 2]");
		new gveh = strval(strtmp);
		if(!(400 <= gveh <= 611)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Vehicle ID must be from 400 to 611");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		new gcolor1, gcolor2;
		if(params[oldpos] == '\0')
		{
			gcolor1 = random(256);
			gcolor2 = random(256);
		}
		else
		{
			while(params[pos] > ' ') pos++;
			strmid(strtmp, params, oldpos, pos);
			if(!admsys_IsNumeric(strtmp))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /veh [vehicle id] [color 1] [color 2]");
			gcolor1 = strval(strtmp);
			if(!(0 <= gcolor1 <= 255))
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Color 1 must be from 0 to 255");
			while(params[pos] == ' ') pos++;
			oldpos = pos;
			while(params[pos] > ' ') pos++;
			strmid(strtmp, params, oldpos, pos);
			if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /veh [vehicle id] [color 1] [color 2]");
			gcolor2 = strval(strtmp);
			if(!(0 <= gcolor2 <= 255))
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Color 2 must be from 0 to 255");
		}
		new vid, Float:pX, Float:pY, Float:pZ, Float:pAngle;
		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pAngle);
		vid = CreateVehicle(gveh, pX, pY, pZ, pAngle, gcolor1, gcolor2, -1);
		SetVehicleVirtualWorld(vid, GetPlayerVirtualWorld(playerid));
		LinkVehicleToInterior(vid, GetPlayerInterior(playerid));
		PutPlayerInVehicle(playerid, vid, 0);
		format(strtmp, sizeof strtmp, "Vehicle id %d with colors %d and %d spawned", vid, gcolor1, gcolor2);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:skick(playerid, const params[]) return admsys_cmd_skick(playerid, params);
CMD:silentkick(playerid, const params[]) return admsys_cmd_skick(playerid, params);
admsys_cmd_skick(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /skick [id]");
		static strtmp2[10];
		for(new i = 1, strtmp[32], pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /skick [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strtmp2, sizeof strtmp2, " [id %d]", j);
							strcat(strtmp, strtmp2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					CallRemoteFunction("OnPlayerKick", "iii", giveid, playerid, true);
					Kick(giveid);
				}
			}
		}
	}
	return 1;
}

CMD:sban(playerid, const params[]) return admsys_cmd_sban(playerid, params);
CMD:silentban(playerid, const params[]) return admsys_cmd_sban(playerid, params);
admsys_cmd_sban(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 5))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Use: /sban [id]");
		static strtmp2[10];
		for(new i = 1, strtmp[32], pos, oldpos, giveid, j; i <= ADMSYS_MAX_GIVE_PLAYERS_IN_CMD; i++)
		{
			while(params[pos] == ' ') pos++;
			if(params[pos])
			{
				oldpos = pos;
				while(params[pos] > ' ') pos++;
				strmid(strtmp, params, oldpos, pos);
				if(!admsys_IsNumeric(strtmp))
				{
					strtmp = "Use: /sban [id]";
					if(i > 1)
					{
						for(j = 2; j <= i; j++)
						{
							format(strtmp2, sizeof strtmp2, " [id %d]", j);
							strcat(strtmp, strtmp2);
						}
					}
					return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, strtmp);
				}
				giveid = strval(strtmp);
				if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Player is not found";
					else format(strtmp, sizeof strtmp, "Player %d is not found", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					CallRemoteFunction("OnPlayerBan", "iii", giveid, playerid, true);
					Ban(giveid);
				}
			}
		}
	}
	return 1;
}

stock SetPlayerAdminLevel(playerid, lvl)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(!(0 <= lvl <= 5)) return -1;
	AdmSysInfo[playerid][asAdminLvl] = lvl;
	return 1;
}

stock GetPlayerAdminLevel(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(IsPlayerAdmin(playerid)) return 5;
	return AdmSysInfo[playerid][asAdminLvl];
}

stock IsPlayerAdminEx(playerid, lvl = 1) return (GetPlayerAdminLevel(playerid) >= lvl);

stock SetPlayerMuteTime(playerid, time)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(time < 0) return -1;
	AdmSysInfo[playerid][asMuteTime] = time;
	return 1;
}

stock GetPlayerMuteTime(playerid) return (IsPlayerConnected(playerid) ? AdmSysInfo[playerid][asMuteTime] : 0);

stock UpdateSuspectList()
{
	new c;
	for(new i, j; i < sizeof SuspectList; ++i)
	{
		if(!IsPlayerConnected(SuspectList[i]))
		{
			c++;
			for(j = i; j < sizeof(SuspectList) - 1; ++j) SuspectList[j] = SuspectList[j + 1];
			SuspectList[j] = INVALID_PLAYER_ID;
		}
	}
	return c;
}

stock AddPlayerInSuspectList(playerid)
{
	UpdateSuspectList();
	if(IsPlayerConnected(playerid))
	{
		new i;
		for(i = sizeof(SuspectList) - 1; i >= 0; --i)
		{
			if(SuspectList[i] == playerid) return 0;
		}
		new tmp1 = SuspectList[0], tmp2;
		for(i = 0; i < sizeof(SuspectList) - 1; ++i)
		{
			tmp2 = SuspectList[i + 1];
			SuspectList[i + 1] = tmp1;
			tmp1 = tmp2;
		}
		SuspectList[0] = playerid;
		return 1;
	}
	return 0;
}

stock RemovePlayerFromSuspectList(playerid)
{
	for(new i = sizeof(SuspectList) - 1; i >= 0; --i)
	{
		if(SuspectList[i] == playerid)
		{
			SuspectList[i] = INVALID_PLAYER_ID;
			break;
		}
	}
	UpdateSuspectList();
	return 1;
}

stock SendMessageToAdmins(lvl, color, const msg[])
{
	#if defined foreach
	foreach(new i : Player)
	#else
	for(new i = GetPlayerPoolSize(); i >= 0; --i)
	#endif
	{
		if(GetPlayerAdminLevel(i) >= lvl) SendClientMessage(i, color, msg);
	}
	return 1;
}

static stock admsys_IsNumeric(const string[])
{
	new ret;
	for(new i, l = strlen(string); i < l; i++)
	{
		if('0' <= string[i] <= '9') ret = 1;
		else if(i != 0 || string[0] != '-') return 0;
	}
	return ret;
}

static stock admsys_IsNumericEx(const string[])
{
	new ret;
	for(new i, c, l = strlen(string); i < l; i++)
	{
		if('0' <= string[i] <= '9') ret = 1;
		else if(string[i] == '.')
		{
			if(ret)
			{
				c++;
				if(c > 1) return 0;
				ret = 0;
			}
			else return 0;
		}
		else if(i != 0 || string[0] != '-') return 0;
	}
	return ret;
}

static IsPlayerSpectating(playerid) return IsPlayerConnected(AdmSysInfo[playerid][asSpecID]);

static StartSpectating(playerid, specid)
{
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(specid)) return 0;
	if(playerid == specid) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You can't spectate yourself");
	if(IsPlayerSpectating(specid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is in spectator mode");
	if(AdmSysInfo[playerid][asSpecID] == specid) return UpdateSpectating(playerid);
	if(!AdmSysInfo[specid][asIsSpawned] && !AdmSysInfo[specid][asIsDead])
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player is not spawned");
	if(!IsPlayerSpectating(playerid))
	{
		for(new i = 12; i >= 0; --i)
			GetPlayerWeaponData(playerid, i, AdmSysInfo[playerid][asLastWeapon][i], AdmSysInfo[playerid][asLastAmmo][i]);
		GetPlayerPos(playerid, AdmSysInfo[playerid][asLastPos][0],
		AdmSysInfo[playerid][asLastPos][1], AdmSysInfo[playerid][asLastPos][2]);
		AdmSysInfo[playerid][asLastSpec] = (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING);
		GetPlayerFacingAngle(playerid, AdmSysInfo[playerid][asLastAngle]);
		AdmSysInfo[playerid][asLastVW] = GetPlayerVirtualWorld(playerid);
		AdmSysInfo[playerid][asLastInt] = GetPlayerInterior(playerid);
	}
	AdmSysInfo[playerid][asLastSpecID] = AdmSysInfo[playerid][asSpecID];
	TogglePlayerSpectating(playerid, 1);
	if(AdmSysInfo[specid][asIsDead]) SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Player has died");
	SetPlayerInterior(playerid, GetPlayerInterior(specid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specid));
	if(IsPlayerInAnyVehicle(specid)) PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specid));
	else PlayerSpectatePlayer(playerid, specid);
	AdmSysInfo[playerid][asSpecID] = specid;
	UpdateSpecInfo(playerid);
	return 1;
}

static UpdateSpectating(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AdmSysInfo[playerid][asSpecID] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are not in spectator mode");
	if(!IsPlayerConnected(AdmSysInfo[playerid][asSpecID])) return StopSpectating(playerid);
	TogglePlayerSpectating(playerid, 1);
	SetPlayerInterior(playerid, GetPlayerInterior(AdmSysInfo[playerid][asSpecID]));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(AdmSysInfo[playerid][asSpecID]));
	if(IsPlayerInAnyVehicle(AdmSysInfo[playerid][asSpecID]))
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(AdmSysInfo[playerid][asSpecID]));
	else PlayerSpectatePlayer(playerid, AdmSysInfo[playerid][asSpecID]);
	return 1;
}

static StopSpectating(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AdmSysInfo[playerid][asSpecID] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "You are not in spectator mode");
	if(AdmSysInfo[playerid][asLastSpecID] == INVALID_PLAYER_ID || AdmSysInfo[playerid][asLastSpecID] == AdmSysInfo[playerid][asSpecID])
	{
		AdmSysInfo[playerid][asSpecID] = INVALID_PLAYER_ID;
		AdmSysInfo[playerid][asLastSpecID] = INVALID_PLAYER_ID;
		TogglePlayerSpectating(playerid, AdmSysInfo[playerid][asLastSpec]);
		KillTimer(AdmSysInfo[playerid][asUpdTimer]);
	}
	else
	{
		AdmSysInfo[playerid][asSpecID] = AdmSysInfo[playerid][asLastSpecID];
		AdmSysInfo[playerid][asLastSpecID] = INVALID_PLAYER_ID;
		UpdateSpectating(playerid);
	}
	return 1;
}

#if ADMSYS_SEND_CONNECT_MSGS_TO_ADM
	#undef ADMSYS_CONNECT_MSG_COLOR
#endif

#undef ADMSYS_SHOW_KILL_LIST_FOR_ADM
#undef ADMSYS_SEND_CONNECT_MSGS_TO_ADM
#undef ADMSYS_SEND_ACTION_MSGS_TO_ALL

#undef ADMSYS_DEFAULT_COLOR
#undef ADMSYS_ADM_CHAT_COLOR
#undef ADMSYS_ADM_ACTION_COLOR
#undef ADMSYS_REPORT_COLOR
#undef ADMSYS_CMD_HELPER_COLOR
#undef ADMSYS_ERROR_COLOR

#undef ADMSYS_MAX_WARNS
#undef ADMSYS_MAX_TAB_INPUT
#undef ADMSYS_MAX_SUSPECTS_IN_TABLE
#undef ADMSYS_MAX_GIVE_PLAYERS_IN_CMD

#undef admsys_isnull
#undef admsys_fpublic
