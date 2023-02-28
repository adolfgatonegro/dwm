/* See LICENSE file for copyright and license details. */

/* for XF86 Media Keys */
#include <X11/XF86keysym.h>

/* constants */
#define TERM "st"
#define TERMCLASS "st"
#define BROWSER "firefox"

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
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';



/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
/* static int fakefsindicatortype           = INDICATOR_PLUS; */
/* static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE; */
static const char *fonts[]               = { "monospace:size=9" };
static const char dmenufont[]            = "monospace:size=9";

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

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
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

const char *spcmd1[] = {TERM, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERM, "-n", "spmusic", "-g", "120x34", "-e", "cmus", NULL };
const char *spcmd3[] = {TERM, "-n", "spsysmon", "-g", "120x34", "-e", "btop", NULL };
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
	RULE(.class = "Gimp", .tags = 1 << 6)
	RULE(.class = "firefox", .tags = 1 << 0)
	RULE(.class = "discord", .tags = 1 << 3)
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
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,            click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_fancybar,           draw_fancybar,          click_fancybar,          NULL,                    "fancybar" },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "|M|",      centeredmaster },
	{ "[D]",      deck },
	{ "HHH",      grid },
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



static const Key keys[] = {
	/* modifier                     key            function                argument */
	/* { MODKEY,                       XK_b,          togglebar,              {0} }, */
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },/*focus down stack*/
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },/*focus up stack*/
	/* { MODKEY|ControlMask,           XK_j,          rotatestack,            {.i = +1 } },*rotate down*/
	/* { MODKEY|ControlMask,           XK_k,          rotatestack,            {.i = -1 } },*rotate up*/
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },/*inc master num*/
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },/*dec master num*/
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },/*dec master size*/
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },/*inc master size*/
	{ MODKEY|Mod1Mask,              XK_Return,     zoom,                   {0} },/*set focused as master*/
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } }, /* inc all gaps */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } }, /* dec all gaps */
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
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },/*toggle gaps*/
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },/*reset gaps to default*/
	{ MODKEY,                       XK_Tab,        view,                   {0} },/*switch to last tag*/
	{ MODKEY|Mod1Mask,              XK_Tab,        shiftviewclients,       { .i = -1 } },/*shift to prev tag with client*/
	{ MODKEY|Mod1Mask,              XK_backslash,  shiftviewclients,       { .i = +1 } },/*shift to next tag with client*/
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} },/*kill focused client*/
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },/*quit dwm*/
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },/*quit with restartsig*/
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },/*reload xresources*/
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	/* { MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} }, */
	/* { MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} }, */
	/* { MODKEY,                       XK_space,      setlayout,              {0} }, */
	/* { MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} }, */
	/* { MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} },*toggle fake fullscreen*/
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },/*toggle sticky*/
	{ MODKEY,                       XK_0,          view,                   {.ui = ~SPTAGMASK } },/*view all tags*/
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~SPTAGMASK } },/*send to all tags?*/
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },/*focus prev monitor*/
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },/*focus next monitor*/
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },/*tag prev monitor*/
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },/*tag next monitor*/
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },/*cycle layouts back*/
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },/*cycle layouts fwd*/
	/* commands */
	{ MODKEY,                       XK_space,     spawn,       {.v = (const char*[]){ "dmrun", "-p", "run:", NULL } } },
	{ MODKEY,                       XK_Return,    spawn,       {.v = termcmd } },
	/* { Mod1Mask,                     XK_Tab,       spawn,       {.v = (const char*[]){ "dmwin", NULL } } }, */
	{ MODKEY,                       XK_grave,     spawn,       {.v = (const char*[]){ "dmunicode", NULL } } },
	{ MODKEY,                       XK_BackSpace, spawn,       {.v = (const char*[]){ "dmsys", NULL } } },
	{ MODKEY,                       XK_F2,        spawn,       {.v = (const char*[]){ "dmconf", NULL } } },
	{ MODKEY,                       XK_F8,        spawn,       {.v = (const char*[]){ "dmmount", NULL } } },
	{ MODKEY|ShiftMask,             XK_F8,        spawn,       {.v = (const char*[]){ "dmunmount", NULL } } },
	{ MODKEY,                       XK_n,         spawn,       {.v = (const char*[]){ "dmnotes", NULL } } },
	{ MODKEY|ShiftMask,             XK_o,         spawn,       {.v = (const char*[]){ "linkhandler", NULL } } },
	{ MODKEY,                       XK_b,         spawn,       {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,             XK_b,         spawn,       {.v = (const char*[]){ BROWSER, "--private-window", NULL } } },
	{ MODKEY,                       XK_f,         spawn,       {.v = (const char*[]){ TERM, "-e", "lfpv", NULL } } },
	{ MODKEY,                       XK_e,         spawn,       {.v = (const char*[]){ TERM, "-e", "vim", NULL } } },
	{ MODKEY,                       XK_d,         spawn,       {.v = (const char*[]){ "discord", NULL } } },
	{ MODKEY,                       XK_F4,        spawn,       {.v = (const char*[]){ "flameshot", "gui", NULL } } },
	{ MODKEY|ShiftMask,             XK_F4,        spawn,       {.v = (const char*[]){ "flameshot", "launcher", NULL } } },
	/* scratchpads */
	{ 0,                            XK_F12,       togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_m,         togglescratch,  {.ui = 1 } },
	{ 0,                            XK_F10,       togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_c,         togglescratch,  {.ui = 3 } },
	/* xf86 media keys */
	{ 0, XF86XK_AudioPlay,         spawn, {.v = (const char*[]){ "playerctl", "play-pause", NULL } } },
	{ 0, XF86XK_AudioStop,         spawn, {.v = (const char*[]){ "playerctl", "stop", NULL } } },
	{ 0, XF86XK_AudioNext,         spawn, {.v = (const char*[]){ "playerctl", "next", NULL } } },
	{ 0, XF86XK_AudioPrev,         spawn, {.v = (const char*[]){ "playerctl", "previous", NULL } } },
	{ 0, XF86XK_AudioRaiseVolume,  spawn, {.v = (const char*[]){ "volctl", "-i", "2", NULL } } },
	{ 0, XF86XK_AudioLowerVolume,  spawn, {.v = (const char*[]){ "volctl", "-d", "2", NULL } } },
	{ 0, XF86XK_AudioMute,         spawn, {.v = (const char*[]){ "volctl", "-t", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,   spawn, {.v = (const char*[]){ "backlightctl", "-inc", "5", NULL } } },
	{ 0, XF86XK_MonBrightnessDown, spawn, {.v = (const char*[]){ "backlightctl", "-dec", "5", NULL } } },
	{ 0, XF86XK_KbdBrightnessUp,   spawn, {.v = (const char*[]){ "xbacklight", "-ctrl", "smc::kbd_backlight", "-inc", "10", NULL } } },
	{ 0, XF86XK_KbdBrightnessDown, spawn, {.v = (const char*[]){ "xbacklight", "-ctrl", "smc::kbd_backlight", "-dec", "10", NULL } } },
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
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};
