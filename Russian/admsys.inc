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
	"Уровень 1:\n",
	"/achat [текст] - Админ чат\n",
	"/ahelp - Помощь по админ командам\n",
	"/showstats [id] - Показать статистику игрока\n",
	"/answer [id] [текст] - Ответить игроку на report\n",
	"/apanel - Админ-панель со всеми доступными командами\n",
	"/admins - Список администраторов онлайн\n",
	"/eject [id] - Высадить игрока из транспорта"
},

AdmSys2LvlCmds[][] =
{
	"Уровень 2:\n",
	"/spec [id] - Войти в режим наблюдения за игроком\n",
	"/spawnveh [id транспорта] - Телепортировать транспорт на респавн\n",
	"/(un)mute [id] [время] [причина] - Выдать/снять с игрока молчанку\n",
	"/asay [текст] - Сообщение в формате: 'Администратор: [текст]'\n",
	"/warn [id] [причина] - Выдать предупреждение игроку\n",
	"/kick [id] [причина] - Выкинуть игрока с сервера\n",
	"/(un)freeze [id] - Заморозить/разморозить игрока\n",
	"/slap [id] [причина] - Дать пинка игроку\n",
	"/goto [id] - Телепортироваться к игроку"
},

AdmSys3LvlCmds[][] =
{
	"Уровень 3:\n",
	"/suspectlist - Список подозреваемых игроков\n",
	"/gethere [id] - Телепортировать игрока к себе\n",
	"/gotoveh [id транспорта] - Телепортироваться к транспорту\n",
	"/gotopos [x] [y] [z] - Телепортироваться на координаты\n",
	"/ban [id] [причина] - Заблокировать аккаунт игрока\n",
	"/gmtest [id] - Проверка на бесконечное здоровье\n",
	"/spawn [id] - Телепортировать игрока на респавн\n",
	"/unwarn [id] - Снять предупреждение с игрока\n",
	"/banip [IP] - Блокировка IP-адреса\n",
	"/cc - Очистка чата"
},

AdmSys4LvlCmds[][] =
{
	"Уровень 4:\n",
	"/sethealth [id] [здоровье] - Установить здоровье игроку\n",
	"/setarmour [id] [броня] - Установить броню игроку\n",
	"/setmoney [id] [деньги] - Установить деньги игроку\n",
	"/givemoney [id] [деньги] - Выдать деньги игроку\n",
	"/setscore [id] [очки] - Установить очки (уровень) игроку\n",
	"/setskin [id] [id скина] - Установить скин игроку\n",
	"/setint [id] [интерьер] - Установить игроку интерьер\n",
	"/setvw [id] [номер] - Установить игроку виртуальный мир\n",
	"/giveweapon [id] [оружие] [патроны] - Выдать игроку оружие\n",
	"/repairveh [id транспорта] - Отремонтировать транспорт\n",
	"/unbanip [IP] - Разблокировать IP-адрес"
},

