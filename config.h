/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx	= 2;
static const unsigned int snap		= 32;
static const char *toggle_float_pos	= "50% 50% 80% 80%";
static int floatposgrid_x			= 5;
static int floatposgrid_y			= 5;

static const unsigned int gappih	= 15;
static const unsigned int gappiv	= 15;
static const unsigned int gappoh	= 15;
static const unsigned int gappov	= 15;
static int smartgaps				= 0;

static const int showbar			= 1;
static const int topbar				= 1;

static const char *fonts[]			= { "Iosevka Nerd Font:size=12",
										"JetBrainsMono Nerd Font:style=ExtraBold:size=10" };
static const char dmenufont[]		= "Iosevka Nerd Font:size=12";

static char normfgcolor[]			= "#bbbbbb";
static char normbgcolor[]			= "#222222";
static char normbordercolor[]		= "#444444";

static char selfgcolor[]			= "#eeeeee";
static char selbgcolor[]			= "#005577";
static char selbordercolor[]		= "#005577";

static char tagsemptyfgcolor[]		= "#444444";
static char tagsemptybgcolor[]		= "#222222";
static char tagsoccfgcolor[]		= "#bbbbbb";
static char tagsoccbgcolor[]		= "#222222";
static char tagsselfgcolor[]		= "#eeeeee";
static char tagsselbgcolor[]		= "#005577";

static char termcol0[]				= "#000000"; /* black   */
static char termcol1[]				= "#ff0000"; /* red     */
static char termcol2[]				= "#33ff00"; /* green   */
static char termcol3[]				= "#ff0099"; /* yellow  */
static char termcol4[]				= "#0066ff"; /* blue    */
static char termcol5[]				= "#cc00ff"; /* magenta */
static char termcol6[]				= "#00ffff"; /* cyan    */
static char termcol7[]				= "#d0d0d0"; /* white   */
static char termcol8[]				= "#808080"; /* black   */
static char termcol9[]				= "#ff0000"; /* red     */
static char termcol10[]				= "#33ff00"; /* green   */
static char termcol11[]				= "#ff0099"; /* yellow  */
static char termcol12[]				= "#0066ff"; /* blue    */
static char termcol13[]				= "#cc00ff"; /* magenta */
static char termcol14[]				= "#00ffff"; /* cyan    */
static char termcol15[]				= "#ffffff"; /* white   */
static char *termcolor[]			= {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};

static char *colors[][3] 	= {
       [SchemeNorm]			= { normfgcolor,		normbgcolor,		normbordercolor },
       [SchemeSel]			= { selfgcolor,			selbgcolor,			selbordercolor },
       [SchemeTagsEmpty]	= { tagsemptyfgcolor,	tagsemptybgcolor,	NULL },
       [SchemeTagsOcc]		= { tagsoccfgcolor,		tagsoccbgcolor,		NULL },
       [SchemeTagsSel]		= { tagsselfgcolor,		tagsselbgcolor,		NULL },
};

static const unsigned int baralpha		= 0xd0;
static const unsigned int borderalpha	= OPAQUE;

static const unsigned int alphas[][3]	= {
    [SchemeNorm]			= { OPAQUE, baralpha, borderalpha },
	[SchemeSel]				= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsEmpty]		= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsOcc]			= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]			= { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "-b", NULL,
	"slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Nwg-look", .isfloating = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
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

#define STATUSBAR "dwmblocks"

/* commands */
static const char *dmenucmd[] 	= { "dmenu_run", "-p", "Run: ", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  	= { "st", "-T", "Terminal", NULL };
static const char *firefoxcmd[]	= { "firefox", NULL };
static const char *volmute[]	= { "pulsemixer", "--toggle-mute", NULL };
static const char *voldown[]	= { "pulsemixer", "--max-volume", "100", "--change-volume", "-5", NULL };
static const char *volup[]		= { "pulsemixer", "--max-volume", "100", "--change-volume", "+5", NULL };
static const char *bldown[]		= { "brightnessctl", "s", "5%-", NULL };
static const char *blup[]		= { "brightnessctl", "s", "+5%", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = firefoxcmd } },
	{ 0,                            XK_F1,     spawn,          {.v = volmute } },
	{ 0,                            XK_F2,     spawn,          {.v = voldown } },
	{ 0,                            XK_F3,     spawn,          {.v = volup } },
	{ 0,                            XK_F5,     spawn,          {.v = bldown } },
	{ 0,                            XK_F6,     spawn,          {.v = blup } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_x,      xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

