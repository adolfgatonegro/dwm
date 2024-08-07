/* See LICENSE file for copyright and license details. */

/* for XF86 Media Keys */
#include <X11/XF86keysym.h>

/* constants */
#define TERM "st"
#define BROWSER "firefox"
/*#define BROWSER "vivaldi"*/

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 0;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 8;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 8;  /* vert inner gap between windows */
static const unsigned int gappoh         = 8;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 8;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 0;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 25;   /* 0 means derive from font, >= 1 explicit height */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 8;   /* systray spacing */
static const unsigned int systrayiconsize = 16; /* systray icon size in px, in bar_systray.c systray->h = systrayiconsize */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "monospace:size=8" };
/* static const char dmenufont[]            = "monospace:size=9"; */

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#0a0a20";
static char normbordercolor[]            = "#0a0a20";
static char normfloatcolor[]             = "#0a0a20";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#ff00aa";
static char selbordercolor[]             = "#ff00aa";
static char selfloatcolor[]              = "#ff00aa";

static char titlenormfgcolor[]           = "#c1c1d1";
static char titlenormbgcolor[]           = "#0a0a20";
static char titlenormbordercolor[]       = "#0a0a20";
static char titlenormfloatcolor[]        = "#0a0a20";

static char titleselfgcolor[]            = "#c1c1d1";
static char titleselbgcolor[]            = "#262639";
static char titleselbordercolor[]        = "#262639";
static char titleselfloatcolor[]         = "#262639";

static char tagsnormfgcolor[]            = "#c1c1d1";
static char tagsnormbgcolor[]            = "#0a0a20";
static char tagsnormbordercolor[]        = "#0a0a20";
static char tagsnormfloatcolor[]         = "#0a0a20";

static char tagsselfgcolor[]             = "#0a0a20";
static char tagsselbgcolor[]             = "#ff00aa";
static char tagsselbordercolor[]         = "#ff00aa";
static char tagsselfloatcolor[]          = "#ff00aa";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#c1c1d1";
static char urgbgcolor[]                 = "#363649";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";

static const unsigned int baralpha = 0xf9;
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
};

const char *spcmd1[] = {TERM, "-n", "spterm", "-g", "120x40", NULL };
const char *spcmd2[] = {TERM, "-n", "spmusic", "-g", "120x40", "-e", "cmus", NULL };
const char *spcmd3[] = {TERM, "-n", "spsysmon", "-g", "120x40", "-e", "btop", NULL };
const char *spcmd4[] = {TERM, "-n", "spcalc", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",   spcmd1},
	{"spmusic",  spcmd2},
	{"spsysmon", spcmd3},
	{"spcalc",   spcmd4},
};

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
	RULE(.class = "firefox", .tags = 1 << 0)
	RULE(.class = "Vivaldi-stable", .tags = 1 << 0)
	RULE(.class = "KOReader", .tags = 1 << 1)
	RULE(.class = "discord", .tags = 1 << 3)
	RULE(.class = "ONLYOFFICE Desktop Editors", .tags = 1 << 4)
	RULE(.class = "steam", .tags = 1 << 5, .isfloating = 1)
	RULE(.class = "Steam", .tags = 1 << 5, .isfloating = 1)
	RULE(.title = "Steam", .tags = 1 << 5, .isfloating = 1)
	RULE(.class = "heroic", .tags = 1 << 5)
	RULE(.class = "Gimp", .tags = 1 << 6)
	RULE(.class = "Gimp", .title = "Change Foreground Colour", .isfloating = 1)
	RULE(.class = "Gimp", .title = "New Layer", .isfloating = 1)
	RULE(.class = "Gimp", .title = "Quit GIMP", .isfloating = 1)
	RULE(.class = "Inkscape", .tags = 1 << 6)
	RULE(.class = "Darktable", .tags = 1 << 6)
	RULE(.class = "Vmplayer", .tags = 1 << 8)
	RULE(.class = "St" TERMINAL)
	RULE(.title = "Event Tester" NOSWALLOW)
	/* scratchpads */
	RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
	RULE(.instance = "spmusic", .tags = SPTAG(1), .isfloating = 1)
	RULE(.instance = "spsysmon", .tags = SPTAG(2), .isfloating = 1)
	RULE(.instance = "spcalc", .tags = SPTAG(3), .isfloating = 1)
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
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_systray,            draw_systray,           click_systray,           NULL,                    "systray" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
	/* to use fancybar replace `draw_wintitle` with this, and include the fancybar patches
	{ -1,        0,     BAR_ALIGN_NONE,   width_fancybar,           draw_fancybar,          click_fancybar,          NULL,                    "fancybar" },
	*/
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;   /* number of clients in master area */
static const int resizehints    = 0;   /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;   /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "[D]",      deck },
	{ "TTT",      bstack },
	/* { "|M|",      centeredmaster }, */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmrun",
	/* "-m", dmenumon, */
	/* "-fn", dmenufont, */
	/* "-nb", normbgcolor, */
	/* "-nf", normfgcolor, */
	/* "-sb", selbgcolor, */
	/* "-sf", selfgcolor, */
	NULL
};
static const char *termcmd[]  = { "st", NULL };

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"

