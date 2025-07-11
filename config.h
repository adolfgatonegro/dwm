/* See LICENSE file for copyright and license details. */

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }
#define TERM "st"
#define BROWSER "firefox"
/* for XF86 Media Keys */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 0;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 4;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 4;  /* vert inner gap between windows */
static const unsigned int gappoh         = 4;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 4;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 0;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 25;   /* 0 means derive from font, >= 1 explicit height */
static const int vertpad                 = 0;  /* vertical padding of bar */
static const int sidepad                 = 0;  /* horizontal padding of bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 8;   /* systray spacing */
static const unsigned int systrayiconsize = 14;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_NONE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "CozetteVector:size=10" };
/*static const char dmenufont[]            = "Cozette:size=10";*/

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";

static char scratchselfgcolor[]          = "#FFF7D4";
static char scratchselbgcolor[]          = "#77547E";
static char scratchselbordercolor[]      = "#894B9F";
static char scratchselfloatcolor[]       = "#894B9F";

static char scratchnormfgcolor[]         = "#FFF7D4";
static char scratchnormbgcolor[]         = "#664C67";
static char scratchnormbordercolor[]     = "#77547E";
static char scratchnormfloatcolor[]      = "#77547E";

static const unsigned int baralpha = 0xf3;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]     = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]          = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
	[SchemeScratchSel]  = { scratchselfgcolor, scratchselbgcolor, scratchselbordercolor, scratchselfloatcolor },
	[SchemeScratchNorm] = { scratchnormfgcolor, scratchnormbgcolor, scratchnormbordercolor, scratchnormfloatcolor },
};

/*Autostart dwmblocks*/
static const char *const autostart[] = {
	"dwmblocks", NULL,
	/*"sxhkd", NULL, started by xorg instead */
	NULL /* terminate */
};

/*Define scratchpads*/
static const char *scratchpadcmd[] = {"s", TERM, "-n", "spterm", "-g", "110x34", NULL};
static const char *spMusic[] = {"m", TERM, "-n", "spmusic", "-g", "110x34", "-e", "cmus", NULL};
static const char *spSysMon[] = {"b", TERM, "-n", "spsysmon", "-g", "110x34", "-e", "btop", NULL};
static const char *spCalc[] = {"c", TERM, "-n", "spcalc", "-g", "50x15", "-e", "bc", "-lq", NULL};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)

	/*Application rules*/
	RULE(.class = "firefox", .tags = 1 << 0)
	RULE(.class = "LibreWolf", .tags = 1 << 0)
	RULE(.class = "Vivaldi-stable", .tags = 1 << 0)
	/* RULE(.class = "KOReader", .tags = 1 << 1) */
	RULE(.class = "obsidian", .tags = 1 << 2)
	RULE(.class = "discord", .tags = 1 << 3)
	RULE(.class = "vesktop", .tags = 1 << 3)
	RULE(.class = "ONLYOFFICE", .tags = 1 << 4)
	RULE(.class = "steam", .tags = 1 << 5, .isfloating = 1, .iscentered = 1)
	RULE(.title = "Steam", .tags = 1 << 5, .isfloating = 1, .iscentered = 1)
	RULE(.class = "heroic", .tags = 1 << 5)
	RULE(.class = "Gimp", .tags = 1 << 6)
	RULE(.class = "Org.gimp.GIMP.Stable", .tags = 1 << 6)
	RULE(.class = "krita", .tags = 1 << 6)
	RULE(.class = "Inkscape", .tags = 1 << 6)
	RULE(.class = "Darktable", .tags = 1 << 6)
	RULE(.class = "Vmplayer", .tags = 1 << 8)
	RULE(.class = "St" TERMINAL)
	RULE(.title = "Event Tester" NOSWALLOW)

	/*Scratchpad window rules*/
	RULE(.instance = "spterm", .scratchkey = 's', .isfloating = 1, .iscentered = 1)
	RULE(.instance = "spmusic", .scratchkey = 'm', .isfloating = 1, .iscentered = 1)
	RULE(.instance = "spsysmon", .scratchkey = 'b', .isfloating = 1, .iscentered = 1)
	RULE(.instance = "spcalc", .scratchkey = 'c', .isfloating = 1, .iscentered = 1)
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,           draw_status2d,          click_statuscmd,         NULL,                    "status2d" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[D]",      deck },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ "[M]",      monocle },
	/*{ "><>",      NULL },       no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmrun",
	"-p",
	"run:",
	"-m", dmenumon,
	/*dmenu colours are defined in xresources*/
	/*"-fn", dmenufont,*/
	/*"-nb", normbgcolor,*/
	/*"-nf", normfgcolor,*/
	/*"-sb", selbgcolor,*/
	/*"-sf", selfgcolor,*/
	NULL
};
static const char *termcmd[]  = { "st", NULL };

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"