AdmSys5LvlCmds[][] =
{
	"Уровень 5:\n",
	"/getall - Телепортировать всех к себе\n",
	"/setweather [номер] - Установить погоду\n",
	"/settime [час] - Установить время суток\n",
	"/destroyveh [id транспорта] - Уничтожить транспорт\n",
	"/veh [id транспорта] [цвет 1] [цвет 2] - Создать транспорт\n",
	"/sban [id] - Тихая блокировка\n",
	"/skick [id] - Тихий кик"
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

	AdmSys1LvlCmdsStr[303],
	AdmSys2LvlCmdsStr[484],
	AdmSys3LvlCmdsStr[460],
	AdmSys4LvlCmdsStr[586],
	AdmSys5LvlCmdsStr[293];

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
		format(strtmp, sizeof strtmp, "[IP: %s] %s[%d] подключился к серверу", sip, sname, playerid);
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
			SendClientMessage(i, ADMSYS_ERROR_COLOR, "Игрок отключился");
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
			SendClientMessage(i, ADMSYS_ERROR_COLOR, "Игрок умер");
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
	static strtmp[61];
	if(AdmSysInfo[playerid][asMuteTime] > 0)
	{
		format(strtmp, sizeof strtmp, "Вы заглушены. До конца молчанки осталось %d минут %d секунд",
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
				SendClientMessage(i, ADMSYS_ERROR_COLOR, "Игрок в режиме наблюдения");
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
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ANSWER, DIALOG_STYLE_INPUT, "Ответить на report", "Введите ответ на report:", "Ок", "Закрыть");
					case 2: admsys_cmd_eject(playerid, strtmp);
					case 3: admsys_cmd_spec(playerid, strtmp);
					case 4:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Выдать молчанку", "Введите время молчанки:", "Ок", "Закрыть");
					case 5: admsys_cmd_unmute(playerid, strtmp);
					case 6:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_WARN, DIALOG_STYLE_INPUT, "Выдать предупреждение", "Введите причину выдачи предупреждения:", "Ок", "Закрыть");
					case 7:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_KICK, DIALOG_STYLE_INPUT, "Выкинуть с сервера", "Введите причину кика:", "Ок", "Закрыть");
					case 8: admsys_cmd_freeze(playerid, strtmp);
					case 9: admsys_cmd_unfreeze(playerid, strtmp);
					case 10:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SLAP, DIALOG_STYLE_INPUT, "Дать пинка", "Введите причину выдачи пинка:", "Ок", "Закрыть");
					case 11: admsys_cmd_goto(playerid, strtmp);
					case 12: admsys_cmd_gethere(playerid, strtmp);
					case 13:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN, DIALOG_STYLE_INPUT, "Заблокировать аккаунт", "Введите причину блокировки:", "Ок", "Закрыть");
					case 14: admsys_cmd_gmtest(playerid, strtmp);
					case 15: admsys_cmd_spawn(playerid, strtmp);
					case 16: admsys_cmd_unwarn(playerid, strtmp);
					case 17:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_HEALTH, DIALOG_STYLE_INPUT, "Установить здоровье", "Введите количество здоровья, которое вы хотите установить:", "Ок", "Закрыть");
					case 18:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_ARMOUR, DIALOG_STYLE_INPUT, "Установить броню", "Введите количество брони, которое вы хотите установить:", "Ок", "Закрыть");
					case 19:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_MONEY, DIALOG_STYLE_INPUT, "Установить деньги", "Введите количество денег, которое вы хотите установить:", "Ок", "Закрыть");
					case 20:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_MONEY, DIALOG_STYLE_INPUT, "Выдать деньги", "Введите количество денег, которое вы хотите выдать:", "Ок", "Закрыть");
					case 21:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_SCORE, DIALOG_STYLE_INPUT, "Установить очки (уровень)", "Введите количество очков, которое вы хотите установить:", "Ок", "Закрыть");
					case 22:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_CHANGE_SKIN, DIALOG_STYLE_INPUT, "Установить скин", "Введите ID скина, который вы хотите установить:", "Ок", "Закрыть");
					case 23:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_INT, DIALOG_STYLE_INPUT, "Установить интерьер", "Введите ID интерьера, который вы хотите установить:", "Ок", "Закрыть");
					case 24:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_VW, DIALOG_STYLE_INPUT, "Установить виртуальный мир", "Введите ID виртуального мира, который вы хотите установить:", "Ок", "Закрыть");
					case 25:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Выдать оружие", "Введите ID оружия, которое вы хотите выдать:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ANSWER, DIALOG_STYLE_INPUT, "Ответить на report", "Введите ответ на report:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Выдать молчанку", "Введите время молчанки:", "Ок", "Закрыть");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE, DIALOG_STYLE_INPUT, "Выдать молчанку", "Введите причину выдачи молчанки:", "Ок", "Назад");
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_MUTE:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE, DIALOG_STYLE_INPUT, "Выдать молчанку", "Введите причину выдачи молчанки:", "Ок", "Назад");
				else
				{
					static strtmp[145];
					format(strtmp, sizeof strtmp, "%d %s %s", AdmSysInfo[playerid][asTabPanel], AdmSysInfo[playerid][asInput], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_mute(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_MUTE_TIME, DIALOG_STYLE_INPUT, "Выдать молчанку", "Введите время молчанки:", "Ок", "Закрыть");
			return 1;
		}
		case ADMSYS_DIALOG_WARN:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_WARN, DIALOG_STYLE_INPUT, "Выдать предупреждение", "Введите причину выдачи предупреждения:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_KICK, DIALOG_STYLE_INPUT, "Выкинуть с сервера", "Введите причину кика:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SLAP, DIALOG_STYLE_INPUT, "Дать пинка", "Введите причину выдачи пинка:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN, DIALOG_STYLE_INPUT, "Заблокировать аккаунт", "Введите причину блокировки:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_HEALTH, DIALOG_STYLE_INPUT, "Установить здоровье", "Введите количество здоровья, которое вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_ARMOUR, DIALOG_STYLE_INPUT, "Установить броню", "Введите количество брони, которое вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_MONEY, DIALOG_STYLE_INPUT, "Установить деньги", "Введите количество денег, которое вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_MONEY, DIALOG_STYLE_INPUT, "Выдать деньги", "Введите количество денег, которое вы хотите выдать:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_SCORE, DIALOG_STYLE_INPUT, "Установить очки (уровень)", "Введите количество очков, которое вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CHANGE_SKIN, DIALOG_STYLE_INPUT, "Установить скин", "Введите ID скина, который вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_INT, DIALOG_STYLE_INPUT, "Установить интерьер", "Введите ID интерьера, который вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_VW, DIALOG_STYLE_INPUT, "Установить виртуальный мир", "Введите ID виртуального мира, который вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Выдать оружие", "Введите ID оружия, которое вы хотите выдать:", "Ок", "Закрыть");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Выдать оружие", "Введите количество патронов, которое вы хотите выдать:", "Ок", "Назад");
				}
			}
			return 1;
		}
		case ADMSYS_DIALOG_GIVE_WEAPON_AMMO:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Выдать оружие", "Введите количество патронов, которое вы хотите выдать:", "Ок", "Назад");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%d %s %s", AdmSysInfo[playerid][asTabPanel], AdmSysInfo[playerid][asInput], inputtext);
					AdmSysInfo[playerid][asTabPanel] = INVALID_PLAYER_ID;
					admsys_cmd_giveweapon(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_GIVE_WEAPON, DIALOG_STYLE_INPUT, "Выдать оружие", "Введите ID оружия, которое вы хотите выдать:", "Ок", "Закрыть");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_1:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_2, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys2LvlCmdsStr, "Далее", "Назад");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_2:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_3, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys3LvlCmdsStr, "Далее", "Назад");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_1, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys1LvlCmdsStr, "Далее", "Закрыть");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_3:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_4, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys4LvlCmdsStr, "Далее", "Назад");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_2, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys2LvlCmdsStr, "Далее", "Назад");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_4:
		{
			if(response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_5, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys5LvlCmdsStr, "Ок", "Назад");
			else
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_3, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys3LvlCmdsStr, "Далее", "Назад");
			return 1;
		}
		case ADMSYS_DIALOG_AHELP_LVL_5:
		{
			if(!response)
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_4, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys4LvlCmdsStr, "Далее", "Назад");
			return 1;
		}
		case ADMSYS_DIALOG_APANEL:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ACHAT, DIALOG_STYLE_INPUT, "Админ чат", "Напишите ваше сообщение:", "Ок", "Закрыть");
					case 1: admsys_cmd_ahelp(playerid, "\1");
					case 2: admsys_cmd_admins(playerid, "\1");
					case 3:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SPAWN_VEH, DIALOG_STYLE_INPUT, "Телепортировать транспорт на респавн", "Введите ID транспорта, который вы хотите заспавнить:", "Ок", "Закрыть");
					case 4:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_ASAY, DIALOG_STYLE_INPUT, "Сообщение от администратора", "Напишите ваше сообщение:", "Ок", "Закрыть");
					case 5: admsys_cmd_suspectlist(playerid, "\1");
					case 6:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_VEH, DIALOG_STYLE_INPUT, "Телепортироваться к транспорту", "Введите ID транспорта, к которому вы хотите телепортироваться:", "Ок", "Закрыть");
					case 7:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_POS, DIALOG_STYLE_INPUT, "Телепортироваться на координаты", "Введите координаты через пробел, на которые вы хотите телепортироваться:", "Ок", "Закрыть");
					case 8:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN_IP, DIALOG_STYLE_INPUT, "Блокировка IP-адреса", "Введите IP-адрес, который вы хотите заблокировать:", "Ок", "Закрыть");
					case 9: admsys_cmd_cc(playerid, "\1");
					case 10:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_REPAIR_VEH, DIALOG_STYLE_INPUT, "Отремонтировать транспорт", "Введите ID транспорта, который вы хотите отремонтировать:", "Ок", "Закрыть");
					case 11:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_UNBAN_IP, DIALOG_STYLE_INPUT, "Разблокировать IP-адрес", "Введите IP-адрес, который вы хотите разблокировать:", "Ок", "Закрыть");
					case 12: admsys_cmd_getall(playerid, "\1");
					case 13:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_WEATHER, DIALOG_STYLE_INPUT, "Установить погоду", "Введите ID погоды, которую вы хотите установить:", "Ок", "Закрыть");
					case 14:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_TIME, DIALOG_STYLE_INPUT, "Установить время суток", "Введите час, который вы хотите установить:", "Ок", "Закрыть");
					case 15:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_DESTROY_VEH, DIALOG_STYLE_INPUT, "Уничтожить транспорт", "Введите ID транспорта, который вы хотите уничтожить:", "Ок", "Закрыть");
					case 16:
						ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите модель транспорта, который вы хотите создать:", "Ок", "Закрыть");
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
							SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, "Команда отменена");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ACHAT, DIALOG_STYLE_INPUT, "Админ чат", "Напишите ваше сообщение:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_ASAY, DIALOG_STYLE_INPUT, "Сообщение от администратора", "Напишите ваше сообщение:", "Ок", "Закрыть");
				else admsys_cmd_asay(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_GOTO_VEH:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_VEH, DIALOG_STYLE_INPUT, "Телепортироваться к транспорту", "Введите ID транспорта, к которому вы хотите телепортироваться:", "Ок", "Закрыть");
				else admsys_cmd_gotoveh(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_GOTO_POS:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_GOTO_POS, DIALOG_STYLE_INPUT, "Телепортироваться на координаты", "Введите координаты через пробел, на которые вы хотите телепортироваться:", "Ок", "Закрыть");
				else admsys_cmd_gotopos(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_BAN_IP:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_BAN_IP, DIALOG_STYLE_INPUT, "Блокировка IP-адреса", "Введите IP-адрес, который вы хотите заблокировать:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_UNBAN_IP, DIALOG_STYLE_INPUT, "Разблокировать IP-адрес", "Введите IP-адрес, который вы хотите разблокировать:", "Ок", "Закрыть");
				else admsys_cmd_unbanip(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_WEATHER:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_WEATHER, DIALOG_STYLE_INPUT, "Установить погоду", "Введите ID погоды, которую вы хотите установить:", "Ок", "Закрыть");
				else admsys_cmd_setweather(playerid, inputtext);
			}
			return 1;
		}
		case ADMSYS_DIALOG_SET_TIME:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_SET_TIME, DIALOG_STYLE_INPUT, "Установить время суток", "Введите час, который вы хотите установить:", "Ок", "Закрыть");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите модель транспорта, который вы хотите создать:", "Ок", "Закрыть");
				else
				{
					format(AdmSysInfo[playerid][asInput], ADMSYS_MAX_TAB_INPUT, "%s", inputtext);
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_1, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите цвет 1 для транспорта, который вы хотите создать:", "Ок", "Назад");
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
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_2, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите цвет 2 для транспорта, который вы хотите создать:", "Ок", "Назад");
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите модель транспорта, который вы хотите создать:", "Ок", "Закрыть");
			return 1;
		}
		case ADMSYS_DIALOG_CREATE_VEH_COL_2:
		{
			if(response)
			{
				if(admsys_isnull(inputtext))
					ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_2, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите цвет 2 для транспорта, который вы хотите создать:", "Ок", "Назад");
				else
				{
					static strtmp[32];
					format(strtmp, sizeof strtmp, "%s %s %s", AdmSysInfo[playerid][asInput], AdmSysInfo[playerid][asInput2], inputtext);
					admsys_cmd_veh(playerid, strtmp);
				}
			}
			else ShowPlayerDialog(playerid, ADMSYS_DIALOG_CREATE_VEH_COL_1, DIALOG_STYLE_INPUT, "Создать транспорт", "Введите цвет 1 для транспорта, который вы хотите создать:", "Ок", "Назад");
			return 1;
		}
		case ADMSYS_DIALOG_SUSPECT_LIST:
		{
			if(response && IsPlayerAdminEx(playerid, 3) && 0 <= listitem < sizeof SuspectList)
			{
				if(!StartSpectating(playerid, SuspectList[listitem]))
				{
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок отключился");
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
		static strtmp[572], strtmp2[44], strname[MAX_PLAYER_NAME + 1];
		strtmp[0] = EOS;
		AdmSysInfo[playerid][asTabPanel] = clickedplayerid;
		GetPlayerName(clickedplayerid, strname, sizeof strname);
		format(strtmp2, sizeof strtmp2, "Админ-панель для %s", strname);
		strcat(strtmp, "Показать статистику\nОтветить на report\nВысадить из транспорта");
		if(IsPlayerAdminEx(playerid, 2)) strcat(strtmp, "\nВойти в режим наблюдения\n\
		Выдать молчанку\nСнять молчанку\nВыдать предупреждение\nВыкинуть с сервера\n\
		Заморозить\nРазморозить\nДать пинка\nТелепортироваться к игроку");
		if(IsPlayerAdminEx(playerid, 3)) strcat(strtmp, "\nТелепортировать к себе\nЗаблокировать аккаунт\n\
		Проверка на бесконечное здоровье\nТелепортировать на респавн\nСнять предупреждение");
		if(IsPlayerAdminEx(playerid, 4)) strcat(strtmp, "\nУстановить здоровье\nУстановить броню\nУстановить деньги\n\
		Выдать деньги\nУстановить очки (уровень)\nУстановить скин\nУстановить интерьер\nУстановить виртуальный мир\nВыдать оружие");
		if(IsPlayerAdminEx(playerid, 5)) strcat(strtmp, "\nТихая блокировка\nТихий кик");
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_TAB_PANEL, DIALOG_STYLE_LIST, strtmp2, strtmp, "Ок", "Закрыть");
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
				SendClientMessage(i, ADMSYS_DEFAULT_COLOR, "Время молчанки истекло");
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
			static strtmp[188];
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
				format(strtmp, sizeof strtmp, "До:\t%.1f здоровья, %.1f брони\nПосле:\t%.1f здоровья, %.1f брони\nЗдоровье и броня не уменьшились\n\nВозможно, игрок использует GodMode.",
				AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR], nowhp, nowar);
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_GMTEST, DIALOG_STYLE_MSGBOX, "Проверка на GodMode", strtmp, "Закрыть", "");
			}
			else
			{
				format(strtmp, sizeof strtmp, "До:\t%.1f здоровья, %.1f брони\nПосле:\t%.1f здоровья, %.1f брони\n\
				Здоровье уменьшилось на:\t%.1f\nБроня уменьшилась на:\t%.1f\n\nGodMode не обнаружено.\nЗдоровье и броня восстановлены.",
				AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestHP], AdmSysInfo[AdmSysInfo[playerid][asGmTestID]][asGmTestAR], nowhp, nowar, hpdiff, ardiff);
				ShowPlayerDialog(playerid, ADMSYS_DIALOG_GMTEST, DIALOG_STYLE_MSGBOX, "Проверка на GodMode", strtmp, "Закрыть", "");
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
		format(strtmp, sizeof strtmp, "Вы заглушены. До конца молчанки осталось %d минут %d секунд",
		floatround(AdmSysInfo[playerid][asMuteTime] / 60, floatround_tozero), AdmSysInfo[playerid][asMuteTime] % 60);
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
	}
	if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /report [текст]");
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /achat [текст]");
		static strtmp[145], strname[MAX_PLAYER_NAME + 1];
		strtmp = "[Админ чат] ";
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
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_AHELP_LVL_1, DIALOG_STYLE_MSGBOX, "Помощь по админ командам", AdmSys1LvlCmdsStr, "Далее", "Закрыть");
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
			if(!admsys_IsNumeric(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /showstats [id]");
			params[0] = strval(params);
			if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		}
		new Float:ghealth, Float:garmour;
		static strtmp[40], strtmp2[200], strname[MAX_PLAYER_NAME + 1], gip[16];
		GetPlayerName(params[0], strname, sizeof strname);
		GetPlayerHealth(params[0], ghealth);
		GetPlayerArmour(params[0], garmour);
		GetPlayerIp(params[0], gip, sizeof gip);
		format(strtmp, sizeof strtmp, "Информация о %s", strname);
		format(strtmp2, sizeof strtmp2, "Здоровье: %.1f\nБроня: %.1f\nДеньги: %d\nИнтерьер: %d\nВиртуальный мир: %d\nУровень розыска: %d\nIP-адрес: %s\nPing: %d\nОружие: %d\nПатроны: %d\nScore: %d\nСкин: %d",
		ghealth, garmour, GetPlayerMoney(params[0]), GetPlayerInterior(params[0]), GetPlayerVirtualWorld(params[0]), GetPlayerWantedLevel(params[0]), gip, GetPlayerPing(params[0]),
		GetPlayerWeapon(params[0]), GetPlayerAmmo(params[0]), GetPlayerScore(params[0]), GetPlayerSkin(params[0]));
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_STATS, DIALOG_STYLE_MSGBOX, strtmp, strtmp2, "Ок", "");
	}
	return 1;
}