static const Key keys[] = {
	/* modifier                     key            function                argument */
	/* commands */
	{ MODKEY,                       XK_space,     spawn,       {.v = (const char*[]){ "dmrun", "-p", "run:", NULL } } },
	{ MODKEY,                       XK_Return,    spawn,       {.v = termcmd } },
	{ MODKEY,                       XK_t,         spawn,       {.v = termcmd } },
	{ MODKEY,                       XK_grave,     spawn,       {.v = (const char*[]){ "dmunicode", NULL } } },
	{ MODKEY,                       XK_x,         spawn,       {.v = (const char*[]){ "dmsys", NULL } } },
	{ MODKEY,                       XK_F2,        spawn,       {.v = (const char*[]){ "dmconf", NULL } } },
	{ MODKEY,                       XK_F8,        spawn,       {.v = (const char*[]){ "dmmount", NULL } } },
	{ MODKEY|ShiftMask,             XK_F8,        spawn,       {.v = (const char*[]){ "dmunmount", NULL } } },
	{ Mod1Mask,                     XK_b,         spawn,       {.v = (const char*[]){ "bmks", NULL } } },
	{ Mod1Mask|ShiftMask,           XK_b,         spawn,       {.v = (const char*[]){ "bmks", "add", NULL } } },
	{ Mod1Mask,                     XK_n,         spawn,       {.v = (const char*[]){ "dmnotes", NULL } } },
	{ Mod1Mask,                     XK_o,         spawn,       {.v = (const char*[]){ "linkhandler", NULL } } },
	{ Mod1Mask|ControlMask,         XK_v,         spawn,       {.v = (const char*[]){ "vim-anywhere", NULL } } },
	{ MODKEY,                       XK_F12,       spawn,       {.v = (const char*[]){ "simplescreenrecorder", "--start-hidden", NULL } } },
	/* { MODKEY|ShiftMask,             XK_F12,       spawn,       {.v = (const char*[]){ "dmrecord", "kill", NULL } } }, */
	{ MODKEY|ControlMask,           XK_p,         spawn,       {.v = (const char*[]){ "dmdisplay", NULL } } },
	{ MODKEY,                       XK_b,         spawn,       {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,             XK_b,         spawn,       {.v = (const char*[]){ "dmbrowser", NULL } } },
	{ MODKEY,                       XK_f,         spawn,       {.v = (const char*[]){ TERM, "-e", "lfpv", NULL } } },
	{ MODKEY,                       XK_e,         spawn,       {.v = (const char*[]){ TERM, "-e", "nvim", NULL } } },
	{ MODKEY,                       XK_d,         spawn,       {.v = (const char*[]){ "discord", NULL } } },
	{ MODKEY,                       XK_k,         spawn,       {.v = (const char*[]){ "books", NULL } } },
	{ MODKEY,                       XK_F4,        spawn,       {.v = (const char*[]){ "flameshot", "gui", NULL } } },
	{ MODKEY|ShiftMask,             XK_F4,        spawn,       {.v = (const char*[]){ "flameshot", "launcher", NULL } } },
	/* window management */
	{ MODKEY|ControlMask,           XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {1} },/*restart dwm*/
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {0} },/*kill dwm*/
	/* tag switching */
	{ Mod1Mask,                     XK_Tab,        view,                   {0} },/*switch to last tag*/
	{ MODKEY,                       XK_Tab,        shiftviewclients,       { .i = +1 } },/*shift to prev tag with client*/
	{ MODKEY|ShiftMask,             XK_Tab,        shiftviewclients,       { .i = -1 } },/*shift to next tag with client*/
	{ MODKEY,                       XK_0,          view,                   {.ui = ~SPTAGMASK } },/*view all tags*/
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~SPTAGMASK } },/*send to all tags?*/
	/* window, layout and monitor */
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ Mod1Mask|ShiftMask,           XK_Return,     zoom,                   {0} },
	{ Mod1Mask|ShiftMask,           XK_s,          togglesticky,           {0} },
	{ ControlMask|Mod1Mask,         XK_Return,     togglefullscr,          {0} },
	{ Mod1Mask|ShiftMask,           XK_f,          float_and_center,       {0} },
	{ Mod1Mask,                     XK_i,          incnmaster,             {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_i,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY,                       XK_period,     cyclelayout,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = -1 } },
	{ MODKEY|ControlMask,           XK_comma,      focusmon,               {.i = -2 } },
	{ MODKEY|ControlMask,           XK_period,     focusmon,               {.i = +1 } },
	/* layouts */
	{ Mod1Mask|ControlMask,         XK_t,          setlayout,              {.v = &layouts[0]} },
	{ Mod1Mask|ControlMask,         XK_f,          setlayout,              {.v = &layouts[1]} },
	/* gaps */
	{ MODKEY|ControlMask,           XK_0,          togglegaps,             {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_0,          defaultgaps,            {0} },
	{ MODKEY|ControlMask,           XK_g,          incrgaps,               {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_g,          incrgaps,               {.i = -1 } },
	/* scratchpads */
	{ 0,                            XK_F12,       togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_m,         togglescratch,  {.ui = 1 } },
	{ 0,                            XK_F10,       togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_c,         togglescratch,  {.ui = 3 } },
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
	{ 0, XF86XK_MonBrightnessUp,    spawn, {.v = (const char*[]){ "backlightctl", "-inc", "5", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,  spawn, {.v = (const char*[]){ "backlightctl", "-dec", "5", NULL } } },
	{ 0, XF86XK_KbdBrightnessUp,    spawn, {.v = (const char*[]){ "brightnessctl", "--device=smc::kbd_backlight", "set", "+10%", NULL } } },
	{ 0, XF86XK_KbdBrightnessDown,  spawn, {.v = (const char*[]){ "brightnessctl", "--device=smc::kbd_backlight", "set", "10%-", NULL } } },
	{ 0, XF86XK_PowerOff,           spawn, {.v = (const char*[]){ "dmsys", NULL } } },
	{ 0, XF86XK_Sleep,              spawn, {.v = (const char*[]){ "dmsys", NULL } } },

	/* { MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } }, */
	/* { MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } }, */
	/* { MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } }, */
	/* { MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } }, */
	/* { MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } }, */
	/* { MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },*reload xresources*/
	/* { MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} }, */
	/* { MODKEY,                       XK_space,      setlayout,              {0} }, */
	TAGKEYS(                        XK_1,                                  0)/* mod > switch view*/
	TAGKEYS(                        XK_2,                                  1)/* mod ctrl > make visible*/
	TAGKEYS(                        XK_3,                                  2)/* mod shift > send active to tag*/
	TAGKEYS(                        XK_4,                                  3)/* mod ctrl shift > tag active with*/
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
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,                   Button4,        focusstack,     {.i = -1 } },
	{ ClkLtSymbol,          0,                   Button5,        focusstack,     {.i = +1 } },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,                   Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,                   Button5,        sigstatusbar,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,                   Button4,        shiftviewclients, {.i = -1 } },
	{ ClkTagBar,            0,                   Button5,        shiftviewclients, {.i = +1 } },
};