static const Key keys[] = {
	/* modifier                     key            function                argument */

	/*Spawn commands*/
	/*{ MODKEY,                       XK_p,          spawn,                  {.v = dmenucmd } },*/
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },

	/*Navigate stack*/
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },

	/*Move clients in stack*/
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } },

	/*Rotate stack in place*/
	/*{ MODKEY|Mod4Mask,              XK_j,          inplacerotate,          {.i = +2 } }, // same as rotatestack*/
	/*{ MODKEY|Mod4Mask,              XK_k,          inplacerotate,          {.i = -2 } }, // same as reotatestack*/
	{ MODKEY|Mod1Mask,              XK_j,          inplacerotate,          {.i = +1} },
	{ MODKEY|Mod1Mask,              XK_k,          inplacerotate,          {.i = -1} },

	/*Increase/decrease number of masters*/
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,          incnmaster,             {.i = -1 } },

	/*Modify factor of master area*/
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },

	/*Modify factor of client area*/
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} },
	/*Reset factor of focused client*/
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {0} },

	/*Zoom on focused client*/
	{ MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },

	/*Modify gaps*/
	/*{ MODKEY|Mod4Mask,              XK_u,          incrgaps,               {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_0,          togglegaps,             {0} },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },*/

	/*No need to do any of this nonsense*/
	/*{ MODKEY|Mod4Mask,              XK_i,          incrigaps,              {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_o,          incrogaps,              {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_6,          incrihgaps,             {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_7,          incrivgaps,             {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_8,          incrohgaps,             {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },*/
	/*{ MODKEY|Mod4Mask,              XK_9,          incrovgaps,             {.i = +1 } },*/
	/*{ MODKEY|Mod4Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },*/

	/*Shift between tags */
	{ Mod1Mask,                     XK_Tab,        view,                   {0} },
	{ MODKEY|ShiftMask,             XK_Tab,        shiftviewclients,       { .i = -1 } },
	{ MODKEY,                       XK_Tab,        shiftviewclients,       { .i = +1 } },

	/*Kill dwm/client window*/
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {0} },

	/*Reload Xresources*/
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },

	/*Switch to layout*/
	{ MODKEY|ControlMask,           XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_d,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_g,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_m,          setlayout,              {.v = &layouts[4]} },

	/*Cycle layouts*/
	{ MODKEY,                       XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY,                       XK_period,     cyclelayout,            {.i = +1 } },

	/*Scratchpads*/
	{ MODKEY,                       XK_grave,      togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_grave,      setscratch,             {.v = scratchpadcmd } },
	{ MODKEY|ControlMask,           XK_grave,      removescratch,          {.v = scratchpadcmd } },
	{ MODKEY,                     XK_m,          togglescratch,          {.v = spMusic } },
	{ 0,                            XK_F10,        togglescratch,          {.v = spSysMon } },
	{ MODKEY,                     XK_c,          togglescratch,          {.v = spCalc } },

	/*Toggle bar*/
	{ MODKEY,                       XK_b,          togglebar,              {0} },

	/*Toggle window states*/
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_y,          togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },

	/*View all tags*/
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },

	/*Send client to all tags*/
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },

	/*Send client to adjacent monitor*/
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },

	/*Move focus between monitors*/
	{ MODKEY|ControlMask,           XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     focusmon,               {.i = +1 } },

	/* media keys */
	{ 0, XF86XK_AudioPlay,          spawn, SHCMD("playerctl play-pause; pkill -RTMIN+13 dwmblocks") },
	{ 0, XF86XK_AudioStop,          spawn, SHCMD("playerctl stop; pkill -RTMIN+13 dwmblocks") },
	{ 0, XF86XK_AudioNext,          spawn, SHCMD("playerctl next; pkill -RTMIN+13 dwmblocks") },
	{ 0, XF86XK_AudioPrev,          spawn, SHCMD("playerctl previous; pkill -RTMIN+13 dwmblocks") },
	{ ShiftMask, XF86XK_AudioNext,  spawn, {.v = (const char*[]){ "playerctl", "position", "10+", NULL } } },
	{ ShiftMask, XF86XK_AudioPrev,  spawn, {.v = (const char*[]){ "playerctl", "position", "10-", NULL } } },
	{ 0, XF86XK_AudioRaiseVolume,   spawn, SHCMD("volctl -i 2; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,   spawn, SHCMD("volctl -d 2; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioMute,          spawn, SHCMD("volctl -t; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_Display,            spawn, {.v = (const char*[]){ "dmdisplay", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,    spawn, {.v = (const char*[]){ "backlightctl", "-inc", "5", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,  spawn, {.v = (const char*[]){ "backlightctl", "-dec", "5", NULL } } },
	{ 0, XF86XK_KbdBrightnessUp,    spawn, {.v = (const char*[]){ "brightnessctl", "--device=smc::kbd_backlight", "set", "+10%", NULL } } },
	{ 0, XF86XK_KbdBrightnessDown,  spawn, {.v = (const char*[]){ "brightnessctl", "--device=smc::kbd_backlight", "set", "10%-", NULL } } },
	{ 0, XF86XK_PowerOff,           spawn, {.v = (const char*[]){ "dmsys", NULL } } },
	{ 0, XF86XK_Sleep,              spawn, {.v = (const char*[]){ "dmsys", NULL } } },

	/*Tag keys*/
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {

	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button3,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,                   Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,                   Button4,        focusstack,     {.i = -1 } },
	{ ClkLtSymbol,          0,                   Button5,        focusstack,     {.i = +1 } },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,                   Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,                   Button5,        sigstatusbar,   {.i = 5 } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,                   Button4,        shiftviewclients, {.i = -1 } },
	{ ClkTagBar,            0,                   Button5,        shiftviewclients, {.i = +1 } },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static const Signal signals[] = {
	/* signum                    function */
	{ "focusstack",              focusstack },
	{ "setmfact",                setmfact },
	{ "togglebar",               togglebar },
	{ "incnmaster",              incnmaster },
	{ "togglefloating",          togglefloating },
	{ "focusmon",                focusmon },
	{ "inplacerotate",           inplacerotate },
	{ "setcfact",                setcfact },
	{ "tagmon",                  tagmon },
	{ "zoom",                    zoom },
	{ "incrgaps",                incrgaps },
	{ "incrigaps",               incrigaps },
	{ "incrogaps",               incrogaps },
	{ "incrihgaps",              incrihgaps },
	{ "incrivgaps",              incrivgaps },
	{ "incrohgaps",              incrohgaps },
	{ "incrovgaps",              incrovgaps },
	{ "togglegaps",              togglegaps },
	{ "defaultgaps",             defaultgaps },
	{ "setgaps",                 setgapsex },
	{ "view",                    view },
	{ "viewall",                 viewallex },
	{ "viewex",                  viewex },
	{ "toggleview",              toggleview },
	{ "shiftviewclients",        shiftviewclients },
	{ "togglesticky",            togglesticky },
	{ "cyclelayout",             cyclelayout },
	{ "toggleviewex",            toggleviewex },
	{ "tag",                     tag },
	{ "tagall",                  tagallex },
	{ "tagex",                   tagex },
	{ "toggletag",               toggletag },
	{ "toggletagex",             toggletagex },
	{ "togglefullscreen",        togglefullscreen },
	{ "killclient",              killclient },
	{ "xrdb",                    xrdb },
	{ "quit",                    quit },
	{ "setlayout",               setlayout },
	{ "setlayoutex",             setlayoutex },
};