CMD:answer(playerid, const params[]) return admsys_cmd_answer(playerid, params);
admsys_cmd_answer(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /answer [id] [текст]");
		new pos;
		static strtmp[145];
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /answer [id] [текст]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /answer [id] [текст]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "[Ответ на report %s] %s: %s", strname2, strname, params[pos]);
		SendMessageToAdmins(1, ADMSYS_REPORT_COLOR, strtmp);
		if(!IsPlayerAdminEx(giveid))
		{
			strtmp = "[Ответ на report]: ";
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
		static strtmp[476];
		strtmp[0] = EOS;
		strcat(strtmp, "Админ чат\nПомощь по админ командам\nСписок администраторов онлайн");
		if(IsPlayerAdminEx(playerid, 2)) strcat(strtmp, "\nТелепортировать транспорт на респавн\n\
		Сообщение в формате: 'Администратор: [текст]'");
		if(IsPlayerAdminEx(playerid, 3)) strcat(strtmp, "\nСписок подозреваемых игроков\n\
		Телепортироваться к транспорту\nТелепортироваться на координаты\nБлокировка IP-адреса\nОчистка чата");
		if(IsPlayerAdminEx(playerid, 4)) strcat(strtmp, "\nОтремонтировать транспорт\nРазблокировать IP-адрес");
		if(IsPlayerAdminEx(playerid, 5)) strcat(strtmp, "\nТелепортировать всех к себе\nУстановить погоду\n\
		Установить время суток\nУничтожить транспорт\nСоздать транспорт");
		strcat(strtmp, "\nОтменить последнюю команду");
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_APANEL, DIALOG_STYLE_LIST, "Админ-панель", strtmp, "Ок", "Закрыть");
	}
	return 1;
}

CMD:admins(playerid, const params[]) return admsys_cmd_admins(playerid, params);
admsys_cmd_admins(playerid, const params[])
{
	#pragma unused params
	if(IsPlayerAdminEx(playerid))
	{
		static strtmp[306];
		strtmp[0] = EOS;
		static strtmp2[61], strtmp3[MAX_PLAYER_NAME + 1];
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			if(IsPlayerAdminEx(i))
			{
				GetPlayerName(i, strtmp3, sizeof strtmp3);
				format(strtmp2, sizeof strtmp2, "Администратор %s[%d] [Уровень %d]\n", strtmp3, i, GetPlayerAdminLevel(i));
				strcat(strtmp, strtmp2);
			}
		}
		if(strtmp[0] == '\0') strtmp = "В данный момент нет администраторов онлайн";
		ShowPlayerDialog(playerid, ADMSYS_DIALOG_ADMINS, DIALOG_STYLE_MSGBOX, "Администраторы онлайн", strtmp, "Ок", "");
	}
	return 1;
}

CMD:eject(playerid, const params[]) return admsys_cmd_eject(playerid, params);
admsys_cmd_eject(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid))
	{
		new strtmp[67];
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
					strtmp = "Используйте: /eject [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(!IsPlayerInAnyVehicle(giveid))
				{
					if(i == 1)
					{
						if(giveid == playerid) strtmp = "Вы не в транспорте";
						else strtmp = "Игрок не в транспорте";
					}
					else format(strtmp, sizeof strtmp, "Игрок %d не в транспорте", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					RemovePlayerFromVehicle(giveid);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Вы высадили %s[%d] из транспорта", strname2, giveid);
					SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
					format(strtmp, sizeof strtmp, "Администратор %s высадил вас из транспорта", strname);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /spec [id]");
		if(!strcmp(params, "off", true)) return admsys_cmd_specoff(playerid, "\1");
		if(!strcmp(params, "update", true)) return admsys_cmd_specupdate(playerid, "\1");
		if(!admsys_IsNumeric(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /spec [id]");
		params[0] = strval(params);
		if(!StartSpectating(playerid, params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
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
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не в транспорте");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /spawnveh [id транспорта]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Транспортное средство не найдено");
		}
		static strtmp[28];
		SetVehicleToRespawn(params[0]);
		format(strtmp, sizeof strtmp, "Транспорт id %d заспавнен", params[0]);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /mute [id] [время] [причина]");
		static strtmp[145];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /mute [id] [время] [причина]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(AdmSysInfo[giveid][asMuteTime] > 0) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок уже заглушен");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете применить это действие к администратору");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /mute [id] [время] [причина]");
		new gtime = strval(strtmp);
		if(!(1 <= gtime <= 60)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Время должно быть от 1 до 60 минут");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /mute [id] [время] [причина]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		AdmSysInfo[giveid][asMuteTime] = gtime * 60;
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Администратор %s выдал молчанку игроку %s[%d] на %d минут. Причина: %s", strname, strname2, giveid, gtime, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Администратор %s выдал вам молчанку на %d минут. Причина: %s", strname, gtime, params[pos]);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:unmute(playerid, const params[]) return admsys_cmd_unmute(playerid, params);
admsys_cmd_unmute(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 2))
	{
		new strtmp[96];
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
					strtmp = "Используйте: /unmute [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(AdmSysInfo[giveid][asMuteTime] < 1)
				{
					if(i == 1) strtmp = "Игрок не заглушен";
					else format(strtmp, sizeof strtmp, "Игрок %d не заглушен", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					AdmSysInfo[giveid][asMuteTime] = 0;
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Администратор %s снял молчанку с игрока %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Администратор %s снял с вас молчанку", strname);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /asay [текст]");
		static strtmp[145], strname[MAX_PLAYER_NAME + 1];
		strtmp = "Администратор ";
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /warn [id] [причина]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /warn [id] [причина]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете применить это действие к администратору");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /warn [id] [причина]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		AdmSysInfo[giveid][asWarns]++;
		CallRemoteFunction("OnPlayerWarn", "iii", giveid, playerid, AdmSysInfo[giveid][asWarns]);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Администратор %s выдал предупреждение игроку %s[%d]. Причина: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Администратор %s выдал вам предупреждение. Причина: %s", strname, params[pos]);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /kick [id] [причина]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /kick [id] [причина]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете применить это действие к администратору");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /kick [id] [причина]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		CallRemoteFunction("OnPlayerKick", "iii", giveid, playerid, false);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Администратор %s кикнул игрока %s[%d]. Причина: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Администратор %s кикнул вас. Причина: %s", strname, params[pos]);
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
					strtmp = "Используйте: /freeze [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					TogglePlayerControllable(giveid, 0);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Администратор %s заморозил игрока %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Администратор %s заморозил вас", strname);
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
		new strtmp[91];
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
					strtmp = "Используйте: /unfreeze [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					TogglePlayerControllable(giveid, 1);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Администратор %s разморозил игрока %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Администратор %s разморозил вас", strname);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /slap [id] [причина]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /slap [id] [причина]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете применить это действие к администратору");
		if(IsPlayerSpectating(giveid))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок в режиме наблюдения");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /slap [id] [причина]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(giveid, pX, pY, pZ);
		SetPlayerPos(giveid, pX, pY, pZ + 8.0);
		PlayerPlaySound(giveid, 1130, 0.0, 0.0, 0.0);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Администратор %s подкинул игрока %s[%d]. Причина: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(2, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Администратор %s подкинул вас. Причина: %s", strname, params[pos]);
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
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы в режиме наблюдения");
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /goto [id]");
		params[0] = strval(params);
		if(params[0] == playerid) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Нельзя указывать свой id");
		if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		static strtmp[55], strname[MAX_PLAYER_NAME + 1];
		new Float:pX, Float:pY, Float:pZ;
		GetPlayerPos(params[0], pX, pY, pZ);
		SetPlayerPos(playerid, pX + 1.0, pY + 1.0, pZ);
		SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
		GetPlayerName(params[0], strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы телепортировались к %s[%d]", strname, params[0]);
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
		if(c) ShowPlayerDialog(playerid, ADMSYS_DIALOG_SUSPECT_LIST, DIALOG_STYLE_LIST, "Ожидают проверки", strtmp, "Ок", "Закрыть");
		else SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, "Список пуст");
	}
	return 1;
}

CMD:gethere(playerid, const params[]) return admsys_cmd_gethere(playerid, params);
CMD:get(playerid, const params[]) return admsys_cmd_gethere(playerid, params);
admsys_cmd_gethere(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gethere [id]");
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
					strtmp = "Используйте: /gethere [id]";
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
				if(giveid == playerid) SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Нельзя указывать свой id");
				else if(!IsPlayerConnected(giveid))
				{
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					SetPlayerPos(giveid, pX, pY, pZ);
					SetPlayerVirtualWorld(giveid, vw);
					SetPlayerInterior(giveid, interior);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Вы телепортировали %s[%d] к себе", strname2, giveid);
					SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
					format(strtmp, sizeof strtmp, "Администратор %s телепортировал вас к себе", strname);
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
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы в режиме наблюдения");
		if(admsys_isnull(params) || !admsys_IsNumeric(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gotoveh [id транспорта]");
		params[0] = strval(params);
		if(GetVehicleModel(params[0]) <= 0) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Транспорт не найден");
		static strtmp[54];
		new Float:vX, Float:vY, Float:vZ;
		GetVehiclePos(params[0], vX, vY, vZ);
		SetPlayerPos(playerid, vX, vY, vZ + 2.5);
		SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(params[0]));
		format(strtmp, sizeof strtmp, "Вы телепортировались к транспорту id %d", params[0]);
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
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы в режиме наблюдения");
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gotopos [x] [y] [z]");
		static strtmp[74];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gotopos [x] [y] [z]");
		new Float:cX = floatstr(strtmp);
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gotopos [x] [y] [z]");
		new Float:cY = floatstr(strtmp);
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumericEx(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gotopos [x] [y] [z]");
		new Float:cZ = floatstr(strtmp);
		SetPlayerPos(playerid, cX, cY, cZ);
		format(strtmp, sizeof strtmp, "Вы телепортированы на координаты %.4f, %.4f, %.4f", cX, cY, cZ);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
	}
	return 1;
}

CMD:ban(playerid, const params[]) return admsys_cmd_ban(playerid, params);
admsys_cmd_ban(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 3))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /ban [id] [причина]");
		static strtmp[145];
		new pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /ban [id] [причина]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(GetPlayerAdminLevel(playerid) <= GetPlayerAdminLevel(giveid) && playerid != giveid)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете применить это действие к администратору");
		while(params[pos] == ' ') pos++;
		if(params[pos] == '\0') return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /ban [id] [причина]");
		static strname[MAX_PLAYER_NAME + 1], strname2[MAX_PLAYER_NAME + 1];
		CallRemoteFunction("OnPlayerBan", "iii", giveid, playerid, false);
		GetPlayerName(playerid, strname, sizeof strname);
		GetPlayerName(giveid, strname2, sizeof strname2);
		format(strtmp, sizeof strtmp, "Администратор %s забанил игрока %s[%d]. Причина: %s", strname, strname2, giveid, params[pos]);
		#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
			SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
		#else
			SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
		#endif
		format(strtmp, sizeof strtmp, "Администратор %s забанил вас. Причина: %s", strname, params[pos]);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /gmtest [id]");
		params[0] = strval(params);
		if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		if(AdmSysInfo[playerid][asGmTestID] != INVALID_PLAYER_ID)
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "В данный момент вы уже проверяете кого-то на GodMode");
		if(AdmSysInfo[params[0]][asGmTest])
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "В данный момент игрок уже проверяется на GodMode");
		if(!AdmSysInfo[params[0]][asIsSpawned])
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не заспавнен");
		if(IsPlayerSpectating(params[0]))
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок в режиме наблюдения");
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
		new strtmp[96];
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
					strtmp = "Используйте: /spawn [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					if(IsPlayerSpectating(giveid)) TogglePlayerSpectating(giveid, 0);
					else SpawnPlayer(giveid);
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Администратор %s заспавнил игрока %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Администратор %s заспавнил вас", strname);
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
		new strtmp[102];
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
					strtmp = "Используйте: /unwarn [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else if(AdmSysInfo[giveid][asWarns] < 1)
				{
					if(i == 1) strtmp = "Игрок не имеет предупреждений";
					else format(strtmp, sizeof strtmp, "Игрок %d не имеет предупреждений", i);
					SendClientMessage(playerid, ADMSYS_ERROR_COLOR, strtmp);
				}
				else
				{
					AdmSysInfo[giveid][asWarns]--;
					GetPlayerName(giveid, strname2, sizeof strname2);
					format(strtmp, sizeof strtmp, "Администратор %s снял предупреждение с игрока %s[%d]", strname, strname2, giveid);
					#if ADMSYS_SEND_ACTION_MSGS_TO_ALL
						SendClientMessageToAll(ADMSYS_ADM_ACTION_COLOR, strtmp);
					#else
						SendMessageToAdmins(3, ADMSYS_ADM_ACTION_COLOR, strtmp);
					#endif
					format(strtmp, sizeof strtmp, "Администратор %s снял с вас предупреждение", strname);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /banip [IP]");
		for(new i, c, j = strlen(params); i < j; i++)
		{
			switch(params[i])
			{
				case '*':
				{
					if(c < 2) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP-адрес введён некорректно");
				}
				case '.': c++;
				case '0'..'9':{}
				default: return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP-адрес введён некорректно");
			}
		}
		static strtmp[75], strname[MAX_PLAYER_NAME + 1];
		format(strtmp, sizeof strtmp, "banip %s", params);
		SendRconCommand(strtmp);
		SendRconCommand("reloadbans");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s заблокировал IP %s", strname, params);
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
		static strtmp[53], strname[MAX_PLAYER_NAME + 1];
		for(new i = 30; i >= 0; --i) SendClientMessageToAll(-1, " ");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s очистил чат", strname);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /sethealth [id] [здоровье]");
		static strtmp[72];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /sethealth [id] [здоровье]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /sethealth [id] [здоровье]");
		static strname[MAX_PLAYER_NAME + 1];
		new Float:ghealth = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 1;
		GetPlayerHealth(giveid, AdmSysInfo[playerid][asLastFloatData]);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerHealth(giveid, ghealth);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] здоровье на %.1f", strname, giveid, ghealth);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам здоровье на %.1f", strname, ghealth);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setarmour [id] [броня]");
		static strtmp[69];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setarmour [id] [броня]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setarmour [id] [броня]");
		static strname[MAX_PLAYER_NAME + 1];
		new Float:garmour = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 2;
		GetPlayerArmour(giveid, AdmSysInfo[playerid][asLastFloatData]);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerArmour(giveid, garmour);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] броню на %.1f", strname, giveid, garmour);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам броню на %.1f", strname, garmour);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setmoney(playerid, const params[]) return admsys_cmd_setmoney(playerid, params);
admsys_cmd_setmoney(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setmoney [id] [сумма]");
		static strtmp[75];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setmoney [id] [сумма]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setmoney [id] [сумма]");
		static strname[MAX_PLAYER_NAME + 1];
		new gmoney = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 3;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerMoney(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		ResetPlayerMoney(giveid);
		GivePlayerMoney(giveid, gmoney);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] сумму денег $%d", strname, giveid, gmoney);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам сумму денег $%d", strname, gmoney);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:givemoney(playerid, const params[]) return admsys_cmd_givemoney(playerid, params);
admsys_cmd_givemoney(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /givemoney [id] [сумма]");
		static strtmp[72];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /givemoney [id] [сумма]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /givemoney [id] [сумма]");
		static strname[MAX_PLAYER_NAME + 1];
		new gmoney = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 4;
		AdmSysInfo[playerid][asLastIntData][0] = gmoney;
		AdmSysInfo[playerid][asLastActionID] = giveid;
		GivePlayerMoney(giveid, gmoney);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы выдали %s[%d] сумму денег $%d", strname, giveid, gmoney);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s выдал вам сумму денег $%d", strname, gmoney);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setscore(playerid, const params[]) return admsys_cmd_setscore(playerid, params);
admsys_cmd_setscore(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setscore [id] [очки]");
		static strtmp[78];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setscore [id] [очки]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setscore [id] [очки]");
		static strname[MAX_PLAYER_NAME + 1];
		new gscore = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 5;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerScore(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerScore(giveid, gscore);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] количество очков (уровень) на %d", strname, giveid, gscore);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам %d очков (уровень)", strname, gscore);
		SendClientMessage(giveid, ADMSYS_ADM_ACTION_COLOR, strtmp);
	}
	return 1;
}

CMD:setskin(playerid, const params[]) return admsys_cmd_setskin(playerid, params);
admsys_cmd_setskin(playerid, const params[])
{
	if(IsPlayerAdminEx(playerid, 4))
	{
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setskin [id] [скин]");
		static strtmp[60];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setskin [id] [скин]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setskin [id] [скин]");
		new skinid = strval(strtmp);
		if(!(0 <= skinid <= 311)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "ID скина должен быть от 0 до 311");
		static strname[MAX_PLAYER_NAME + 1];
		AdmSysInfo[playerid][asLastAction] = 6;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerSkin(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerSkin(giveid, skinid);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы изменили скин %s[%d] на %d", strname, giveid, skinid);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s изменил ваш скин на %d", strname, skinid);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setint [id] [интерьер]");
		static strtmp[68];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setint [id] [интерьер]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setint [id] [интерьер]");
		static strname[MAX_PLAYER_NAME + 1];
		new gint = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 7;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerInterior(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerInterior(giveid, gint);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] интерьер %d", strname, giveid, gint);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам интерьер %d", strname, gint);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setvw [id] [виртуальный мир]");
		static strtmp[82];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setvw [id] [виртуальный мир]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setvw [id] [виртуальный мир]");
		static strname[MAX_PLAYER_NAME + 1];
		new gvw = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 8;
		AdmSysInfo[playerid][asLastIntData][0] = GetPlayerVirtualWorld(giveid);
		AdmSysInfo[playerid][asLastActionID] = giveid;
		SetPlayerVirtualWorld(giveid, gvw);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы установили %s[%d] виртуальный мир %d", strname, giveid, gvw);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s установил вам виртуальный мир %d", strname, gvw);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /giveweapon [id] [оружие] [патроны]");
		static strtmp[80];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /giveweapon [id] [оружие] [патроны]");
		new giveid = strval(strtmp);
		if(!IsPlayerConnected(giveid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не найден");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /giveweapon [id] [оружие] [патроны]");
		new gweapon = strval(strtmp);
		if(!(0 <= gweapon <= 46)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "ID оружия должен быть от 0 до 46");
		while(params[pos] == ' ') pos++;
		oldpos = pos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, oldpos, pos);
		if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /giveweapon [id] [оружие] [патроны]");
		static strname[MAX_PLAYER_NAME + 1];
		new gammo = strval(strtmp);
		AdmSysInfo[playerid][asLastAction] = 9;
		AdmSysInfo[playerid][asLastIntData][0] = gweapon;
		AdmSysInfo[playerid][asLastIntData][1] = gammo;
		AdmSysInfo[playerid][asLastActionID] = giveid;
		GivePlayerWeapon(giveid, gweapon, gammo);
		GetPlayerName(giveid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Вы выдали %s[%d] оружие %d с %d патронами", strname, giveid, gweapon, gammo);
		SendClientMessage(playerid, ADMSYS_DEFAULT_COLOR, strtmp);
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s выдал вам оружие %d с %d патронами", strname, gweapon, gammo);
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
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не в транспорте");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /repairveh [id транспорта]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Транспортное средство не найдено");
		}
		static strtmp[33];
		RepairVehicle(params[0]);
		format(strtmp, sizeof strtmp, "Транспорт id %d отремонтирован", params[0]);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /unbanip [IP]");
		for(new i, j = strlen(params); i < j; i++)
		{
			switch(params[i])
			{
				case '*', '.', '0'..'9':{}
				default: return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "IP-адрес введён некорректно");
			}
		}
		static strtmp[76], strname[MAX_PLAYER_NAME + 1];
		format(strtmp, sizeof strtmp, "unbanip %s", params);
		SendRconCommand(strtmp);
		SendRconCommand("reloadbans");
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s разблокировал IP %s", strname, params);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /setweather [погода]");
		params[0] = strval(params);
		if(!(0 <= params[0] <= 20)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "ID погоды должен быть от 0 до 20");
		SetWeather(params[0]);
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			SetPlayerWeather(i, params[0]);
		}
		static strtmp[61], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s изменил погоду на %d", strname, params[0]);
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
		static strtmp[68], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s телепортировал всех к себе", strname);
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
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /settime [час]");
		params[0] = strval(params);
		if(!(0 <= params[0] <= 23)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Час должен быть от 0 до 23");
		SetWorldTime(params[0]);
		#if defined foreach
		foreach(new i : Player)
		#else
		for(new i = GetPlayerPoolSize(); i >= 0; --i)
		#endif
		{
			SetPlayerTime(i, params[0], 0);
		}
		static strtmp[67], strname[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, strname, sizeof strname);
		format(strtmp, sizeof strtmp, "Администратор %s изменил время на %d часов", strname, params[0]);
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
			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не в транспорте");
			params[0] = GetPlayerVehicleID(playerid);
		}
		else
		{
			if(!admsys_IsNumeric(params))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /destroyveh [id транспорта]");
			params[0] = strval(params);
			if(GetVehicleModel(params[0]) <= 0)
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Транспортное средство не найдено");
		}
		static strtmp[28];
		DestroyVehicle(params[0]);
		format(strtmp, sizeof strtmp, "Транспорт id %d уничтожен", params[0]);
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
			return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы в режиме наблюдения");
		if(admsys_isnull(params))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /veh [id транспорта] [цвет 1] [цвет 2]");
		static strtmp[48];
		new pos, oldpos;
		while(params[pos] > ' ') pos++;
		strmid(strtmp, params, 0, pos);
		if(!admsys_IsNumeric(strtmp))
			return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /veh [id транспорта] [цвет 1] [цвет 2]");
		new gveh = strval(strtmp);
		if(!(400 <= gveh <= 611)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "ID транспорта должен быть от 400 до 611");
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
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /veh [id транспорта] [цвет 1] [цвет 2]");
			gcolor1 = strval(strtmp);
			if(!(0 <= gcolor1 <= 255))
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Цвет 1 должен быть от 0 до 255");
			while(params[pos] == ' ') pos++;
			oldpos = pos;
			while(params[pos] > ' ') pos++;
			strmid(strtmp, params, oldpos, pos);
			if(params[oldpos] == '\0' || !admsys_IsNumeric(strtmp))
				return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /veh [id транспорта] [цвет 1] [цвет 2]");
			gcolor2 = strval(strtmp);
			if(!(0 <= gcolor2 <= 255))
				return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Цвет 2 должен быть от 0 до 255");
		}
		new vid, Float:pX, Float:pY, Float:pZ, Float:pAngle;
		GetPlayerPos(playerid, pX, pY, pZ);
		GetPlayerFacingAngle(playerid, pAngle);
		vid = CreateVehicle(gveh, pX, pY, pZ, pAngle, gcolor1, gcolor2, -1);
		SetVehicleVirtualWorld(vid, GetPlayerVirtualWorld(playerid));
		LinkVehicleToInterior(vid, GetPlayerInterior(playerid));
		PutPlayerInVehicle(playerid, vid, 0);
		format(strtmp, sizeof strtmp, "Транспорт id %d с цветами %d и %d заспавнен", vid, gcolor1, gcolor2);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /skick [id]");
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
					strtmp = "Используйте: /skick [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
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
		if(admsys_isnull(params)) return SendClientMessage(playerid, ADMSYS_CMD_HELPER_COLOR, "Используйте: /sban [id]");
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
					strtmp = "Используйте: /sban [id]";
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
					if(i == 1) strtmp = "Игрок не найден";
					else format(strtmp, sizeof strtmp, "Игрок %d не найден", i);
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
	if(playerid == specid) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не можете следить за самим собой");
	if(IsPlayerSpectating(specid)) return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок в режиме наблюдения");
	if(AdmSysInfo[playerid][asSpecID] == specid) return UpdateSpectating(playerid);
	if(!AdmSysInfo[specid][asIsSpawned] && !AdmSysInfo[specid][asIsDead])
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок не заспавнен");
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
	if(AdmSysInfo[specid][asIsDead]) SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Игрок умер");
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
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не в режиме наблюдения");
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
		return SendClientMessage(playerid, ADMSYS_ERROR_COLOR, "Вы не в режиме наблюдения");
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
